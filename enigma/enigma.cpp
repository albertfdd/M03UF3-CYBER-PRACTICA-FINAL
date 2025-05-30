#include "enigma.h"
#include <cctype>
#include <algorithm>

std::array<char, ALPHABET_SIZE> plugboard;

// Normalizaci�n
std::string normalize(const std::string& raw) {
    std::string filtered;
    for (char ch : raw) {
        if (std::isalpha(static_cast<unsigned char>(ch))) {
            filtered += std::toupper(static_cast<unsigned char>(ch));
        }
    }
    // Agrupar en bloques de 5
    std::string out;
    for (size_t i = 0; i < filtered.size(); ++i) {
        if (i > 0 && i % 5 == 0) out += ' ';
        out += filtered[i];
    }
    return out;
}

// Avance
void stepRotors(Rotor& r1, Rotor& r2, Rotor& r3) {
    // Rotor 1 siempre avanza
    r1.position = (r1.position + 1) % ALPHABET_SIZE;
    // Doble-stepping tradicional
    if (indexToLetter(r1.position) == r1.notch) {
        r2.position = (r2.position + 1) % ALPHABET_SIZE;
        if (indexToLetter(r2.position) == r2.notch) {
            r3.position = (r3.position + 1) % ALPHABET_SIZE;
        }
    }
}

// Mapeo hacia delante
char mapForward(const Rotor& r, char c) {
    int idx = (letterToIndex(c) + r.position) % ALPHABET_SIZE;
    char wired = r.wiring[idx];
    int outIdx = (letterToIndex(wired) - r.position + ALPHABET_SIZE) % ALPHABET_SIZE;
    return indexToLetter(outIdx);
}

// Mapeo hacia atr�s
char mapBackward(const Rotor& r, char c) {
    // Ajustar posici�n
    int shifted = (letterToIndex(c) + r.position) % ALPHABET_SIZE;
    // Buscar cu�l wiring[i] coincide con letra
    int i = 0;
    for (; i < ALPHABET_SIZE; ++i) {
        if (letterToIndex(r.wiring[i]) == shifted) break;
    }
    // i es la posici�n original antes del wiring
    int outIdx = (i - r.position + ALPHABET_SIZE) % ALPHABET_SIZE;
    return indexToLetter(outIdx);
}
