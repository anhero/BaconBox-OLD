#include "PlatformFlagger.h"

#ifdef RB_IPHONE_PLATFORM

#include "IOSPointer.h"
#include "CursorButton.h"
#include <iostream>

using namespace RedBox;

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
	
	// We check the touch moving event.
	getCursorPreviousPosition(0) = getCursorPosition(0);
	getCursorPosition(0) = iosPosition;
	if(hasMoved()) {
		Pointer::move.shoot(PointerMoveSignalData(state, 0));
	}
}

void IOSPointer::onTouchBegin(NSSet* touches, UIEvent* event) {
	UITouch * touch = [touches anyObject];
	CGPoint location = [touch locationInView: [touch view]];
	iosPosition.setX(static_cast<float>(location.x));
	iosPosition.setY(static_cast<float>(location.y));
	isTouchDown = true;
}

void IOSPointer::onTouchEnd(NSSet* touches, UIEvent* event) {
	UITouch * touch = [touches anyObject];
	CGPoint location = [touch locationInView: [touch view]];
	iosPosition.setX(static_cast<float>(location.x));
	iosPosition.setY(static_cast<float>(location.y));
	isTouchDown = false;
}

void IOSPointer::onTouchMove(NSSet* touches, UIEvent* event) {
	UITouch * touch = [touches anyObject];
	CGPoint location = [touch locationInView: [touch view]];
	iosPosition.setX(static_cast<float>(location.x));
	iosPosition.setY(static_cast<float>(location.y));
}

#endif