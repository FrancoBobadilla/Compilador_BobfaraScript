#include "Analizador.h"


Analizador::Analizador(FILE *A) {
    if (A == NULL)
        throw 1;
    fseek(A, 0, SEEK_END);
    this->tamanio = ftell(A);
    rewind(A);
    codigoFuente = new int[tamanio];
    tipo i = 0;
    int c;
    while ((c = fgetc(A)) != EOF)
        if (c > 32)
            codigoFuente[i++] = c;
    rewind(A);
    this->tamanio = i;
}


bool Analizador::analizar() {
    return lexico() && sintactico() && semantico();
}


bool Analizador::lexico() {
    int i, c;
    for (i = 0; i < tamanio; i++) {
        c = this->codigoFuente[i];
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

bool Analizador::sintactico() {
	if(Programa(0) > 0)
		return true;
	return false;
}

bool Analizador::semantico() {
    return true;
}


tipo Analizador::Programa(tipo posicion) {
	if(codigoFuente[posicion++] != 'M')	//se evalua si "da error"
		return 0;
	if(codigoFuente[posicion++] != '{')
		return 0;
	if(!(posicion = bloque(posicion)))
		return 0;
	if(codigoFuente[posicion++] != '}')
		return 0;
    return posicion;
}

tipo Analizador::bloque(tipo posicion) {
    if(!(posicion = sentencia(posicion)))
    	return 0;
    if(!(posicion = otra_sentencia(posicion)))
    	return 0;
    return posicion;
}

tipo Analizador::otra_sentencia(tipo posicion) {
    while(codigoFuente[posicion] == ';')
    	if(!(posicion = sentencia(++posicion)))	//cuando se encuentre un ; debe haber necesariamente otra sentencia
    		return 0;
    return posicion;
}

tipo Analizador::sentencia(tipo posicion) {
    unsigned long int posicionTmp;
    if (posicionTmp = asignacion(posicion))
    	return posicionTmp;
    if (posicionTmp = lectura(posicion))
    	return posicionTmp;
    if (posicionTmp = escritura(posicion))
    	return posicionTmp;
    return 0;
}

tipo Analizador::asignacion(tipo posicion) {
    if(!(posicion = variable(posicion)))
    	return 0;
    if(codigoFuente[posicion++] != '=')
    	return 0;
    if(!(posicion = expresion(posicion)))
    	return 0;
    return posicion;
}

tipo Analizador::expresion(tipo posicion) {
    if(!(posicion = termino(posicion)))
    	return 0;
    if(!(posicion = mas_terminos(posicion)))
    	return 0;
    return posicion;
}

tipo Analizador::mas_terminos(tipo posicion) {
    while(codigoFuente[posicion] == '+' || codigoFuente[posicion] == '-')
    	if(!(posicion = termino(++posicion)))	//cuando se encuentre un + o - debe haber necesariamente otro termino
    		return 0;
    return posicion;
}

tipo Analizador::termino(tipo posicion) {
    if(!(posicion = factor(posicion)))
    	return 0;
    if(!(posicion = mas_factores(posicion)))
    	return 0;
    return posicion;
}

tipo Analizador::mas_factores(tipo posicion) {
    while(codigoFuente[posicion] == '*' || codigoFuente[posicion] == '/' || codigoFuente[posicion] == '%')
    	if(!(posicion = factor(++posicion)))	//cuando se encuentre un *, / o % debe haber necesariamente otro factor
    		return 0;
    return posicion;
}

tipo Analizador::factor(tipo posicion) {
    tipo posicionTmp = posicion;
	if(codigoFuente[posicionTmp++] == '('){
		if(!(posicionTmp = expresion(posicionTmp)))
			return 0;
		if(codigoFuente[posicionTmp++] != ')')
			return 0;
		return posicionTmp;
	}
	if(posicionTmp = variable(posicion))
		return posicionTmp;
	if(posicionTmp = constante(posicion))
		return posicionTmp;
	return 0;    
}

tipo Analizador::lectura(tipo posicion) {
    if(codigoFuente[posicion++] != 'R')
		return 0;
	if(!(posicion = variable(posicion)))
		return 0;
	return posicion;
}

tipo Analizador::escritura(tipo posicion) {
    if(codigoFuente[posicion++] != 'W')
		return 0;
	if(!(posicion = variable(posicion)))
		return 0;
	return posicion;
}

tipo Analizador::variable(tipo posicion) {
    tipo desde = 'a';
    while (desde++ <= 'z')
    	if (codigoFuente[posicion] == desde)
        	return ++posicion;
    return 0;
}

tipo Analizador::constante(tipo posicion) {
	tipo desde = '0';
    while (desde++ <= '9')
    	if (codigoFuente[posicion] == desde)
        	return ++posicion;
    return 0;
}
