#pragma once
#include "clef.hpp"
 
// Clave de Sol: usada para registros mais agudos.
class TrebleClef : public Clef {
public:
    using Clef::Clef;
    // Nota de referencia da pauta, nome exibido e simbolo SMuFL.
    int  referenceNote()   const override { return 64; }
    std::string name()     const override { return "Sol"; }
    int  glyphCodepoint()  const override { return 0x1D11E; }
};
 
// Clave de Fa: usada para registros mais graves.
class BassClef : public Clef {
public:
    using Clef::Clef;
    // Nota de referencia da pauta, nome exibido e simbolo SMuFL.
    int  referenceNote()   const override { return 43; }
    std::string name()     const override { return "Fa"; }
    int  glyphCodepoint()  const override { return 0x1D122; }
};