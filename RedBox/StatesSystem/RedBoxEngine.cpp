#include "RedBoxEngine.h"

#include "TimeHelper.h"
#include "Drawer.h"
#include "Font.h"
#include "AudioEngine.h"
#include "SoundEngine.h"
#include "MusicEngine.h"

using namespace RedBox;

std::map<std::string, State*> RedBoxEngine::states = std::map<std::string, State*>();
State* RedBoxEngine::currentState = NULL;
double RedBoxEngine::maxRenderDelay = 0.0;
double RedBoxEngine::updateDelay = 0.0;
double RedBoxEngine::lastUpdate = 0.0;
double RedBoxEngine::lastRender = 0.0;
double RedBoxEngine::deltaRatio = 0.0;

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
		TimeHelper::refreshTime();
		// We check if we need to update.
		if(TimeHelper::getSinceEpoch() >= lastUpdate + updateDelay) {
			// We update the delta ratio.
			deltaRatio = 1.0 + (TimeHelper::getSinceEpoch() - 
						  (lastUpdate + updateDelay)) / updateDelay;
			currentState->update();
			// We take note of the time.
			lastUpdate = TimeHelper::getSinceEpoch();
		}
		// We check that the delay between renders doesn't go too high or that
		// the updates aren't lagging behind.
		if((TimeHelper::getSinceEpoch() >= lastUpdate + maxRenderDelay) ||
		   deltaRatio < 2.0) {
			// We take note of the time at which the render was done.
			lastRender = TimeHelper::getSinceEpoch();
			currentState->render();
		}
	}
	if(AudioEngine::getSoundEngine()) {
		AudioEngine::getSoundEngine()->update();
	}
	if(AudioEngine::getMusicEngine()) {
		AudioEngine::getMusicEngine()->update();
	}
}

void RedBoxEngine::initializeEngine(int screenWidth, int screenHeight) {
	TimeHelper::init();
	Drawer::initializeDrawer(screenWidth, screenHeight);
	Font::initializeFontRenderer();
}

double RedBoxEngine::getUpdateDelta() {
	return TimeHelper::getSinceEpoch() - lastUpdate;
}