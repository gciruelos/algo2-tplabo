#ifndef CORREPOCOYO_H_
#define CORREPOCOYO_H_

#include <iostream>
#include <cassert>
using namespace std;

/* 
 * Se puede asumir que el tipo T tiene constructor por copia y operator==
 * No se puede asumir que el tipo T tenga operator=
 */
template<typename T>
class CorrePocoyo{

  public:

	/*
	 * Crea una nueva carrera
	 */	
	CorrePocoyo();

	/*
	 * Una vez copiada, ambas CorrePocoyos deben ser independientes, 
	 * es decir, cuando se borre una no debe borrar la otra.
	 */	
	CorrePocoyo(const CorrePocoyo<T>&);
	
	/*
	 * Acordarse de liberar toda la memoria!
	 */	 
	~CorrePocoyo();

	/*
	 * Agrega un nuevo corredor al CorrePocoyo. Lo agregará al final 
	 */
	void nuevoCorredor(const T&);
	
	/*
	 * Agrega un nuevo corredor al CorrePocoyo. El primer T es el corredor a agregar y lo hace delante del segundo
	 *
	 * PRE: Existe el segundo corredor 
	 */
	void nuevoCorredor(const T&, const T&);
	
	/*
	 * Elimina del pocoyo al que se envía
	 *
	 * PRE: Existe el corredor
	 */
	void seCansa(const T&);
	/*
	 * El corredor pasa al que está adelante 
	 *
	 * PRE: Existe un corredor delante de él y T es un corredor 
	 */
	void sobrepasar(const T&);
	
	/*
	 * Devuelve el corredor que está siendo filmado.
	 *
	 * PRE: Hay adeptos en la CorrePocoyo.
	 */
	const T& corredorFilmado() const;
	
    /*
	 * Devuelve el próximo elemento según el orden dado.
	 * Pasa a filmar al corredor de atás 
	 *
	 * PRE: Hay corredore en la CorrePocoyo.
	 */
	void filmarProxPerdedor();
	    /*
	 * Devuelve el próximo elemento según el orden dado.
	 * Pasa a filmar al corredor de adelante 
	 *
	 * PRE: Hay corredore en la CorrePocoyo.
	 */
	void filmarProxExitoso();
	
	/*
	 * Devuelve al Primero. 
	 *
	 * PRE: Hay elementos 
	 */
	const T& damePrimero() const;	

	/*
	 * Devuelve la posición del elemento pasado por parámetro. 
	 *
	 * PRE: Existe ese corredor 
	 */
	int damePosicion(const T& ) const;	

	/*
	 * Devuelve el corredor de la posición. 
	 *
	 * PRE: Existe al menos esa cantidad de corredores en la carrera
	 */
	const T& dameCorredorEnPos(int) const;	




	/*
	 * Dice si la CorrePocoyo tiene o no corredores.
	 */
	bool esVacia() const;

	
	/*
	 * Devuelve la cantidad de corredores de la CorrePocoyo.
	 */
	int tamanio() const;	

	/*
	 * Devuelve true si las CorrePocoyos son iguales.
	 */
	bool operator==(const CorrePocoyo<T>&) const;	
	
	/*
	 * Debe mostrar la carrera por el ostream (y retornar el mismo).
	 * CorrePocoyo vacio: []
	 */
	ostream& mostrarCorrePocoyo(ostream&) const;
	
	
  private:
	/*
	 * No se puede modificar esta funcion.
	 */
	CorrePocoyo<T>& operator=(const CorrePocoyo<T>& otra) {
		assert(false);
		return *this;
	}

	/*
	 * Aca va la implementación del nodo.
	 */
	struct Nodo {
		struct Nodo * siguiente;
		struct Nodo * anterior;
		T corredor;
	};

  Nodo * primero;
	Nodo * ultimo;

  Nodo * camara;
	int cant_corredores;

};

template<class T>
ostream& operator<<(ostream& out, const CorrePocoyo<T>& a) {
	return a.mostrarCorrePocoyo(out);
}

// Implementación a hacer por los alumnos.

template<typename T>
CorrePocoyo<T>::CorrePocoyo(){
	primero = NULL;
	ultimo = NULL;
	camara = NULL;
	cant_corredores = 0;
}


template<typename T>
CorrePocoyo<T>::CorrePocoyo(const CorrePocoyo<T>& otro){
  cant_corredores = otro.cant_corredores;


  if(otro.esVacia()){
		primero = NULL;
		ultimo = NULL;
		camara = NULL;
	} else{
    Nodo * nodoActual_otro = otro.primero;

    Nodo * nodoAnterior = NULL;
    Nodo * nodoActual = new Nodo;
  	
		nodoActual->anterior = nodoAnterior;
		T dato(nodoActual_otro->corredor); nodoActual->corredor = dato;
    //falta copiar dato

	  primero = nodoActual;

  

  	while(nodoActual_otro->siguiente != NULL){
			nodoActual_otro = nodoActual_otro->siguiente;
			
			nodoAnterior = nodoActual;
			nodoActual = new Nodo;

			nodoActual->anterior = nodoAnterior;
			nodoAnterior->siguiente = nodoActual;
			
		  T dato(nodoActual_otro->corredor); nodoActual->corredor = dato;
			//copiar dato

			//fijarme a donde apunta la camara
		}

    nodoActual->siguiente = NULL;
		ultimo = nodoActual;
	}
}

template<typename T>
CorrePocoyo<T>::~CorrePocoyo(){

}

/*
 * Agrega un nuevo corredor al CorrePocoyo. Lo agregará al final 
 */
template<typename T>
void CorrePocoyo<T>::nuevoCorredor(const T& t){
  cant_corredores++;

  Nodo * nuevo = new Nodo;
  
  nuevo->siguiente = NULL;
  nuevo->anterior = ultimo;
  T dato(t); nuevo->corredor = dato;

  if(this->esVacia()){
		primero = nuevo;
	} else{
  	ultimo->siguiente = nuevo; 
  }

	ultimo = nuevo;

}

/*
 * Agrega un nuevo corredor al CorrePocoyo. El primer T es el corredor a agregar y lo hace delante del segundo
 *
 * PRE: Existe el segundo corredor 
 */
template<typename T>
void CorrePocoyo<T>::nuevoCorredor(const T& nuevo_corredor, const T& existente){
	cant_corredores++;
  Nodo * nuevo = new Nodo;
  T dato(nuevo_corredor); nuevo->corredor = dato;

	
	Nodo * nodoActual = primero;

	while(nodoActual->corredor != existente){
		nodoActual = nodoActual->siguiente;
	}

	// nodoActual->corredor == existente
  if(nodoActual->anterior == NULL){ //es el primero
	  nodoActual->anterior = nuevo;
		nuevo->siguiente = nodoActual;
		primero = nuevo;
		nuevo->anterior = NULL;
	}
	else{
		(nodoActual->anterior)->siguiente = nuevo;
	  nuevo->anterior = nodoActual->anterior;
	  nodoActual->anterior = nuevo;
	  nuevo->siguiente = nodoActual;
  }

}


/*
 * Elimina del pocoyo al que se envía
 *
 * PRE: Existe el corredor
 */
template<typename T>
void CorrePocoyo<T>::seCansa(const T& cansado){
	
	cant_corredores--;

	Nodo * nodoActual = primero;

	while(nodoActual->corredor != cansado){
		nodoActual = nodoActual -> siguiente;
	}

	//COSULTAR: que hacer si la camara lo apunta al borrado
  //nodoActual->corredor = cansado
  if(nodoActual->siguiente == NULL && nodoActual->anterior == NULL){
		primero = NULL;
		ultimo = NULL;
		camara = NULL;
	} else if(nodoActual->siguiente == NULL){ //es el ultimo
    (nodoActual->anterior)->siguiente = NULL;
		ultimo = nodoActual->anterior;
	} else if(nodoActual->anterior == NULL){ // es el primero
    (nodoActual->siguiente)->anterior = NULL;
		primero = nodoActual->siguiente;
	}else{
	  (nodoActual->anterior)->siguiente = nodoActual->siguiente;
	  (nodoActual->siguiente)->anterior = nodoActual->anterior;
	}

	delete nodoActual;
	
}

/*
 * El corredor pasa al que está adelante 
 *
 * PRE: Existe un corredor delante de él y T es un corredor 
 */
template<typename T>
void CorrePocoyo<T>::sobrepasar(const T& pasador){
	Nodo * nodoActual = primero;
  Nodo * nodoAnterior, * nodoSiguiente; 

	while(nodoActual->corredor != pasador){
		nodoActual = nodoActual->siguiente;
	}
	//nodoActual->corredor = pasador

  nodoAnterior = nodoActual->anterior;
  nodoSiguiente = nodoActual->siguiente;
	
	nodoActual->siguiente = nodoAnterior;
	nodoActual->anterior = nodoAnterior->anterior;

	nodoAnterior->anterior = nodoActual;
	nodoAnterior->siguiente = nodoSiguiente;

	nodoSiguiente->anterior = nodoAnterior;

	(nodoAnterior->anterior)->siguiente = nodoActual;

	//FALTA TERMINAR
}


template<typename T>
const T& CorrePocoyo<T>::corredorFilmado() const{
   return camara->corredor;
}


template<typename T>
void CorrePocoyo<T>::filmarProxPerdedor(){
	camara = camara->siguiente;

}

template<typename T>
void CorrePocoyo<T>::filmarProxExitoso(){
  camara = camara->anterior;
}


template<typename T>
const T& CorrePocoyo<T>::damePrimero() const{
  return primero->corredor;
}

template<typename T>
int CorrePocoyo<T>::damePosicion(const T& ) const{

}


template<typename T>
const T& CorrePocoyo<T>::dameCorredorEnPos(int) const{

}


template<typename T>
bool CorrePocoyo<T>::esVacia() const{
	return primero == NULL;
}
	

template<typename T>
int CorrePocoyo<T>::tamanio() const{
	return cant_corredores;
}


template<typename T>
bool CorrePocoyo<T>::operator==(const CorrePocoyo<T>&) const{

}

/*
 * Debe mostrar la carrera por el ostream (y retornar el mismo).
 * CorrePocoyo vacio: []
 */
template<typename T>
ostream& CorrePocoyo<T>::mostrarCorrePocoyo(ostream& os) const{
	os << "[";
  
	Nodo * nodoActual = primero;

	while(nodoActual != NULL){

    os << nodoActual->corredor;

    if(nodoActual->siguiente != NULL) os << ", ";
	
	  nodoActual = nodoActual->siguiente;
}
	os << "]";
}
	

#endif //CORREPOCOYO_H_
