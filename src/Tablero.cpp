#include "Celda.h"
#include "Tablero.h"
#include <vector>
//template<> Tablero* Ogre::Singleton<Tablero>::msSingleton = 0;

Tablero::Tablero(){}
Tablero::~Tablero(){limpiarTablero();}

void Tablero::crearTablero(int dim, std::vector<Barco*> barcos){
  _dim = dim;
  _tab = new Celda*[_dim];
  _barcos = barcos;
  _rest = new vector <Celda*>();
  for(int x = 0; x < _dim; x++){
    _tab[x] = new Celda[_dim];
    for(int y = 0; y < _dim; y++){
      _tab[x][y].setX(x);
      _tab[x][y].setY(y);
      _tab[x][y].setEstado(0);
      _rest->push_back(&_tab[x][y]);
    }
  }
  rellenar();
}

void Tablero::limpiarTablero(){
  _barcos.clear();
  /*Aqui habia un swap que no se lo que hacia*/
  for (int i = 0; i < _dim; i++){
    delete [] _tab[i];
  }
  delete [] _tab;
}

void Tablero::reiniciarTablero(){
  limpiarTablero();
  crearTablero(_dim, _barcos);
}

Celda* Tablero::getCelda(int x, int y){
  Celda* aux = &_tab[x][y];
  return aux;
}

void Tablero::rellenar(){
  int idx, idy, idxf, idyf, orientation;
  srand(time(NULL));
  /*Colocacion de barcos*/
  usleep(1000000);
  for(unsigned int i = 0; i < _barcos.size(); i++){
    while(true){
      orientation = rand() % 2;//0->hor 1->ver
      idx = rand() % _dim;
      idy = rand() % _dim;
      idxf = idx+(_barcos[i]->getVida()-1)*((orientation+1)%2);
      idyf = idy+((_barcos[i]->getVida()-1)*orientation);
      if(colocado(idx, idxf, idy, idyf)){
	for(int x = idx; x <idxf+1; x++){
	  for(int y = idy; y <idyf+1; y++){
	    _tab[x][y].setEstado(i+1);//ponemos nº del barco
	  }
	}
	break;
      }
    }
  }
}

bool Tablero::colocado(int idx, int idxf, int idy, int idyf){
  bool ok = true;
  if(idxf>_dim-1 or idyf >_dim-1){ok = false;}
  else{
    for(int i = idx; i <idxf+1; i++){
      for(int j = idy; j <idyf+1; j++){
	if(_tab[i][j].getEstado() != 0){ok = false;}
      }
    }
  }
  return ok;
}

int Tablero::onClick(Celda *cel){
  int acierto = -1;
  int est = cel->getEstado();
  //std::cout << "Estado = " << est << '\n';
  if(est == 0){
    std::cout << "Agua!" << '\n';
    _tab[cel->getX()][cel->getY()].setEstado(-1);
    acierto = 0;
  }
  else if(est>0 && est<10){
    std::cout << "Tocado!" << '\n';
    if(_barcos[est-1]->getVida()<=1){
      _tab[cel->getX()][cel->getY()].setEstado(est+20);
      acierto = 2;
      std::cout << "... Y Hundido!" << '\n';
    }
    else{
      _tab[cel->getX()][cel->getY()].setEstado(est+10);
      acierto = 1;
    }
    _barcos[est-1]->setVida(_barcos[est-1]->getVida()-1);

  }
  return acierto;
}

void Tablero::printTablero(){
  std::cout << '\n';
  for(int x = 0; x < _dim; x++){
    for(int y = 0; y < _dim; y++){
      std::cout << _tab[x][y].getEstado() << '\t';
    }
    std::cout << '\n';
  }
  std::cout << '\n';
}
std::vector<Celda*>* Tablero::getRest(){return _rest;}
void Tablero::setRest(std::vector <Celda*> *rest){_rest = rest;}
