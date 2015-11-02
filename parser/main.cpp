#include "sintactico.h"
#include <iostream>
#include <cctype>
using namespace std;

string CTRL_L=" ";

int main(){
	//ifstream f("tokens.txt");
	CTRL_L[0] = 12;
	do{
		string codigo;//((istreambuf_iterator<char>(f)),istreambuf_iterator<char>());
		getline(cin, codigo);
		if(codigo == CTRL_L){
			system("cls||clear");
		}else{
			Lex<TAM_G> *lex = new Lex<TAM_G>(G,codigo,tipoToken,clase);
			Sintax<TAM_G> sintax(lex);
			sintax.analiza();
		}

	}while(not cin.eof());
	return 0;
}