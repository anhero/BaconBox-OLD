#include "Engine.h"

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

std::string Engine::applicationPath = "";


std::map<std::string, State*> Engine::states = std::map<std::string, State*>();
State* Engine::currentState = NULL;
State* Engine::lastState = NULL;
double Engine::lastUpdate = 0.0;
unsigned int Engine::loops = 0;
double Engine::nextUpdate = 0;
double Engine::updateDelay = 1.0 / DEFAULT_UPDATES_PER_SECOND;
unsigned int Engine::minFps = DEFAULT_MIN_FRAMES_PER_SECOND;
bool Engine::bufferSwapped = false;
bool Engine::renderedSinceLastUpdate = false;
sigly::Signal2<int, int> Engine::onInitialize = sigly::Signal2<int, int>();
int Engine::screenWidth = 0;
int Engine::screenHeight = 0;

State* Engine::addState(State* newState) {
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

void Engine::removeState(const std::string& name) {
	std::map<std::string, State*>::iterator toDelete = states.find(name);

	if(currentState != toDelete->second) {
		if(toDelete->second) {
			delete toDelete->second;
		}

		states.erase(toDelete);
	}
}

State* Engine::playState(const std::string& name) {
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

State* Engine::getCurrentState() {
	return currentState;
}

unsigned int Engine::getMinFps() {
	return minFps;
}

double Engine::getUpdatesPerSecond() {
	assert(updateDelay);
	return 1.0 / updateDelay;
}

double Engine::getUpdateDelay() {
	return updateDelay;
}

void Engine::setMinFps(unsigned int newMinFps) {
	minFps = newMinFps;
}

void Engine::setUpdatesPerSecond(double updatesPerSecond) {
	if(updatesPerSecond) {
		// Calculate the update delay.
		updateDelay = 1.0 / static_cast<double>(updatesPerSecond);
	}
}

void Engine::pulse() {
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

void Engine::initializeEngine(int newScreenWidth, int newScreenHeight) {
	screenWidth = newScreenWidth;
	screenHeight = newScreenHeight;
	TimeHelper::getInstance();
	InputManager::getInstance();
	onInitialize.shoot(screenWidth, screenHeight);
	GraphicDriver::initializeGraphicDriver(screenWidth, screenHeight);
	Font::initializeFontRenderer();
}

double Engine::getSinceLastUpdate() {
	return TimeHelper::getInstance().getSinceStartComplete() - lastUpdate;
}

int Engine::getScreenWidth() {
	return screenWidth;
}

int Engine::getScreenHeight() {
	return screenHeight;
}

bool Engine::isBufferSwapped() {
	return bufferSwapped;
}

void Engine::setBufferSwapped() {
	bufferSwapped = true;
}

void Engine::application(int argc, char* argv[]) {
	applicationPath = dirname(argv[0]);
}
