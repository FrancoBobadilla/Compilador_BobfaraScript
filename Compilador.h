//
// Created by FrancoBobadilla on 11/6/2018.
//

#ifndef UNTITLED_COMPILADOR_H
#define UNTITLED_COMPILADOR_H

#include "Analizador.cpp"
#include "Sintetizador.cpp"

#include <fstream>

class Compilador {
private:
    Analizador A;

    Sintetizador S;

public:
    Compilador();

    FILE *compilar(FILE *);

};

#endif //UNTITLED_COMPILADOR_H
