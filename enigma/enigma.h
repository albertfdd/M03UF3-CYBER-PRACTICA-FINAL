#pragma once
#include "rotor.h"
#include <string>

// Normaliza un texto:
//  - Convierte a may�sculas
//  - Elimina todo lo que no sea A�Z
//  - Agrupa en bloques de 5 separando con espacios
std::string normalize(const std::string& raw);

// Avanza los rotors r1 (r�pido), r2 (medio), r3 (lento) seg�n notch
void stepRotors(Rotor& r1, Rotor& r2, Rotor& r3);

// Mapea car�cter c hacia delante pasando por un rotor r
char mapForward(const Rotor& r, char c);

// Mapea car�cter c hacia atr�s pasando por un rotor r
char mapBackward(const Rotor& r, char c);
