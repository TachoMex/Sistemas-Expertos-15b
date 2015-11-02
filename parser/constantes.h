#ifndef CONSTANTES
#define CONSTANTES 
#include <string>


const int OK = -1;
const int ER = -2;

const std::string TOK_ERROR = "Error";
const std::string TOK_ENTERO = "Entero";
const std::string TOK_REAL = "Real";
const std::string TOK_CONSTANTE = "Constante";
const std::string TOK_VARIABLE = "Variable";
const std::string TOK_CUANTIFICADOR = "Cuantificador";
const std::string TOK_EXPONENCIAL = "Exponencial";
const std::string TOK_PRODUCTO = "Producto";
const std::string TOK_ADITIVO = "Aditivo";
const std::string TOK_RELACIONAL = "Relacional";
const std::string TOK_LOGICO = "Logico";
const std::string TOK_PARENTESIS = "Parentesis";
const std::string TOK_SEPARADOR = "Separador";
const std::string TOK_NEGACION = "Negacion";
const int TAM_G = 21;
int G[TAM_G][TAM_G]{
	//      00, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19
	/*00*/ { 1, 4, 5,20,14,13,11,10, 9, 8, 7,17, 6,ER,18,12, 0, 0,19,15},
	/*01*/ { 1,OK,OK, 2,OK,OK,OK,OK,OK,OK,OK,OK,ER,ER,OK,OK,OK,OK,ER,OK},
	/*02*/ { 3,ER,ER,ER,ER,ER,ER,ER,ER,ER,ER,ER,ER,ER,ER,ER,ER,ER,ER,ER},
	/*03*/ { 3,ER,ER,OK,OK,OK,OK,OK,OK,OK,OK,OK,ER,ER,OK,OK,OK,OK,ER,OK},
	/*04*/ { 4, 4, 4,OK,OK,OK,OK,OK,OK,OK,OK,OK,OK, 4,OK,OK,OK,OK,ER,OK},
	/*05*/ { 5, 5, 5,OK,OK,OK,OK,OK,OK,ER,ER,OK,ER, 5,OK,OK,OK,OK,ER,OK},
	/*06*/ {OK,OK,OK,ER,ER,ER,ER,ER,ER,ER,ER,OK,ER,ER,ER,ER,OK,OK,ER,ER},
	/*07*/ {OK,OK,OK,OK,ER,ER,OK,ER,ER,ER,ER,OK,ER,ER,ER,ER,OK,OK,ER,ER},
	/*08*/ {OK,OK,OK,OK,ER,ER,OK,ER,ER,ER,ER,OK,ER,ER,ER,ER,OK,OK,ER,ER},
	/*09*/ {OK,OK,OK,OK,ER,ER,OK,ER,ER,ER,ER,OK,ER,ER,ER,12,OK,OK,ER,ER},
	/*10*/ {OK,OK,OK,OK,ER,ER,OK,ER,ER,ER,ER,OK,ER,ER,ER,ER,OK,OK,ER,ER},
	/*11*/ {OK,OK,OK,OK,ER,15,ER,ER,ER,ER,ER,OK,ER,ER,ER,ER,OK,OK,ER,ER},
	/*12*/ {OK,OK,OK,OK,ER,ER,OK,ER,ER,ER,ER,OK,ER,ER,ER,ER,OK,OK,ER,ER},
	/*13*/ {OK,OK,OK,OK,ER,ER,OK,ER,ER,ER,ER,OK,ER,ER,ER,12,OK,OK,ER,ER},
	/*14*/ {OK,OK,OK,OK,ER,ER,16,ER,ER,ER,ER,OK,ER,ER,ER,12,OK,OK,ER,ER},
	/*15*/ {OK,OK,OK,OK,ER,ER,ER,ER,ER,ER,ER,OK,ER,ER,ER,ER,OK,OK,OK,ER},
	/*16*/ {OK,OK,OK,OK,ER,15,ER,ER,ER,ER,ER,OK,ER,ER,ER,ER,OK,OK,OK,ER},
	/*17*/ {OK,OK,OK,OK,ER,ER,ER,ER,ER,ER,ER,OK,ER,ER,ER,ER,OK,OK,OK,OK},
	/*18*/ {OK,OK,OK,OK,ER,ER,ER,ER,ER,ER,ER,OK,ER,ER,ER,ER,OK,OK,OK,ER},
	/*19*/ {OK,OK,OK,OK,ER,ER,ER,ER,ER,ER,ER,OK,ER,ER,ER,ER,OK,OK,OK,OK},
	/*20*/ {OK,OK, 3,OK,ER,ER,ER,ER,ER,ER,ER,OK,ER,ER,ER,ER,OK,OK,OK,ER},
};

int clase(char c){
	if(isupper(c)){
		return 2;
	}else if(islower(c)){
		return 1;
	}else if(isdigit(c)){
		return 0;
	};
	switch(c){
		case '.': return 3;
		case '<': return 4;
		case '>': return 5;
		case '-': return 6;
		case '+': return 7;
		case '/': return 8;
		case '*': case '%': return 9;
		case '^': return 10;
		case '(': case ')': return 11;
		case '#': case '@': return 12;
		case '\'': case '_': return 13;
		case ',': return 14;
		case '=': return 15;
		case ' ': case '\t': return 16;
		case '\n': case '\r': return 17;
		case '~': return 18;
		case '&': case '|': return 19;
		default:
			return ER;
	}
}

std::string tipoToken(int e){
	switch(e){
		case 0: return TOK_ERROR;
		case 1: return TOK_ENTERO;
		case 2: return TOK_ERROR;
		case 3: return TOK_REAL;
		case 4: return TOK_CONSTANTE;
		case 5: return TOK_VARIABLE;
		case 6: return TOK_CUANTIFICADOR;
		case 7: return TOK_EXPONENCIAL;
		case 8: return TOK_PRODUCTO;
		case 9: return TOK_PRODUCTO;
		case 10: return TOK_ADITIVO;
		case 11: return TOK_ADITIVO;
		case 12: return TOK_RELACIONAL;
		case 13: return TOK_RELACIONAL;
		case 14: return TOK_RELACIONAL;
		case 15: return TOK_LOGICO;
		case 16: return TOK_LOGICO;
		case 17: return TOK_PARENTESIS;
		case 18: return TOK_SEPARADOR;
		case 19: return TOK_NEGACION;
		case 20: return TOK_SEPARADOR;
		default:
			return TOK_ERROR;
	}
}
#endif