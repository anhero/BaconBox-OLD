#ifndef __LOADER_H
#define __LOADER_H

#include <BaconBox.h>

#include "PlayState.h"
namespace BaconBox {
	class Loader  {
	public:
		static void load(){
			//Setup and add your first state here
			BaconBox::Engine::setUpdatesPerSecond(60);
			BaconBox::Engine::setMinFps(5);
			BaconBox::Engine::initializeEngine(320, 480);
			Engine::addState(new PlayState());
		}
	};
}
#endif
