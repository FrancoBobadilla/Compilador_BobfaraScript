#include "Sintetizador.h"

Sintetizador::Sintetizador() {

}

char *Sintetizador::sintetizar(char *codigoFuente) {
    this->codigoFuente = codigoFuente;
    return codigoFuente;
    //ACORDARSE DE METER UN char(0) AL FINAL DE LA CADENA
}

int Sintetizador::prioridad(char c) {
    if (c == '*' || c == '/' || c == '%')
        return 2;
    if (c == '+' || c == '-')
        return 1;
    if (c == '(')       //menor prioridad
        return 0;
    return 10;
}

char *Sintetizador::postfija(char *e, tipo tamanio) {
    char *r = new char [tamanio]; // la cadena posfija nunca va a ser mas grande que la infija
    Pila<char> p;
    tipo posicion = 0;
    tipo i;
    for (i = 0; e[i] != '\0'; ++i) {
        if ((e[i] >= '0' && e[i] <= '9') || (e[i] >= 'a' && e[i] <= 'z')) {
            r[posicion++] = e[i];   // los numeros siempre pasan a la expresion posfija
        } else {
            if (e[i] != ')') {      // Entran operadores. ^ * / + - (
                bool desapilar = true;
                while (desapilar) { //empila si no hay operadores, hay un operador menor o tiene la maxima prioridad
                    if (p.esVacia() || e[i] == '(' || prioridad(e[i]) > prioridad(p.peek())) {
                        p.push(e[i]);
                        desapilar = false;
                    } else {
                        if (prioridad(e[i]) <= prioridad(p.peek())) {
                            r[posicion++] = p.pop();
                            desapilar = true;
                        }
                    }
                }
            } else {       // es un ')'
                while (p.peek() != '(')
                    r[posicion++] = p.pop();
                p.pop();
            }
        }
    }
    while (!p.esVacia())
        r[posicion++] = p.pop();
    return r;
}
