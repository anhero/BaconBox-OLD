#include "IOSPointer.h"

#include "CursorButton.h"
#include "MainWindow.h"
#include <algorithm>

namespace RedBox {
	
	sigly::Signal2<NSSet*, UIEvent*> IOSPointer::touchBegin = sigly::Signal2<NSSet*, UIEvent*>();
	sigly::Signal2<NSSet*, UIEvent*> IOSPointer::touchEnd = sigly::Signal2<NSSet*, UIEvent*>();
	sigly::Signal2<NSSet*, UIEvent*> IOSPointer::touchMove = sigly::Signal2<NSSet*, UIEvent*>();
	
	IOSPointer::IOSPointer(): Pointer(), sigly::HasSlots<>(),
	iosPosition(Vector2(0.0f, 0.0f)), isTouchDown(false) {
		touchBegin.connect(this, &IOSPointer::onTouchBegin);
		touchEnd.connect(this, &IOSPointer::onTouchEnd);
		touchMove.connect(this, &IOSPointer::onTouchMove);
	}
	
	IOSPointer::~IOSPointer() {
	}
	
	void IOSPointer::updateDevice() {
		
		// We check the touch moving event.
		getCursorPreviousPosition(0) = getCursorPosition(0);
		getCursorPosition(0) = iosPosition;
		
		
		// We check the touch press event.
		getCursorPreviousButtons(0)[CursorButton::LEFT] = getCursorButtons(0)[0];
		getCursorButtons(0)[CursorButton::LEFT] = isTouchDown;
		
		if(isButtonPressed(CursorButton::LEFT)) {
			buttonPress(PointerButtonSignalData(state, 0, CursorButton::LEFT));
		} else if(isButtonHeld(CursorButton::LEFT)) {
			buttonHold(PointerButtonSignalData(state, 0, CursorButton::LEFT));
		} else if(isButtonReleased(CursorButton::LEFT)) {
			buttonRelease(PointerButtonSignalData(state, 0, CursorButton::LEFT));
		}
		
		
		if(hasMoved()) {
			Pointer::move.shoot(PointerSignalData(state, 0));
		}
	}
	
	void IOSPointer::convertToRedBoxScreenPosition(Vector2 *newIosPosition) {
		if (std::max(MainWindow::getInstance().getResolutionWidth(), MainWindow::getInstance().getResolutionHeight()) == 960) {
			newIosPosition->scalarMultiplication(2.0f);
		}
		switch (MainWindow::getInstance().getOrientation().underlying()) {
			case WindowOrientation::UPSIDE_DOWN:
				newIosPosition->setY(MainWindow::getInstance().getResolutionHeight() - newIosPosition->getY());
				break;
			case WindowOrientation::HORIZONTAL_LEFT:
				newIosPosition->setXY(newIosPosition->getY(),
									  MainWindow::getInstance().getResolutionHeight() - newIosPosition->getX());
				break;
			case WindowOrientation::HORIZONTAL_RIGHT:
				newIosPosition->setXY(MainWindow::getInstance().getResolutionWidth() - newIosPosition->getY(),
									  newIosPosition->getX());
				break;
			default:
				break;
		}
	}
	
	void IOSPointer::onTouchBegin(NSSet* touches, UIEvent* event) {
		UITouch * touch = [touches anyObject];
		CGPoint location = [touch locationInView: [touch view]];
		iosPosition.setX(static_cast<float>(location.x));
		iosPosition.setY(static_cast<float>(location.y));
		convertToRedBoxScreenPosition(&iosPosition);
		isTouchDown = true;
	}
	
	void IOSPointer::onTouchEnd(NSSet* touches, UIEvent* event) {
		UITouch * touch = [touches anyObject];
		CGPoint location = [touch locationInView: [touch view]];
		iosPosition.setX(static_cast<float>(location.x));
		iosPosition.setY(static_cast<float>(location.y));
		convertToRedBoxScreenPosition(&iosPosition);
		isTouchDown = false;
	}
	
	void IOSPointer::onTouchMove(NSSet* touches, UIEvent* event) {
		UITouch * touch = [touches anyObject];
		CGPoint location = [touch locationInView: [touch view]];
		iosPosition.setX(static_cast<float>(location.x));
		iosPosition.setY(static_cast<float>(location.y));
		convertToRedBoxScreenPosition(&iosPosition);
	}
	
}
