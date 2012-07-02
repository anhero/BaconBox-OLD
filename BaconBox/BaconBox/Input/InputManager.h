/**
 * @file
 * @ingroup Input
 */
#ifndef RB_INPUT_MANAGER_H
#define RB_INPUT_MANAGER_H

#include <vector>

#include "BaconBox/Input/Accelerometer/Accelerometer.h"
#include "BaconBox/Input/GamePad/GamePad.h"
#include "BaconBox/Input/Keyboard/Keyboard.h"
#include "BaconBox/Input/Pointer/Pointer.h"

namespace BaconBox {
	/**
	 * Singleton class that manages all input devices. Lets you access all
	 * input devices' states and information.
	 * @ingroup Input
	 */
	class InputManager {
		friend class Engine;
		friend class Accelerometer;
		friend class GamePad;
		friend class Keyboard;
		friend class Pointer;
	public:
		/**
		 * Gets the InputManager's singleton instance.
		 * @return Pointer to the instance.
		 */
		static InputManager& getInstance();

		/**
		 * Gets a pointer to the default accelerometer device.
		 * @return Pointer to the default accelerometer device. Null if none are
		 * available.
		 */
		static Accelerometer* getDefaultAccelerometer();
		/**
		 * Gets a pointer to the default gamepad device.
		 * @return Pointer to the default gamepad device. Null if none are
		 * available.
		 */
		static GamePad* getDefaultGamePad();
		/**
		 * Gets a pointer to the default keyboard device.
		 * @return Pointer to the default keyboard device. Null if none are
		 * available.
		 */
		static Keyboard* getDefaultKeyboard();
		/**
		 * Gets a pointer to the default pointer device.
		 * @return Pointer to the default pointer device. Null if none are
		 * available.
		 */
		static Pointer* getDefaultPointer();
		
		/**
		 * Gets the number of accelerometers initialized.
		 * @return Number of accelerometers initialized.
		 */
		unsigned int getNbAccelerometers() const;
		
		/**
		 * Gets the number of game pads initialized.
		 * @return Number of game pads initialized.
		 */
		unsigned int getNbGamePads() const;
		
		/**
		 * Gets the number of keyboards initialized.
		 * @return Number of keyboards initialized.
		 */
		unsigned int getNbKeyboards() const;
		
		/**
		 * Gets the number of pointers initialized.
		 * @return Number of pointers initialized.
		 */
		unsigned int getNbPointers() const;
		
		/**
		 * Sets the number of accelerometers to be initialized and ready to be
		 * plugged and used.
		 * @param nb Number of accelerometers to make sure to be loaded.
		 */
		void setNbAccelerometers(unsigned int nb);
		
		/**
		 * Sets the number of game pads to be initialized and ready to be
		 * plugged and used.
		 * @param nb Number of game pads to make sure to be loaded.
		 */
		void setNbGamePads(unsigned int nb);
		
		/**
		 * Sets the number of keyboards to be initialized and ready to be
		 * plugged and used.
		 * @param nb Number of keyboards to make sure to be loaded.
		 */
		void setNbKeyboards(unsigned int nb);
		
		/**
		 * Sets the number of pointers to be initialized and ready to be
		 * plugged and used.
		 * @param nb Number of pointers to make sure to be loaded.
		 */
		void setNbPointers(unsigned int nb);
		
		/**
		 * Gets an accelerometer.
		 * @param index Index of the accelerometer to get.
		 * @return Pointer to the accelerometer corresponding to the received
		 * index.
		 */
		Accelerometer* getAccelerometer(unsigned int index = 0);
		
		/**
		 * Gets a game pad.
		 * @param index Index of the game pad to get.
		 * @return Pointer to the game pad corresponding to the received index.
		 */
		GamePad* getGamePad(unsigned int index = 0);
		
		/**
		 * Gets a keyboard.
		 * @param index Index of the keyboard to get.
		 * @return Pointer to the keyboard corresponding to the received index.
		 */
		Keyboard* getKeyboard(unsigned int index = 0);
		
		/**
		 * Gets a pointer.
		 * @param index Index of the pointer to get.
		 * @return Pointer to the pointer corresponding to the received index.
		 */
		Pointer* getPointer(unsigned int index = 0);
		
		/**
		 * Specify to not delete the accelerometers when the input manager is
		 * destroyed.
		 */
		void dontDeleteAccelerometers();
		/**
		 * Specify to not delete the game pads when the input manager is
		 * destroyed.
		 */
		void dontDeleteGamePads();
		/**
		 * Specify to not delete the keyboards when the input manager is
		 * destroyed.
		 */
		void dontDeleteKeyboards();
		/**
		 * Specify to not delete the pointers when the input manager is
		 * destroyed.
		 */
		void dontDeletePointers();
		/**
		 * Specify to delete the accelerometers when the input manager is
		 * destroyed.
		 */
		void deleteAccelerometersOnQuit();
		/**
		 * Specify to delete the game pads when the input manager is destroyed.
		 */
		void deleteGamePadsOnQuit();
		/**
		 * Specify to delete the keyboards when the input manager is destroyed.
		 */
		void deleteKeyboardsOnQuit();
		/**
		 * Specify to delete the pointers when the input manager is destroyed.
		 */
		void deletePointersOnQuit();
	protected:
		/**
		 * Default constructor.
		 */
		InputManager();
		
		/**
		 * Destructor.
		 */
		virtual ~InputManager();

		/**
		 * Updates all input devices' states.
		 */
		virtual void update();
	private:
		/// Pointers to the loaded accelerometers.
		std::vector<Accelerometer*> accelerometers;
		
		/// Pointers to the loaded game pads.
		std::vector<GamePad*> gamePads;
		
		/// Pointers to the loaded keyboards.
		std::vector<Keyboard*> keyboards;
		
		/// Pointers to the loaded pointing devices.
		std::vector<Pointer*> pointers;

		/**
		 * Flag set to know if the input manager has to delete the
		 * accelerometers.
		 */
		bool deleteAccelerometers;

		/// Flag set to know if the input manager has to delete the game pads.
		bool deleteGamePads;

		/// Flag set to know if the input manager has to delete the keyboards.
		bool deleteKeyboards;

		/// Flag set to know if the input manager has to delete the pointers.
		bool deletePointers;
	};
}

#endif
