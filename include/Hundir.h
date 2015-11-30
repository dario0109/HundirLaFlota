#include <Ogre.h>
#include "MyFrameListener.h"

class Hundir{
  
private:
  Ogre::SceneManager* _sceneManager;
  Ogre::Root* _root;
  MyFrameListener* _framelistener;
  
public:
  Hundir();
  ~Hundir();  
  int start();
  void loadResources();
  void createScene();
};
