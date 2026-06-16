#pragma once
#include <string>
#include <array>
#include <cmath>

// Valores ritmicos suportados pelo jogo.
enum class NoteValue {
    WHOLE, HALF, QUARTER, EIGHTH, SIXTEENTH,
    DOTTED_HALF, DOTTED_QUARTER, DOTTED_EIGHTH
};

// Acidentes musicais usados para alterar ou descrever notas.
enum class Accidental { NONE, SHARP, FLAT, NATURAL, DOUBLE_SHARP, DOUBLE_FLAT };

// Representa uma nota ou pausa com pitch MIDI, duracao e acidente.
class Note {
    // Estado musical armazenado pela nota.
    int        midiPitch_;
    NoteValue  duration_;
    Accidental accidental_;
    bool       isRest_;

public:
    // Cria nota com pitch MIDI, valor ritmico, acidente opcional e flag de pausa.
    Note(int pitch, NoteValue dur,
         Accidental acc = Accidental::NONE, bool rest = false)
        : midiPitch_(pitch), duration_(dur),
          accidental_(acc), isRest_(rest) {}

    // --- Getters ---
    int        pitch()      const { return midiPitch_; }
    NoteValue  duration()   const { return duration_;  }
    Accidental accidental() const { return accidental_; }
    bool       isRest()     const { return isRest_;     }

    // --- Conversões ---
    // Converte MIDI em frequencia Hz; pausas retornam zero.
    float frequency() const {
        if (isRest_) return 0.0f;
        return 440.0f * std::pow(2.0f, (midiPitch_ - 69) / 12.0f);
    }

    // Converte o valor ritmico em quantidade de tempos.
    float durationInBeats() const {
        static const std::array<float, 8> beats =
            {4.f, 2.f, 1.f, 0.5f, 0.25f, 3.f, 1.5f, 0.75f};
        return beats[static_cast<int>(duration_)];
    }

    // Retorna o nome da classe de pitch em solfejo ou notacao ABC.
    std::string name(bool solfege = true) const {
        static const std::array<std::string,12> sol =
            {"Dó","Dó#","Ré","Ré#","Mi","Fá","Fá#","Sol","Sol#","Lá","Lá#","Si"};
        static const std::array<std::string,12> abc =
            {"C","C#","D","D#","E","F","F#","G","G#","A","A#","B"};
        int pc = midiPitch_ % 12;
        return solfege ? sol[pc] : abc[pc];
    }

    // Operador de igualdade (ignora oitava por padrão)
    // Compara apenas classe de pitch, ignorando oitava e duracao.
    bool sameClass(const Note& other) const {
        return (midiPitch_ % 12) == (other.midiPitch_ % 12);
    }
    // Compara pitch absoluto e duracao.
    bool operator==(const Note& other) const {
        return midiPitch_ == other.midiPitch_ && duration_ == other.duration_;
    }
};