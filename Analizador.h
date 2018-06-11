#ifndef UNTITLED_ANALIZADOR_H
#define UNTITLED_ANALIZADOR_H

#include <fstream>

#define tipo long int

class Analizador {
private:
	
    int *codigoFuente;

    tipo tamanio;


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


public:
	
    Analizador(FILE *);

    bool analizar();

};

#endif //UNTITLED_ANALIZADOR_H
