#include "rotor_io.h"
#include "enigma.h"
#include "message_io.h"
#include <iostream>

int main() {
    // Cargar rotores iniciales
    Rotor r1, r2, r3;
    if (!loadRotor("Rotor1.txt", r1) ||
        !loadRotor("Rotor2.txt", r2) ||
        !loadRotor("Rotor3.txt", r3)) {
        std::cerr << "[ERROR] Fallo en la carga de uno o mas rotores. Surt.\n";
        return 1;
    }

    // Inicializar plugboard como identidad
    char plugboard[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; ++i)
        plugboard[i] = 'A' + i;

    // Definir intercambios manuales (ejemplo A<->M, F<->Z)
    plugboard[letterToIndex('A')] = 'M';
    plugboard[letterToIndex('M')] = 'A';
    plugboard[letterToIndex('F')] = 'Z';
    plugboard[letterToIndex('Z')] = 'F';

    while (true) {
        std::cout << "\n=== MAQUINA ENIGMA ===\n"
            << "1. Xifrar missatge\n"
            << "2. Desxifrar missatge\n"
            << "3. Editar rotors\n"
            << "4. Sortir\n"
            << "Tria una opcio: ";
        int opt;
        if (!(std::cin >> opt)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cerr << "[ERROR] Entrada no valida.\n";
            continue;
        }

        if (opt == 4) {
            std::cout << "Adeu!\n";
            break;
        }

        switch (opt) {
        case 1: {
            char a, b, c;
            std::cout << "Posicio inicial R1 (A..Z): "; std::cin >> a;
            std::cout << "Posicio inicial R2 (A..Z): "; std::cin >> b;
            std::cout << "Posicio inicial R3 (A..Z): "; std::cin >> c;
            r1.position = letterToIndex(a);
            r2.position = letterToIndex(b);
            r3.position = letterToIndex(c);
            if (encryptFile("Missatge.txt", "Xifrat.txt", r1, r2, r3, plugboard))
                std::cout << "[OK] Missatge xifrat a Xifrat.txt\n";
            break;
        }
        case 2: {
            char a, b, c;
            std::cout << "Posicio inicial R1 (A..Z): "; std::cin >> a;
            std::cout << "Posicio inicial R2 (A..Z): "; std::cin >> b;
            std::cout << "Posicio inicial R3 (A..Z): "; std::cin >> c;
            r1.position = letterToIndex(a);
            r2.position = letterToIndex(b);
            r3.position = letterToIndex(c);
            if (decryptFile("Xifrat.txt", "Desxifrat.txt", r1, r2, r3, plugboard))
                std::cout << "[OK] Missatge desxifrat a Desxifrat.txt\n";
            break;
        }
        case 3: {
            int idx;
            std::cout << "Quin rotor vols editar (1..3)? "; std::cin >> idx;
            if (idx < 1 || idx > 3) {
                std::cerr << "[ERROR] Índex fora de rang.\n";
                break;
            }
            Rotor* rp = (idx == 1 ? &r1 : idx == 2 ? &r2 : &r3);
            std::string wiring;
            char notch;
            std::cout << "Nova permutacio (26 lletres A..Z): ";
            std::cin >> wiring;
            std::cout << "Nova notch (A..Z): ";
            std::cin >> notch;
            if (!validateWiring(wiring) || notch < 'A' || notch > 'Z') {
                std::cerr << "[ERROR] Dades no valides.\n";
            }
            else {
                for (int i = 0; i < ALPHABET_SIZE; ++i)
                    rp->wiring[i] = wiring[i];
                rp->notch = notch;
                rp->position = 0;
                std::string fname = "Rotor" + std::to_string(idx) + ".txt";
                if (saveRotor(fname, *rp))
                    std::cout << "[OK] " << fname << " actualitzat\n";
            }
            break;
        }
        default:
            std::cerr << "[ERROR] Opcio desconeguda.\n";
        }
    }

    return 0;
}
