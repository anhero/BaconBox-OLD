#include "SDLMainWindow.h"

#include "PlatformFlagger.h"

#include <SDL/SDL.h>

#include "SDLInputManager.h"
#include "RBOpenGL.h"
#include "Engine.h"

using namespace RedBox;

SDLMainWindow& SDLMainWindow::getInstance() {
	static SDLMainWindow instance;
	return instance;
}

void SDLMainWindow::onRedBoxInit(int width, int height) {
	SDL_SetVideoMode(width, height, 32, SDL_OPENGL);
	InputManager::getInstance().setNbKeyboards(1);
	InputManager::getInstance().setNbPointers(1);
}

SDLMainWindow::SDLMainWindow() : MainWindow() {
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
}

void SDLMainWindow::setCaption(const std::string& caption) {
	SDL_WM_SetCaption(caption.c_str(), NULL);
}
	
void SDLMainWindow::show() {
	while(SDLInputManager::getSDLInstance()->isRunning()) {
		Engine::pulse();
		if(!Engine::isBufferSwapped()) {
			SDL_GL_SwapBuffers();
			Engine::setBufferSwapped();
		}
	}
}

SDLMainWindow::~SDLMainWindow() {
	SDL_Quit();
}
