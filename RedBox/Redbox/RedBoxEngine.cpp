#include "RedBoxEngine.h"

#include "TimeHelper.h"
#include "GraphicDriver.h"
#include "Font.h"
#include "AudioEngine.h"
#include "SoundEngine.h"
#include "MusicEngine.h"
#include "InputManager.h"
#include <libgen.h>
using namespace RedBox;

std::string RedBoxEngine::applicationPath = "";


std::map<std::string, State*> RedBoxEngine::states = std::map<std::string, State*>();
State* RedBoxEngine::currentState = NULL;
double RedBoxEngine::maxRenderDelay = 1.0 / 30.0;
double RedBoxEngine::updateDelay = 1.0 / 120.0;
double RedBoxEngine::lastUpdate = 0.0;
double RedBoxEngine::lastRender = 0.0;
double RedBoxEngine::deltaRatio = 0.0;
bool RedBoxEngine::bufferSwapped = false;
bool RedBoxEngine::renderedSinceLastUpdate = false;
sigly::Signal2<int, int> RedBoxEngine::onInitialize = sigly::Signal2<int, int>();
int RedBoxEngine::screenWidth = 0;
int RedBoxEngine::screenHeight = 0;

State* RedBoxEngine::addState(State* newState) {
	if(newState) {
		if(states.empty()) {
			currentState = newState;
		}
		states.insert(std::pair<std::string, State*>(newState->getName(), newState));
	}
	return newState;
}

void RedBoxEngine::removeState(const std::string& name) {
	std::map<std::string, State*>::iterator toDelete = states.find(name);
	if(currentState != toDelete->second) {
		states.erase(toDelete);
	}
}

State* RedBoxEngine::playState(const std::string& name) {
	currentState = states[name];
	return currentState;
}

State* RedBoxEngine::getCurrentState() {
	return currentState;
}

int RedBoxEngine::getFpsMin() {
	return static_cast<int>(1.0 / maxRenderDelay);
}

int RedBoxEngine::getUpdatesPerSecond() {
	return static_cast<int>(1.0 / updateDelay);
}

double RedBoxEngine::getDeltaRatio() {
	return deltaRatio;
}

void RedBoxEngine::setFpsMin(int fpsMin) {
	// Calculate the maximum render delay.
	double newMaxRenderDelay = 1.0 / static_cast<double>(fpsMin);
	// We make sure the maximum render delay is higher than the update delay.
	if(newMaxRenderDelay >= updateDelay) {
		maxRenderDelay = newMaxRenderDelay;
	}
}

void RedBoxEngine::setUpdatesPerSecond(int updatesPerSecond) {
	// Calculate the update delay.
	double newUpdateDelay = 1.0 / static_cast<double>(updatesPerSecond);
	// We make sure the maximum render delay is higher than the update delay.
	if(newUpdateDelay <= maxRenderDelay) {
		updateDelay = newUpdateDelay;
	}
}

void RedBoxEngine::pulse() {
	// We make sure the pointer to the current state is valid.
	if(currentState) {
		// We update the time from TimeHelper.
		TimeHelper::getInstance().refreshTime();
		// We check if we need to update.
		if(TimeHelper::getInstance().getSinceStartComplete() >= lastUpdate + updateDelay) {
			// We update the delta ratio.
			deltaRatio = 1.0 + (TimeHelper::getInstance().getSinceStartComplete() -
						  (lastUpdate + updateDelay)) / updateDelay;
			// We update the current state.
			currentState->update();
			renderedSinceLastUpdate = false;
			// We update the input manager.
			InputManager::getInstance()->update();
			// We take note of the time.
			if(lastUpdate) {
				lastUpdate += updateDelay;
			} else {
				lastUpdate = TimeHelper::getInstance().getSinceStartComplete();
			}
			//TimeHelper::getInstance()->sleep(0.01);
		}
		// We check that the delay between renders doesn't go too high or that
		// the updates aren't lagging behind.
		if(((TimeHelper::getInstance().getSinceStartComplete() >= lastUpdate + maxRenderDelay) ||
		   deltaRatio < 2.0) && !renderedSinceLastUpdate) {
			// We take note of the time at which the render was done.
			lastRender += maxRenderDelay;
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

bool RedBoxEngine::isBufferSwapped() {
	return bufferSwapped;
}

void RedBoxEngine::setBufferSwapped() {
	bufferSwapped = true;
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

double RedBoxEngine::getUpdateDelta() {
	return TimeHelper::getInstance().getSinceStartComplete() - lastUpdate;
}

int RedBoxEngine::getScreenWidth() {
	return screenWidth;
}

int RedBoxEngine::getScreenHeight() {
	return screenHeight;
}

void RedBoxEngine::application(int argc, char *argv[]){
	applicationPath = dirname(argv[0]);
}

double RedBoxEngine::getUpdateDelay(){
	return updateDelay;
}
