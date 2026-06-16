#pragma once
#include <string>
#include <vector>
#include <cmath>
#include <array>
 
// ============================================================
//  Enums
// ============================================================
 
enum class NoteValue {
    WHOLE, HALF, QUARTER, EIGHTH, SIXTEENTH,
    DOTTED_HALF, DOTTED_QUARTER, DOTTED_EIGHTH
};
 
enum class Accidental { NONE, SHARP, FLAT, NATURAL };
 
enum class ClefType { TREBLE, BASS };
 
// ============================================================
//  Note
// ============================================================
 
class Note {
    // Estado musical basico usado por exercicios antigos deste header.
    int        midiPitch_;
    NoteValue  duration_;
    Accidental accidental_;
    bool       isRest_;
 
public:
    // Cria nota com pitch MIDI, valor ritmico, acidente e opcao de pausa.
    Note(int pitch = 60, NoteValue dur = NoteValue::QUARTER,
         Accidental acc = Accidental::NONE, bool rest = false)
        : midiPitch_(pitch), duration_(dur),
          accidental_(acc), isRest_(rest) {}
 
    int        pitch()       const { return midiPitch_;   }
    NoteValue  duration()    const { return duration_;    }
    Accidental accidental()  const { return accidental_;  }
    bool       isRest()      const { return isRest_;      }
 
    // Converte MIDI em frequencia Hz; pausas retornam zero.
    float frequency() const {
        if (isRest_) return 0.f;
        return 440.f * std::pow(2.f, (midiPitch_ - 69) / 12.f);
    }
 
    // Converte a figura ritmica para tempos.
    float durationInBeats() const {
        static const std::array<float,8> b =
            {4.f,2.f,1.f,.5f,.25f,3.f,1.5f,.75f};
        return b[static_cast<int>(duration_)];
    }
 
    // Retorna nome da nota em solfejo ou em letras.
    std::string name(bool solfege = true) const {
        static const std::array<std::string,12> sol =
            {"Do","Do#","Re","Re#","Mi","Fa","Fa#","Sol","Sol#","La","La#","Si"};
        static const std::array<std::string,12> abc =
            {"C","C#","D","D#","E","F","F#","G","G#","A","A#","B"};
        return (solfege ? sol : abc)[midiPitch_ % 12];
    }
 
    // Compara pitch absoluto e duracao.
    bool operator==(const Note& o) const {
        return midiPitch_ == o.midiPitch_ && duration_ == o.duration_;
    }
    // Compara apenas classe de pitch, ignorando oitava.
    bool sameClass(const Note& o) const {
        return (midiPitch_ % 12) == (o.midiPitch_ % 12);
    }
};
 
// ============================================================
//  TimeSignature
// ============================================================
 
struct TimeSignature {
    int numerator   = 4;
    int denominator = 4;
    // Identifica compassos compostos pelo numerador.
    bool isCompound() const { return numerator % 3 == 0 && numerator > 3; }
};
 
// ============================================================
//  Measure
// ============================================================
 
struct Measure {
    // Lista de notas e assinatura de tempo deste compasso.
    std::vector<Note> notes;
    TimeSignature     timeSig;
};
 
// ============================================================
//  Exercise
// ============================================================
 
struct Exercise {
    // Dados necessarios para renderizar e avaliar um exercicio.
    std::string           id;
    ClefType              clef       = ClefType::TREBLE;
    TimeSignature         timeSig;
    int                   keySignature = 0;   // -7..+7
    std::vector<Measure>  measures;
 
    // Achata todos os compassos em uma lista unica de notas.
    std::vector<Note> allNotes() const {
        std::vector<Note> out;
        for (auto& m : measures)
            for (auto& n : m.notes) out.push_back(n);
        return out;
    }
 
    // Busca uma nota pelo indice linear; retorna dummy se passar do fim.
    const Note& noteAt(int idx) const {
        int i = 0;
        for (auto& m : measures)
            for (auto& n : m.notes)
                if (i++ == idx) return n;
        static Note dummy;
        return dummy;
    }
 
    // Conta todas as notas dos compassos.
    int totalNotes() const {
        int c = 0;
        for (auto& m : measures) c += (int)m.notes.size();
        return c;
    }
};
