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

#include "Hundir.h" 

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
  Ogre::Entity* plano1 = _sceneManager->createEntity("Cube.mesh");
  Ogre::SceneNode* nplano1 = _sceneManager->createSceneNode("nplano1");
  _sceneManager->getRootSceneNode()->addChild(nplano1);
  nplano1->attachObject(plano1);
  nplano1->setPosition(0,0,8.5);
  plano1 = _sceneManager->createEntity("Cube.mesh");
  Ogre::SceneNode* nplano2 = _sceneManager->createSceneNode("nplano2");
  _sceneManager->getRootSceneNode()->addChild(nplano2);
  nplano2->attachObject(plano1);
  nplano2->setPosition(0,0,-8.5);
  Ogre::Entity* barrera = _sceneManager->createEntity("Barrera.mesh");
  Ogre::SceneNode* nbarrera = _sceneManager->createSceneNode("nbarrera");
  _sceneManager->getRootSceneNode()->addChild(nbarrera);
  nbarrera->attachObject(barrera);
  nbarrera->setPosition(0,0,0);
  nbarrera->yaw(Ogre::Degree(90));
  _sceneManager->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
}
