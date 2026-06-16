#pragma once
#include "note.hpp"
#include <string>
#include <vector>
 
// Tipos de clave aceitos pelo gerador e pelo renderizador.
enum class ClefType { TREBLE, BASS };
 
// Representa a formula de compasso do exercicio.
struct TimeSignature {
    int numerator = 4;
    int denominator = 4;
    // Compassos compostos geralmente tem numerador multiplo de 3 maior que 3.
    bool isCompound() const { return numerator % 3 == 0 && numerator > 3; }
};
 
// Agrupa as notas pertencentes a um compasso.
struct Measure {
    std::vector<Note> notes;
    TimeSignature timeSig;
};
 
// Modelo completo de um exercicio musical exibido pelos modos de jogo.
struct Exercise {
    std::string id;
    ClefType clef = ClefType::TREBLE;
    TimeSignature timeSig;
    int keySignature = 0;
    std::vector<Measure> measures;
 
    // Junta todas as notas de todos os compassos em uma lista linear.
    std::vector<Note> allNotes() const {
        std::vector<Note> out;
        for (const auto& measure : measures) {
            for (const auto& note : measure.notes) out.push_back(note);
        }
        return out;
    }
 
    // Retorna a nota pelo indice linear; se nao encontrar, devolve uma nota dummy.
    const Note& noteAt(int idx) const {
        int current = 0;
        for (const auto& measure : measures) {
            for (const auto& note : measure.notes) {
                if (current++ == idx) return note;
            }
        }
        static const Note dummy(60, NoteValue::QUARTER);
        return dummy;
    }
 
    // Conta todas as notas existentes nos compassos.
    int totalNotes() const {
        int total = 0;
        for (const auto& measure : measures) total += static_cast<int>(measure.notes.size());
        return total;
    }
};
