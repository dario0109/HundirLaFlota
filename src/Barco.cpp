#include "Barco.h"
#include <vector>
using namespace std;

Barco::Barco(std::string nombre, int vida){
  _nombre = nombre;
  _vida = vida;
}

void Barco::setNombre (std::string nombre){_nombre = nombre;}
void Barco::setVida (int vida){_vida = vida;}
void Barco::setX(int x){_x = x;}
void Barco::setY(int y){_y = y;}
void Barco::setDir(int d){_dir = d;}

std::string Barco::getNombre(){return _nombre;}
int Barco::getVida(){return _vida;}
int Barco::getX(){return _x;}
int Barco::getY(){return _y;}
int Barco::getDir(){return _dir;}
