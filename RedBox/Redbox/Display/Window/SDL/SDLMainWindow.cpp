#include "SDLMainWindow.h"

#include "PlatformFlagger.h"

#include "SDLInputManager.h"
#include "RBOpenGL.h"
#include "Engine.h"
#include "SDLMixerEngine.h"

using namespace RedBox;

SDLMainWindow& SDLMainWindow::getInstance() {
	static SDLMainWindow instance;
	return instance;
}

void SDLMainWindow::onRedBoxInit(unsigned int resolutionWidth, unsigned int resolutionHeight, float contextWidth, float contextHeight) {
    
    this->resolutionWidth = resolutionWidth;
    this->resolutionHeight = resolutionHeight;
    setContextSize(contextWidth, contextHeight);
    
	mainWindow = SDL_CreateWindow(MainWindow::DEFAULT_NAME.c_str(),
								SDL_WINDOWPOS_CENTERED,
								SDL_WINDOWPOS_CENTERED, this->resolutionWidth, this->resolutionHeight,
								SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	mainContext = SDL_GL_CreateContext(mainWindow);
	if(SDL_GL_SetSwapInterval(1) < 0) { printf("opengl error [SetSwapInterval]: %s\n", SDL_GetError()); }
	InputManager::getInstance().setNbKeyboards(1);
	InputManager::getInstance().setNbPointers(1);
}

void SDLMainWindow::show() {
#ifdef RB_GLEW
glewInit();
#endif
	while(SDLInputManager::getSDLInstance()->isRunning()) {
		Engine::pulse();
		if(!Engine::isBufferSwapped()) {
			SDL_GL_SwapWindow(mainWindow);
			Engine::setBufferSwapped();
		}
	}
}
void SDLMainWindow::setResolution(unsigned int resolutionWidth, unsigned int resolutionHeight){
    //TODO!!!!
}



void SDLMainWindow::setCaption(const std::string& caption) {
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

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

	if(SDL_GL_SetAttribute(SDL_GL_RED_SIZE,   8) < 0) { printf("opengl error: %s\n", SDL_GetError()); }
	if(SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,  8) < 0) { printf("opengl error: %s\n", SDL_GetError()); }
	if(SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8) < 0) { printf("opengl error: %s\n", SDL_GetError()); }
	if(SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8) < 0) { printf("opengl error: %s\n", SDL_GetError()); }
	if(SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,  32) < 0) { printf("opengl error: %s\n", SDL_GetError()); }
	if(SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,  1) < 0) { printf("Couldn't set double buffering: %s\n", SDL_GetError()); }

	SDLMixerEngine::getInstance();
}

SDLMainWindow::~SDLMainWindow() {
	if(mainContext) {
		SDL_GL_DeleteContext(mainContext);
		SDL_DestroyWindow(mainWindow);
	}
	SDL_Quit();
}
