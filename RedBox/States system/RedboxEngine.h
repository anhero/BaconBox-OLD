#ifndef __REDBOXENGINE_H
#define __REDBOXENGINE_H

#include <string>
#include <list>
#include <iostream>

#include "State.h"
#include "TimeHelper.h"

namespace RedBox {
	class State;
class RedBoxEngine {
public:
	static std::list<State*> loadedStates;
	static State* currentState;
	static void initialize();
	static void addState(State * aState, bool andPlay = true);
	static void playState(const std::string& name);
	static void render();
	static void update();
	static State * getCurrentState();
};
}
#endif