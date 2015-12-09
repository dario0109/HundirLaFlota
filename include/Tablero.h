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
  
  void crearTablero(int dim, std::vector<Barco*>barcos);
  void limpiarTablero();
  void reiniciarTablero();
  Celda* getCelda(int x, int y);
  bool colocado(int idx, int idxf, int idy, int idyf);
  int onClick(Celda *cel);
  void printTablero();

  /*std::vector <Celda*>* getRest();
  void setRest(std::vector <Celda*> *rest);
  Celda** getTablero();
  static Tablero& getSingleton();
  static Tablero* getSingletonPtr();
  void swapShips();
  bool Click(Ogre::String nombre_nodo);
  void addToMap(Ogre::String nombre_nodo, Celda *cel);
  int getCClick();
  Celda* getCelda(Ogre::String nombre_nodo);*/

private:
  int _dim;
  Celda **_tab;
  std::vector <Barco*> _barcos;
  //std::vector <Celda*> *_rest;//celdas sin atacar
  //std::map<Ogre::String, Celda*> _relaciones;

  void rellenar();
  /*void swap(Ogre::SceneNode *nodo);
    void descubrirAdyacentes(Celda *cel);*/
};
#endif
