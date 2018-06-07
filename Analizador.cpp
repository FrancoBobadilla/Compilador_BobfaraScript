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
    int c;
    while ((c = fgetc(this->A)) != EOF) {
        if (c > 32) //no tiene en cuenta espacios, saltos de linea, etc
            if ((c < 'a' || c > 'z')
                && (c < '0' || c > '9')
                && c != '+' && c != '-' && c != '*' && c != '/' && c != '%'
                && c != '='
                && c != '(' && c != ')'
                && c != ';'
                && c != '{' && c != '}'
                && c != 'M' && c != 'R' && c != 'W')
                return false;
    }
    return true;
}

tipo Analizador::sintactico() {
    return Programa();
}

tipo Analizador::semantico() {
    return true;
}

tipo Analizador::Programa() {
    return (noTerminal('M', 'M') && noTerminal('{', '{') && bloque() && noTerminal('}', '}'));
}

tipo Analizador::bloque() {
    return (sentencia() && otra_sentencia());
}

tipo Analizador::otra_sentencia() {
    return (noTerminal(';', ';') && sentencia() && otra_sentencia())
           || (vacio());
}

tipo Analizador::sentencia() {
    return (asignacion())
           || (lectura())
           || (escritura());
}

tipo Analizador::asignacion() {
    return (variable() && noTerminal('=', '=') && expresion());
}

tipo Analizador::expresion() {
    return (termino() && mas_terminos());
}

tipo Analizador::mas_terminos() {
    return (noTerminal('+', '+') && termino() && mas_terminos())
           || (noTerminal('-', '-') && termino() && mas_terminos())
           || (vacio());
}

tipo Analizador::termino() {
    return (factor() && mas_factores());
}

tipo Analizador::mas_factores() {
    return (noTerminal('*', '*') && factor() && mas_factores())
           || (noTerminal('/', '/') && factor() && mas_factores())
           || (noTerminal('%', '%') && factor() && mas_factores())
           || (vacio());
}

tipo Analizador::factor() {
    return expresion()
           || variable()
           || constante();
}

tipo Analizador::lectura() {
    return noTerminal('R', 'R') && variable();
}

tipo Analizador::escritura() {
    return noTerminal('W', 'W') && variable();
}

tipo Analizador::variable() {
    return noTerminal('a', 'z');
}

tipo Analizador::constante() {
    return noTerminal('0', '9');
}

tipo Analizador::vacio() {
    return true;
}

/*
 * funcion que toma dos caracteres y retorna "true" si un caracter leido en el documento A esta dentro del rango que definen las dos entradas
 */
bool Analizador::noTerminal(int desde, int hasta) {
    if (hasta == desde) return desde == fgetc(this->A);
    int i;
    if (hasta < desde) {
        i = desde;
        desde = hasta;
        hasta = i;
    }
    for (i = desde/*redundante, porque i ya vale desde*/; i < hasta; i++)
        if (i == fgetc(this->A))
            return true;
    return false;
}