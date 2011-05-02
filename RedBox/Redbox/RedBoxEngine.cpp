#include "RedBoxEngine.h"

#include <cassert>

#include "TimeHelper.h"
#include "GraphicDriver.h"
#include "Font.h"
#include "AudioEngine.h"
#include "SoundEngine.h"
#include "MusicEngine.h"
#include "InputManager.h"
#include "TimerManager.h"
#include "Debug.h"
#include <libgen.h>
using namespace RedBox;

std::string RedBoxEngine::applicationPath = "";


std::map<std::string, State*> RedBoxEngine::states = std::map<std::string, State*>();
State* RedBoxEngine::currentState = NULL;
State* RedBoxEngine::lastState = NULL;
double RedBoxEngine::lastUpdate = 0.0;
unsigned int RedBoxEngine::loops = 0;
double RedBoxEngine::nextUpdate = 0;
double RedBoxEngine::updateDelay = 1.0 / DEFAULT_UPDATES_PER_SECOND;
unsigned int RedBoxEngine::minFps = DEFAULT_MIN_FRAMES_PER_SECOND;
bool RedBoxEngine::bufferSwapped = false;
bool RedBoxEngine::renderedSinceLastUpdate = false;
sigly::Signal2<int, int> RedBoxEngine::onInitialize = sigly::Signal2<int, int>();
int RedBoxEngine::screenWidth = 0;
int RedBoxEngine::screenHeight = 0;

State* RedBoxEngine::addState(State* newState) {
	if(newState) {
		if(states.empty()) {
			currentState = newState;
		} else {
			newState->deactivateSlots();
		}
		states.insert(std::pair<std::string, State*>(newState->getName(), newState));
	}
	return newState;
}

void RedBoxEngine::removeState(const std::string& name) {
	std::map<std::string, State*>::iterator toDelete = states.find(name);
	if(currentState != toDelete->second) {
		if(toDelete->second) {
			delete toDelete->second;
		}
		states.erase(toDelete);
	}
}

State* RedBoxEngine::playState(const std::string& name) {
	// We make sure the state asked for exists.
	std::map<std::string, State*>::iterator it = states.find(name);
	if(it != states.end()) {
		currentState = it->second;
	} else {
		RB_ECHO("State \"" << name <<
				"\" doesn't exist so it cannot be played.");
	}
	return currentState;
}

State* RedBoxEngine::getCurrentState() {
	return currentState;
}

unsigned int RedBoxEngine::getMinFps() {
	return minFps;
}

double RedBoxEngine::getUpdatesPerSecond() {
	assert(updateDelay);
	return 1.0 / updateDelay;
}

double RedBoxEngine::getUpdateDelay() {
	return updateDelay;
}

void RedBoxEngine::setMinFps(unsigned int newMinFps) {
	minFps = newMinFps;
}

void RedBoxEngine::setUpdatesPerSecond(double updatesPerSecond) {
	if(updatesPerSecond) {
		// Calculate the update delay.
		updateDelay = 1.0 / static_cast<double>(updatesPerSecond);
	}
}

void RedBoxEngine::pulse() {
	// We make sure the pointer to the current state is valid.
	if(currentState) {
		TimeHelper::getInstance().refreshTime();
		// We update the time from TimeHelper.
		if(!nextUpdate) {
			nextUpdate = TimeHelper::getInstance().getSinceStartComplete();
		}
		loops = 0;
		while(TimeHelper::getInstance().getSinceStartComplete() > nextUpdate &&
			  loops < minFps) {
			// We refresh the time.
			TimeHelper::getInstance().refreshTime();

			// We call the focus methods if needed.
			if(currentState != lastState) {
				if(lastState) {
					lastState->onLoseFocus();
				}
				currentState->onGetFocus();
			}

			lastState = currentState;
			// We update the current state.
			currentState->update();
			renderedSinceLastUpdate = false;
			// We update the input manager.
			InputManager::getInstance().update();
			// We update the timers.
			TimerManager::update();
			nextUpdate += updateDelay;
			lastUpdate = TimeHelper::getInstance().getSinceStartComplete();
			++loops;
		}
		if(!renderedSinceLastUpdate) {
			currentState->render();
			renderedSinceLastUpdate = true;
			bufferSwapped = false;
		}
		if(AudioEngine::getSoundEngine()) {
			AudioEngine::getSoundEngine()->update();
		}
		if(AudioEngine::getMusicEngine()) {
			AudioEngine::getMusicEngine()->update();
		}
	}
}

void RedBoxEngine::initializeEngine(int newScreenWidth, int newScreenHeight) {
	screenWidth = newScreenWidth;
	screenHeight = newScreenHeight;
	TimeHelper::getInstance();
	InputManager::getInstance();
	onInitialize.shoot(screenWidth, screenHeight);
	GraphicDriver::initializeGraphicDriver(screenWidth, screenHeight);
	Font::initializeFontRenderer();
}

double RedBoxEngine::getSinceLastUpdate() {
	return TimeHelper::getInstance().getSinceStartComplete() - lastUpdate;
}

int RedBoxEngine::getScreenWidth() {
	return screenWidth;
}

int RedBoxEngine::getScreenHeight() {
	return screenHeight;
}

bool RedBoxEngine::isBufferSwapped() {
	return bufferSwapped;
}

void RedBoxEngine::setBufferSwapped() {
	bufferSwapped = true;
}

void RedBoxEngine::application(int argc, char *argv[]){
	applicationPath = dirname(argv[0]);
}
