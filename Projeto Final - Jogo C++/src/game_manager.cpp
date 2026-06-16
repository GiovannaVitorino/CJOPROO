#include "game_manager.hpp"
#include "mode_read_name.hpp"
#include "mode_quiz.hpp"
 
// Registra cada modo jogavel em um mapa de fabricas.
void GameManager::registerModes() {
    modeRegistry["read_name"] = [this]() {
        return std::make_unique<ReadAndName>(*renderer, *audio, *factory);
    };
    modeRegistry["quiz"] = [this]() {
        return std::make_unique<QuizMode>(*renderer, *audio, *factory);
    };
 
    menuOptions = {
        {"read_name", "Ler e nomear notas", "Acerte o nome da nota em destaque."},
        {"quiz", "Quiz de teoria", "Responda perguntas de multipla escolha sobre teoria musical."},
    };
}
 
// Atualiza a tela atual: menu, resultado, pausa ou modo ativo.
void GameManager::update(float dt) {
    if (estado == GameState::MENU) {
        updateMenu();
        return;
    }
 
    if (estado == GameState::RESULT) {
        if (IsKeyPressed(KEY_ENTER)) {
            if (activeMode) {
                totalScore += activeMode->getScore();
            }
            estado = GameState::MENU;
            activeMode.reset();
        }
        return;
    }
 
    if (estado == GameState::PAUSED) {
        updatePause();
        return;
    }
 
    if (estado == GameState::PLAYING && activeMode) {
        if (IsKeyPressed(KEY_ESCAPE)) {
            estado = GameState::PAUSED;
            return;
        }
 
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
            CheckCollisionPointRec(GetMousePosition(), pauseButtonRect())) {
            estado = GameState::PAUSED;
            return;
        }
 
        activeMode->update(dt);
    }
}
 
// Desenha a tela adequada ao estado atual do jogo.
void GameManager::render() const {
    if (estado == GameState::MENU) {
        renderMenu();
    } else if (estado == GameState::RESULT) {
        renderResult();
    } else if (activeMode) {
        activeMode->render();
        if (estado == GameState::PLAYING) {
            renderPauseButton();
        } else if (estado == GameState::PAUSED) {
            renderPauseOverlay();
        }
    }
}
 
// Troca para o modo escolhido e conecta o callback de pontuacao.
void GameManager::switchMode(const std::string& name) {
    auto it = modeRegistry.find(name);
    if (it != modeRegistry.end()) {
        audio->stop();
        // Cria modo com pontuação acumulada
        activeMode = it->second();
        // Precisa acessar diretamente para passar initialScore
        // Como a factory não suporta, vou recrear o modo aqui
        if (name == "read_name") {
            activeMode = std::make_unique<ReadAndName>(*renderer, *audio, *factory, totalScore);
        } else if (name == "quiz") {
            activeMode = std::make_unique<QuizMode>(*renderer, *audio, *factory, totalScore);
        }
        
        estado = GameState::PLAYING;
        // Dispara game over quando pontos ficam negativos
        activeMode->onResult = [this](ModeResult, int, bool ended) {
            if (ended) {
                audio->stop();
                estado = GameState::RESULT;
            }
        };
    }
}
 
// Processa cliques do menu principal e abre a configuracao de clave.
void GameManager::updateMenu() {
    if (claveConfig_) {
        updateClefSettings();
        return;
    }
 
    if (!IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) return;
 
    Vector2 mouse = GetMousePosition();
    if (CheckCollisionPointRec(mouse, settingsButtonRect())) {
        claveConfig_ = true;
        return;
    }
 
    for (int i = 0; i < static_cast<int>(menuOptions.size()); ++i) {
        if (CheckCollisionPointRec(mouse, menuButtonRect(i))) {
            switchMode(menuOptions[i].key);
            return;
        }
    }
}
 
// Processa cliques no modal de configuracao de clave.
void GameManager::updateClefSettings() {
    if (!IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) return;
 
    Vector2 mouse = GetMousePosition();
    if (CheckCollisionPointRec(mouse, clefOptionRect(0))) {
        factory->setClef(ClefType::TREBLE);
        return;
    }
 
    if (CheckCollisionPointRec(mouse, clefOptionRect(1))) {
        factory->setClef(ClefType::BASS);
        return;
    }
 
    if (CheckCollisionPointRec(mouse, clefSettingsContinueRect())) {
        claveConfig_ = false;
    }
}
 
// Processa comandos do overlay de pausa.
void GameManager::updatePause() {
    if (IsKeyPressed(KEY_ESCAPE)) {
        estado = GameState::PLAYING;
        return;
    }
 
    if (!IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) return;
 
    Vector2 mouse = GetMousePosition();
    if (CheckCollisionPointRec(mouse, pauseContinueRect())) {
        estado = GameState::PLAYING;
        return;
    }
 
    if (CheckCollisionPointRec(mouse, pauseMenuRect())) {
        audio->stop();
        if (activeMode) {
            totalScore += activeMode->getScore();
        }
        activeMode.reset();
        estado = GameState::MENU;
    }
}
 
// Renderiza titulo, pontuacao, clave selecionada e botoes de modo.
void GameManager::renderMenu() const {
    DrawText("SheetMasters", 64, 58, 42, DARKBLUE);
    DrawText("Escolha um modo de jogo", 68, 112, 24, DARKGRAY);
    DrawText(TextFormat("Pontuacao total: %d", totalScore), GetScreenWidth() - 260, 66, 22, DARKGRAY);
    DrawText(TextFormat("Recorde: %d acertos", GameMode::bestStreakRecord()), GetScreenWidth() - 260, 94, 20, DARKGRAY);
    const char* clefName = factory->selectedClef() == ClefType::BASS ? "Fa" : "Sol";
    DrawText(TextFormat("Clave: %s", clefName), GetScreenWidth() - 260, 120, 20, DARKGRAY);
    DrawText(TextFormat("Dificuldade: %.1f", factory->difficulty()), GetScreenWidth() - 260, 146, 20, DARKGRAY);
    drawActionButton("Configurar clave", settingsButtonRect(), DARKBLUE);
 
    for (int i = 0; i < static_cast<int>(menuOptions.size()); ++i) {
        drawMenuButton(menuOptions[i], menuButtonRect(i));
    }
 
    if (claveConfig_) {
        renderClefSettings();
    }
}
 
// Renderiza o painel modal que permite escolher clave de Sol ou Fa.
void GameManager::renderClefSettings() const {
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.42f));
 
    Rectangle panel = clefSettingsPanelRect();
    DrawRectangleRec(panel, RAYWHITE);
    DrawRectangleLinesEx(panel, 2.0f, DARKBLUE);
    DrawText("Configuracoes", static_cast<int>(panel.x + 34), static_cast<int>(panel.y + 28), 30, DARKBLUE);
    DrawText("Escolha a clave para jogar", static_cast<int>(panel.x + 36), static_cast<int>(panel.y + 72), 19, DARKGRAY);
 
    const char* labels[] = {"Clave de Sol", "Clave de Fa"};
    ClefType clefs[] = {ClefType::TREBLE, ClefType::BASS};
    Texture2D textures[] = {claveSol, claveFa};
    for (int i = 0; i < 2; ++i) {
        Rectangle rect = clefOptionRect(i);
        bool selected = factory->selectedClef() == clefs[i];
        bool hover = CheckCollisionPointRec(GetMousePosition(), rect);
        Color fill = selected ? Color{224, 237, 229, 255}
                              : hover ? Color{221, 232, 245, 255}
                                      : Color{238, 242, 247, 255};
        DrawRectangleRec(rect, fill);
        DrawRectangleLinesEx(rect, selected ? 3.0f : 2.0f, selected ? DARKGREEN : LIGHTGRAY);
 
        Texture2D texture = textures[i];
        if (texture.id != 0) {
            float imageHeight = rect.height - 34.0f;
            float imageWidth = imageHeight * static_cast<float>(texture.width) / static_cast<float>(texture.height);
            Rectangle source{0.0f, 0.0f, static_cast<float>(texture.width), static_cast<float>(texture.height)};
            Rectangle dest{rect.x + 20.0f, rect.y + 17.0f, imageWidth, imageHeight};
            DrawTexturePro(texture, source, dest, {0.0f, 0.0f}, 0.0f, BLACK);
        }
 
        DrawText(labels[i], static_cast<int>(rect.x + 86), static_cast<int>(rect.y + 32), 22, DARKBLUE);
    }
 
    drawActionButton("Continuar", clefSettingsContinueRect(), DARKGREEN);
}
 
// Desenha o botao de pausa exibido durante a partida.
void GameManager::renderPauseButton() const {
    drawActionButton("Pausar", pauseButtonRect(), DARKBLUE);
}
 
// Desenha o overlay que aparece quando o jogo esta pausado.
void GameManager::renderPauseOverlay() const {
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.42f));
 
    const float width = 420.0f;
    const float height = 250.0f;
    const float x = (GetScreenWidth() - width) / 2.0f;
    const float y = (GetScreenHeight() - height) / 2.0f;
    Rectangle panel{x, y, width, height};
 
    DrawRectangleRec(panel, RAYWHITE);
    DrawRectangleLinesEx(panel, 2.0f, DARKBLUE);
    DrawText("Jogo pausado", static_cast<int>(x + 40), static_cast<int>(y + 34), 30, DARKBLUE);
    DrawText("Escolha uma opcao", static_cast<int>(x + 42), static_cast<int>(y + 78), 18, DARKGRAY);
 
    drawActionButton("Continuar", pauseContinueRect(), DARKGREEN);
    drawActionButton("Voltar ao menu", pauseMenuRect(), MAROON);
}
 
// Desenha a tela de resultado e instrui o retorno ao menu.
void GameManager::renderResult() const {
    DrawText("Resultado registrado", 64, 72, 34, DARKBLUE);
    DrawText(TextFormat("Pontuacao total: %d", totalScore), 68, 126, 24, DARKGRAY);
    DrawText("Pressione Enter para voltar ao menu", 68, 178, 22, MAROON);
}
 
// Calcula a area de um botao de modo no menu.
Rectangle GameManager::menuButtonRect(int index) const {
    const float width = 520.0f;
    const float height = 86.0f;
    const float gap = 18.0f;
    const float x = (GetScreenWidth() - width) / 2.0f;
    const float y = 290.0f + index * (height + gap);
    return {x, y, width, height};
}
 
// Calcula a area do botao de configuracao de clave.
Rectangle GameManager::settingsButtonRect() const {
    return {static_cast<float>(GetScreenWidth() - 260), 174.0f, 198.0f, 38.0f};
}
 
// Calcula a area do painel de configuracoes.
Rectangle GameManager::clefSettingsPanelRect() const {
    const float width = 520.0f;
    const float height = 340.0f;
    return {(GetScreenWidth() - width) / 2.0f, (GetScreenHeight() - height) / 2.0f, width, height};
}
 
// Calcula a area de cada opcao de clave.
Rectangle GameManager::clefOptionRect(int index) const {
    Rectangle panel = clefSettingsPanelRect();
    return {panel.x + 36.0f, panel.y + 112.0f + index * 88.0f, panel.width - 72.0f, 70.0f};
}
 
// Calcula a area do botao "Continuar" nas configuracoes.
Rectangle GameManager::clefSettingsContinueRect() const {
    Rectangle panel = clefSettingsPanelRect();
    return {panel.x + panel.width - 196.0f, panel.y + panel.height - 68.0f, 160.0f, 42.0f};
}
 
// Calcula a area do botao de pausa.
Rectangle GameManager::pauseButtonRect() const {
    return {static_cast<float>(GetScreenWidth() - 136), 52.0f, 104.0f, 36.0f};
}
 
// Calcula a area do botao "Continuar" no overlay de pausa.
Rectangle GameManager::pauseContinueRect() const {
    const float width = 280.0f;
    const float height = 42.0f;
    const float x = (GetScreenWidth() - width) / 2.0f;
    const float y = (GetScreenHeight() - 250.0f) / 2.0f + 120.0f;
    return {x, y, width, height};
}
 
// Calcula a area do botao que volta ao menu durante a pausa.
Rectangle GameManager::pauseMenuRect() const {
    Rectangle rect = pauseContinueRect();
    rect.y += 58.0f;
    return rect;
}
 
// Desenha um botao de modo e retorna se houve clique.
bool GameManager::drawMenuButton(const MenuOption& option, Rectangle rect) const {
    Vector2 mouse = GetMousePosition();
    bool hover = CheckCollisionPointRec(mouse, rect);
    Color fill = hover ? Color{221, 232, 245, 255} : Color{238, 242, 247, 255};
    Color border = hover ? DARKBLUE : LIGHTGRAY;
 
    DrawRectangleRec(rect, fill);
    DrawRectangleLinesEx(rect, 2.0f, border);
    DrawText(option.title.c_str(), static_cast<int>(rect.x + 22), static_cast<int>(rect.y + 16), 22, DARKBLUE);
    DrawText(option.description.c_str(), static_cast<int>(rect.x + 22), static_cast<int>(rect.y + 48), 17, DARKGRAY);
 
    return hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}
 
// Desenha um botao de acao e retorna se houve clique.
bool GameManager::drawActionButton(const char* text, Rectangle rect, Color color) const {
    Vector2 mouse = GetMousePosition();
    bool hover = CheckCollisionPointRec(mouse, rect);
    Color fill = hover ? Fade(color, 0.82f) : color;
    DrawRectangleRec(rect, fill);
    DrawRectangleLinesEx(rect, 1.0f, BLACK);
 
    const int fontSize = 18;
    int textWidth = MeasureText(text, fontSize);
    DrawText(text,
             static_cast<int>(rect.x + (rect.width - textWidth) / 2.0f),
             static_cast<int>(rect.y + (rect.height - fontSize) / 2.0f),
             fontSize, RAYWHITE);
 
    return hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}
