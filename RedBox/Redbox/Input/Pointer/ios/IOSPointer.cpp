#include "IOSPointer.h"
#include "CursorButton.h"
#define RB_MAX_IOS_NB_OF_TOUCH 11
using namespace RedBox;

sigly::Signal2<NSSet*, UIEvent*> IOSPointer::touchBegin = sigly::Signal2<NSSet*, UIEvent*>();
sigly::Signal2<NSSet*, UIEvent*> IOSPointer::touchEnd = sigly::Signal2<NSSet*, UIEvent*>();
sigly::Signal2<NSSet*, UIEvent*> IOSPointer::touchMove = sigly::Signal2<NSSet*, UIEvent*>();
sigly::Signal2<NSSet*, UIEvent*> IOSPointer::touchCancelled = sigly::Signal2<NSSet*, UIEvent*>();

IOSPointer::IOSPointer(): Pointer(RB_MAX_IOS_NB_OF_TOUCH), sigly::HasSlots<>(), touches(RB_MAX_IOS_NB_OF_TOUCH) {
	touchBegin.connect(this, &IOSPointer::onTouchBegin);
	touchEnd.connect(this, &IOSPointer::onTouchEnd);
	touchMove.connect(this, &IOSPointer::onTouchMove);
    touchCancelled.connect(this, &IOSPointer::onTouchCancelled);
}

IOSPointer::~IOSPointer() {
}

void IOSPointer::updateDevice() {
    
    
    for (unsigned int i = 0;  i < RB_MAX_IOS_NB_OF_TOUCH; i++) {
        getCursorPreviousPosition(i) = getCursorPosition(i);
        getCursorPosition(i) = this->touches[i].position;
        getCursorPreviousButtons(i)[CursorButton::LEFT] = getCursorButtons(i)[CursorButton::LEFT];
        getCursorButtons(i)[CursorButton::LEFT] = this->touches[i].inContact;
        
        
        if(isButtonPressed(CursorButton::LEFT, i)) {
            buttonPress(PointerButtonSignalData(state, i, CursorButton::LEFT));
        } 
        else if(isButtonHeld(CursorButton::LEFT, i)) {
            buttonHold(PointerButtonSignalData(state, i, CursorButton::LEFT));
        } 
        else if(isButtonReleased(CursorButton::LEFT, i)) {
            buttonRelease(PointerButtonSignalData(state, i, CursorButton::LEFT));
        }
        if(hasMoved(i)) {
            Pointer::move.shoot(PointerSignalData(state, i));
        }
    }
	
	
}

int IOSPointer::AddNewTouch(UITouch* touch){
    for (unsigned int i = 0; i < RB_MAX_IOS_NB_OF_TOUCH; i++) {
        if(touches[i].touch == NULL){
            touches[i].touch = touch;
            return  i;
        }
    }
    return -1;
}

int IOSPointer::getTouchID(UITouch* touch){
    for (unsigned int i = 0; i < RB_MAX_IOS_NB_OF_TOUCH; i++) {
        if (touches[i].touch == touch) {
            return i;
        }
    }
    return -1;
}

void IOSPointer::onTouchBegin(NSSet* touches, UIEvent* event) {
	for(UITouch * touch in touches){
        int touchID = getTouchID(touch);
        
        if (touchID == -1){
            touchID = AddNewTouch(touch);
        }
        if(touchID != -1){
            CGPoint location = [touch locationInView: [touch view]];
            this->touches[touchID].position =  Vector2(static_cast<float>(location.x), static_cast<float>(location.y) );
            this->touches[touchID].inContact = true;
        }
    }
    
}

void IOSPointer::onTouchEnd(NSSet* touches, UIEvent* event) {
	for(UITouch * touch in touches){
        int touchID = getTouchID(touch);
        
        if (touchID != -1){
            this->touches[touchID].touch = NULL;
            
            CGPoint location = [touch locationInView: [touch view]];
            this->touches[touchID].position =  Vector2(static_cast<float>(location.x), static_cast<float>(location.y) );
            this->touches[touchID].inContact = false;
        }
        
        
    }
}

void IOSPointer::onTouchCancelled(NSSet* touches, UIEvent* event){
    onTouchEnd(touches, event);
}

void IOSPointer::onTouchMove(NSSet* touches, UIEvent* event) {
	for(UITouch * touch in touches){
        int touchID = getTouchID(touch);
        
        if(touchID != -1){
            CGPoint location = [touch locationInView: [touch view]];
            this->touches[touchID].position =  Vector2(static_cast<float>(location.x), static_cast<float>(location.y) );
            this->touches[touchID].inContact = true;
        }
    }
    
}

