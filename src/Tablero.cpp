#include "Celda.h"
#include "Tablero.h"
#include <vector>
template<> Tablero* Ogre::Singleton<Tablero>::msSingleton = 0;

Tablero::Tablero(){}
Tablero::~Tablero(){limpiarTablero();}

void Tablero::crearTablero(std::vector<Barco*> barcos){
  _tab = new Celda*[10];
  _c_click = 76;
  _barcos = barcos;

  for(int x = 0; x < 10; x++){
    _tab[x] = new Celda[10];
    for(int y = 0; y < 10; y++){
      _tab[x][y].setX(x);
      _tab[x][y].setY(y);
      _tab[x][y].setEstado(0);
    }
  }
  rellenar();
}

void Tablero::limpiarTablero(){
  _barcos.clear();
  //std::vector<Celda*>().swap(_barcos);
  for (int i = 0; (unsigned)i < 10; i++){
    delete [] _tab[i];
  }
  delete [] _tab;
}

void Tablero::reiniciarTablero(){
  limpiarTablero();
  crearTablero(_barcos);
}

void Tablero::rellenar(){
  int idx, idy, idxf, idyf, orientation;
  srand(time(NULL));
  /*Colocacion de barcos*/
  for(unsigned int i = 0; i < _barcos.size(); i++){
    while(true){
      orientation = (unsigned)rand() % 2;//0->hor 1->ver
      idx = (unsigned)rand() % 10;//0-9 posicion x
      idy = (unsigned)rand() % 10;//"          " y
      idxf = idx+(_barcos[i]->getVida()-1)*((orientation+1)%2);
      idyf = idy+((_barcos[i]->getVida()-1)*orientation);
      if(colocado(idx, idxf, idy, idyf)){
	for(int x = idx; x <idxf+1; x++){
	  for(int y = idy; y <idyf+1; y++){
	    _tab[x][y].setEstado(1);
	    //std::cout << "Barco " << i << "colocado en x = " << x << " y = " << y << '\n';
	  }
	}
	break;
      }
    }
  }
  for(int x = 0; x < 10; x++){
    for(int y = 0; y < 10; y++){
      std::cout << _tab[x][y].getEstado() << '\t';
    }
    std::cout << '\n';
  }
}

bool Tablero::colocado(int idx, int idxf, int idy, int idyf){
  bool ok = true;
  if(idxf>9 or idyf >9){ok = false;}
  else{
    for(int i = idx; i <idxf+1; i++){
      for(int j = idy; j <idyf+1; j++){
	if(_tab[i][j].getEstado() != 0){ok = false;}
      }
    }
  }
  return ok;
}
