#ifndef SINTACTICO_H
#define SINTACTICO_H 

#include "lex.h"

template<int TG>
class Sintax{
private:
	Lex	<TG> * lex;
	Token siguiente;
	bool flagError;
public:
	Sintax(Lex<TG> *lex){
		this->lex = lex;
		flagError = false;
	}

	void analiza();
private:
	void evalTermino(); 			// signo| (termino) | constante | variable | functor | Cuantificador| logico
	void evalSigno(); 				// - termino
	void evalExponencial(); 		// termino ^ termino
	void evalProducto();    		// exponencial (* / %) exponencial
	void evalSuma();				// producto (+ -) producto
	void evalRelacional(); 			// suma (> < >= <= /= =) suma
	void evalLogico();				// relacional (& |) relacional
	void evalNegacion();			// ~ negacion
	void evalFunctor();				// constante (termino,termino,...)
	void evalCuantificador();		// (# @) variable termino 
	void error(const string&);
	void leeToken(){
		siguiente = lex -> siguiente();
		flagError = lex -> error;
	//	cout<<siguiente<<endl;
	}
};

template<int TG>
void Sintax<TG>::analiza(){
	leeToken();
	evalTermino();
	if(siguiente.tipo != TOK_FIN){
		error("OPERADOR");
	}
	if(not flagError){
		cout<<"Formula bien formada"<<endl;
	}
}


template<int TG>
void Sintax<TG>::error(const string& esperado){
	if(flagError)
		return;
	cout<<"Error en "<<lex->numeroLinea()<<":"<<lex->numeroCaracter()<<endl;
	cout<<"Se esperaba: "<<esperado<<endl;
	cout<<"Obtenido   : "<<siguiente<<endl;
	flagError = true;
}

template<int TG>
void Sintax<TG>::evalTermino(){
	// cout<<"#Termino: "<<siguiente<<endl;
	if(flagError)
		return;
	evalLogico();
		// cout<<"@Termino: "<<siguiente<<endl;
}

template<int TG>
void Sintax<TG>::evalSigno(){
	// cout<<"#Signo: "<<siguiente<<endl;
	if(flagError)
		return;
	if(siguiente.token=="-" or siguiente.token == "+" or siguiente.token == "~"){
		leeToken();
		evalTermino();
	}else if(siguiente.tipo == TOK_ENTERO or siguiente.tipo == TOK_REAL or siguiente.tipo == TOK_VARIABLE){
		leeToken();
	}else if(siguiente.tipo == TOK_CONSTANTE){
		leeToken();
		if(siguiente.token=="("){
			evalFunctor();
		}
	}else if(siguiente.tipo == TOK_CUANTIFICADOR){
		evalCuantificador();
	}else if(siguiente.token == "("){
		leeToken();
		evalTermino();
		if(siguiente.token != ")"){
			error(")");
		}
		leeToken();
	}else {
		error("TERMINO");
	}
	// cout<<"@Signo: "<<siguiente<<endl;
}

template<int TG>
void Sintax<TG>::evalNegacion(){
	evalSigno();
}

template<int TG>
void Sintax<TG>::evalCuantificador(){
	// cout<<"#Cuantificador: "<<siguiente<<endl;
	if(flagError)
		return;
	if(siguiente.tipo == TOK_CUANTIFICADOR){
		leeToken();
		if(siguiente.tipo == TOK_VARIABLE){
			leeToken();

//			cout<<"#Cuantificador"<<endl;
//			cout<<siguiente<<endl;

			evalTermino();
		}else{
			error("VARIABLE");
		}
	}
	// cout<<"@Cuantificador: "<<siguiente<<endl;
}

template<int TG>
void Sintax<TG>::evalExponencial(){
	// cout<<"#Exponencial: "<<siguiente<<endl;
	if(flagError)
		return;
	do{
		if(siguiente.token=="^"){
			leeToken();
		}
		evalSigno(); 
	}while(siguiente.token=="^");
	// cout<<"@Exponencial: "<<siguiente<<endl;
}

template<int TG>
void Sintax<TG>::evalProducto(){
	// cout<<"#Producto: "<<siguiente<<endl;
	if(flagError)
		return;
	do{
		if(siguiente.tipo == TOK_PRODUCTO){
			leeToken();
		}
		evalExponencial(); 
	}while(siguiente.tipo == TOK_PRODUCTO);
	// cout<<"@Producto: "<<siguiente<<endl;
}

template<int TG>
void Sintax<TG>::evalSuma(){
	// cout<<"#Suma: "<<siguiente<<endl;
	if(flagError)
		return;
	do{
		if(siguiente.tipo == TOK_ADITIVO){
			leeToken();
		}
		evalProducto(); 
	}while(siguiente.tipo == TOK_ADITIVO);
	// cout<<"@Suma: "<<siguiente<<endl;
}


template<int TG>
void Sintax<TG>::evalRelacional(){
	// cout<<"#Relacional: "<<siguiente<<endl;
	if(flagError)
		return;
	do{
		if(siguiente.tipo == TOK_RELACIONAL){
			leeToken();
		}
		evalSuma(); 
	}while(siguiente.tipo == TOK_RELACIONAL);
	// cout<<"@Relacional: "<<siguiente<<endl;
}

template<int TG>
void Sintax<TG>::evalLogico(){
	// cout<<"#Logico: "<<siguiente<<endl;
	if(flagError)
		return;
	do{
		if(siguiente.tipo == TOK_LOGICO){
			leeToken();
		}
		evalRelacional(); 
	}while(siguiente.tipo == TOK_LOGICO);
	// cout<<"@Logico: "<<siguiente<<endl;
}


template<int TG>
void Sintax<TG>::evalFunctor(){
	// cout<<"#Functor: "<<siguiente<<endl;
	if(flagError)
		return;
	if(siguiente.token=="("){
		leeToken();
		evalTermino();
		while(siguiente.token==","){
			leeToken();
			evalTermino();			
		}
		if(siguiente.token==")"){
			// cout<<"Se espera cerrar parentesis de functor"<<endl;
			leeToken();
		}else{
			error(")");
		}
	}else{
		error("(");
	}
	// cout<<"@Functor: "<<siguiente<<endl;
}

#endif