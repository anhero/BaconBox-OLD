#include "RedBoxEngine.h"

using namespace RedBox;

State* State::addState(State* newState) {
	return newState;
}

void State::removeState(const std::string& name) {
	std::map<std::string, State*>::iteratir toDelete = states.find(name);
	if(currentState != toDelete->second) {
		states.erase(toDelete);
	}
}

State* State::playState(const std::string& name) {
	currentState = states[name];
}

State* State::getCurrentState() {
	return currentState;
}

unsigned int State::getFpsMin() {
	return fpsMin;
}