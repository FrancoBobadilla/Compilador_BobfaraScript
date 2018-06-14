#include "Sintetizador.h"

using namespace std;

Sintetizador::Sintetizador() {
	finComp = 0;
	codigoCompilado = new char[9]; //.CODE\0END (el programa mas pequeño posible)
}

char *Sintetizador::sintetizar(char *codigoFuente) {
    this->codigoFuente = codigoFuente;
    tipo i, j, k;
    
    //FASE 1
    for(i = 0; codigoFuente[i]; i++){
    	if(codigoFuente[i] == '{' || codigoFuente[i] == '}')
			codigoFuente[i] = ';';

    	if(codigoFuente[i] == '='){
    		codigoFuente [i] = codigoFuente [i - 1];
    		codigoFuente [i - 1] = '=';
    		i++;
    		for(j = 0; codigoFuente[i + j] != ';'; j++);
    		char *aux = postfija(codigoFuente + i, j);
    		for(k = 0; k < j; k++){
    			if(aux[k] == '#')
    				codigoFuente[i + k] = ';';
    			else
    				codigoFuente[i + k] = aux[k];
			}
		}
		
	}
	
	//FASE 2
	i = 0;
    while(codigoFuente[i]){
    	switch (codigoFuente[i]){
			case 'M':
				agregar('.');
    			agregar('C');
    			agregar('O');
    			agregar('D');
    			agregar('E');
    			agregar('\n');
    			i++;
    			break;
    		case 'R':
    			agregar('I');
    			agregar('N');
    			agregar('P');
    			agregar('U');
    			agregar('T');
    			agregar(' ');
    			i++;
    			agregar(codigoFuente[i]);
    			agregar('\n');
    			i++;
    			break;
    		case 'W':
    			agregar('O');
    			agregar('U');
    			agregar('T');
    			agregar('P');
    			agregar('U');
    			agregar('T');
    			agregar(' ');
    			i++;
    			agregar(codigoFuente[i]);
    			agregar('\n');
    			i++;
    			break;
    		case '=':
    			i++;
    			agregar('P');
    			agregar('U');
    			agregar('S');
    			agregar('H');
    			agregar('A');
    			agregar(' ');
    			agregar(codigoFuente[i]);
    			agregar('\n');
    			i++;
    			for(j = i; codigoFuente[j] != ';'; j++){
    				switch (codigoFuente[j]){
    					case '+':
    						agregar('A');
    						agregar('D');
    						agregar('D');
    						agregar('\n');
    						break;
    					case '-':
    						agregar('N');
    						agregar('E');
    						agregar('G');
    						agregar('\n');
    						agregar('A');
    						agregar('D');
    						agregar('D');
    						agregar('\n');
    						break;
    					case '*':
    						agregar('M');
    						agregar('U');
    						agregar('L');
    						agregar('\n');
    						break;
    					case '/':
    						agregar('D');
    						agregar('I');
    						agregar('V');
    						agregar('\n');
    						break;
    					case '%':
    						agregar('M');
    						agregar('O');
    						agregar('D');
    						agregar('\n');
    					default:
    						if('a' <= codigoFuente[j] && codigoFuente[j] <= 'z'){
    							agregar('P');
    							agregar('U');
    							agregar('S');
    							agregar('H');
    							agregar('A');
    							agregar(' ');
    							agregar(codigoFuente[j]);
    							agregar('\n');
    							agregar('L');
    							agregar('O');
    							agregar('A');
    							agregar('D');
    							agregar('\n');
							}else{
								if('0' <= codigoFuente[j] && codigoFuente[j] <= '9'){
									agregar('P');
    								agregar('U');
    								agregar('S');
    								agregar('H');
    								agregar('C');
    								agregar(' ');
    								agregar(codigoFuente[j]);
    								agregar('\n');
								}
							}
							break;
					}
				}
				agregar('S');
    			agregar('T');
    			agregar('O');
    			agregar('R');
    			agregar('E');
    			agregar('\n');
    			break;
    		default:
    			i++;
    			break;
		}		
	}
	agregar('E');
    agregar('N');
    agregar('D');
    agregar(0);
	return codigoCompilado;
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
    for (i = 0; i<tamanio; ++i) {
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
        
    for(;posicion < tamanio; posicion++)
    	r[posicion] = '#';
    	
    return r;
}

void Sintetizador::agregar(char nuevo){
	if(!codigoCompilado[finComp]){
		char *nuevoCodigoCompilado = new char[finComp * 2];
		tipo i;
		for(i = 0; codigoCompilado[i]; i++)
			nuevoCodigoCompilado[i] = codigoCompilado[i];
		codigoCompilado = nuevoCodigoCompilado;
	}
	codigoCompilado[finComp] = nuevo;
	finComp++;
}
