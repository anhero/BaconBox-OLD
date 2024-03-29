#include "BaconBox/Display/Window/SDL/SDLMainWindow.h"

#include "BaconBox/PlatformFlagger.h"

#include "BaconBox/Input/SDL/SDLInputManager.h"
#include "BaconBox/Display/Driver/OpenGL/RBOpenGL.h"
#include "BaconBox/Engine.h"
#include "BaconBox/Display/Driver/GraphicDriver.h"

namespace BaconBox {

	void SDLMainWindow::onBaconBoxInit(unsigned int resolutionWidth, unsigned int resolutionHeight, float contextWidth, float contextHeight) {
		this->MainWindow::setResolution(resolutionWidth, resolutionHeight);
		this->MainWindow::setContextSize(contextWidth, contextHeight);

		mainWindow = SDL_CreateWindow(Engine::getApplicationName().c_str(),
		                              SDL_WINDOWPOS_CENTERED,
		                              SDL_WINDOWPOS_CENTERED,
		                              static_cast<int>(this->getResolutionWidth()),
		                              static_cast<int>(this->getResolutionHeight()),
		                              SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		mainContext = SDL_GL_CreateContext(mainWindow);

		if (SDL_GL_SetSwapInterval(1) < 0) {
			printf("opengl error [SetSwapInterval]: %s\n", SDL_GetError());
		}

		InputManager::getInstance().setNbKeyboards(1);
		InputManager::getInstance().setNbPointers(1);

#ifdef RB_GLEW
		glewInit();
#endif
	}

	void SDLMainWindow::show() {
		while (SDLInputManager::getSDLInstance()->isRunning()) {
			Engine::pulse();

			if (!Engine::isBufferSwapped()) {
				SDL_GL_SwapWindow(mainWindow);
				Engine::setBufferSwapped();
			}
		}
	}

	void SDLMainWindow::setResolution(unsigned int resolutionWidth,
	                                  unsigned int resolutionHeight) {
		this->MainWindow::setResolution(resolutionWidth, resolutionHeight);
		SDL_SetWindowSize(mainWindow, static_cast<int>(this->getResolutionWidth()), static_cast<int>(this->getResolutionHeight()));
		GraphicDriver::getInstance().initializeGraphicDriver();
	}

	void SDLMainWindow::setContextSize(float newContextWidth,
	                                   float newContextHeight) {
		this->MainWindow::setContextSize(newContextWidth, newContextHeight);
		GraphicDriver::getInstance().initializeGraphicDriver();
	}

	void SDLMainWindow::setCaption(const std::string &caption) {
		SDL_SetWindowTitle(mainWindow, caption.c_str());
	}

	bool SDLMainWindow::isFullScreen() const {
		return static_cast<bool>(SDL_GetWindowFlags(mainWindow) & SDL_WINDOW_FULLSCREEN);
	}

	void SDLMainWindow::setFullScreen(bool newFullScreen) {
		SDL_SetWindowFullscreen(mainWindow, ((newFullScreen) ? (SDL_TRUE) : (SDL_FALSE)));
	}

	bool SDLMainWindow::isInputGrabbed() const {
		return static_cast<bool>(SDL_GetWindowFlags(mainWindow) & SDL_WINDOW_INPUT_GRABBED);
	}

	void SDLMainWindow::setInputGrabbed(bool newInputGrabbed) {
		SDL_SetWindowGrab(mainWindow, ((newInputGrabbed) ? (SDL_TRUE) : (SDL_FALSE)));
	}

	SDLMainWindow::SDLMainWindow() : MainWindow(), mainWindow(NULL),
		mainContext(NULL) {

        SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK);
        
            unsigned int  nbJoystick = SDL_NumJoysticks();
            if(nbJoystick){
                SDL_JoystickEventState(SDL_ENABLE);
        InputManager::getInstance().setNbGamePads(SDL_NumJoysticks());
            }
            

//            std::cout << SDL_JoystickName(0)<< std::endl; 
            
		if (SDL_GL_SetAttribute(SDL_GL_RED_SIZE,   8) < 0) {
			printf("opengl error: %s\n", SDL_GetError());
		}

		if (SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,  8) < 0) {
			printf("opengl error: %s\n", SDL_GetError());
		}

		if (SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8) < 0) {
			printf("opengl error: %s\n", SDL_GetError());
		}

		if (SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8) < 0) {
			printf("opengl error: %s\n", SDL_GetError());
		}

		if (SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,  32) < 0) {
			printf("opengl error: %s\n", SDL_GetError());
		}

		if (SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,  1) < 0) {
			printf("Couldn't set double buffering: %s\n", SDL_GetError());
		}
	}

	SDLMainWindow::~SDLMainWindow() {
		if (mainContext) {
			SDL_GL_DeleteContext(mainContext);
			SDL_DestroyWindow(mainWindow);
		}

		SDL_Quit();
	}
    
    void SDLMainWindow::hideCursor(){
        SDL_ShowCursor(SDL_DISABLE);
    }
    
    void SDLMainWindow::showCursor(){
        SDL_ShowCursor(SDL_ENABLE);
    }
}
