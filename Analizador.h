#ifndef UNTITLED_ANALIZADOR_H
#define UNTITLED_ANALIZADOR_H

#define tipo bool

#include <fstream>

class Analizador {
private:

    FILE *A;

    tipo lexico();

    tipo sintactico();

    tipo semantico();


    tipo Programa();

    tipo bloque();

    tipo otra_sentencia();

    tipo sentencia();

    tipo asignacion();

    tipo expresion();

    tipo mas_terminos();

    tipo termino();

    tipo mas_factores();

    tipo factor();

    tipo lectura();

    tipo escritura();

    tipo variable();

    tipo constante();

    tipo vacio();


    bool noTerminal(int, int);

public:
    Analizador(FILE *);

    tipo analizar();

};

#endif
