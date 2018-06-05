//
// Created by FrancoBobadilla on 5/6/2018.
//

#include "Analizador.h"

#define tipo bool

Analizador::Analizador(FILE *A) {
    this->A = A;
}

tipo Analizador::analizar() {
    return lexico() && sintactico() && semantico();
}

tipo Analizador::lexico() {
    char c;

    while ((c = fgetc(A)) != EOF) {
        if (c > 32) //no tiene en cuenta espacios, saltos de linea, etc
            if ((c < 'a' || c > 'z')
                && (c < '0' || c > '9')
                && c != '+' && c != '-' && c != '*' && c != '/' && c != '%'
                && c != '='
                && c != '(' && c != ')'
                && c != ';'
                && c != '{' && c != '}'
                && c != 'M' && c != 'R' && c != 'W')
                return 0;
    }
    return 1;
}

tipo Analizador::sintactico() {
    return 1;
}

tipo Analizador::semantico() {
    return 1;
}
