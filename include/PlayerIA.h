#ifndef PLAYERIA
#define PLAYERIA

#include <Tablero.h>
#include <Barco.h>

#include <Ogre.h>

class PlayerIA{
public:
  PlayerIA();
  ~PlayerIA();

  void crearPlayer(std::string n, Tablero t,  std::vector<Barco*> barcos);

  int getVida();
  std::vector<Barco*> getBarcos();
  Tablero getTablero();
  std::string getNombre();

  void setVida(int v);
  void setNombre(std::string n);

  void printState();
private:
  std::string _nombre;
  Tablero _tab;
  std::vector<Barco*> _barcos;
  int _vida;
};
#endif
