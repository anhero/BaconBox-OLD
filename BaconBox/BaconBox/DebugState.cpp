#if 0
#include "BaconBox/DebugState.h"

#include "GraphicBody.h" //@TODO: WARNING: Missing file. (automated script)
#include "BaconBox/Console.h"
#include "BaconBox/Input/Pointer/Pointer.h"
#include "BaconBox/Input/Keyboard/Keyboard.h"
#include "AABB.h" //@TODO: WARNING: Missing file. (automated script)

using namespace BaconBox;

DebugState::DebugState(const std::string& newName,
                       Key::Enum newDebugKey) : State(newName),
    selectedBody(NULL), cursorOffset(), debugKey(newDebugKey) {
	Pointer::connectButtonPress(this, &DebugState::onPointerButtonPress);
	Pointer::connectButtonHold(this, &DebugState::onPointerButtonHold);
	Pointer::connectButtonRelease(this, &DebugState::onPointerButtonRelease);
	Keyboard::connectKeyRelease(this, &DebugState::onKeyRelease);
}

DebugState::~DebugState() {
}

void DebugState::onPointerButtonPress(PointerButtonSignalData data) {
	if(data.cursorButton == CursorButton::LEFT) {
		BodyMap::const_reverse_iterator i = graphicBodies.rbegin();
		AABB boundingBox;
		selectedBody = NULL;
		while(i != graphicBodies.rend() && selectedBody == NULL) {
			if(i->second->isVisible()) {
				boundingBox = AABB(i->second->getXPosition(),
								   i->second->getXPosition() + i->second->getWidth(),
								   i->second->getYPosition(),
								   i->second->getYPosition() + i->second->getHeight());
				if(boundingBox.overlaps(data.getPosition())) {
					cursorOffset = data.getPosition() - i->second->getPosition();
					Console::print("Cursor position: ");
					Console::println(camera.screenToWorld(data.getPosition()));
					Console::print("GraphicBody position: ");
					Console::println(i->second->getPosition());
					selectedBody = i->second;
				} else {
					++i;
				}
			} else {
				++i;
			}
		}
	}
}

void DebugState::onPointerButtonHold(PointerButtonSignalData data) {
	if(data.cursorButton == CursorButton::LEFT && selectedBody) {
		selectedBody->move(data.getPosition() - data.getPreviousPosition());
		Console::print("GraphicBody position: ");
		Console::println(selectedBody->getPosition());
	}
}

void DebugState::onPointerButtonRelease(PointerButtonSignalData data) {
	if(data.cursorButton == CursorButton::LEFT) {
		selectedBody = NULL;
	}
}

void DebugState::onKeyRelease(KeySignalData data) {
	if(data.key == debugKey && Pointer::getDefault()) {
		Console::print("Cursor position: ");
		Console::println(camera.screenToWorld(Pointer::getDefault()->getState().getCursorState().getPosition()));
	}
}

#endif
