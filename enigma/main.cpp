#include "enig.h"
#include "rotor_io.h"

void printRotor(const std::string& name, const Wiring& w, char notch, int pos) {
    std::cout << name << ": wiring=";
    for (char c : w) std::cout << c;
    std::cout << ", notch=" << notch
        << ", pos=" << static_cast<char>('A' + pos) << "\n";
}

int main() {
    Rotor r1, r2, r3;
    loadRotor("Rotor1.txt", r1);
    loadRotor("Rotor2.txt", r2);
    loadRotor("Rotor3.txt", r3);

    printRotor("Rotor1", r1.wiring, r1.notch, r1.position);
    printRotor("Rotor2", r2.wiring, r2.notch, r2.position);
    printRotor("Rotor3", r3.wiring, r3.notch, r3.position);

    // Ejemplo de edición (descomentar para probar)
//    r2.wiring = {/* … alguna permutación válida … */};
//    r2.notch = 'Q';
//    saveRotor("Rotor2.txt", r2);

    return 0;
}
