#include <vector>

#include "Hundir.h"
#include "Barco.h"
#include "PlayerIA.h"
#include <unistd.h>

using namespace std;

Hundir::Hundir() {
  _sceneManager = NULL;
  _framelistener = NULL;
}

Hundir::~Hundir() {
  delete _root;
  delete _framelistener;
}

int Hundir::start() {
  _root = new Ogre::Root();
  
  if(!_root->restoreConfig()) {
    _root->showConfigDialog();
    _root->saveConfig();
  }
  
  Ogre::RenderWindow* window = _root->initialise(true,"Hundir Example");
  _sceneManager = _root->createSceneManager(Ogre::ST_GENERIC);
  
  Ogre::Camera* cam = _sceneManager->createCamera("MainCamera");
  cam->setPosition(Ogre::Vector3(-10,30,35));
  cam->lookAt(Ogre::Vector3(0,0,0));
  cam->setNearClipDistance(5);
  cam->setFarClipDistance(10000);

  Ogre::Viewport* viewport = window->addViewport(cam);
  viewport->setBackgroundColour(Ogre::ColourValue(0.0,0.0,0.0));
  double width = viewport->getActualWidth();
  double height = viewport->getActualHeight();
  cam->setAspectRatio(width / height);

  generarPlayers();
  
  loadResources();
  createScene();

  simular();
  std::cout << "Antes MyFrameListener" << std::endl;
  _framelistener = new MyFrameListener(window, cam, _sceneManager);
  _root->addFrameListener(_framelistener);
  std::cout << "Añadido" << std::endl;
  _root->startRendering();
  return 0;
}

void Hundir::loadResources() {
  Ogre::ConfigFile cf;
  cf.load("resources.cfg");
  
  std::cout << "Inicio de load resources" << std::endl;
  Ogre::ConfigFile::SectionIterator sI = cf.getSectionIterator();
  Ogre::String sectionstr, typestr, datastr;
  while (sI.hasMoreElements()) {
    sectionstr = sI.peekNextKey();
    Ogre::ConfigFile::SettingsMultiMap *settings = sI.getNext();
    Ogre::ConfigFile::SettingsMultiMap::iterator i;
    for (i = settings->begin(); i != settings->end(); ++i) {
      typestr = i->first;    datastr = i->second;
      Ogre::ResourceGroupManager::getSingleton().addResourceLocation
            (datastr, typestr, sectionstr);	
    }
  }
  Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void Hundir::createScene() {
  double ini_x, x, z, tam_celda;
  int n_celdas;
  std::stringstream sncasilla, snbarco, sentity;

   /* Nodo base */
  Ogre::Entity *ent = NULL, *entbar = NULL;
  Ogre::SceneNode *nodo_cel = NULL, *nodo_bar = NULL;

  Ogre::Entity* tablero = _sceneManager->createEntity("Tablero.mesh");
  Ogre::SceneNode* ntablero = _sceneManager->createSceneNode("ntablero");
  _sceneManager->getRootSceneNode()->addChild(ntablero);
  ntablero->attachObject(tablero);

  tam_celda = 2; z = 1.5; ini_x= -7; n_celdas= 8;

    /* Igualamos x la posicion inicial */
    x = ini_x;
    for(int f = 0; f < n_celdas; f++){
        for(int c = 0; c < n_celdas; c++){
            /* Nombre del nodo para esa celda */
            sncasilla << "C" << f << "_"<< c;
            /* Creamos el nodo para una determinada celda */
            nodo_cel = ntablero->createChildSceneNode(sncasilla.str(), Ogre::Vector3(x, 1, z));
	    /****************/
	    if(_p1->getTablero()->getCelda(f,c)->getEstado()>0){
	      snbarco << "B" << f << "_" << c;
	      nodo_bar = ntablero->createChildSceneNode(snbarco.str(), Ogre::Vector3(x, 1, -z));
	      entbar = _sceneManager->createEntity("Barco.mesh");
	      entbar->setQueryFlags(CUBE1);
	      entbar->setVisible(true);
	      nodo_bar->attachObject(entbar);
	      }
	    /****************/
             /* Para ese nodo creamos visualizacion estandar */ 
            ent = _sceneManager->createEntity("Casilla.mesh");
            ent->setQueryFlags(CUBE1);
            ent->setVisible(false);
            nodo_cel->attachObject(ent);

           
            x += tam_celda; sncasilla.str(""); sentity.str("");
        }//Fin for
        x = ini_x;
        z += tam_celda;  
    }//Fin for

    /* Sombras */
    _sceneManager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);
    _sceneManager->setShadowColour(Ogre::ColourValue(0.5, 0.5, 0.5) );
    _sceneManager->setAmbientLight(Ogre::ColourValue(0.9, 0.9, 0.9));
    _sceneManager->setShadowTextureCount(2);
    _sceneManager->setShadowTextureSize(512);

    /* Iluminacion */
    Ogre::Light *light = _sceneManager->createLight("Light");
    light->setType(Ogre::Light::LT_SPOTLIGHT);
    light->setDirection(Ogre::Vector3(0,-1,0));
    light->setSpotlightInnerAngle(Ogre::Degree(25.0f));
    light->setSpotlightOuterAngle(Ogre::Degree(200.0f));
    light->setPosition(0, 150, 0);
    light->setSpecularColour(1, 1, 1);
    light->setDiffuseColour(1, 1, 1);
    light->setSpotlightFalloff(5.0f);
    light->setCastShadows(true);
}
std::vector<Barco*> Hundir::generarBarcos(){
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
void Hundir::generarPlayers(){
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
void Hundir::simular(){
  int acierto = -1;
  Celda* aux1,* aux11,* aux2,* aux22;
  aux11 = new Celda();
  aux22 = new Celda();
  int i = 0;
  int j = 0;
  while(true){
    i++;
    std::cout << "Turno " << i << '\n';
    std::cout << "Vida J1 = " << _p1->getVida() << '\n';
    std::cout << "Vida J2 = " << _p2->getVida() << '\n';
    std::cout << "Jugador 1 ataca y... ";
    j = 0;
    if(aux11->getX()<0 && _p1->getTocados().size() > 0){aux11 = _p1->popTocado();}
    do{
      aux1 = selCelda(1, aux11);
      acierto = (_p2->getTablero())->onClick(aux1);
      if(j>16){aux11->setX(-1);}//chapuza aqui
      j++;
    }while(acierto<0);
    std::cout << " en la posicion (" << aux1->getX()+1 << ","<< aux1->getY()+1 <<")"<<'\n';
    if(acierto>0){
      _p2->setVida(_p2->getVida()-1);
      if(acierto<2){
	aux11 = aux1;
	_p1->pushTocado(aux1);
      }
      else{aux11->setX(-1);}
    }
    if(_p2->getVida()<1){
      std::cout << "Gana el jugador 1!" << '\n';
      break;
    }
    std::cout << "Jugador 2 ataca y... ";
    j=0;

    if(aux22->getX()<0 && _p2->getTocados().size() > 0){aux22 = _p2->popTocado();}
    do{
      aux2 = selCelda(2, aux22);
      acierto = _p1->getTablero()->onClick(aux2);
      if(j>16){aux22->setX(-1);}//chapuza aqui
      j++;
    }while(acierto<0);
    std::cout << "en la posicion (" << aux2->getX()+1 << ","<< aux2->getY()+1 <<")"<<'\n';
    if(acierto>0){
      _p1->setVida(_p1->getVida()-1);
      if(acierto<2){
	aux22 = aux2;
	_p2->pushTocado(aux2);
      }
      else{aux22->setX(-1);}
    }
    if(_p1->getVida()<1){
      std::cout << "Gana el jugador 2!" << '\n';
      break;
    }
  }
}
Celda* Hundir::selCelda(int nplayer, Celda *anterior){
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
