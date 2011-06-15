#include "Engine.h"

#include <cassert>
#include <cstdlib>
#include <algorithm>

#include "TimeHelper.h"
#include "GraphicDriver.h"
#include "DeleteHelper.h"

#include "Font.h"

#include "AudioEngine.h"
#include "SoundEngine.h"
#include "MusicEngine.h"
#include "InputManager.h"
#include "TimerManager.h"
#include "Console.h"
#include <libgen.h>

#include RB_MAINWINDOW_INCLUDE

using namespace RedBox;

sigly::Signal2<unsigned int, unsigned int> Engine::onInitialize = sigly::Signal2<unsigned int, unsigned int>();

State* Engine::addState(State* newState) {
	Engine& engine = getInstance();
	if(newState) {
		if(engine.states.empty()) {
			engine.currentState = newState;
		} else {
			newState->deactivateSlots();
		}

		engine.states.insert(std::pair<std::string, State*>(newState->getName(), newState));
	}

	return newState;
}

void Engine::removeState(const std::string& name) {
	Engine& engine = getInstance();
	std::map<std::string, State*>::iterator toDelete = engine.states.find(name);

	if(engine.currentState != toDelete->second) {
		if(toDelete->second) {
			delete toDelete->second;
		}

		engine.states.erase(toDelete);
	}
}

State* Engine::playState(const std::string& name) {
	Engine& engine = getInstance();
	// We make sure the state asked for exists.
	std::map<std::string, State*>::iterator it = engine.states.find(name);

	if(it != engine.states.end()) {
		engine.currentState = it->second;
	} else {
		Console::print("State \"" + name +
		        "\" doesn't exist so it cannot be played.");
	}

	return engine.currentState;
}

State* Engine::getCurrentState() {
	return getInstance().currentState;
}

unsigned int Engine::getMinFps() {
	return getInstance().minFps;
}

double Engine::getUpdatesPerSecond() {
	assert(getInstance().updateDelay);
	return 1.0 / getInstance().updateDelay;
}

double Engine::getUpdateDelay() {
	return getInstance().updateDelay;
}

void Engine::setMinFps(unsigned int newMinFps) {
	getInstance().minFps = newMinFps;
}

void Engine::setUpdatesPerSecond(double updatesPerSecond) {
	if(updatesPerSecond) {
		// Calculate the update delay.
		getInstance().updateDelay = 1.0 / static_cast<double>(updatesPerSecond);
	}
}

void Engine::pulse() {
	Engine& engine = getInstance();
	// We make sure the pointer to the current state is valid.
	if(engine.currentState) {
		TimeHelper::getInstance().refreshTime();

		// We update the time from TimeHelper.
		if(!engine.nextUpdate) {
			engine.nextUpdate = TimeHelper::getInstance().getSinceStartComplete();
		}

		engine.loops = 0;

		while(TimeHelper::getInstance().getSinceStartComplete() > engine.nextUpdate &&
				engine.loops < engine.minFps) {
			// We refresh the time.
			TimeHelper::getInstance().refreshTime();

			// We call the focus methods if needed.
			if(engine.currentState != engine.lastState) {
				if(engine.lastState) {
					engine.lastState->internalOnLoseFocus();
				}

				engine.currentState->internalOnGetFocus();
			}

			engine.lastState = engine.currentState;
			// We update the current state.
			engine.currentState->internalUpdate();
			engine.renderedSinceLastUpdate = false;
			// We update the input manager.
			InputManager::getInstance().update();
			// We update the timers.
			TimerManager::update();
			engine.nextUpdate += engine.updateDelay;
			engine.lastUpdate = TimeHelper::getInstance().getSinceStartComplete();
			++engine.loops;
		}

		if(!engine.renderedSinceLastUpdate) {
			engine.currentState->internalRender();
			engine.renderedSinceLastUpdate = true;
			engine.bufferSwapped = false;
		}

		if(AudioEngine::getSoundEngine()) {
			AudioEngine::getSoundEngine()->update();
		}

		if(AudioEngine::getMusicEngine()) {
			AudioEngine::getMusicEngine()->update();
		}
	}

	if(engine.needsExit) {
		exit(engine.tmpExitCode);
	}
}

void Engine::initializeEngine(unsigned int newScreenWidth,
							  unsigned int newScreenHeight) {
	Engine& engine = getInstance();
	engine.screenWidth = newScreenWidth;
	engine.screenHeight = newScreenHeight;
	TimeHelper::getInstance();
	InputManager::getInstance();
	onInitialize.shoot(engine.screenWidth, engine.screenHeight);
	GraphicDriver::initializeGraphicDriver(engine.screenWidth, engine.screenHeight);
	Font::initializeFontRenderer();
}

double Engine::getSinceLastUpdate() {
	return TimeHelper::getInstance().getSinceStartComplete() - getInstance().lastUpdate;
}

unsigned int Engine::getScreenWidth() {
	return getInstance().screenWidth;
}

unsigned int Engine::getScreenHeight() {
	return getInstance().screenHeight;
}

bool Engine::isBufferSwapped() {
	return getInstance().bufferSwapped;
}

void Engine::setBufferSwapped() {
	getInstance().bufferSwapped = true;
}

void Engine::exitApplication(int exitCode) {
	getInstance().needsExit = true;
	getInstance().tmpExitCode = exitCode;
}

void Engine::showMainWindow() {
	MainWindow::getInstance().show();
}

const std::string& Engine::getApplicationPath() {
	return getInstance().applicationPath;
}


int Engine::argc;
char** Engine::argv;

int& Engine::getApplicationArgc() {
	return Engine::argc;
}

char** Engine::getApplicationArgv() {
	return Engine::argv;
}


void Engine::application(int argc, char* argv[]) {
	Engine::argc = argc;
	Engine::argv = argv;

	getInstance().applicationPath = dirname(argv[0]);
}

Engine& Engine::getInstance() {
	static Engine instance;
	return instance;
}

Engine::Engine() : currentState(NULL), lastState(NULL) , lastUpdate(0.0),
loops(0), nextUpdate(0), updateDelay(1.0 / DEFAULT_UPDATES_PER_SECOND),
minFps(DEFAULT_MIN_FRAMES_PER_SECOND), bufferSwapped(false),
renderedSinceLastUpdate(false), screenWidth(0), screenHeight(0),
needsExit(false), tmpExitCode(0) {
	MainWindow::getInstance().setCaption("An unnamed RedBox application");
}

Engine::~Engine() {
	// We delete the states.
	std::for_each(states.begin(), states.end(), DeletePointerFromPair());
}
