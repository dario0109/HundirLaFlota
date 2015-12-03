#ifndef BARCO_H
#define BARCO_H

#include <string>
#include <vector>
#include "Celda.h"

using namespace std;

class Barco{
public:
  Barco(std::string nombre, int vida);
  void setNombre(std::string nombre);
  void setVida(int vida);
  void addPosicion(Celda* pos);
  
  std::string getNombre();
  int getVida();
  std::vector<Celda*> getPosiciones();
private:
  std::vector<Celda*> _pos;
  std::string _nombre;
  int _vida;
};
#endif
