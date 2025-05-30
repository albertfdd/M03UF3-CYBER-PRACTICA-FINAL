#pragma once
#include "rotor.h"
#include <string>

// Normaliza un texto:
//  - Convierte a mayúsculas
//  - Elimina todo lo que no sea A–Z
//  - Agrupa en bloques de 5 separando con espacios
std::string normalize(const std::string& raw);

// Avanza los rotors r1 (rápido), r2 (medio), r3 (lento) según notch
void stepRotors(Rotor& r1, Rotor& r2, Rotor& r3);

// Mapea carácter c hacia delante pasando por un rotor r
char mapForward(const Rotor& r, char c);

// Mapea carácter c hacia atrás pasando por un rotor r
char mapBackward(const Rotor& r, char c);
