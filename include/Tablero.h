#ifndef TABLERO
#define TABLERO

#include <Ogre.h>
#include <OgreSingleton.h>

#include <ctime>
#include <cstdio>
#include <cstdlib>

#include <map>
#include <vector>

#include <Celda.h>
#include <Barco.h>

class Tablero: public Ogre::Singleton<Tablero>{
public:
  Tablero();
  ~Tablero();
  
  void limpiarTablero();
  void reiniciarTablero();
  void swapShips();
  bool Click(Ogre::String nombre_nodo);
  void crearTablero(std::vector<Barco*>barcos);
  void addToMap(Ogre::String nombre_nodo, Celda *cel);
  bool colocado(int idx, int idxf, int idy, int idyf);
  
  int getCClick();
  Celda* getCelda(int x, int y);
  Celda* getCelda(Ogre::String nombre_nodo);
  /*vector <Barco*> getBarcos();
    void setBarcos(vector<Barco*>b);*/

  static Tablero& getSingleton();
  static Tablero* getSingletonPtr();
private:
  int _c_click;
  Celda **_tab;
  std::vector <Barco*> _barcos;
  std::map<Ogre::String, Celda*> _relaciones;

  void rellenar();
  bool onClick(Celda *cel);
  void swap(Ogre::SceneNode *nodo);
  void descubrirAdyacentes(Celda *cel);
};
#endif
