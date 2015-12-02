#ifndef CELDA
#define CELDA

#include <Ogre.h>

class Celda{
 public:
  Celda();

  int getX() const;
  int getY() const;
  int getEstado() const;
  Ogre::SceneNode* getNodo() const;

  void setX(int x);
  void setY(int y);
  void setEstado(int estado);
  void setNodo(Ogre::SceneNode *n);

 private:
  int _estado, _x, _y;
  Ogre::SceneNode *_nodo;
};
#endif
