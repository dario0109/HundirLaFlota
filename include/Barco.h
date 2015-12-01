#ifndef BARCO_H
#define BARCO_H

#include <string>
#include <vector>

using namespace std;

class Barco{
public:
  Barco(std::string nombre, int vida);
  void setNombre(std::string nombre);
  void setVida(int vida);
  void setX(int x);
  void setY(int y);
  
  std::string getNombre();
  int getVida();
  int getX();
  int getY();
  
private:
  std::string _nombre;
  int _vida, _x, _y;
};//Fin Barco

#endif
