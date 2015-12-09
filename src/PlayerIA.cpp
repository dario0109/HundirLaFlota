#include "PlayerIA.h"

PlayerIA::PlayerIA(){}
PlayerIA::~PlayerIA(){/*eliminarPlayer();*/}

void PlayerIA::crearPlayer(std::string n, Tablero* t, std::vector<Barco*> barcos){
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
Tablero* PlayerIA::getTablero(){return _tab;}
std::string PlayerIA::getNombre(){return _nombre;}

void PlayerIA::setVida(int v){_vida = v;}
void PlayerIA::setNombre(std::string n){_nombre = n;}

void PlayerIA::printState(){
  std::cout << "Jugador:" << _nombre << " Estado:" << std::endl;
  _tab->printTablero();
}

std::vector<Celda*> PlayerIA::getTocados(){return _tocados;}
void PlayerIA::setTocados(std::vector<Celda*> toc){_tocados = toc;}
void PlayerIA::pushTocado(Celda* c){_tocados.push_back(c);}
Celda* PlayerIA::popTocado(){
  Celda* aux;
  aux = _tocados.at(_tocados.size()-1);
  _tocados.erase(_tocados.begin() + _tocados.size() -1);
  return aux;
}
