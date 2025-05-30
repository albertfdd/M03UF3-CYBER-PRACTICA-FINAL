#include "message_io.h"
#include "enigma.h"
#include <fstream>
#include <sstream>

static bool readAll(const std::string& filename, std::string& out) {
    std::ifstream in(filename);
    if (!in) return false;
    std::ostringstream ss;
    ss << in.rdbuf();
    out = ss.str();
    return true;
}

static bool writeAll(const std::string& filename, const std::string& text) {
    std::ofstream out(filename);
    if (!out) return false;
    out << text;
    return true;
}

bool encryptFile(const std::string& inFile,
    const std::string& outFile,
    Rotor r1, Rotor r2, Rotor r3,
    char plugboard[]) {
    std::string raw;
    if (!readAll(inFile, raw)) {
        std::cerr << "[ERROR] No s'ha pogut llegir " << inFile << "\n";
        return false;
    }

    std::string norm = normalize(raw);
    std::string cipher;

    for (char ch : norm) {
        if (ch == ' ') {
            cipher += ' ';
            continue;
        }

        stepRotors(r1, r2, r3);

        // Plugboard entrada
        char c = plugboard[letterToIndex(ch)];

        // Rotores hacia adelante
        c = mapForward(r1, mapForward(r2, mapForward(r3, c)));

        // Reflector
        c = REFLECTOR[letterToIndex(c)];

        // Rotores hacia atrás
        c = mapBackward(r3, mapBackward(r2, mapBackward(r1, c)));

        // Plugboard salida
        c = plugboard[letterToIndex(c)];

        cipher += c;
    }

    // Reagrupar en bloques de 5
    std::string out;
    for (size_t i = 0; i < cipher.size(); ++i) {
        if (i > 0 && i % 5 == 0) out += ' ';
        out += cipher[i];
    }

    if (!writeAll(outFile, out)) {
        std::cerr << "[ERROR] No s'ha pogut escriure " << outFile << "\n";
        return false;
    }

    return true;
}



bool decryptFile(const std::string& inFile,
    const std::string& outFile,
    Rotor r1, Rotor r2, Rotor r3,
    char plugboard[]) {
    std::string raw;
    if (!readAll(inFile, raw)) {
        std::cerr << "[ERROR] No s'ha pogut llegir " << inFile << "\n";
        return false;
    }

    std::string packed;
    for (char ch : raw)
        if (ch != ' ' && std::isalpha(ch)) packed += ch;

    std::string plain;

    for (char ch : packed) {
        stepRotors(r1, r2, r3);

        // Plugboard entrada
        char c = plugboard[letterToIndex(ch)];

        // Rotores hacia adelante
        c = mapForward(r1, mapForward(r2, mapForward(r3, c)));

        // Reflector
        c = REFLECTOR[letterToIndex(c)];

        // Rotores hacia atrás
        c = mapBackward(r3, mapBackward(r2, mapBackward(r1, c)));

        // Plugboard salida
        c = plugboard[letterToIndex(c)];

        plain += c;
    }

    if (!writeAll(outFile, plain)) {
        std::cerr << "[ERROR] No s'ha pogut escriure " << outFile << "\n";
        return false;
    }

    return true;
}


