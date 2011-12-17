#include <RedBox.h>
#include "PlayState.h"
int main(int argc, char* argv[]) {
	// Initialize RedBox
	RedBox::Engine::application(argc, argv);
    
	// We set the number of updates per second to be executed.
	RedBox::Engine::setUpdatesPerSecond(60);
    
	// We set the minimum number of frames per second that are
	// tolerated before sacrificing on the number of updates per second.
	RedBox::Engine::setMinFps(60);
    
	// We initialize the engine with a screen resolution.
	RedBox::Engine::initializeEngine(320, 480);
    
	// We add our states to the engine. The first state added
	// automatically starts playing.
	RedBox::Engine::addState(new RedBox::PlayState());
    
	// Then start everything.
	RedBox::Engine::showMainWindow();
    
	return 0;
}
