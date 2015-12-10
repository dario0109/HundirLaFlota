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
  std::vector<Barco*> generarBarcos();
  void generarPlayers();
  void simular();
  Celda* selCelda(int nplayer, Celda *anterior);

  
  bool _endGame;
  /*Tablero generarTablero(int dim);
  PlayerIA* getPlayer1();
  PlayerIA* getPlayer2();
  void setPlayer1(PlayerIA* p1);
  void setPlayer2(PlayerIA* p2);*/
};
