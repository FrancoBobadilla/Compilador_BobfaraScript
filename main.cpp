#include <iostream>
#include <fstream>
#include "Analizador.cpp"

using namespace std;

int main() {
	/*
	int datos[5]={'a','b',0,'d','e'};
	for(int i = 0; i<=5;i++)
		cout<<int(datos[i])<<endl;
	FILE *doc = fopen("CO.txt", "w");
	fputs (datos, doc);
    fclose (doc);/**/
    
    /*
    FILE *doc = fopen("CF.txt", "r");
    fseek(doc, 0, SEEK_END);
    long int tamanio = ftell(doc);
    rewind(doc);
    char cod[tamanio+1];
    long int i = 0;
    char c;
    while ((c = fgetc(doc)) != EOF)
        cod[i++] = c;
    tamanio = i;
    cod[tamanio]=0;
    rewind(doc);
    Analizador A;
    if (!A.analizar(cod)) cout << "DES";
    cout << "APROBADO" << endl << endl;/**/
    
    system("pause");
}
