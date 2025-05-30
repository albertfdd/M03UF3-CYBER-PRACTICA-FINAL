#pragma once
#include "rotor.h"
#include <string>

// Carga un rotor desde fichero:
//  - Primera l�nea: 26 letras may�sculas �nicas (wirings).
//  - Segunda l�nea (opcional): notch (una letra). Si falta, notch='Z'.
// Devuelve true si ok, false si error (imprime mensaje [ERROR])
bool loadRotor(const std::string& filename, Rotor& r);

// Guarda un rotor en fichero (mismas dos l�neas).
// Devuelve true si ok, false si error (imprime mensaje [ERROR])
bool saveRotor(const std::string& filename, const Rotor& r);

// Funci�n para que main.cpp tambi�n valide permutaciones
bool validateWiring(const std::string& s);
