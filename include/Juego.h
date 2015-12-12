#include <Ogre.h>
#include "Tablero.h"
#include "Barco.h"
#include <vector>
#include "PlayerIA.h"

#define STAGE 1 << 0  // Mascara para el escenario
#define CUBE1 1 << 1  // Mascara para objetos de tipo 1
#define CUBE2 1 << 2

class Juego{  
private:
  Ogre::SceneManager* _sceneManager;
  PlayerIA* _p1;
  PlayerIA* _p2;
  
public:
  Juego(Ogre::SceneManager* sm);
  ~Juego();  
  std::vector<Barco*> generarBarcos();

  void colocarBarcos();
  void generarPlayers();
  bool simular(int x, int y);
  Celda* selCelda(int nplayer, Celda *anterior);

  
  bool _endGame;
  /*Tablero generarTablero(int dim);
  PlayerIA* getPlayer1();
  PlayerIA* getPlayer2();
  void setPlayer1(PlayerIA* p1);
  void setPlayer2(PlayerIA* p2);*/
};
