#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <string>
#include <stack>
#include "constantes.h"

using namespace std;


class Token{
public:
	string token;
	string tipo;
	Token(){

	}
	Token(const string& tok,const string& tip ){
		token = tok;
		tipo = tip;
	}
};

ostream& operator<<(ostream& s, const Token& tok){
	s<<"< Token = "<<tok.tipo<<":\""<<tok.token<<"\">";
	return s;
}

template<int Tam_G>
class Lex{
private:
	int **G;
	int estadoActual;
	stack<int> pilaEstados;
	string buff;
	string (*tipoToken)(int);
	int (*clase)(char);
	int idx;
	int contLinea;
	int contCol;

	int incrementaContador(){
		int res = idx;
		if(buff[idx++]=='\n'){
			contLinea++;
			contCol = 1;
		}
		contCol++;
		return res;
	}

public:
	bool error;
	Lex(int grafo[Tam_G][Tam_G], string& b, string (*tipo)(int), int (*clase)(char)){
		this->G = new int*[Tam_G];
		for(int i=0;i<Tam_G;i++){
			this->G[i] = grafo[i];
		}
		this->buff = b;
		this->tipoToken = tipo;
		this->clase = clase;
		this->idx = 0;
		contCol = 1;
		contLinea = 1;
		error = false;
	}

	~Lex(){
		delete[] G;
	}

	void deshacer(int k){

	}

	bool fin(){
		return idx == buff.size();
	}

	Token siguiente(){
		string lexema="";
		int estado = 0, estAnt=0;
		while(buff[idx]==' ' or buff[idx]=='\t' or buff[idx]=='\n'){
			incrementaContador();
		}
		while( idx < buff.size() and estado != ER and estado != OK){
			char c = buff[idx];
			incrementaContador();
			int t = clase(c);
			if( t >= 0 and estado != ER and estado != OK){
				estAnt = estado;
				estado = G[estado][t];
				if( estado != ER and estado != OK){ 
					lexema += c;
				}
			}else if (t < 0 ){ 
				estado = ER;
			}
		}
		if(estado==ER){
			cout<<buff[idx]<<" inesperado en "<<this->contLinea<<":"<<this->contCol<<endl;
			error = true;
			return Token();
		}
		if(estado == OK) 
			idx--;
		if(estado != ER and estado != OK) 
			estAnt = estado;
		return Token(lexema, tipoToken(estAnt));
	}

	int numeroLinea(){
		return contLinea;
	}
	int numeroCaracter(){
		return contCol;
	}
};

