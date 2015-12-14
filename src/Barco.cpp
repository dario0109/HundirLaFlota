#include "Barco.h"
using namespace std;

Barco::Barco(std::string nombre, int vida){
  _nombre = nombre;
  _vida = vida;
  _pos = new vector<pair<int, int> >();
}

void Barco::setNombre (std::string nombre){_nombre = nombre;}
void Barco::setVida (int vida){_vida = vida;}
void Barco::addPosicion(int x, int y){_pos->push_back(std::make_pair(x,y));}

std::string Barco::getNombre(){return _nombre;}
int Barco::getVida(){return _vida;}
std::vector<pair<int, int> >* Barco::getPosiciones(){return _pos;}
