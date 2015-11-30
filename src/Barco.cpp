#include "Barco.h"
#include <vector>
using namespace std;

Barco::Barco(std::string nombre, int vida, vector<int> posiciones){
	_nombre = nombre;
	_vida = vida;
	_posiciones = posiciones;
}//Fin constructor

void Barco::setNombre (std::string nombre){
	_nombre = nombre;
}//Fin setNombre

void Barco::setVida (int vida){
	_vida = vida;
}//Fin setVida

void Barco::setPosiciones(vector<int> posiciones){
	_posiciones = posiciones;
}//Fin setPosicion

std::string Barco::getNombre (){
	return _nombre;
}//Fin getNombre

int Barco::getVida (){
	return _vida;
}//Fin getVida

vector<int>* Barco::getPosiciones(){
	return &_posiciones;
}//Fin getPosicion