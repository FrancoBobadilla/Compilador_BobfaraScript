#include "Analizador.cpp"
#include "Sintetizador.cpp"

#include <fstream>

using namespace std;

bool compilar(FILE *documentoFuente, FILE *documentoCompilado){
	Analizador A;
    Sintetizador S;
	fseek(documentoFuente, 0, SEEK_END);
    char codigoFuente[ftell(documentoFuente) + 1];
    rewind(documentoFuente);
    tipo i = 0;
    char caracter;
    while ((caracter = fgetc(documentoFuente)) != EOF)
    	if (caracter > 32)
        	codigoFuente[i++] = caracter;
    codigoFuente[i] = 0;
    rewind(documentoFuente);
    if(A.analizar(codigoFuente)){
    	fputs (S.sintetizar(codigoFuente), documentoCompilado);
    	return true;
	}
	return false;    	
}
