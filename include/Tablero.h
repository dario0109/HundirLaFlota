#ifndef TABLERO
#define TABLERO

#include <Ogre.h>


#include <ctime>
#include <cstdio>
#include <cstdlib>

#include <map>
#include <vector>

#include <Celda.h>
#include <Barco.h>

class Tablero{
public:
  Tablero();
  ~Tablero();
  
  void crearTablero(int dim, std::vector<Barco*>barcos);
  void limpiarTablero();
  void reiniciarTablero();
  Celda* getCelda(int x, int y);
  bool colocado(int idx, int idxf, int idy, int idyf);
  int onClick(Celda *cel);
  void printTablero();

private:
  int _dim;
  Celda **_tab;
  std::vector <Barco*> _barcos;


  void rellenar();
};
#endif
