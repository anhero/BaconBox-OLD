#ifndef __LOADER_H
#define __LOADER_H

#include <RedBox.h>

#include "PlayState.h"
namespace RedBox {
	class Loader  {
	public:
		static void load(){
			//Setup and add your first state here
			RedBox::Engine::setUpdatesPerSecond(60);
			RedBox::Engine::setMinFps(5);
			RedBox::Engine::initializeEngine(320, 480);
			Engine::addState(new PlayState());
		}
	};
}
#endif
