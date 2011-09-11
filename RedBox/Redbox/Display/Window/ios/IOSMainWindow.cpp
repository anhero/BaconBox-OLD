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

void IOSMainWindow::onRedBoxInit(unsigned int resolutionWidth, unsigned int resolutionHeight, unsigned int contextWidth, unsigned int contextHeight) {
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];

	InputManager::getInstance().setNbPointers(1);
    
    CGRect screenBounds = [[UIScreen mainScreen] bounds];
    resolutionWidth = screenBounds.size.width;
    resolutionHeight = screenBounds.size.height;
    setContextSize(contextWidth, contextHeight);


    RedBoxAppViewController* viewController = [[RedBoxAppViewController alloc] initWithFrame:screenBounds];
    [RedBoxAppAppDelegate setViewController:viewController];
    [pool release];

}

IOSMainWindow::IOSMainWindow() : MainWindow() {
	fullscreen = true;
}

void IOSMainWindow::setCaption(const std::string& caption) {
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

void IOSMainWindow::setResolution(unsigned int resolutionWidth, unsigned int resolutionHeight){

}

void IOSMainWindow::setContextSize(unsigned int contextWidth, unsigned int contextHeight){
    if (this->contextWidth == 0) {
        this->contextWidth =resolutionWidth;
    }
    else{
        this->contextWidth = contextWidth;
    }
    
    if (this->contextHeight == 0) {
        this->contextHeight = resolutionHeight;
    }
    else{
        this->contextHeight = contextHeight;
    }
}


