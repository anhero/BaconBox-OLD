#include <BaconBox.h>
#include "PlayState.h"
int main(int argc, char* argv[]) {
	// Initialize BaconBox
	BaconBox::Engine::application(argc, argv);
    
	// We set the number of updates per second to be executed.
	BaconBox::Engine::setUpdatesPerSecond(60);
    
	// We set the minimum number of frames per second that are
	// tolerated before sacrificing on the number of updates per second.
	BaconBox::Engine::setMinFps(60);
    
	// We initialize the engine with a screen resolution.
	BaconBox::Engine::initializeEngine(320, 480);
    
	// We add our states to the engine. The first state added
	// automatically starts playing.
	BaconBox::Engine::addState(new BaconBox::PlayState());
    
	// Then start everything.
	BaconBox::Engine::showMainWindow();
    
	return 0;
}
