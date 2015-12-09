#ifndef PLAYERIA
#define PLAYERIA

#include <Tablero.h>
#include <Barco.h>

#include <Ogre.h>

class PlayerIA{
public:
  PlayerIA();
  ~PlayerIA();
  void crearPlayer(std::string n, Tablero* t,  std::vector<Barco*> barcos);
  int getVida();
  std::vector<Barco*> getBarcos();
  Tablero* getTablero();
  std::string getNombre();
  void setVida(int v);
  void setNombre(std::string n);
  void printState();

  std::vector<Celda*> getTocados();
  void setTocados(std::vector<Celda*> toc);
  void pushTocado(Celda* c);
  Celda* popTocado();
private:
  std::string _nombre;
  Tablero* _tab;
  std::vector<Barco*> _barcos;
  int _vida;

  std::vector<Celda*> _tocados;//vector de posiciones con barco sin hundir
  
};
#endif
