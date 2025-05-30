#pragma once
#include <string>
#include <array>
#include <iostream>

// Constantes de la máquina
constexpr int ALPHABET_SIZE = 26;
using Wiring = std::array<char, ALPHABET_SIZE>;

// Prototipos de pruebas informales
void printRotor(const std::string& name, const Wiring& w, char notch, int pos);
