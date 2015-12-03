#include "Barco.h"
using namespace std;

Barco::Barco(std::string nombre, int vida){
  _nombre = nombre;
  _vida = vida;
}

void Barco::setNombre (std::string nombre){_nombre = nombre;}
void Barco::setVida (int vida){_vida = vida;}
void Barco::addPosicion(Celda* pos){_pos.push_back(pos);}

std::string Barco::getNombre(){return _nombre;}
int Barco::getVida(){return _vida;}
std::vector<Celda*> Barco::getPosiciones(){return _pos;}
