#include "BaconBox/Input/InputManager.h"

#include "BaconBox/PlatformFlagger.h"

#ifdef RB_ACCELEROMETER_INCLUDE
#include RB_ACCELEROMETER_INCLUDE
#endif

#ifdef RB_GAME_PAD_INCLUDE
#include RB_GAME_PAD_INCLUDE
#endif

#ifdef RB_KEYBOARD_INCLUDE
#include RB_KEYBOARD_INCLUDE
#endif

#ifdef RB_POINTER_INCLUDE
#include RB_POINTER_INCLUDE
#endif

#ifdef RB_INPUT_MANAGER_INCLUDE
#include RB_INPUT_MANAGER_INCLUDE
#endif

using namespace BaconBox;

InputManager& InputManager::getInstance() {
	static RB_INPUT_MANAGER_IMPL instance;
	return instance;
}

Accelerometer* InputManager::getDefaultAccelerometer() {
	return InputManager::getInstance().getAccelerometer();
}

GamePad* InputManager::getDefaultGamePad() {
	return InputManager::getInstance().getGamePad();
}

Keyboard* InputManager::getDefaultKeyboard() {
	return InputManager::getInstance().getKeyboard();
}

Pointer* InputManager::getDefaultPointer() {
	return InputManager::getInstance().getPointer();
}

unsigned int InputManager::getNbAccelerometers() const {
	return accelerometers.size();
}

unsigned int InputManager::getNbGamePads() const {
	return gamePads.size();
}

unsigned int InputManager::getNbKeyboards() const {
	return keyboards.size();
}

unsigned int InputManager::getNbPointers() const {
	return pointers.size();
}

void InputManager::setNbAccelerometers(unsigned int nb) {
	if (nb > accelerometers.size()) {
		unsigned int oldSize = accelerometers.size();
		accelerometers.resize(nb, NULL);
		for(unsigned int i = oldSize; i < nb; ++i) {
			accelerometers[i] = RB_ACCELEROMETER_IMPL;
		}
	} else if(nb < accelerometers.size()) {
		for(unsigned int i = nb; i < accelerometers.size(); ++i) {
			if(accelerometers[i]) {
				delete accelerometers[i];
			}
		}
		accelerometers.resize(nb);
	}
}

void InputManager::setNbGamePads(unsigned int nb) {
	if (nb > gamePads.size()) {
		unsigned int oldSize = gamePads.size();
		gamePads.resize(nb, NULL);
		for(unsigned int i = oldSize; i < nb; ++i) {
			gamePads[i] = RB_GAME_PAD_IMPL;
		}
	} else if(nb < gamePads.size()) {
		for(unsigned int i = nb; i < gamePads.size(); ++i) {
			if(gamePads[i]) {
				delete gamePads[i];
			}
		}
		gamePads.resize(nb);
	}
}

void InputManager::setNbKeyboards(unsigned int nb) {
	if (nb > keyboards.size()) {
		unsigned int oldSize = keyboards.size();
		keyboards.resize(nb, NULL);
		for(unsigned int i = oldSize; i < nb; ++i) {
			keyboards[i] = RB_KEYBOARD_IMPL;
		}
	} else if(nb < keyboards.size()) {
		for(unsigned int i = nb; i < keyboards.size(); ++i) {
			if(keyboards[i]) {
				delete keyboards[i];
			}
		}
		keyboards.resize(nb);
	}
}

void InputManager::setNbPointers(unsigned int nb) {
	if (nb > pointers.size()) {
		unsigned int oldSize = pointers.size();
		pointers.resize(nb, NULL);
		for(unsigned int i = oldSize; i < nb; ++i) {
			pointers[i] = RB_POINTER_IMPL;
		}
	} else if(nb < pointers.size()) {
		for(unsigned int i = nb; i < pointers.size(); ++i) {
			if(pointers[i]) {
				delete pointers[i];
			}
		}
		pointers.resize(nb);
	}
}

Accelerometer* InputManager::getAccelerometer(unsigned int index) {
	if(index >= accelerometers.size()) {
		return NULL;
	} else {
		return accelerometers[index];
	}
}

GamePad* InputManager::getGamePad(unsigned int index) {
	if(index >= gamePads.size()) {
		return NULL;
	} else {
		return gamePads[index];
	}
}

Keyboard* InputManager::getKeyboard(unsigned int index) {
	if(index >= keyboards.size()) {
		return NULL;
	} else {
		return keyboards[index];
	}
}

Pointer* InputManager::getPointer(unsigned int index) {
	if(index >= pointers.size()) {
		return NULL;
	} else {
		return pointers[index];
	}
}

void InputManager::dontDeleteAccelerometers() {
	deleteAccelerometers = false;
}
void InputManager::dontDeleteGamePads() {
	deleteGamePads = false;
}
void InputManager::dontDeleteKeyboards() {
	deleteKeyboards = false;
}
void InputManager::dontDeletePointers() {
	deletePointers = false;
}

void InputManager::deleteAccelerometersOnQuit() {
	deleteAccelerometers = true;
}
void InputManager::deleteGamePadsOnQuit() {
	deleteGamePads = true;
}

void InputManager::deleteKeyboardsOnQuit() {
	deleteKeyboards = true;
}

void InputManager::deletePointersOnQuit() {
	deletePointers = true;
}

InputManager::InputManager() : deleteAccelerometers(true), deleteGamePads(true),
deleteKeyboards(true), deletePointers(this) {
}

InputManager::~InputManager() {
	// We delete all the devices.
	if(deleteAccelerometers) {
		for (std::vector<Accelerometer*>::iterator i = accelerometers.begin();
			 i != accelerometers.end(); ++i) {
			if(*i) {
				delete *i;
			}
		}
	}

	if(deleteGamePads) {
		for (std::vector<GamePad*>::iterator i = gamePads.begin();
			 i != gamePads.end(); ++i) {
			if(*i) {
				delete *i;
			}
		}
	}

	if(deleteKeyboards) {
		for (std::vector<Keyboard*>::iterator i = keyboards.begin();
			 i != keyboards.end(); ++i) {
			if(*i) {
				delete *i;
			}
		}
	}

	if(deletePointers) {
		for (std::vector<Pointer*>::iterator i = pointers.begin();
			 i != pointers.end(); ++i) {
			if(*i) {
				delete *i;
			}
		}
	}
}

void InputManager::update() {
	for (std::vector<Accelerometer*>::iterator i = accelerometers.begin();
		 i != accelerometers.end(); ++i) {
		if(*i) {
			(*i)->updateDevice();
		}
	}
	for (std::vector<GamePad*>::iterator i = gamePads.begin();
		 i != gamePads.end(); ++i) {
		if(*i) {
			(*i)->updateDevice();
		}
	}
	for (std::vector<Keyboard*>::iterator i = keyboards.begin();
		 i != keyboards.end(); ++i) {
		if(*i) {
			(*i)->updateDevice();
		}
	}
	for (std::vector<Pointer*>::iterator i = pointers.begin();
		 i != pointers.end(); ++i) {
		if(*i) {
			(*i)->updateDevice();
		}
	}
}
