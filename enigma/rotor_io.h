#pragma once
#include "rotor.h"
#include <string>

// Carga un rotor desde fichero:
//  - Primera línea: 26 letras mayúsculas únicas (wirings).
//  - Segunda línea (opcional): notch (una letra). Si falta, notch='Z'.
// Devuelve true si ok, false si error (imprime mensaje [ERROR])
bool loadRotor(const std::string& filename, Rotor& r);

// Guarda un rotor en fichero (mismas dos líneas).
// Devuelve true si ok, false si error (imprime mensaje [ERROR])
bool saveRotor(const std::string& filename, const Rotor& r);

// Función para que main.cpp también valide permutaciones
bool validateWiring(const std::string& s);
