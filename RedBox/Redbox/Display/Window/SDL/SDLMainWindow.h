/**
 * @file
 * @ingroup WindowDisplay
 */
#ifndef RB_SDL_MAIN_WINDOW_H
#define RB_SDL_MAIN_WINDOW_H

#include <sigly.h>

#include <SDL/SDL.h>

#include "MainWindow.h"

namespace RedBox {
	/**
	 * This is an implementation of MainWindow using SDL.
	 */
	class SDLMainWindow : public MainWindow {
	public:
		/// Gets the singleton instance of SDLMainWindow.
		static SDLMainWindow& getInstance();
		void onRedBoxInit(unsigned int width, unsigned int height);
		void show();
		void setCaption(const std::string& caption);
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
