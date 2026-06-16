#pragma once
#include "interfaces.hpp"
#include "exercise.hpp"
#include "score_renderer.hpp"
#include "audio_engine.hpp"
#include "exercise_factory.hpp"
#include <functional>
#include <memory>
#include <string>
 
// Resultado possivel de uma interacao dentro de um modo.
enum class ModeResult { NONE, CORRECT, WRONG, TIMEOUT };
 
// Classe base dos modos; implementa fluxo comum de pontuacao, tempo e HUD.
class GameMode : public IRenderable, public IUpdatable {
protected:
    // Dependencias compartilhadas recebidas do GameManager.
    ScoreRenderer&          renderer;
    AudioEngine&            audio;
    ExerciseFactory&        factory;
 
    Exercise                exercicioAtual;
    Exercise&               current_ = exercicioAtual;
    ModeResult              lastResult_ = ModeResult::NONE;
    int                     score_      = 0;
    int                     streak_     = 0;
    int                     livesRemaining_ = 3;  // Vidas globais da sessão
    static constexpr int    initialLives_ = 3;
    static constexpr int    difficultyStreakStep_ = 10;
    inline static int       bestStreakRecord_ = 0;
    // Controle de tempo por exercicio.
    float                   timer_      = 0.0f;
    float                   timeLimit_  = 30.0f;
 
    // Hook para subclasses implementarem a avaliação
    virtual ModeResult evaluate() = 0;
 
    // Feedback visual (flash verde/vermelho)
    void showFeedback(ModeResult r) { lastResult_ = r; }
 
    virtual std::string modeNameStr() const { return "Modo"; }
 
    // Desenha um botao retangular padrao e informa se foi clicado.
    bool drawButton(const char* text, Rectangle rect, Color color) const {
        Vector2 mouse = GetMousePosition();
        bool hover = CheckCollisionPointRec(mouse, rect);
        Color fill = hover ? Fade(color, 0.85f) : color;
        DrawRectangleRec(rect, fill);
        DrawRectangleLinesEx(rect, 1.0f, BLACK);
        int fontSize = 18;
        int textWidth = MeasureText(text, fontSize);
        DrawText(text,
                 static_cast<int>(rect.x + (rect.width - textWidth) / 2.0f),
                 static_cast<int>(rect.y + (rect.height - fontSize) / 2.0f),
                 fontSize,
                 RAYWHITE);
        return hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    }
 
    // Aplica pontuacao, erros, hooks e callback apos uma resposta.
    void applyResult(ModeResult r) {
        lastResult_ = r;
        if (r == ModeResult::CORRECT) {
            score_ += 10;
            streak_++;
            if (streak_ > bestStreakRecord_) bestStreakRecord_ = streak_;
            if (streak_ > 0 && streak_ % difficultyStreakStep_ == 0) {
                factory.increaseDifficulty(0.5f);
            }
            onCorrect();
        } else if (r == ModeResult::WRONG) {
            score_ -= 5;
            if (score_ < 0) score_ = 0;  // Garante que pontuação nunca fique negativa
            streak_ = 0;
            livesRemaining_--;
            onWrong();
            
            // Game over ao perder todas as vidas
            if (livesRemaining_ <= 0) {
                livesRemaining_ = 0;
                bool ended = true;
                if (onResult) onResult(r, score_, ended);
                return;
            }
            // Continua com próximo exercício
            onExerciseFailed();
        } else if (r == ModeResult::TIMEOUT) {
            streak_ = 0;
            onTimeout();
        }
        if (onResult) onResult(r, score_, false);
    }
 
    // Desenha um icone simples de vida usando primitivas da raylib.
    void drawHeart(Vector2 center, float size, Color color) const {
        DrawCircleV({center.x - size * 0.25f, center.y - size * 0.15f}, size * 0.32f, color);
        DrawCircleV({center.x + size * 0.25f, center.y - size * 0.15f}, size * 0.32f, color);
        DrawTriangle({center.x - size * 0.58f, center.y},
                     {center.x + size * 0.58f, center.y},
                     {center.x, center.y + size * 0.68f},
                     color);
    }
 
    // Mostra quantas vidas restam na sessão.
    void drawLives() const {
        const float startX = static_cast<float>(GetScreenWidth() - 160);
        const float y = 50.0f;
        for (int i = 0; i < initialLives_; ++i) {
            Color color = i < livesRemaining_ ? MAROON : LIGHTGRAY;
            drawHeart({startX + i * 28.0f, y}, 18.0f, color);
        }
    }
 
    // Mostra o tempo restante do exercicio atual.
    void drawTimer() const {
        const float remaining = timer_ >= timeLimit_ ? 0.0f : (timeLimit_ - timer_);
        const float ratio = timeLimit_ > 0.0f ? remaining / timeLimit_ : 0.0f;
        const float barWidth = 240.0f;
        const float barHeight = 14.0f;
        const float x = (static_cast<float>(GetScreenWidth()) - barWidth) / 2.0f;
        const float y = 60.0f;
        Rectangle barBack{x, y, barWidth, barHeight};
        Rectangle barFill{x, y, barWidth * ratio, barHeight};
 
        DrawText(TextFormat("Tempo: %.0fs", remaining), static_cast<int>(x), 40, 18, DARKGRAY);
        DrawRectangleRec(barBack, LIGHTGRAY);
        DrawRectangleRec(barFill, ratio <= 0.25f ? MAROON : DARKGREEN);
        DrawRectangleLinesEx(barBack, 1.0f, DARKGRAY);
    }
 
    // Desenha nome do modo, score e vidas.
    void drawHUD() const {
        DrawText(modeNameStr().c_str(), 40, 16, 20, DARKGRAY);
        DrawText(TextFormat("Sequencia: %d", streak_), 270, 16, 20, DARKGRAY);
        DrawText(TextFormat("Recorde: %d", bestStreakRecord_), 470, 16, 20, DARKGRAY);
        DrawText(TextFormat("Dif.: %.1f", factory.difficulty()), 640, 16, 20, DARKGRAY);
        drawTimer();
        DrawText(TextFormat("Score: %d", score_), GetScreenWidth() - 160, 16, 20, DARKGRAY);
        drawLives();
    }
 
    // Mostra a mensagem textual da ultima resposta.
    void drawFeedback() const {
        if (lastResult_ == ModeResult::CORRECT) {
            DrawText("Correto", 40, GetScreenHeight() - 100, 22, DARKGREEN);
        } else if (lastResult_ == ModeResult::WRONG) {
            DrawText("Tente novamente", 40, GetScreenHeight() - 100, 22, MAROON);
        } else if (lastResult_ == ModeResult::TIMEOUT) {
            DrawText("Tempo esgotado", 40, GetScreenHeight() - 100, 22, MAROON);
        }
    }
 
public:
    using ResultCallback = std::function<void(ModeResult, int score, bool ended)>;
 
    // Guarda as dependencias e cria o primeiro exercicio do modo.
    GameMode(ScoreRenderer& r, AudioEngine& a, ExerciseFactory& f, int initialScore = 0)
        : renderer(r), audio(a), factory(f), score_(initialScore), livesRemaining_(initialLives_) {
        exercicioAtual = factory.create();
    }
 
    virtual ~GameMode() = default;
 
    // --- Template Method Pattern ---
    // Subclasses personalizam os hooks, não o fluxo principal
    void update(float dt) override final {
        timer_ += dt;
        if (timer_ >= timeLimit_) {
            lastResult_ = ModeResult::TIMEOUT;
            onTimeout();
            return;
        }
        onUpdate(dt);  // hook específico do modo
    }
 
    // Hooks opcionais (subclasses fazem override se precisar)
    virtual void onUpdate(float) {}
    virtual void onTimeout()       {}
    virtual void onCorrect()       {}
    virtual void onWrong()         {}
    virtual void onExerciseFailed() { nextExercise(); }
 
    // Avança para próximo exercício
    // Reinicia estado local e pede novo exercicio para a fabrica.
    void nextExercise() {
        exercicioAtual = factory.create();
        timer_ = 0.0f;
        lastResult_ = ModeResult::NONE;
    }
 
    int         getScore()  const { return score_;      }
    int         getStreak() const { return streak_;     }
    ModeResult  getResult() const { return lastResult_; }
    static int  bestStreakRecord() { return bestStreakRecord_; }
 
    ResultCallback onResult; // callback para GameManager
};
