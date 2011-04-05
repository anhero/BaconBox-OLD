/**
 * @file
 * @ingroup Input
 */
#ifndef RB_KEYBOARD_H
#define RB_KEYBOARD_H

#include <sigly.h>

#include "InputDevice.h"
#include "KeyboardState.h"
#include "KeyMaskSignalData.h"
#include "KeySignalData.h"

namespace RedBox {
	/**
	 * Base class for keyboard devices. When writing an implementation for a
	 * specific platform, the keyboard implementation must inherit from this
	 * class.
	 * @ingroup Input
	 */
	class Keyboard : public InputDevice {
		friend class InputManager;
	public:
		/// Signal sent when a key is pressed.
		sigly::Signal1<KeySignalData> keyPress;
		
		/// Signal sent when a key is being held.
		sigly::Signal1<KeySignalData> keyHold;
		
		/// Signal sent when a key is released.
		sigly::Signal1<KeySignalData> keyRelease;
		
		/// Signal sent when a key mask is pressed.
		sigly::Signal1<KeyMaskSignalData> keyMaskPress;
		
		/// Signal sent when a key mask is held.
		sigly::Signal1<KeyMaskSignalData> keyMaskHold;
		
		/// Signal sent when a key mask is released.
		sigly::Signal1<KeyMaskSignalData> keyMaskRelease;
		
		/**
		 * Gets the keyboard's current state.
		 * @return Keyboard's current state. Contains information about the keys
		 * and key masks (which ones are pressed and which ones aren't).
		 */
		const KeyboardState& getState() const;
		
		/**
		 * Checks if a specific key was just pressed.
		 * @param key Key to check.
		 * @return True if the key wasn't previously pressed but is now pressed,
		 * false if not.
		 */
		bool isKeyPressed(Key::Enum key) const;
		
		/**
		 * Checks if a specific key is being held.
		 * @param key Key to check.
		 * @return True if the key is set to pressed in previousKeys and in
		 * keys, false if not.
		 */
		bool isKeyHeld(Key::Enum key) const;
		
		/**
		 * Checks if a specific key was just released.
		 * @param key Key to check.
		 * @return True if the key was previously pressed but isn't pressed
		 * anymore, false if not.
		 */
		bool isKeyReleased(Key::Enum key) const;
		
		/**
		 * Checks if a specific key mask was just pressed.
		 * @param maskName Key mask to check.
		 * @return True if the key mask wasn't previously pressed but is now
		 * pressed, false if not.
		 */
		bool isKeyMaskPressed(const std::string& maskName) const;
		
		/**
		 * Checks if a specific key mask is being held.
		 * @param maskName Key mask to check.
		 * @return True if the key mask was previously pressed and is also
		 * currently pressed, false if not.
		 */
		bool isKeyMaskHeld(const std::string& maskName) const;
		
		/**
		 * Checks if a specific key mask was just released.
		 * @param maskName Key mask to check.
		 * @return True if the key mask was previously pressed but isn't
		 * pressed anymore, false if not.
		 */
		bool isKeyMaskReleased(const std::string& maskName) const;
		
		/**
		 * Checks if a key masks contains a key.
		 * @param maskName Name of the mask to check.
		 * @param key Key to check for.
		 * @return True if the mask contains the key, false if not. Returns
		 * false if the key mask doesn't exist.
		 */
		bool maskHasKey(const std::string& maskName, Key::Enum key) const;
		
		/**
		 * Adds a key to a mask. If the mask didn't previously exist, it will be
		 * created.
		 * @param maskName Name of the mask to add a key to. If the mask
		 * doesn't already exist, it is created.
		 * @param key Key to add to the mask. Will not be added if the mask
		 * already contains it.
		 */
		void addMaskKey(const std::string& maskName, Key::Enum key);
		
		/**
		 * Removes a key from a mask. If the mask is then empty, it will be
		 * deleted completely. If the key isn't part of the mask, nothing will
		 * be done.
		 * @param maskName Name of the mask to have a key removed. If the
		 * mask is empty after the operation, it will be deleted.
		 * @param key Key to remove from the mask. If the mask doesn't contain
		 * the key, nothing will be done.
		 */
		void removeMaskKey(const std::string& maskName, Key::Enum key);
		
		/**
		 * Removes a mask whatever its number of keys left in it.
		 * @param maskName Name of the mask to delete. If the mask
		 * doesn't exist, nothing is done.
		 */
		void removeMask(const std::string& maskName);
	protected:
		/**
		 * State of the keyboard device. Contains information about which keys
		 * and keymasks are pressed.
		 */
		KeyboardState state;
		
		/**
		 * Default constructor.
		 */
		Keyboard();
		
		/**
		 * Destructor.
		 */
		virtual ~Keyboard();
	};
}

#endif
