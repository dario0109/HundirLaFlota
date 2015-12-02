//#include <vector>

#include "Hundir.h"
#include "Barco.h"
#include "PlayerIA.h"

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
  
  loadResources();
  createScene();
  
  _framelistener = new MyFrameListener();
  _root->addFrameListener(_framelistener);
  
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
  Ogre::Entity* tablero = _sceneManager->createEntity("Tablero.mesh");
  Ogre::SceneNode* ntablero = _sceneManager->createSceneNode("ntablero");
  _sceneManager->getRootSceneNode()->addChild(ntablero);
  ntablero->attachObject(tablero);


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
/*Riballo modificaciones*/
vector<Barco*> Hundir::generarBarcos(){
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
  vector <Barco*> barcos1 = generarBarcos();
  Tablero t1;
  t1.crearTablero(8, barcos1);
  PlayerIA* p1;
  p1 = new PlayerIA();
  p1->crearPlayer("IA Player 1", t1, barcos1);
  p1->printState();
  /*vector <Barco*> barcos2 = generarBarcos();
  Tablero t2;
  t2.crearTablero(8, barcos2);
  _p2->crearPlayer("IA Player 2", t2, barcos2);
  _p2->printState();*/
}
