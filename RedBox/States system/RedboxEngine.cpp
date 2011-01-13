#include "RedboxEngine.h"
#include "Font.h"
using namespace RedBox;

State* RedBoxEngine::currentState = NULL;
std::list<State*> RedBoxEngine::loadedStates = std::list<State*>();

void RedBoxEngine::initialize(){
	Font::setupFontRenderer();
}


void RedBoxEngine::addState(State * aState, bool andPlay) {
	loadedStates.push_front(aState);
	// If we need to also play it.
	if(andPlay) {
		playState(aState->getName());
	}
}

void RedBoxEngine::playState(const std::string& name) {
	//TODO: Print a message if the state passed in parameter doesnt exist (his "name" parameter is not set)
	// We initialize the variables used for searching for the State to play.
	std::list<State*>::iterator i = loadedStates.begin();
	bool stateFound = false;
	while (!stateFound && i != loadedStates.end()) {
		// If we found the new State to be played.
		if((*i)->getName() == name) {
			// We make sure there IS a currentState loaded.
			if(currentState != NULL) currentState->stopMusic();
			// We take note of the new State.
			currentState = *i;
			// We make sure the state is initialized.
			if ( ! currentState->isInitialized()) {
				currentState->initializeState();
			}
			currentState->resumingState();
			// We signal that the new State has been found.
			stateFound = true;
		}
		else {
			i++;
		}

	}
}

/**
 * Calls Render() on current State object.
 *
 * NEEDS COMMENT APPROBATION BY FUNCTION AUTHOR
 */
void RedBoxEngine::render() {
	currentState->render();
}

/**
 * Calls Update() on current State object.
 *
 * NEEDS COMMENT APPROBATION BY FUNCTION AUTHOR
 */
void RedBoxEngine::update() {
	TimeHelper::refreshTime();
	currentState->update();
}

State * RedBoxEngine::getCurrentState(){
	return currentState;
}

