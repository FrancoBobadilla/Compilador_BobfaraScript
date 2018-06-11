#include <iostream>
#include <fstream>
#include "Analizador.cpp"

using namespace std;

int main() {
    FILE *doc = fopen("CF.txt", "r");
    Analizador A(doc);
    if (A.analizar())
        cout << "APROBADO" << endl << endl;
    else
        cout << "DESAPROBADO" << endl << endl;
    system("pause");
}
