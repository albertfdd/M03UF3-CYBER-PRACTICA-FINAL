#pragma once
#include "rotor.h"
#include <string>

// Cifra el texto en `inFile` y guarda el resultado en `outFile`.
// Usa r1, r2, r3 como rotores en estado inicial.
bool encryptFile(const std::string& inFile,
    const std::string& outFile,
    Rotor r1, Rotor r2, Rotor r3);

// Descifra el texto en `inFile` y guarda el resultado en `outFile`.
bool decryptFile(const std::string& inFile,
    const std::string& outFile,
    Rotor r1, Rotor r2, Rotor r3);
