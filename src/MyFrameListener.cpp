/*********************************************************************
 * Módulo 2. Curso de Experto en Desarrollo de Videojuegos
 * Autor: Carlos González Morcillo     Carlos.Gonzalez@uclm.es
 *
 * You can redistribute and/or modify this file under the terms of the
 * GNU General Public License ad published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * and later version. See <http://www.gnu.org/licenses/>.
 *
 * This file is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.  
 *********************************************************************/
#include "MyFrameListener.h"

MyFrameListener::MyFrameListener(RenderWindow* win, Camera* cam, SceneManager *sm){
  OIS::ParamList param; size_t windowHandle;  ostringstream wHandleStr;

  /****************/
  /*param.insert(std::make_pair(std::string("WINDOW"), wHandleStr.str()));
  param.insert(std::make_pair(std::string("x11_mouse_grab"), std::string("false")));
  param.insert(std::make_pair(std::string("x11_mouse_hide"), std::string("false")));
  param.insert(std::make_pair(std::string("x11_keyboard_grab"), std::string("false")));
  param.insert(std::make_pair(std::string("XAutoRepeatOn"), std::string("true")));*/
  /********************/

  
  _camera = cam;
  _sceneManager = sm; _win = win;
  
  srand((unsigned)time(NULL));   // Semilla aleatorios
  _win->getCustomAttribute("WINDOW", &windowHandle);
  wHandleStr << windowHandle;
  //param.insert(make_pair("WINDOW", wHandleStr.str()));
  param.insert(std::make_pair(std::string("WINDOW"), wHandleStr.str()));
  param.insert(std::make_pair(std::string("x11_mouse_grab"), std::string("false")));
  param.insert(std::make_pair(std::string("x11_mouse_hide"), std::string("false")));

  _inputManager = OIS::InputManager::createInputSystem(param);
  _keyboard = static_cast<OIS::Keyboard*>
    (_inputManager->createInputObject(OIS::OISKeyboard,true /*false*/));
  //_keyboard->setEventCallback(this);
  
  _mouse = static_cast<OIS::Mouse*>
    (_inputManager->createInputObject(OIS::OISMouse, true/*false*/));
  /*_mouse->setEventCallback(this);/*
  _mouse->getMouseState().width = _win->getWidth();
  _mouse->getMouseState().height = _win->getHeight();*/
  /**/
  int left, top;
  unsigned int width, height, depth;
  win->getMetrics(width, height, depth, left, top);
  //this->setWindowExtents(width, height);
  /**/
  _raySceneQuery = _sceneManager->createRayQuery(Ray());
  //_selectedNode = NULL;
}

MyFrameListener::~MyFrameListener() {
  _inputManager->destroyInputObject(_keyboard);
  _inputManager->destroyInputObject(_mouse);
  _sceneManager->destroyQuery(_raySceneQuery);
  OIS::InputManager::destroyInputSystem(_inputManager);
}

Ray MyFrameListener::setRayQuery(int posx, int posy, uint32 mask) {
  Ogre::Ray rayMouse = _camera->getCameraToViewportRay
    (posx/float(_win->getWidth()), posy/float(_win->getHeight()));
  _raySceneQuery->setRay(rayMouse);
  _raySceneQuery->setSortByDistance(true);
  _raySceneQuery->setQueryMask(mask);
  return (rayMouse);
}

bool MyFrameListener::frameStarted(const FrameEvent& evt) {
  Vector3 vt(0,0,0);     Real tSpeed = 10.0;  
  Real deltaT = evt.timeSinceLastFrame;

  bool mbleft, mbmiddle, mbright; // Botones del raton pulsados

  _keyboard->capture();  _mouse->capture();   // Captura eventos

  int posx = _mouse->getMouseState().X.abs;   // Posicion del puntero
  int posy = _mouse->getMouseState().Y.abs;   //  en pixeles.

  if(_keyboard->isKeyDown(OIS::KC_ESCAPE)) return false;   // Exit!
/*
  // Operaciones posibles con el nodo seleccionado -------------------
  if (_selectedNode != NULL) {
    Real deltaTaux = deltaT;
    if(_keyboard->isKeyDown(OIS::KC_LSHIFT) ||    // Si pulsamos Shift
       _keyboard->isKeyDown(OIS::KC_RSHIFT))      // invertimos la
      deltaTaux *= -1;                            // operacion
    if(_keyboard->isKeyDown(OIS::KC_S))   
      _selectedNode->setScale(_selectedNode->getScale()+deltaTaux);
    if(_keyboard->isKeyDown(OIS::KC_R)) 
      _selectedNode->yaw(Degree(90)*deltaTaux);
    if(_keyboard->isKeyDown(OIS::KC_DELETE)) { 
      _sceneManager->getRootSceneNode()->
	removeAndDestroyChild(_selectedNode->getName());
      _selectedNode = NULL;
    }
  }
*/
  // Si usamos la rueda, desplazamos en Z la camara ------------------
  vt+= Vector3(0,0,-10)*deltaT * _mouse->getMouseState().Z.rel;   
  _camera->moveRelative(vt * deltaT * tSpeed);

  // Botones del raton pulsados? -------------------------------------
  mbleft = _mouse->getMouseState().buttonDown(OIS::MB_Left);
  mbmiddle = _mouse->getMouseState().buttonDown(OIS::MB_Middle);
  mbright = _mouse->getMouseState().buttonDown(OIS::MB_Right);

  
  if (mbmiddle) { // Con boton medio pulsado, rotamos camara ---------
    float rotx = _mouse->getMouseState().X.rel * deltaT * -1;
    float roty = _mouse->getMouseState().Y.rel * deltaT * -1;
    _camera->yaw(Radian(rotx));
    _camera->pitch(Radian(roty));
    cout << "Boton Medio" << endl;
  }
  
  if (mbleft) {  // Boton izquierdo o derecho -------------
  	uint32 mask;
    cout << "Boton Izquierdo" << endl;
    mask = STAGE | CUBE1 | CUBE2;  // Podemos elegir todo

    Ogre::Ray r = setRayQuery(posx, posy, mask);
    Ogre::RaySceneQueryResult &result = _raySceneQuery->execute();
    Ogre::RaySceneQueryResult::iterator it;
    it = result.begin();
    //std::cout << it->movable->getParentSceneNode()->getName() <<std::endl;

    if (it != result.end()) {
      if (mbleft) {
	if (it->movable->getParentSceneNode()->getName() == "Col_Suelo") {
	  SceneNode *nodeaux = _sceneManager->createSceneNode();
	  int i = rand()%2;   std::stringstream saux;
	  saux << "Cube" << i+1 << ".mesh";
	  Entity *entaux = _sceneManager->createEntity(saux.str());
	  entaux->setQueryFlags(i?CUBE1:CUBE2);
	  nodeaux->attachObject(entaux);
	  nodeaux->translate(r.getPoint(it->distance));
	  _sceneManager->getRootSceneNode()->addChild(nodeaux);
	}
      }
      _selectedNode = it->movable->getParentSceneNode();
      _selectedNode->showBoundingBox(true);
      }

  }  
  return true;
}


/*void MyFrameListener::setWindowExtents(int width, int height){

    const OIS::MouseState &mouseState = _mouse->getMouseState();
    mouseState.width = width;
    mouseState.height = height;
    }*/

void MyFrameListener::mouseMoved(const OIS::MouseEvent &e){
    Ogre::OverlayElement *oe;
    oe = _overlayManager->getOverlayElement("cursor");
    oe->setLeft(e.state.X.abs);  oe->setTop(e.state.Y.abs);
}
