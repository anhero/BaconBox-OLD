/**
 * @file
 * @ingroup WindowDisplay
 */
#ifndef RB_SDL_MAIN_WINDOW_H
#define RB_SDL_MAIN_WINDOW_H

#include <sigly.h>
#include "MainWindow.h"

namespace RedBox {
	/**
	 * This is an implementation of MainWindow using SDL.
	 */
	class IOSMainWindow : public MainWindow {
	public:
		/// Gets the singleton instance of SDLMainWindow.
		static IOSMainWindow& getInstance();
		void onRedBoxInit(unsigned int width, unsigned int height);
		void show();
		void setCaption(const std::string& caption);
		bool isFullScreen() const;
		void setFullScreen(bool);
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
		IOSMainWindow();
		/**
		 * Properly quits calling SDL_Quit.
		 */
		~IOSMainWindow();
	};
}

#endif
