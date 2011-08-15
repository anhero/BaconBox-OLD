/**
 * @file
 * @ingroup WindowDisplay
 */
#ifndef RB_SDL_MAIN_WINDOW_H
#define RB_SDL_MAIN_WINDOW_H

#include <SDL/SDL.h>

#include "MainWindow.h"

namespace RedBox {
	/**
	 * This is an implementation of MainWindow using SDL.
	 * @ingroup WindowDisplay
	 */
	class SDLMainWindow : public MainWindow {
	public:
		/**
		 * Gets the singleton instance of SDLMainWindow.
		 * @return Reference to the singleton.
		 */
		static SDLMainWindow& getInstance();

		/**
		 * Method called when the engine is initialized.
		 * It is used to setup the geometry of the window.
		 * @param width The width of the window.
		 * @param height The height of the window
		 */
		void onRedBoxInit(unsigned int width, unsigned int height);

		/**
		 * Activates and opens the window.
		 */
		void show();

		/**
		 * Changes the caption of the window. This is usually
		 * the title in the titlebar.
		 * @param caption The text used to replace the title.
		 */
		void setCaption(const std::string& caption);

		/**
		 * Checks if the main window is full screen.
		 * @param True if the main window is in full screen, false if not.
		 */
		bool isFullScreen() const;

		/**
		 * Makes the main window full screen or not.
		 * @param newFullScreen If true, sets the main window to full screen.
		 * If false, makes sure it's not full screen.
		 */
		void setFullScreen(bool newFullScreen);

		/**
		 * Checks if the main window grabs the input. When the input is
		 * grabbed, the cursor is invisible.
		 * @return True if the main window grabbed the input, false if not.
		 */
		bool isInputGrabbed() const;

		/**
		 * Sets if the main window grabbed the input or not.
		 * @param newInputGrabbed
		 */
		void setInputGrabbed(bool newInputGrabbed);
	private:
		/**
		 * Initializes SDL.
		 */
		SDLMainWindow();

		/**
		 * Properly quits calling SDL_Quit.
		 */
		~SDLMainWindow();

		/// Handle to the main window.
		SDL_Window* mainWindow;

		/// Handle to the OpenGL context in the main window.
		SDL_GLContext mainContext;
	};
}

#endif
