#ifndef ANALIZADOR_H
#define ANALIZADOR_H

#define tipo long int

class Analizador{
private:
	
    char *codigoFuente;


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
	
    Analizador();

    bool analizar(char *);

};

#endif //ANALIZADOR_H
