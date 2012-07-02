#include "BaconBox/Display/Window/MainWindow.h"

#include "BaconBox/Engine.h"
#include "BaconBox/Display/Driver/GraphicDriver.h"

namespace BaconBox {
	const std::string MainWindow::DEFAULT_NAME = std::string("An unnamed BaconBox application");

	MainWindow &MainWindow::getInstance() {
		return Engine::getMainWindow();
	}

	void MainWindow::grabInput() {
		setInputGrabbed(true);
	}

	void MainWindow::releaseInput() {
		setInputGrabbed(false);
	}

	unsigned int MainWindow::getResolutionWidth() {
		return resolutionWidth;
	}
	
	unsigned int MainWindow::getResolutionHeight() {
		return resolutionHeight;
	}
	
	void MainWindow::setResolution(unsigned int newResolutionWidth,
								   unsigned int newResolutionHeight) {
		resolutionWidth = newResolutionWidth;
		resolutionHeight = newResolutionHeight;
	}
	
	float MainWindow::getContextWidth() {
		return contextWidth;
	}
	
	float MainWindow::getContextHeight() {
		return contextHeight;
	}
    
    void MainWindow::showCursor(){
        
    }
    
    void MainWindow::hideCursor(){
        
    }

	void MainWindow::setContextSize(float newContextWidth, float newContextHeight) {
		if (newContextWidth == 0.0f) {
			contextWidth = resolutionWidth;

		} else {
			contextWidth = newContextWidth;
		}

		if (newContextHeight == 0.0f) {
			contextHeight = resolutionHeight;

		} else {
			contextHeight = newContextHeight;
		}
	}
	
	WindowOrientation MainWindow::getOrientation() const {
		return orientation;
	}
	
	void MainWindow::setOrientation(WindowOrientation newOrientation) {
		if (orientation != newOrientation) {
			if (((orientation == WindowOrientation::NORMAL ||
				orientation == WindowOrientation::UPSIDE_DOWN) &&
				(newOrientation == WindowOrientation::HORIZONTAL_LEFT ||
				 newOrientation == WindowOrientation::HORIZONTAL_RIGHT)) ||
				((orientation == WindowOrientation::HORIZONTAL_LEFT ||
				 orientation == WindowOrientation::HORIZONTAL_RIGHT) &&
				 (newOrientation == WindowOrientation::NORMAL ||
				  newOrientation == WindowOrientation::UPSIDE_DOWN))) {
					 unsigned int tmp = resolutionWidth;
					 resolutionWidth = resolutionHeight;
					 resolutionHeight = tmp;
				}
			orientation = newOrientation;
			GraphicDriver::getInstance().initializeGraphicDriver();
		}
	}
	
	MainWindow::MainWindow() : sigly::HasSlots<>(), resolutionWidth(0), resolutionHeight(0),
		contextWidth(0), contextHeight(0), orientation(WindowOrientation::NORMAL) {
		Engine::onInitialize.connect(this, &MainWindow::onBaconBoxInit);
	}
	
	MainWindow::~MainWindow() {
	}
}
