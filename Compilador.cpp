#include "Compilador.h"
//#include <iostream>

//using namespace std;

Compilador::Compilador() {

}

bool Compilador::compilar(FILE *documentoFuente, FILE *documentoCompilado) {
    if (documentoFuente == NULL || documentoCompilado == NULL)
        throw 1;
    fseek(documentoFuente, 0, SEEK_END);
    this->codigoFuente = new char[ftell(documentoFuente)];
    this->codigoCompilado = new char[9]; //.CODE\nEND (el programa mas peque�o posible)
    this->finComp = 0;
    bool salida = false;
    rewind(documentoFuente);
    //cout<<"DOCUMENTO LEIDO"<<endl<<endl;
    tipo i = 0;
    char caracter;
    while ((caracter = fgetc(documentoFuente)) != EOF)
        //cout<<caracter;
        if (caracter > 32)
            this->codigoFuente[i++] = caracter;
    //cout<<endl<<endl<<endl;
    this->codigoFuente[i] = 0;
    rewind(documentoFuente);
    if (analizar()) {
        fputs(sintetizar(), documentoCompilado);
        salida = true;
    }
    delete this->codigoFuente;
    return salida;
}

bool Compilador::analizar() {
    return lexico() && sintactico() && semantico();
}

bool Compilador::lexico() {
    tipo i;
    char c;
    for (i = 0; c = this->codigoFuente[i]; i++) {
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

bool Compilador::sintactico() {
    return Programa(0);
}

bool Compilador::semantico() {
    char variablesDeclaradas[26];
    char c;
    tipo i, j, k;
    for (i = 0, j = 0; c = this->codigoFuente[i]; i++) {
        if (c == 'R')
            variablesDeclaradas[j++] = codigoFuente[++i];
        if ('a' <= c && c <= 'z') {
            for (k = 0; k < j; k++) {
                if (variablesDeclaradas[k] == c) {
                    k = j + 1;
                }
            }
            if (j == k)
                return 0;
        }
        if (c == '/' || c == '%')
            if (codigoFuente[++i] == '0')
                return 0;
    }
    return 1;
}

tipo Compilador::Programa(tipo posicion) {
    if (this->codigoFuente[posicion++] != 'M')    //se evalua si "da error"
        return 0;
    if (this->codigoFuente[posicion++] != '{')
        return 0;
    if (!(posicion = bloque(posicion)))
        return 0;
    if (this->codigoFuente[posicion++] != '}')
        return 0;
    if (this->codigoFuente[posicion] != 0)
        return 0;
    return posicion;
}

tipo Compilador::bloque(tipo posicion) {
    if (!(posicion = sentencia(posicion)))
        return 0;
    if (!(posicion = otra_sentencia(posicion)))
        return 0;
    return posicion;
}

tipo Compilador::otra_sentencia(tipo posicion) {
    while (this->codigoFuente[posicion] == ';')
        if (!(posicion = sentencia(++posicion)))    //cuando se encuentre un ; debe haber necesariamente otra sentencia
            return 0;
    return posicion;
}

tipo Compilador::sentencia(tipo posicion) {
    unsigned long int posicionTmp;
    if (posicionTmp = asignacion(posicion))
        return posicionTmp;
    if (posicionTmp = lectura(posicion))
        return posicionTmp;
    if (posicionTmp = escritura(posicion))
        return posicionTmp;
    return 0;
}

tipo Compilador::asignacion(tipo posicion) {
    if (!(posicion = variable(posicion)))
        return 0;
    if (this->codigoFuente[posicion++] != '=')
        return 0;
    if (!(posicion = expresion(posicion)))
        return 0;
    return posicion;
}

tipo Compilador::expresion(tipo posicion) {
    if (!(posicion = termino(posicion)))
        return 0;
    if (!(posicion = mas_terminos(posicion)))
        return 0;
    return posicion;
}

tipo Compilador::mas_terminos(tipo posicion) {
    while (this->codigoFuente[posicion] == '+' || codigoFuente[posicion] == '-')
        if (!(posicion = termino(++posicion)))    //cuando se encuentre un + o - debe haber necesariamente otro termino
            return 0;
    return posicion;
}

tipo Compilador::termino(tipo posicion) {
    if (!(posicion = factor(posicion)))
        return 0;
    if (!(posicion = mas_factores(posicion)))
        return 0;
    return posicion;
}

tipo Compilador::mas_factores(tipo posicion) {
    while (this->codigoFuente[posicion] == '*' || codigoFuente[posicion] == '/' || codigoFuente[posicion] == '%')
        if (!(posicion = factor(++posicion)))    //cuando se encuentre un *, / o % debe haber necesariamente otro factor
            return 0;
    return posicion;
}

tipo Compilador::factor(tipo posicion) {
    tipo posicionTmp = posicion;
    if (codigoFuente[posicionTmp++] == '(') {
        if (!(posicionTmp = expresion(posicionTmp)))
            return 0;
        if (this->codigoFuente[posicionTmp++] != ')')
            return 0;
        return posicionTmp;
    }
    if (posicionTmp = variable(posicion))
        return posicionTmp;
    if (posicionTmp = constante(posicion))
        return posicionTmp;
    return 0;
}

tipo Compilador::lectura(tipo posicion) {
    if (this->codigoFuente[posicion++] != 'R')
        return 0;
    if (!(posicion = variable(posicion)))
        return 0;
    return posicion;
}

tipo Compilador::escritura(tipo posicion) {
    if (this->codigoFuente[posicion++] != 'W')
        return 0;
    if (!(posicion = variable(posicion)))
        return 0;
    return posicion;
}

tipo Compilador::variable(tipo posicion) {
    tipo desde = 'a';
    while (desde <= 'z')
        if (this->codigoFuente[posicion] == desde++)
            return ++posicion;
    return 0;
}

tipo Compilador::constante(tipo posicion) {
    tipo desde = '0';
    while (desde <= '9')
        if (this->codigoFuente[posicion] == desde++)
            return ++posicion;
    return 0;
}

char *Compilador::sintetizar() {
    //cout<<"CODIGO FUENTE\n\n<<codigoFuente;
    tipo i, j, k;
    char pusha[] = {"PUSHA "};
    char code[] = {".CODE\n"};
    char input[] = {"INPUT "};
    char output[] = {"OUTPUT "};
    char add[] = {"ADD\n"};
    char negAdd[] = {"NEG\nADD\n"};
    char mul[] = {"MUL\n"};
    char div[] = {"DIV\n"};
    char mod[] = {"MOD\n"};
    char load[] = {"\nLOAD\n"};
    char pushc[] = {"PUSHC "};
    char store[] = {"STORE\n"};
    char end[] = {"END\0"};
    for (i = 0; this->codigoFuente[i]; i++) {
        if (this->codigoFuente[i] == '{' || this->codigoFuente[i] == '}')
            codigoFuente[i] = ';';
        if (this->codigoFuente[i] == '=') {
            this->codigoFuente[i] = this->codigoFuente[i - 1];
            this->codigoFuente[i - 1] = '=';
            i++;
            for (j = 0; this->codigoFuente[i + j] != ';'; j++);
            char *aux = postfija(this->codigoFuente + i, j);
            for (k = 0; k < j; k++) {
                if (aux[k] == '#')
                    this->codigoFuente[i + k] = ';';
                else
                    this->codigoFuente[i + k] = aux[k];
            }
            delete aux;
        }

    }
    //cout<<"CODIGO INTERMEDIO\n\n<<codigoFuente;
    i = 0;
    while (this->codigoFuente[i]) {
        switch (this->codigoFuente[i]) {
            case 'M':
                agregarComp(code);
                i++;
                break;
            case 'R':
                agregarComp(input);
                i++;
                agregarComp(this->codigoFuente[i]);
                agregarComp('\n');
                i++;
                break;
            case 'W':
                agregarComp(output);
                i++;
                agregarComp(this->codigoFuente[i]);
                agregarComp('\n');
                i++;
                break;
            case '=':
                i++;
                agregarComp(pusha);
                agregarComp(this->codigoFuente[i]);
                agregarComp('\n');
                i++;
                for (j = i; this->codigoFuente[j] != ';'; j++) {
                    switch (this->codigoFuente[j]) {
                        case '+':
                            agregarComp(add);
                            break;
                        case '-':
                            agregarComp(negAdd);
                            break;
                        case '*':
                            agregarComp(mul);
                            break;
                        case '/':
                            agregarComp(div);
                            break;
                        case '%':
                            agregarComp(mod);
                        default:
                            if ('a' <= this->codigoFuente[j] && this->codigoFuente[j] <= 'z') {
                                agregarComp(pusha);
                                agregarComp(this->codigoFuente[j]);
                                agregarComp(load);
                            }
                            if ('0' <= this->codigoFuente[j] && this->codigoFuente[j] <= '9') {
                                agregarComp(pushc);
                                agregarComp(this->codigoFuente[j]);
                                agregarComp('\n');
                            }
                            break;
                    }
                }
                agregarComp(store);
                break;
            default:
                i++;
                break;
        }
    }
    agregarComp(end);
    //cout<<"CODIGO COMPILADO\n\n<<codigoCompilado;
    return this->codigoCompilado;
}

int Compilador::prioridad(char c) {
    if (c == '*' || c == '/' || c == '%')
        return 2;
    if (c == '+' || c == '-')
        return 1;
    if (c == '(')       //menor prioridad
        return 0;
    return 10;
}

char *Compilador::postfija(char *e, tipo tamanio) {
    char *r = new char[tamanio]; // la cadena posfija nunca va a ser mas grande que la infija
    Pila<char> p;
    tipo posicion = 0;
    tipo i;
    for (i = 0; i < tamanio; ++i) {
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
    for (; posicion < tamanio; posicion++)
        r[posicion] = '#';
    return r;
}

void Compilador::agregarComp(char nuevo) {
    if (!this->codigoCompilado[this->finComp]) {
        char *nuevoCodigoCompilado = new char[this->finComp * 2];
        tipo i;
        for (i = 0; this->codigoCompilado[i]; i++)
            nuevoCodigoCompilado[i] = this->codigoCompilado[i];
        this->codigoCompilado = nuevoCodigoCompilado;
    }
    codigoCompilado[finComp] = nuevo;
    this->finComp++;
}

void Compilador::agregarComp(char *nuevo) {
    tipo i, j;
    for (i = 0; nuevo[i]; i++, finComp++) {
        if (!this->codigoCompilado[this->finComp]) {
            char *nuevoCodigoCompilado = new char[this->finComp * 2];
            for (j = 0; this->codigoCompilado[j]; j++)
                nuevoCodigoCompilado[j] = this->codigoCompilado[j];
            this->codigoCompilado = nuevoCodigoCompilado;
        }
        codigoCompilado[finComp] = nuevo[i];
    }
}
/*
void Compilador::agregarLog(char nuevo){
	if(!this->consoleLog[this->finLog]){
		char *nuevoCodigoCompilado = new char[this->finLog * 2];
		tipo i;
		for(i = 0; this->consoleLog[i]; i++)
			nuevoCodigoCompilado[i] = this->consoleLog[i];
		this->consoleLog = nuevoCodigoCompilado;
	}
	consoleLog[finLog] = nuevo;
	this->finLog++;
}

void Compilador::agregarLog(char *nuevo){
	tipo i, j;
	for(i = 0; nuevo[i]; i++, finLog++){
		if(!this->consoleLog[this->finComp]){
			char *nuevoCodigoCompilado = new char[this->finLog * 2];
			for(j = 0; this->consoleLog[j]; j++)
				nuevoCodigoCompilado[j] = this->consoleLog[j];
			this->consoleLog = nuevoCodigoCompilado;
		}
		consoleLog[finLog] = nuevo[i];
	}
}/**/
