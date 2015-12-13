#ifndef BARCO_H
#define BARCO_H

#include <string>
#include <vector>
#include <utility>
#include "Celda.h"

using namespace std;

class Barco{
public:
  Barco(std::string nombre, int vida);
  void setNombre(std::string nombre);
  void setVida(int vida);
  void addPosicion(int x, int y);
  
  std::string getNombre();
  int getVida();
  std::vector<pair<int, int> >* getPosiciones();
private:
  std::vector<pair<int, int> >* _pos;
  std::string _nombre;
  int _vida;
};
#endif
