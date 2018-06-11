#include "Sintetizador.h"

Sintetizador::Sintetizador(){
	
}

char *Sintetizador::sintetizar(char *codigoFuente) {
	this->codigoFuente = codigoFuente;
	return codigoFuente;
	//ACORDARSE DE METER UN char(0) AL FINAL DE LA CADENA
}

/*
string postfija(string e) {
    string r; // r = "";
    for (int i = 0; e[i] != '\0'; ++i) {
        if ((e[i] >= 0 && e[i] <= 9) || (e[i] >= 'a' && e[i] <= 'z') || e[i] >= 'A' && e[i] <= 'Z') {
            r += (e[i]);   // los numeros siempre pasan a la expresion posfija
        } else {
            if (e[i] != ')') {     // Entran operadores. ^ * / + - (
                bool desapilar = true;
                while (desapilar) {
                    //empila si no hay operadores, hay un operador menor o tiene la maxima prioridad
                    if (p.esVacia() || e[i] == '(' || e[i] == '^' || prioridad(e[i]) > prioridad(p.peek())) {
                        p.push(e[i]);
                        desapilar = false;
                    } else {
                        if (prioridad(e[i]) <= prioridad(p.peek())) {
                            r += p.pop();
                            desapilar = true;
                        }
                    }
                }
            } else {       // es un ')'
                while (p.peek() != '(')
                    r += p.pop();
                p.pop();
            }
        }
    }

    while (!p.esVacia())
        r += p.pop();

    return r;
}

int prioridad(char c) {
    if (c == '^')
        return 3;
    if (c == '*' || c == '/')
        return 2;
    if (c == '+' || c == '-')
        return 1;
    if (c == '(')       //menor prioridad
        return 0;
    return 10;
}
 */
