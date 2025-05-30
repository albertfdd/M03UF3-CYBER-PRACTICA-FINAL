#pragma once
#include "enig.h"

// Estructura de un rotor: wiring, notch y posici�n actual (0�25)
struct Rotor {
    Wiring wiring;     // Permutaci�n A?wiring[0], B?wiring[1], �
    char notch;        // Letra que provoca el avance del siguiente rotor
    int position;      // Offset actual: 0='A', 25='Z'
};

// Convierte letra 'A'�'Z' a �ndice 0�25
inline int letterToIndex(char c) {
    return static_cast<int>(c - 'A');
}

// Convierte �ndice 0�25 a letra 'A'�'Z'
inline char indexToLetter(int i) {
    return static_cast<char>('A' + (i % ALPHABET_SIZE + ALPHABET_SIZE) % ALPHABET_SIZE);
}
