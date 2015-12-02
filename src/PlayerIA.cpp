#include "PlayerIA.h"

PlayerIA::PlayerIA(){}
PlayerIA::~PlayerIA(){/*eliminarPlayer();*/}

void PlayerIA::crearPlayer(std::string n, Tablero t, std::vector<Barco*> barcos){
  _nombre = n;
  _tab = t;
  _barcos = barcos;
  _vida = 0;
  for(unsigned int i = 0; i < _barcos.size(); i++){
  _vida += _barcos[i]->getVida();
  }
}
int PlayerIA::getVida(){return _vida;}
std::vector<Barco*> PlayerIA::getBarcos(){return _barcos;}
Tablero PlayerIA::getTablero(){return _tab;}
std::string PlayerIA::getNombre(){return _nombre;}

void PlayerIA::setVida(int v){_vida = v;}
void PlayerIA::setNombre(std::string n){_nombre = n;}

void PlayerIA::printState(){
  std::cout << "Jugador:" << _nombre << " Estado:" ;
  _tab.printTablero();
}
