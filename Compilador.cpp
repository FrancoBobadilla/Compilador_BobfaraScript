#include "Compilador.h"

Compilador::Compilador(){
	
}

FILE *Compilador::compilar(FILE *documento){
	fseek(documento, 0, SEEK_END);
    char codigoFuente[ftell(documento) + 1];
    rewind(documento);
    tipo i = 0;
    char caracter;
    while ((caracter = fgetc(documento)) != EOF)
    	if (caracter > 32)
        	codigoFuente[i++] = caracter;
    codigoFuente[i + 1] = 0;
    rewind(documento);
    if(!this->A.analizar(codigoFuente))
    	return NULL;
    FILE *salida;
    fputs (S.sintetizar(codigoFuente), salida);
    return salida;
}
