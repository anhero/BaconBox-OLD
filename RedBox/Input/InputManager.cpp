#include "InputManager.h"

#include "PlatformFlagger.h"

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


using namespace RedBox;

InputManager* InputManager::instance = NULL;

InputManager* InputManager::getInstance() {
	if(!instance) {
		instance = new InputManager();
	}
	return instance;
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


InputManager::InputManager() {
}

InputManager::~InputManager() {
	// We delete all the devices.
	for (std::vector<Accelerometer*>::iterator i = accelerometers.begin();
		 i != accelerometers.end(); ++i) {
		if(*i) {
			delete *i;
		}
	}
	for (std::vector<GamePad*>::iterator i = gamePads.begin();
		 i != gamePads.end(); ++i) {
		if(*i) {
			delete *i;
		}
	}
	for (std::vector<Keyboard*>::iterator i = keyboards.begin();
		 i != keyboards.end(); ++i) {
		if(*i) {
			delete *i;
		}
	}
	for (std::vector<Pointer*>::iterator i = pointers.begin();
		 i != pointers.end(); ++i) {
		if(*i) {
			delete *i;
		}
	}
}

void InputManager::update() {
	for (std::vector<Accelerometer*>::iterator i = accelerometers.begin();
		 i != accelerometers.end(); ++i) {
		if(*i) {
			(*i)->update();
		}
	}
	for (std::vector<GamePad*>::iterator i = gamePads.begin();
		 i != gamePads.end(); ++i) {
		if(*i) {
			(*i)->update();
		}
	}
	for (std::vector<Keyboard*>::iterator i = keyboards.begin();
		 i != keyboards.end(); ++i) {
		if(*i) {
			(*i)->update();
		}
	}
	for (std::vector<Pointer*>::iterator i = pointers.begin();
		 i != pointers.end(); ++i) {
		if(*i) {
			(*i)->update();
		}
	}
}
