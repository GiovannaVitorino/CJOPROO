#pragma once
#include "interfaces.hpp"
#include "game_mode.hpp"
#include "score_renderer.hpp"
#include "audio_engine.hpp"
#include "exercise_factory.hpp"
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

// Estados de alto nivel que determinam update/render da aplicacao.
enum class GameState { MENU, MODE_SELECT, PLAYING, RESULT, PAUSED };

// Gerenciador do jogo: controla janela, recursos, menu e modo ativo.
class GameManager : public IUpdatable, public IRenderable {
    // --- Singleton ---
    static std::unique_ptr<GameManager> instance;
    GameManager() {}

    // --- Estado ---
    // Guarda a tela atual e a instancia do modo em execucao.
    GameState estado = GameState::MENU;
    std::unique_ptr<GameMode> activeMode;
    int totalScore = 0;

    // --- Dependencias (composicao) ---
    // Componentes compartilhados pelos modos.
    std::unique_ptr<ScoreRenderer>   renderer;
    std::unique_ptr<AudioEngine>     audio;
    std::unique_ptr<ExerciseFactory> factory;
    Font defaultFont_;

    // Texturas de claves e compasso
    Texture2D claveSol{};
    Texture2D claveFa{};
    Texture2D formulaCompasso{};

    // Texturas de figuras ritmicas — notas
    Texture2D semibreve{};      // semibreve.png
    Texture2D minima{};        // minima.png
    Texture2D seminima{};     // seminima.png
    Texture2D colcheia{};      // colcheia.png

    // Texturas de figuras ritmicas — pausas
    Texture2D pausaSemibreve{};      // pausaSemibreve.png
    Texture2D pauseHalfTexture_{};        // pausaSeminim.png
    Texture2D pauseQuarterTexture_{};     // pausaColcheia.png

    bool claveConfig_ = true;

    // Mapa de factories para cada modo
    using ModeFactory = std::function<std::unique_ptr<GameMode>()>;
    std::unordered_map<std::string, ModeFactory> modeRegistry;

    struct MenuOption {
        // Chave interna usada para criar o modo e textos exibidos no menu.
        std::string key;
        std::string title;
        std::string description;
    };

    std::vector<MenuOption> menuOptions;

    // Metodos auxiliares privados separam logica de estado e desenho da UI.
    void registerModes();
    void updateMenu();
    void updateClefSettings();
    void updatePause();
    void renderMenu() const;
    void renderClefSettings() const;
    void renderPauseButton() const;
    void renderPauseOverlay() const;
    void renderResult() const;
    Rectangle menuButtonRect(int index) const;
    Rectangle settingsButtonRect() const;
    Rectangle clefSettingsPanelRect() const;
    Rectangle clefOptionRect(int index) const;
    Rectangle clefSettingsContinueRect() const;
    Rectangle pauseButtonRect() const;
    Rectangle pauseContinueRect() const;
    Rectangle pauseMenuRect() const;
    bool drawMenuButton(const MenuOption& option, Rectangle rect) const;
    bool drawActionButton(const char* text, Rectangle rect, Color color) const;

public:
    // Singleton — cria sob demanda a unica instancia do gerenciador.
    static GameManager& get() {
        if (!instance) instance.reset(new GameManager());
        return *instance;
    }

    // Inicializa raylib, carrega assets e monta dependencias do jogo.
    void init() {
        InitWindow(1280, 720, "NoteReader");
        SetTargetFPS(60);
        defaultFont_ = GetFontDefault();

        // --- Claves e compasso ---
        claveSol  = LoadTexture("assets/images/ClaveSol.png");
        claveFa    = LoadTexture("assets/images/ClaveFa.png");
        formulaCompasso  = LoadTexture("assets/images/CompassoQuaternario.png");

        // --- Figuras ritmicas: notas ---
        semibreve   = LoadTexture("assets/images/semibreve.png");
        minima    = LoadTexture("assets/images/minima.png");
        seminima = LoadTexture("assets/images/seminima.png");
        colcheia  = LoadTexture("assets/images/colcheia.png");

        // --- Figuras ritmicas: pausas ---
        pausaSemibreve   = LoadTexture("assets/images/pausaSemibreve.png");
        pauseHalfTexture_    = LoadTexture("assets/images/pausaSeminim.png");
        pauseQuarterTexture_ = LoadTexture("assets/images/pausaColcheia.png");

        renderer = std::make_unique<ScoreRenderer>(
            defaultFont_,
            StaffLayout{{100, 300}, 14.0f, 200.0f, 24.0f},
            claveSol,
            claveFa,
            formulaCompasso,
            semibreve,
            minima,
            seminima,
            colcheia,
            pausaSemibreve,
            pauseHalfTexture_,
            pauseQuarterTexture_
        );

        audio = std::make_unique<AudioEngine>();
        factory = std::make_unique<ExerciseFactory>();

        registerModes();
    }

    // Loop principal: atualiza, desenha e libera recursos ao finalizar.
    void run() {
        while (!WindowShouldClose()) {
            float dt = GetFrameTime();
            update(dt);
            BeginDrawing();
            ClearBackground(RAYWHITE);
            render();
            EndDrawing();
        }

        // Descarrega texturas de claves e compasso
        UnloadTexture(claveSol);
        UnloadTexture(claveFa);
        UnloadTexture(formulaCompasso);

        // Descarrega texturas de figuras ritmicas
        UnloadTexture(semibreve);
        UnloadTexture(minima);
        UnloadTexture(seminima);
        UnloadTexture(colcheia);
        UnloadTexture(pausaSemibreve);
        UnloadTexture(pauseHalfTexture_);
        UnloadTexture(pauseQuarterTexture_);

        CloseWindow();
    }

    void update(float dt) override;
    void render() const override;

    // Troca de modo por nome
    void switchMode(const std::string& name);
};