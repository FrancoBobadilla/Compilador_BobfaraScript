#ifndef SINTETIZADOR_H
#define SINTETIZADOR_H

#define tipo long int

#include "Pila.h"

class Sintetizador {
private:
	
	char *codigoFuente;
    
    
public:
	
	Sintetizador ();
	
	char *sintetizar(char *);
};


#endif //SINTETIZADOR_H
