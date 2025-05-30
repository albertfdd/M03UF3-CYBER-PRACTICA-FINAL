#include "rotor_io.h"
#include <fstream>
#include <set>

// Valida que 's' tenga exactamente 26 letras A–Z sin repetir
bool validateWiring(const std::string& s) {
    if (s.size() != ALPHABET_SIZE) return false;
    std::set<char> seen;
    for (char c : s) {
        if (c < 'A' || c > 'Z') return false;
        seen.insert(c);
    }
    return seen.size() == ALPHABET_SIZE;
}

bool loadRotor(const std::string& filename, Rotor& r) {
    std::ifstream in(filename);
    if (!in) {
        std::cerr << "[ERROR] " << filename << ": no s'ha pogut obrir per lectura\n";
        return false;
    }
    std::string line;
    // Leer wiring
    if (!std::getline(in, line) || !validateWiring(line)) {
        std::cerr << "[ERROR] " << filename << ": permutació incorrecta — calen 26 lletres úniques A–Z\n";
        return false;
    }
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        r.wiring[i] = line[i];
    }
    // Leer notch (opcional)
    if (std::getline(in, line) && line.size() >= 1 && line[0] >= 'A' && line[0] <= 'Z') {
        r.notch = line[0];
    }
    else {
        r.notch = 'Z';
    }
    r.position = 0; // posición inicial A
    return true;
}

bool saveRotor(const std::string& filename, const Rotor& r) {
    std::ofstream out(filename);
    if (!out) {
        std::cerr << "[ERROR] " << filename << ": no s'ha pogut obrir per escriptura\n";
        return false;
    }
    // Escribir wiring
    for (char c : r.wiring) out << c;
    out << "\n";
    // Escribir notch
    out << r.notch << "\n";
    return true;
}

 
