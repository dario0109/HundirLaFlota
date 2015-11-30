#include <OgreFrameListener.h>

class MyFrameListener : public Ogre::FrameListener {
public:
  bool frameStarted(const Ogre::FrameEvent& evt);  
  bool frameEnded(const Ogre::FrameEvent& evt); 
};
