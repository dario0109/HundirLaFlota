#ifndef TABLERO
#define TABLERO

#include <Ogre.h>
//#include <OgreSingleton.h>

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
  
  void limpiarTablero();
  void reiniciarTablero();
  void swapShips();
  bool Click(Ogre::String nombre_nodo);
  void crearTablero(int dim, std::vector<Barco*>barcos);
  void addToMap(Ogre::String nombre_nodo, Celda *cel);
  bool colocado(int idx, int idxf, int idy, int idyf);
  void printTablero();
  std::vector <Celda*>* getRest();
  void setRest(std::vector <Celda*> *rest);
  int getCClick();
  Celda* getCelda(int x, int y);
  Celda* getCelda(Ogre::String nombre_nodo);
  int onClick(Celda *cel);
  
  static Tablero& getSingleton();
  static Tablero* getSingletonPtr();

private:
  int _dim;
  Celda **_tab;
  std::vector <Barco*> _barcos;
  std::vector <Celda*> *_rest;//celdas sin atacar
  std::map<Ogre::String, Celda*> _relaciones;

  void rellenar();
  void swap(Ogre::SceneNode *nodo);
  void descubrirAdyacentes(Celda *cel);
};
#endif
