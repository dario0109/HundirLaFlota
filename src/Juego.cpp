#include <Juego.h>

Juego::Juego(Ogre::SceneManager* sm) {
  _sceneManager = sm;
  _endGame = false;
}

Juego::~Juego() {
}

std::vector<Barco*> Juego::generarBarcos(){
  std::vector <Barco*> barcos;
  Barco* b1 = new Barco("Portaviones", 5);
  barcos.push_back(b1);
  Barco* b2 = new Barco("Artillero 1", 3);
  barcos.push_back(b2);
  Barco* b3 = new Barco("Artillero 2", 3);
  barcos.push_back(b3);
  Barco* b4 = new Barco("Lancha 1", 1);
  barcos.push_back(b4);
  Barco* b5 = new Barco("Lancha 2", 1);
  barcos.push_back(b5);
  Barco* b6 = new Barco("Lancha 3", 1);
  barcos.push_back(b6);

  return barcos;
}
void Juego::generarPlayers(){
  std::vector <Barco*> barcos1 = generarBarcos();
  Tablero* t1 = new Tablero();
  t1->crearTablero(8, barcos1);
  _p1 = new PlayerIA();
  _p1->crearPlayer("IA Player 1", t1, barcos1);
  _p1->printState();
  std::vector <Barco*> barcos2 = generarBarcos();
  Tablero* t2 = new Tablero();
  t2->crearTablero(8, barcos2);
  _p2 = new PlayerIA();
  _p2->crearPlayer("IA Player 2", t2, barcos2);
  _p2->printState();
}
bool Juego::simular(int x, int y){
  std::stringstream snbarco1, snbarco2, sncelda1, sncelda2;
  int acierto = -1;
  Celda* aux1,* aux2,* aux22;
  bool turno = false;
  
  aux22 = new Celda();
  int i = 0;
  int j = 0;    i++;
  /*std::cout << "Turno " << i << '\n';
  std::cout << "Vida J1 = " << _p1->getVida() << '\n';
  std::cout << "Vida J2 = " << _p2->getVida() << '\n';*/
  std::cout << "Jugador 1 ataca en  (" << x+1 << "," << y+1 << ")" << '\n';
  aux1 = _p2->getTablero()->getCelda(x,y);
  acierto = (_p2->getTablero())->onClick(aux1);
  if(acierto>0){
    _p2->setVida(_p2->getVida()-1);
    snbarco2 << "B2(" << aux1->getX() << "," << aux1->getY() << ")";
    Ogre::SceneNode* casilla = _sceneManager->getSceneNode(snbarco2.str());
    Ogre::Entity* pieza = static_cast<Ogre::Entity*>(casilla->getAttachedObject(0));
    pieza->setMaterialName("Tocado");
    pieza->setVisible(true);
    snbarco2.str("");
  }
  else if(acierto < 0){//casilla ya pulsada
    turno = true;
  }
  else{//agua
    sncelda1 << "C" << aux1->getX() << "_" << aux1->getY();
    Ogre::SceneNode* casilla2 = _sceneManager->getSceneNode(sncelda1.str());
    Ogre::Entity* pieza2 = static_cast<Ogre::Entity*>(casilla2->getAttachedObject(0));
    pieza2->setMaterialName("Rojo");
    pieza2->setVisible(true);
    snbarco2.str("");
  }
  if(_p2->getVida()<1){
    std::cout << "Gana el jugador 1!" << '\n';
    turno = false;
  }
  if (!turno){
    usleep(1000000);
    std::cout << "Jugador 2 ataca y... ";
    j=0;
    
    if(aux22->getX()<0 && _p2->getTocados().size() > 0){aux22 = _p2->popTocado();}
    do{
      aux2 = selCelda(2, aux22);
      acierto = _p1->getTablero()->onClick(aux2);
      if(j>16){aux22->setX(-1);}
      j++;
      }while(acierto<0);
    std::cout << "en la posicion (" << aux2->getX()+1 << ","<< aux2->getY()+1 <<")"<<'\n';
    if(acierto>0){
      _p1->setVida(_p1->getVida()-1);
      snbarco1 << "B1(" << aux2->getX() << "," << aux2->getY() << ")";
      Ogre::SceneNode* casilla = _sceneManager->getSceneNode(snbarco1.str());
      Ogre::Entity* pieza = static_cast<Ogre::Entity*>(casilla->getAttachedObject(0));
      pieza->setMaterialName("Tocado");
      snbarco1.str("");
      if(acierto<2){
	aux22 = aux2;
	_p2->pushTocado(aux2);
      }
      else{aux22->setX(-1);
      }
    }
    if(_p1->getVida()<1){
      std::cout << "Gana el jugador 2!" << '\n';
    }
    turno = true;
  }
  return turno;
}
Celda* Juego::selCelda(int nplayer, Celda *anterior){
  Celda* aux;
  int rand = random(), rand2 = random();
  if(nplayer == 2){
    if(anterior->getX()>-1){
      if(rand%2 > 0){
	if(anterior->getX()<7){aux =_p1->getTablero()->getCelda(anterior->getX()+1, anterior->getY());}
	else if(anterior->getX()>-1){aux =_p1->getTablero()->getCelda(anterior->getX()-1, anterior->getY());}
      }
      else{
	if(anterior->getY()<7){aux =_p1->getTablero()->getCelda(anterior->getX(), anterior->getY()+1);}
	else{aux =_p1->getTablero()->getCelda(anterior->getX(), anterior->getY()-1);}
      }
    }
    else{aux = _p1->getTablero()->getCelda(rand%8, rand2%8);}
  }
  else{
    if(anterior->getX()>-1){
      if(rand%2>0){
	if(anterior->getX()<7){aux =_p2->getTablero()->getCelda(anterior->getX()+1, anterior->getY());}
	else{aux =_p2->getTablero()->getCelda(anterior->getX()-1, anterior->getY());}
      }
      else{
	if(anterior->getY()<7){aux =_p2->getTablero()->getCelda(anterior->getX(), anterior->getY()+1);}
	else{aux =_p2->getTablero()->getCelda(anterior->getX(), anterior->getY()-1);}
      }
    }
    else{aux = _p2->getTablero()->getCelda(rand%8, rand2%8);}
  }
  return aux;
}

void Juego::colocarBarcos(){

	double ini_x, x, z, tam_celda;
 	int n_celdas;
  	std::stringstream sncasilla, snbarco1, snbarco2, sentity;

	   /* Nodo base */
	  Ogre::Entity *ent = NULL, *entbar = NULL;
	  Ogre::SceneNode *nodo_cel = NULL, *nodo_bar = NULL;
	  tam_celda = 2; z = 1.5; ini_x= -7; n_celdas= 8;
	  Ogre::SceneNode* ntablero = _sceneManager->getSceneNode("ntablero");

	    /* Igualamos x la posicion inicial */
	    x = ini_x;
	    for(int f = 0; f < n_celdas; f++){
	        for(int c = 0; c < n_celdas; c++){
	            /* Nombre del nodo para esa celda */
	            sncasilla << "C" << f << "_"<< c;
	            /* Creamos el nodo para una determinada celda */
	            nodo_cel = ntablero->createChildSceneNode(sncasilla.str(), Ogre::Vector3(x, 1, z));
	             /* Para ese nodo creamos visualizacion estandar */ 
	            ent = _sceneManager->createEntity("Casilla.mesh");
	            ent->setQueryFlags(CUBE1);
	            ent->setVisible(false);
	            nodo_cel->attachObject(ent);
		        _p2->getTablero()->getCelda(f,c)->setNodo(nodo_cel);

		    if(_p1->getTablero()->getCelda(f,c)->getEstado()>0){
		      snbarco1 << "B1(" << f << "," << c << ")";
		      nodo_bar = ntablero->createChildSceneNode(snbarco1.str(), Ogre::Vector3(x, 1,-z));
	          std::cout << snbarco1.str() + "\n" << std::endl;
		      entbar = _sceneManager->createEntity("Barco.mesh");
		      entbar->setQueryFlags(STAGE);
		      entbar->setVisible(true);
		      nodo_bar->attachObject(entbar);
		    }
		    if(_p2->getTablero()->getCelda(f,c)->getEstado()>0){
		      snbarco2 << "B2(" << f << "," << c << ")";
		      nodo_bar = ntablero->createChildSceneNode(snbarco2.str(), Ogre::Vector3(x, 1, z));
		      entbar = _sceneManager->createEntity("Barco.mesh");
		      entbar->setQueryFlags(STAGE);
		      entbar->setVisible(false);/*cambiar a false*/
		      nodo_bar->attachObject(entbar);
		    }
	            x += tam_celda; sncasilla.str(""); snbarco1.str("");snbarco2.str(""); 
	      }//Fin for
	        x = ini_x;
	        z += tam_celda;
	    }//Fin for
}
