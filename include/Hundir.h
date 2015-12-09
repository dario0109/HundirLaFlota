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
  Ogre::OverlayManager* _overlayManager;
  PlayerIA* _p1;
  PlayerIA* _p2;
  
public:
  Hundir();
  ~Hundir();  
  int start();
  void loadResources();
  void createScene();
  void createOverlay();
  
  PlayerIA* getPlayer1();
  PlayerIA* getPlayer2();
  void setPlayer1(PlayerIA* p1);
  void setPlayer2(PlayerIA* p2);
  std::vector<Barco*> generarBarcos();
  Tablero generarTablero(int dim);
  void generarPlayers();
  void simular();
  Celda* selCelda(int nplayer, Celda& anterior);
};
