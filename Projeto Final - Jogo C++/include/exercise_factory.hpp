#pragma once
#include "exercise.hpp"
#include "clefs.hpp"
#include <algorithm>
#include <array>
#include <memory>
#include <optional>
#include <random>
#include <string>
#include <vector>
 
// Fabrica exercicios conforme dificuldade e clave escolhida.
class ExerciseFactory {
    // RNG para escolher claves aleatorias quando necessario.
    std::mt19937            rng_;
    // Parametros de progressao do jogo.
    float                   difficulty_   = 1.0f;
    ClefType                selectedClef_  = ClefType::TREBLE;
    std::optional<NoteValue> fixedRhythm_;
    // Recursos usados para manter as claves desbloqueadas.
    Font                    clefFont_{};
    std::vector<std::shared_ptr<Clef>> unlockedClefs_;
    std::vector<NoteValue>  rhythmBag_;
    std::vector<int>        recentPitches_;
    std::vector<NoteValue>  recentDurations_;
 
    static constexpr int    maxRecent_ = 2;
 
    // Sorteia duracoes em uma "sacola" embaralhada para manter distribuicao equilibrada.
    NoteValue chooseDuration(float remainingBeats) {
        if (fixedRhythm_ && Note(60, *fixedRhythm_).durationInBeats() <= remainingBeats + 0.001f) {
            remember(recentDurations_, *fixedRhythm_);
            return *fixedRhythm_;
        }
 
        const std::array<NoteValue, 4> base = {
            NoteValue::WHOLE, NoteValue::HALF, NoteValue::QUARTER, NoteValue::EIGHTH
        };
 
        auto fits = [remainingBeats](NoteValue value) {
            return Note(60, value).durationInBeats() <= remainingBeats + 0.001f;
        };
 
        if (rhythmBag_.empty()) {
            rhythmBag_.assign(base.begin(), base.end());
            std::shuffle(rhythmBag_.begin(), rhythmBag_.end(), rng_);
        }
 
        for (auto it = rhythmBag_.begin(); it != rhythmBag_.end(); ++it) {
            NoteValue candidate = *it;
            if (!fits(candidate)) continue;
            if (repeatedTooMuch(recentDurations_, candidate)) continue;
            rhythmBag_.erase(it);
            remember(recentDurations_, candidate);
            return candidate;
        }
 
        for (auto it = rhythmBag_.begin(); it != rhythmBag_.end(); ++it) {
            NoteValue candidate = *it;
            if (!fits(candidate)) continue;
            rhythmBag_.erase(it);
            remember(recentDurations_, candidate);
            return candidate;
        }
 
        remember(recentDurations_, NoteValue::EIGHTH);
        return NoteValue::EIGHTH;
    }
 
    template <typename T>
    bool repeatedTooMuch(const std::vector<T>& recent, T value) const {
        if (recent.size() < maxRecent_) return false;
        return recent[recent.size() - 1] == value &&
               recent[recent.size() - 2] == value;
    }
 
    template <typename T>
    void remember(std::vector<T>& recent, T value) {
        recent.push_back(value);
        if (recent.size() > maxRecent_) recent.erase(recent.begin());
    }
 
    std::vector<int> pitchPool() const {
        const bool advanced = difficulty_ >= 4.0f;
        if (selectedClef_ == ClefType::BASS) {
            return advanced
                ? std::vector<int>{36, 38, 40, 41, 43, 45, 47, 48, 50, 52, 53, 55, 57, 59, 60}
                : std::vector<int>{43, 45, 47, 48, 50, 52, 53};
        }
 
        return advanced
            ? std::vector<int>{60, 62, 64, 65, 67, 69, 71, 72, 74, 76, 77, 79, 81}
            : std::vector<int>{64, 65, 67, 69, 71, 72, 74};
    }
 
    Note chooseNote(float remainingBeats) {
        auto pitches = pitchPool();
        std::shuffle(pitches.begin(), pitches.end(), rng_);
 
        int pitch = pitches.front();
        for (int candidate : pitches) {
            if (!repeatedTooMuch(recentPitches_, candidate)) {
                pitch = candidate;
                break;
            }
        }
 
        Accidental accidental = Accidental::NONE;
        if (difficulty_ >= 2.0f) {
            std::uniform_int_distribution<int> accidentalRoll(0, 5);
            int roll = accidentalRoll(rng_);
            if (roll == 0) {
                accidental = Accidental::SHARP;
                pitch += 1;
            } else if (roll == 1) {
                accidental = Accidental::FLAT;
                pitch -= 1;
            }
        }
 
        remember(recentPitches_, pitch);
        return Note(pitch, chooseDuration(remainingBeats), accidental);
    }
 
    // Cria exercicios variados respeitando dificuldade, ritmo e anti-repeticao.
    virtual Exercise buildAdaptive() {
        Exercise ex;
        ex.id = TextFormat("adaptive_%.1f", difficulty_);
        ex.clef = selectedClef_;
        Measure m;
        m.timeSig = ex.timeSig;
 
        float remainingBeats = 4.0f;
        while (remainingBeats > 0.001f) {
            Note note = chooseNote(remainingBeats);
            m.notes.push_back(note);
            remainingBeats -= note.durationInBeats();
        }
 
        ex.measures.push_back(m);
        return ex;
    }
 
public:
    // Inicializa o gerador aleatorio e libera as claves iniciais.
    ExerciseFactory() : rng_(std::random_device{}()) {
        unlockedClefs_.push_back(
            std::make_shared<TrebleClef>(Vector2{}, clefFont_, 14.0f));
        unlockedClefs_.push_back(
            std::make_shared<BassClef>(Vector2{}, clefFont_, 14.0f));
    }
 
    // Escolhe qual construtor usar a partir da dificuldade atual.
    Exercise create() { return buildAdaptive(); }
 
    // Permite adicionar novas claves ao conjunto disponivel.
    void unlockClef(std::shared_ptr<Clef> clef) {
        unlockedClefs_.push_back(std::move(clef));
    }
 
    // Ajusta parametros controlados pelo menu ou pela progressao.
    void setDifficulty(float d) { difficulty_ = std::max(1.0f, std::min(d, 6.0f)); }
    void increaseDifficulty(float amount = 0.5f) { setDifficulty(difficulty_ + amount); }
    float difficulty() const { return difficulty_; }
    void setFixedRhythm(NoteValue value) { fixedRhythm_ = value; }
    void clearFixedRhythm() { fixedRhythm_.reset(); }
    void setClef(ClefType clef) { selectedClef_ = clef; }
    ClefType selectedClef() const { return selectedClef_; }
 
    // Sorteia uma clave entre as desbloqueadas.
    Clef& randomClef() {
        std::uniform_int_distribution<> dist(0, unlockedClefs_.size() - 1);
        return *unlockedClefs_[dist(rng_)];
    }
};
