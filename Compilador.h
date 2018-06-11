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

    int *codigoFuente;
    tipo tamanioFuente;

    int *codigoCompilado;
    tipo tamanioCompilado;

public:
    Compilador(FILE *);

    FILE *compilar();

};

#endif //UNTITLED_COMPILADOR_H
