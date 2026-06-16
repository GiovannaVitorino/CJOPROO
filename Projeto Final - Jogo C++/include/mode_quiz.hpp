#pragma once
#include "game_mode.hpp"
#include <random>
#include <vector>
#include <string>
 
// ============================================================
//  QuizMode  —  Modo 4
//  Perguntas de múltipla escolha sobre teoria musical
// ============================================================
 
// Estrutura simples para uma pergunta de multipla escolha.
struct QuizQuestion {
    std::string              question;
    std::vector<std::string> options;
    int                      correctIdx;
};
 
// Modo de quiz teorico com perguntas sorteadas de um banco local.
class QuizMode : public GameMode {
    QuizQuestion current_q_;
    int          selectedIdx_ = -1;
 
    // Banco de perguntas
    // Monta o banco fixo de perguntas usadas no modo.
    // {"texto da pergunta",  {"opção 0", "opção 1", "opção 2", "opção 3"},  índice_correto}
    static std::vector<QuizQuestion> buildBank() {
        return {
            {"Quantos tempos tem um compasso 4/4?",
             {"2","3","4","6"}, 2},
            {"Qual duracao tem uma minima (considere um compasso 4/4)?",
             {"1 tempo","2 tempos","3 tempos","4 tempos"}, 1},
            {"Qual clave e usada para instrumentos agudos (violino)?",
             {"Clave de Sol","Clave de Fa","Ambas","Nenhuma"}, 0},
            {"Um sustenido (#) faz a nota...",
             {"Meio tom acima","Meio tom abaixo","Um tom acima","Nada"}, 0},
            {"Quantas semicolcheias cabem em uma seminima?",
             {"2","4","8","1"}, 1},
            {"Compasso 6/8 e considerado...",
             {"Simples binario","Composto binario","Simples ternario","Livre"}, 1},
            {"Qual intervalo ha entre Do e Sol?",
             {"3a justa","4a justa","5a justa","6a maior"}, 2},
            {"Um bemol (b) faz a nota...",
             {"Meio tom acima","Meio tom abaixo","Um tom abaixo","Nada"}, 1},
            {"Quantas colcheias cabem em um compasso 3/4?",
             {"3","4","6","8"}, 2},
            {"A clave de Fa e usada principalmente para...",
             {"Flauta","Violino","Contrabaixo/Violoncelo","Piano treble"}, 2},
            {"Uma semibreve (whole note) dura quantos tempos (em 4/4)?",
             {"1","2","3","4"}, 3},
            {"Quantos semitons ha em uma oitava?",
             {"7", "10", "12", "14"}, 2},
            {"Qual e o nome da linha adicional usada para notas fora da pauta?",
             {"Linha de clave", "Linha suplementar", "Linha de compasso", "Linha de frase"}, 1},
            {"Em um compasso 3/4, quantas seminimas cabem por compasso?",
             {"2", "3", "4", "6"}, 1},
            {"O que e um intervalo de unissono?",
             {"Duas notas com um tom de diferenca", "Duas notas identicas", "Um acorde de tres notas", "Uma escala descendente"}, 1},
            {"Qual clave e usada normalmente para a mao esquerda no piano?",
             {"Clave de Sol", "Clave de Do", "Clave de Fa", "Clave de Tenor"}, 2},
            {"O que e uma escala diatonica?",
             {"Uma escala com 12 semitons", "Uma escala de 7 notas com tons e semitons", "Uma escala apenas com semitons", "Uma escala de 5 notas"}, 1},
        };
    }
 
    // Sorteia uma nova pergunta e reinicia o estado da rodada.
    void nextQuestion(bool clearFeedback = true) {
        static auto bank = buildBank();
        std::uniform_int_distribution<> d(0, (int)bank.size()-1);
        std::mt19937 rng(std::random_device{}());
        current_q_ = bank[d(rng)];
        selectedIdx_ = -1;
        timer_ = 0.0f;
        if (clearFeedback) {
            lastResult_ = ModeResult::NONE;
        }
    }
 
    // Calcula a area clicavel de cada alternativa.
    Rectangle optionRect(int i) const {
        float w = GetScreenWidth() - 80.f;
        float h = 46.f;
        float gap = 10.f;
        return {40.f, 260.f + i * (h + gap), w, h};
    }
 
    // Confere se a alternativa selecionada e a correta.
    ModeResult evaluate() override {
        return (selectedIdx_ == current_q_.correctIdx)
               ? ModeResult::CORRECT : ModeResult::WRONG;
    }
 
    // Avanca para outra pergunta quando a atual termina.
    void onCorrect() override { nextQuestion(); }
    void onWrong() override { selectedIdx_ = -1; }
    void onTimeout() override {
        score_ -= 5;
        if (score_ < 0) score_ = 0;
        streak_ = 0;
        livesRemaining_--;
        selectedIdx_ = -1;
 
        if (livesRemaining_ <= 0) {
            livesRemaining_ = 0;
            if (onResult) onResult(ModeResult::TIMEOUT, score_, true);
            return;
        }
 
        nextQuestion(false);
        if (onResult) onResult(ModeResult::TIMEOUT, score_, false);
    }
    void onExerciseFailed() override {
    }
 
    // Desenha botoes clicaveis e aplica o resultado ao escolher uma opcao.
    void onUpdate(float) override {
        for (int i = 0; i < (int)current_q_.options.size(); i++) {
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) &&
                CheckCollisionPointRec(GetMousePosition(), optionRect(i))) {
                selectedIdx_ = i;
                applyResult(evaluate());
                break;
            }
        }
    }
 
protected:
    // Nome mostrado no HUD.
    std::string modeNameStr() const override { return "Quiz de Teoria"; }
 
public:
    // Inicializa o modo e ja sorteia a primeira pergunta.
    QuizMode(ScoreRenderer& r, AudioEngine& a, ExerciseFactory& f, int initialScore = 0)
        : GameMode(r, a, f, initialScore) { nextQuestion(); }
 
    // Renderiza pergunta, alternativas, HUD e feedback visual.
    void render() const override {
        DrawText("Quiz de Teoria Musical", 40, 50, 24, DARKBLUE);
        DrawLine(40, 80, GetScreenWidth()-40, 80, LIGHTGRAY);
 
        // Pergunta
        DrawTextEx(GetFontDefault(),
                   current_q_.question.c_str(),
                   {40, 120}, 22, 1, BLACK);
 
        // Botões (re-renderizados aqui para hover)
        for (int i = 0; i < (int)current_q_.options.size(); i++) {
            Color col = DARKBLUE;
            if (selectedIdx_ == i)
                col = (i == current_q_.correctIdx) ? DARKGREEN : MAROON;
            drawButton(current_q_.options[i].c_str(), optionRect(i), col);
        }
 
        drawHUD();
        drawFeedback();
    }
};
