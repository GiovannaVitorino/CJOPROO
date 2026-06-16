#pragma once
#include "game_mode.hpp"
#include <string>
#include <vector>
 
// Modo em que o jogador le a nota destacada e escolhe seu nome.
class ReadAndName : public GameMode {
    int     currentNoteIdx_  = 0;   // qual nota está sendo perguntada
    int     lastPlayedNoteIdx_ = -1;
    int     selectedAnswer_  = -1;
    std::vector<std::string> opcoes; // botões de nome das notas
 
    std::string solfegeLabelFor(const Note& note) const {
        int pc = (note.pitch() % 12 + 12) % 12;
        if (note.accidental() == Accidental::FLAT) {
            switch (pc) {
                case 1: return "Réb";
                case 3: return "Mib";
                case 6: return "Solb";
                case 8: return "Láb";
                case 10: return "Sib";
                default: break;
            }
        }
 
        switch (pc) {
            case 0: return "Dó";
            case 1: return "Dó#";
            case 2: return "Ré";
            case 3: return "Ré#";
            case 4: return "Mi";
            case 5: return "Fá";
            case 6: return "Fá#";
            case 7: return "Sol";
            case 8: return "Sol#";
            case 9: return "Lá";
            case 10: return "Lá#";
            case 11: return "Si";
            default: return "Dó";
        }
    }
 
    int choiceIndexFor(const Note& note) const {
        std::string label = solfegeLabelFor(note);
        for (int i = 0; i < static_cast<int>(opcoes.size()); ++i) {
            if (opcoes[i] == label) return i;
        }
        return -1;
    }
 
    // Compara a escolha do jogador com o nome da nota destacada.
    ModeResult evaluate() override {
        if (selectedAnswer_ < 0 || selectedAnswer_ >= (int)opcoes.size()) {
            return ModeResult::WRONG;
        }
        const Note& target = exercicioAtual.noteAt(currentNoteIdx_);
        bool correct = selectedAnswer_ == choiceIndexFor(target);
        return correct ? ModeResult::CORRECT : ModeResult::WRONG;
    }
 
    void buildChoices(); // gera botoes cromaticos com sustenidos e bemois usuais
 
    // Toca a nota, avanca o destaque e troca de exercicio ao chegar ao fim.
    void onCorrect() override {
        currentNoteIdx_++;
        if (currentNoteIdx_ >= (int)exercicioAtual.allNotes().size()) {
            nextExercise();
            currentNoteIdx_ = 0;
            lastPlayedNoteIdx_ = -1;
            selectedAnswer_ = -1;
        }
    }
 
    void onWrong() override {
        selectedAnswer_ = -1;
    }
 
    void onTimeout() override {
        score_ -= 5;
        if (score_ < 0) score_ = 0;
        streak_ = 0;
        livesRemaining_--;
        selectedAnswer_ = -1;
 
        if (livesRemaining_ <= 0) {
            livesRemaining_ = 0;
            if (onResult) onResult(ModeResult::TIMEOUT, score_, true);
            return;
        }
 
        nextExercise();
        currentNoteIdx_ = 0;
        lastPlayedNoteIdx_ = -1;
        lastResult_ = ModeResult::TIMEOUT;
        if (onResult) onResult(ModeResult::TIMEOUT, score_, false);
    }
 
    // Mantém o mesmo exercício/note até que o jogador acerte ou perca todas as vidas.
    void onExerciseFailed() override {
    }
 
public:
    // Inicializa o modo e cria as opcoes de resposta.
    ReadAndName(ScoreRenderer& r, AudioEngine& a, ExerciseFactory& f, int initialScore = 0)
        : GameMode(r, a, f, initialScore) { buildChoices(); }
 
    // Desenha a partitura, botoes, HUD e feedback.
    void render() const override;
 
    // Destaca a nota atual e processa cliques nos botoes de nome.
    void onUpdate(float) override {
        // Mostra partitura com a nota atual destacada
        renderer.clearHighlights();
        renderer.highlight(currentNoteIdx_, ORANGE);
        if (currentNoteIdx_ != lastPlayedNoteIdx_ && !audio.isPlaying()) {
            audio.playNote(exercicioAtual.noteAt(currentNoteIdx_), 80.0f);
            lastPlayedNoteIdx_ = currentNoteIdx_;
        }
 
        // Clique nos botões de nome
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 m = GetMousePosition();
            for (int i = 0; i < (int)opcoes.size(); i++) {
                if (CheckCollisionPointRec(m, getButtonRect(i))) {
                    selectedAnswer_ = i;
                    applyResult(evaluate());
                }
            }
        }
    }
 
private:
    // Retorna areas clicaveis usadas na interface do modo.
    Rectangle getButtonRect(int i) const;
    Rectangle getClefButtonRect(int i) const;
};
