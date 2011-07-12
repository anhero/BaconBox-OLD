#include "IOSMainWindow.h"

#include "PlatformFlagger.h"


#include "RBOpenGL.h"
#include "Engine.h"
#include "InputManager.h"
#include "RedBoxAppAppDelegate.h"
#import <UIKit/UIKit.h>

using namespace RedBox;

IOSMainWindow& IOSMainWindow::getInstance() {
	static IOSMainWindow instance;
	return instance;
}

void IOSMainWindow::onRedBoxInit(unsigned int width, unsigned int height) {
	//SDL_SetVideoMode(width, height, 32, SDL_OPENGL);
	//InputManager::getInstance().setNbKeyboards(1);
	InputManager::getInstance().setNbPointers(1);
}

IOSMainWindow::IOSMainWindow() : MainWindow() {
	//SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
}

void IOSMainWindow::setCaption(const std::string& caption) {
	//SDL_WM_SetCaption(caption.c_str(), NULL);
}
	
void IOSMainWindow::show() {
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    //Need the next to lines of code to prevent the dead code strip 
    //from striping the RedBoxAppDelegate Class
    RedBoxAppAppDelegate * appDelegate = [RedBoxAppAppDelegate alloc];
    [appDelegate release];
    
	UIApplicationMain(Engine::getApplicationArgc(), Engine::getApplicationArgv(), nil, @"RedBoxAppAppDelegate");
    [pool release];
}

IOSMainWindow::~IOSMainWindow() {
	//SDL_Quit();
}


