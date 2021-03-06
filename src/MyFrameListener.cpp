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

  _camera = cam;
  _sceneManager = sm; _win = win;
  _juego = new Juego(sm);
  _turno = 1;
  _estado = 1;
  
  
  srand((unsigned)time(NULL));   // Semilla aleatorios
  _win->getCustomAttribute("WINDOW", &windowHandle);
  wHandleStr << windowHandle;
  param.insert(make_pair("WINDOW", wHandleStr.str()));
  param.insert(std::make_pair(std::string("x11_mouse_grab"), std::string("false")));
  param.insert(std::make_pair(std::string("x11_mouse_hide"), std::string("false")));
  
  _inputManager = OIS::InputManager::createInputSystem(param);
  _keyboard = static_cast<OIS::Keyboard*>
    (_inputManager->createInputObject(OIS::OISKeyboard, false));
  _mouse = static_cast<OIS::Mouse*>
    (_inputManager->createInputObject(OIS::OISMouse, false));
  _mouse->getMouseState().width = _win->getWidth();
  _mouse->getMouseState().height = _win->getHeight();

  _mouse->capture();

  _raySceneQuery = _sceneManager->createRayQuery(Ray());

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


  bool mbleft; // Botones del raton pulsados

  _keyboard->capture();  _mouse->capture();   // Captura eventos

  int posx = _mouse->getMouseState().X.abs;   // Posicion del puntero
  int posy = _mouse->getMouseState().Y.abs;   //  en pixeles.

  // Botones del raton pulsados? -------------------------------------
  mbleft = _mouse->getMouseState().buttonDown(OIS::MB_Left);

 if(_keyboard->isKeyDown(OIS::KC_ESCAPE)) return false;
  switch(_estado){
    case 1:
      if(_keyboard->isKeyDown(OIS::KC_1)){
        _sceneManager->destroySceneNode("ninicio");
        _juego->generarTablero();
        _juego->generarPlayers();
        _juego->colocarBarcos(); 
        _estado = 5;
      }
      if(_keyboard->isKeyDown(OIS::KC_2)){
        _sceneManager->destroySceneNode("ninicio");
        _juego->crearCreditos();
        _estado = 2;
      }
    break;

    case 2:
      if(_keyboard->isKeyDown(OIS::KC_B)){
        _sceneManager->destroySceneNode("ncreditos");
        _juego->crearMenu();
        _estado = 1;
      }
      break;
       // Exit!

    case 5:
      if (mbleft) {
        uint32 mask;
        mask = CUBE1 | STAGE;  // Podemos elegir todo
        setRayQuery(posx, posy, mask);
        Ogre::RaySceneQueryResult &result = _raySceneQuery->execute();
        Ogre::RaySceneQueryResult::iterator it;
        if(result.begin()!=result.end()){
          it = result.begin();
          Ogre::SceneNode* nodo = it->movable->getParentSceneNode();
          Ogre::MovableObject* clickado = nodo->getAttachedObject(0);
          if(clickado->getQueryFlags()==CUBE1){
            if(_turno==1 && (int)it->movable->getParentSceneNode()->getName()[3]-48>=0 && (int)it->movable->getParentSceneNode()->getName()[3]-48<8 && (int)it->movable->getParentSceneNode()->getName()[5]-48>=0 && (int)it->movable->getParentSceneNode()->getName()[5]-48<8){
              _turno = _juego->simular((int)it->movable->getParentSceneNode()->getName()[3]-48, (int)it->movable->getParentSceneNode()->getName()[5 ]-48);//tabla ascii
            }
            if(_turno == 2){
              _estado = 6;
            }
          }
        }
      }
      break;
  case 6:
    if(_keyboard->isKeyDown(OIS::KC_RETURN)){
      _juego->reiniciar();
      _juego->generarPlayers();
      _juego->colocarBarcos();
      _estado = 5;
      _turno = 1;
      std::cout << _estado << std::endl;
    }
    break;
 }
  return true;
}
