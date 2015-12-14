#include <Ogre.h>
#include "MyFrameListener.h"
#include "Tablero.h"
#include "Barco.h"
#include <vector>
#include "PlayerIA.h"

class Hundir{  
private:
  Ogre::SceneManager* _sceneManager;
  Ogre::Root* _root;
  MyFrameListener* _framelistener;
  Juego* _juego;
  
public:
  Hundir();
  ~Hundir();  
  int start();
  void loadResources();
  void createScene();
  
};
