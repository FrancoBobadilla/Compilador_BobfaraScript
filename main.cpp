#include "Compilador.cpp"

int main() {
	Compilador C;
	return C.compilar(fopen("CF.txt", "r"), fopen("CO.txt", "w"));
}
