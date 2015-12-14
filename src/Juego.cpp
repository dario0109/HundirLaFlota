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

void Juego::generarTablero(){
  Ogre::Entity* tablero = _sceneManager->createEntity("Tablero.mesh");
  Ogre::SceneNode* ntablero = _sceneManager->createSceneNode("ntablero");
  tablero->setQueryFlags(STAGE);
  _sceneManager->getRootSceneNode()->addChild(ntablero);
  ntablero->attachObject(tablero);
}
int Juego::simular(int x, int y){
  std::stringstream snbarco1, snbarco2, sncelda1, sncelda2;
  int acierto = -1;
  Celda* aux1,* aux2,* aux22;
  int turno = 1;
  
  aux22 = new Celda();
  int i = 0;
  int j = 0;    i++;
  aux1 = _p2->getTablero()->getCelda(x,y);
  acierto = (_p2->getTablero())->onClick(aux1);
  if(acierto>0){
    _p2->setVida(_p2->getVida()-1);
    snbarco2 << "B2(" << aux1->getX() << "," << aux1->getY() << ")";
    Ogre::SceneNode* casilla = _sceneManager->getSceneNode(snbarco2.str());
    Ogre::Entity* pieza = static_cast<Ogre::Entity*>(casilla->getAttachedObject(0));
    //std::cout << "Cambiando color" << std::endl;
    pieza->setQueryFlags(STAGE);
    pieza->setMaterialName("Tocado");
    pieza->setVisible(true);
    snbarco2.str("");
    if(acierto > 1){
      //std::cout << "Estado de celda en hundido " << aux1->getEstado() << '\n';
      for(unsigned int w = 0; w < (_p2->getBarcos().at(aux1->getEstado()-21))->getPosiciones()->size(); w++){
	snbarco2 << "B2(" << _p2->getBarcos().at(aux1->getEstado()-21)->getPosiciones()->at(w).first << "," << _p2->getBarcos().at(aux1->getEstado()-21)->getPosiciones()->at(w).second << ")";
	Ogre::SceneNode* casilla = _sceneManager->getSceneNode(snbarco2.str());
	Ogre::Entity* pieza = static_cast<Ogre::Entity*>(casilla->getAttachedObject(0));
	//std::cout << "Cambiando color" << std::endl;
	pieza->setMaterialName("Hundido");
	pieza->setVisible(true);
	snbarco2.str("");
      }
    }
  }
  else if(acierto < 0){//casilla ya pulsada
    turno = 0;
  }
  else{//agua
    sncelda1 << "C1(" << aux1->getX() << "," << aux1->getY() << ")";
    Ogre::SceneNode* casilla2 = _sceneManager->getSceneNode(sncelda1.str());
    Ogre::Entity* pieza2 = static_cast<Ogre::Entity*>(casilla2->getAttachedObject(0));
    pieza2->setQueryFlags(STAGE);
    pieza2->setMaterialName("Agua");
    pieza2->setVisible(true);
    sncelda1.str("");
  }
  if(_p2->getVida()<1){
    turno = 2;
  }
  if (turno==1){
    usleep(1000000);
    j=0;
    
    if(aux22->getX()<0 && _p2->getTocados().size() > 0){aux22 = _p2->popTocado();}
    do{
      aux2 = selCelda(2, aux22);
      acierto = _p1->getTablero()->onClick(aux2);
      if(j>64){aux22->setX(-1);}
      j++;
    }while(acierto<0);
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
      else{
        aux22->setX(-1);
	for(unsigned int w = 0; w < (_p1->getBarcos().at(aux2->getEstado()-21))->getPosiciones()->size(); w++){
	  snbarco2 << "B1(" << _p1->getBarcos().at(aux2->getEstado()-21)->getPosiciones()->at(w).first << "," << _p1->getBarcos().at(aux2->getEstado()-21)->getPosiciones()->at(w).second << ")";
	  Ogre::SceneNode* casilla = _sceneManager->getSceneNode(snbarco2.str());
	  Ogre::Entity* pieza = static_cast<Ogre::Entity*>(casilla->getAttachedObject(0));
	  //std::cout << "Cambiando color" << std::endl;
	  pieza->setMaterialName("Hundido");
	  pieza->setVisible(true);
	  snbarco2.str("");
	}
      }
    }
    else{
      sncelda2 << "C2(" << aux2->getX() << "," << aux2->getY() << ")";
      Ogre::SceneNode* casilla2 = _sceneManager->getSceneNode(sncelda2.str());
      Ogre::Entity* pieza2 = static_cast<Ogre::Entity*>(casilla2->getAttachedObject(0));
      pieza2->setMaterialName("Agua");
      pieza2->setVisible(true);
      sncelda2.str("");
    }
    if(_p1->getVida()<1){turno = 2;}
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
	            sncasilla << "C1(" << f << ","<< c << ")";
	            /* Creamos el nodo para una determinada celda */
	            nodo_cel = ntablero->createChildSceneNode(sncasilla.str(), Ogre::Vector3(x, 1, z));
	             /* Para ese nodo creamos visualizacion estandar */ 
	            ent = _sceneManager->createEntity("Casilla.mesh");
	            ent->setQueryFlags(CUBE1);
	            ent->setVisible(false);
	            nodo_cel->attachObject(ent);
		    //_p2->getTablero()->getCelda(f,c)->setNodo(nodo_cel);
              sncasilla.str("");

               /* Nombre del nodo para esa celda */
              sncasilla << "C2(" << f << ","<< c << ")";
              /* Creamos el nodo para una determinada celda */
              nodo_cel = ntablero->createChildSceneNode(sncasilla.str(), Ogre::Vector3(x, 1, -z));
               /* Para ese nodo creamos visualizacion estandar */ 
              ent = _sceneManager->createEntity("Casilla.mesh");
              ent->setQueryFlags(STAGE);
              ent->setVisible(false);
              nodo_cel->attachObject(ent);
              //_p1->getTablero()->getCelda(f,c)->setNodo(nodo_cel);

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
		      entbar->setQueryFlags(CUBE1);
		      entbar->setVisible(false);/*cambiar a false*/
		      nodo_bar->attachObject(entbar);
		    }
	            x += tam_celda; sncasilla.str(""); snbarco1.str("");snbarco2.str(""); 
	      }//Fin for
	        x = ini_x;
	        z += tam_celda;
	    }//Fin for
}

void Juego::reiniciar(){
  _p1->getTablero()->limpiarTablero();
  _p2->getTablero()->limpiarTablero();
  Ogre::SceneNode* ntablero = _sceneManager->getSceneNode("ntablero");
  Ogre::SceneNode::ChildNodeIterator itChild = ntablero->getChildIterator();
  while ( itChild.hasMoreElements() ){
      Ogre::SceneNode* childNode = static_cast<Ogre::SceneNode*>(itChild.getNext());
      Ogre::SceneNode::ObjectIterator itObject = childNode->getAttachedObjectIterator();
      while ( itObject.hasMoreElements() ){
        Ogre::MovableObject* object = static_cast<Ogre::MovableObject*>(itObject.getNext());
        childNode->getCreator()->destroyMovableObject(object);
      }
      _sceneManager->destroySceneNode(childNode->getName());  
  }
}

void Juego::crearMenu(){
  Ogre::Entity* inicio = _sceneManager->createEntity("Inicio.mesh");
  Ogre::SceneNode* ninicio = _sceneManager->createSceneNode("ninicio");
  _sceneManager->getRootSceneNode()->addChild(ninicio);
  ninicio->attachObject(inicio);
  ninicio->yaw(Ogre::Degree(-15));
  ninicio->pitch(Ogre::Degree(50));
  ninicio->roll(Ogre::Degree(90));
  ninicio->setScale(1,1.5,1.2);
  ninicio->setPosition(0,0,-2);
}

void Juego::crearCreditos(){
  Ogre::Entity* creditos = _sceneManager->createEntity("Creditos.mesh");
  Ogre::SceneNode* ncreditos = _sceneManager->createSceneNode("ncreditos");
  _sceneManager->getRootSceneNode()->addChild(ncreditos);
  ncreditos->attachObject(creditos);
  ncreditos->yaw(Ogre::Degree(-15));
  ncreditos->pitch(Ogre::Degree(50));
  ncreditos->roll(Ogre::Degree(90));
  ncreditos->pitch(Ogre::Degree(90));
  ncreditos->setScale(1,1,1.2);
  ncreditos->setPosition(0,0,-2);
}
