#include "Celda.h"

Celda::Celda():
  _estado(0),
  _x(-1),_y(-1),
  _nodo(NULL){}

int Celda::getX() const{return _x;}
int Celda::getY() const{return _y;}
int Celda::getEstado() const{return _estado;}


void Celda::setX(int x){_x = x;}
void Celda::setY(int y){_y = y;}
void Celda::setEstado(int e){_estado = e;}

