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
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];

	//SDL_SetVideoMode(width, height, 32, SDL_OPENGL);
	//InputManager::getInstance().setNbKeyboards(1);
	InputManager::getInstance().setNbPointers(1);
    
    CGRect screenBounds = [[UIScreen mainScreen] bounds];
    RedBoxAppViewController* viewController = [[RedBoxAppViewController alloc] initWithFrame:screenBounds];
    [RedBoxAppAppDelegate setViewController:viewController];
    [pool release];

}

IOSMainWindow::IOSMainWindow() : MainWindow() {
	//SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
}

void IOSMainWindow::setCaption(const std::string& caption) {
	//SDL_WM_SetCaption(caption.c_str(), NULL);
}

bool IOSMainWindow::isFullScreen() const {
	return true;
}

void IOSMainWindow::setFullScreen(bool) {
}

bool IOSMainWindow::isInputGrabbed() const {
	return true;
}

void IOSMainWindow::setInputGrabbed(bool newInputGrabbed) {
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


