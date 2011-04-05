#include "KeyboardState.h"

#include <string>

#include "Key.h"

using namespace RedBox;

KeyboardState::KeyboardState(): InputState() {
	for(unsigned int i = 0; i < Key::NB_KEYS; ++i) {
		previousKeys[i] = keys[i] = false;
	}
}

KeyboardState::~KeyboardState() {
}

bool KeyboardState::isKeyPressed(Key::Enum key) const {
	// We make sure the key recieved makes sense before returning our answer.
	return (key < Key::NB_KEYS) ? (keys[key] && !previousKeys[key]) : (false);
}

bool KeyboardState::isKeyHeld(Key::Enum key) const {
	// We make sure the key recieved makes sense before returning our answer.
	return (key < Key::NB_KEYS) ? (keys[key] && previousKeys[key]) : (false);
}

bool KeyboardState::isKeyReleased(Key::Enum key) const {
	// We make sure the key recieved makes sense before returning our answer.
	return (key < Key::NB_KEYS) ? (!keys[key] && previousKeys[key]) : (false);
}

bool KeyboardState::isKeyMaskPressed(const std::string& maskName) const {

	std::map<std::string, std::set<Key::Enum> >::const_iterator mask =
		keyMasks.find(maskName);

	bool result = false;

	if(mask != keyMasks.end()) {
		std::set<Key::Enum>::const_iterator i = mask->second.begin();

		while(!result && i != mask->second.end()) {
			if(isKeyPressed(*i)) {
				result = true;
			}
		}
	}
	return result;
}
bool KeyboardState::isKeyMaskHeld(const std::string& maskName) const {

	std::map<std::string, std::set<Key::Enum> >::const_iterator mask =
		keyMasks.find(maskName);

	bool result = false;

	if(mask != keyMasks.end()) {
		std::set<Key::Enum>::const_iterator i = mask->second.begin();

		while(!result && i != mask->second.end()) {
			if(isKeyHeld(*i)) {
				result = true;
			}
		}
	}
	return result;
}

bool KeyboardState::isKeyMaskReleased(const std::string& maskName) const {

	std::map<std::string, std::set<Key::Enum> >::const_iterator mask =
		keyMasks.find(maskName);

	bool result = false;

	if(mask != keyMasks.end()) {
		std::set<Key::Enum>::const_iterator i = mask->second.begin();

		while(!result && i != mask->second.end()) {
			if(isKeyReleased(*i)) {
				result = true;
			}
		}
	}
	return result;
}

bool KeyboardState::maskHasKey(const std::string& maskName, Key::Enum key) const {

	std::map<std::string, std::set<Key::Enum> >::const_iterator mask =
		keyMasks.find(maskName);

	if(mask != keyMasks.end()) {
		return mask->second.find(key) != mask->second.end();
	}

	return false;
}

void KeyboardState::addMaskKey(const std::string& maskName, Key::Enum key) {
	keyMasks[maskName].insert(key);
}

void KeyboardState::removeMaskKey(const std::string& maskName, Key::Enum key) {
	std::map<std::string, std::set<Key::Enum> >::iterator mask =
		keyMasks.find(maskName);
	// We make sure the mask exists.
	if(mask != keyMasks.end()) {
		// We erase the key from the mask.
		mask->second.erase(key);
		// We erase the mask if it is empty.
		if(mask->second.empty()) {
			keyMasks.erase(mask);
		}
	}
}

void KeyboardState::removeMask(const std::string& maskName) {
	keyMasks.erase(maskName);
}
