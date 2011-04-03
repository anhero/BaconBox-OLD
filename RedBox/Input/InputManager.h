/**
 * @file
 * @ingroup Input
 */
#ifndef RB_INPUT_MANAGER_H
#define RB_INPUT_MANAGER_H

#include <vector>

#include "Accelerometer.h"
#include "GamePad.h"
#include "Keyboard.h"
#include "Pointer.h"

namespace RedBox {
	/**
	 * Singleton class that manages all input devices. Lets you access all
	 * input devices' states and information.
	 * @ingroup Input
	 */
	class InputManager {
		friend class RedBoxEngine;
	public:
		/**
		 * Gets the InputManager's singleton instance.
		 * @return Pointer to the instance.
		 */
		static InputManager* getInstance();
		
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
		 * @return Pointer to the accelerometer corresponding to the recieved
		 * index.
		 */
		Accelerometer* getAccelerometer(unsigned int index = 0);
		
		/**
		 * Gets a game pad.
		 * @param index Index of the game pad to get.
		 * @return Pointer to the game pad corresponding to the recieved index.
		 */
		GamePad* getGamePad(unsigned int index = 0);
		
		/**
		 * Gets a keyboard.
		 * @param index Index of the keyboard to get.
		 * @return Pointer to the keyboard corresponding to the recieved index.
		 */
		Keyboard* getKeyboard(unsigned int index = 0);
		
		/**
		 * Gets a pointer.
		 * @param index Index of the pointer to get.
		 * @return Pointer to the pointer corresponding to the recieved index.
		 */
		Pointer* getPointer(unsigned int index = 0);
		
	private:
		/// Pointer to the class's unique instance.
		static InputManager* instance;
		
		/// Pointers to the loaded accelerometers.
		std::vector<Accelerometer*> accelerometers;
		
		/// Pointers to the loaded game pads.
		std::vector<GamePad*> gamePads;
		
		/// Pointers to the loaded keyboards.
		std::vector<Keyboard*> keyboards;
		
		/// Pointers to the loaded pointing devices.
		std::vector<Pointer*> pointers;
		
		/**
		 * Default constructor.
		 */
		InputManager();
		
		/**
		 * Destructor.
		 */
		~InputManager();
		
		/**
		 * Updates all input devices' states.
		 */
		void update();
	};
}

#endif