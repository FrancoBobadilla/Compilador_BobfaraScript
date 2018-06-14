#ifndef SINTETIZADOR_H
#define SINTETIZADOR_H

#define tipo long int

#include "Pila.h"

class Sintetizador {
private:
	
	char *codigoFuente;
	
	char *codigoCompilado;
    
    tipo finComp;
    
    int prioridad(char);
    
    char *postfija(char *, tipo);
    
    void agregar(char);
    
public:
	
	Sintetizador ();
	
	char *sintetizar(char *);
};


#endif //SINTETIZADOR_H
