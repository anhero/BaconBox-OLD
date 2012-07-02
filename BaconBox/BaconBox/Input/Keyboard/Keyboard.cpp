#include "BaconBox/Input/Keyboard/Keyboard.h"

#include "BaconBox/Input/InputManager.h"

using namespace BaconBox;

Keyboard* Keyboard::getDefault() {
	return InputManager::getDefaultKeyboard();
}

const KeyboardState& Keyboard::getState() const {
	return state;
}

bool Keyboard::isKeyPressed(Key::Enum key) const {
	return state.isKeyPressed(key);
}

bool Keyboard::isKeyHeld(Key::Enum key) const {
	return state.isKeyHeld(key);
}

bool Keyboard::isKeyReleased(Key::Enum key) const {
	return state.isKeyReleased(key);
}

bool Keyboard::isKeyMaskPressed(const std::string& maskName) const {
	return state.isKeyMaskPressed(maskName);
}

bool Keyboard::isKeyMaskHeld(const std::string& maskName) const {
	return state.isKeyMaskHeld(maskName);
}

bool Keyboard::isKeyMaskReleased(const std::string& maskName) const {
	return state.isKeyMaskReleased(maskName);
}

bool Keyboard::maskHasKey(const std::string& maskName, Key::Enum key) const {
	return state.maskHasKey(maskName, key);
}

void Keyboard::addMaskKey(const std::string& maskName, Key::Enum key) {
	state.addMaskKey(maskName, key);
}

void Keyboard::removeMaskKey(const std::string& maskName, Key::Enum key) {
	state.removeMaskKey(maskName, key);
}

void Keyboard::removeMask(const std::string& maskName) {
	state.removeMask(maskName);
}

Keyboard::Keyboard() : InputDevice() {
}

Keyboard::~Keyboard() {
}

void Keyboard::updateDevice() {
	InputDevice::updateDevice();
}

std::vector<bool>& Keyboard::getPreviousKeys() {
	return state.previousKeys;
}

std::vector<bool>& Keyboard::getKeys() {
	return state.keys;
}

std::map<std::string, std::set<Key::Enum> >& Keyboard::getKeyMasks() {
	return state.keyMasks;
}

