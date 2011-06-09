#ifndef RB_SDL_MAIN_WINDOW_H
#define RB_SDL_MAIN_WINDOW_H

#include <sigly.h>
#include "MainWindow.h"

namespace RedBox {
	class SDLMainWindow : public MainWindow {
	public:
		static SDLMainWindow& getInstance();
		void onRedBoxInit(int width, int height);
		void show();
		void setCaption(const std::string& caption);
	private:
		SDLMainWindow();
		~SDLMainWindow();
	};
}

#endif
