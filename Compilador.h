#ifndef COMPILADOR_H
#define COMPILADOR_H

#include <fstream>
#include "Pila.h"

#define tipo long int

class Compilador {
private:

    char *codigoFuente;

    tipo *posicionesDocumentoFuente;

    char *codigoCompilado;

    tipo finComp;

    bool analizar();

    bool lexico();

    bool sintactico();

    bool semantico();

    tipo Programa(tipo);

    tipo bloque(tipo);

    tipo otra_sentencia(tipo);

    tipo sentencia(tipo);

    tipo asignacion(tipo);

    tipo expresion(tipo);

    tipo mas_terminos(tipo);

    tipo termino(tipo);

    tipo mas_factores(tipo);

    tipo factor(tipo);

    tipo lectura(tipo);

    tipo escritura(tipo);

    tipo variable(tipo);

    tipo constante(tipo);

    char *sintetizar();

    int prioridad(char);

    char *postfija(char *, tipo);

    void agregarComp(char);

    void agregarComp(char *);

    void agregarLog(char);

    void agregarLog(char *);

public:

    Compilador();

    bool compilar(FILE *, FILE *);
};


#endif //COMPILADOR_H
