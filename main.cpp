#include <iostream>
#include <fstream>
#include "Compilador.cpp"

using namespace std;

int main() {
	if(!compilar(fopen("CF.txt", "r"), fopen("CO.txt", "w")))
		cout<<endl<<"ERROR DE COMPILACION"<<endl<<endl;
	else
		cout<<endl<<"COMPILADO EXITOSAMENTE"<<endl<<endl;
    system("pause");
}
