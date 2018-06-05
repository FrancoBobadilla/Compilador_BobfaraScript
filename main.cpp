#include <iostream>
#include <fstream>

using namespace std;

int main() {
    int c;  //deberia ser ascii
    char hl[10]={'0','1','2','3','4','5','6','7','8','9'};
    FILE *doc = fopen("CF.txt", "r");
    if (doc == NULL)return 1;
    for (int i = 0; (c = fgetc(doc)) != EOF; i++) {
        hl[i] = c;
    }
    for(int i=0; i<10;i++){
    	cout<<hl[i];
	}
    return 0;
}
