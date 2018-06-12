#include "Analizador.cpp"
#include "Sintetizador.cpp"

#include <fstream>

FILE *compilar(FILE *documento){
	Analizador A;
    Sintetizador S;
	fseek(documento, 0, SEEK_END);
    char codigoFuente[ftell(documento) + 1];
    rewind(documento);
    tipo i = 0;
    char caracter;
    while ((caracter = fgetc(documento)) != EOF)
    	if (caracter > 32)
        	codigoFuente[i++] = caracter;
    codigoFuente[i] = 0;
    rewind(documento);
    if(!A.analizar(codigoFuente))
    	return NULL;
    FILE *salida = NULL;
    fputs (S.sintetizar(codigoFuente), salida);
    return salida;
}
