#include "BaconBox/Input/Pointer/Qt/QtPointer.h"

#include "BaconBox/Input/InputManager.h"

#include <QMouseEvent>
#include <QCursor>
#include <QPoint>
#include <QApplication>

using namespace BaconBox;

QtPointer* QtPointer::instance = NULL;

void QtPointer::setParentWidget(QWidget* parent) {
	if(instance && parent) {
		instance->setParent(parent);
		instance->setMinimumSize(parent->minimumSize());
		instance->setEnabled(true);
		instance->grabMouse();
		instance->setMouseTracking(true);
		instance->raise();
		InputManager::getInstance().dontDeletePointers();
	}
}

QtPointer::QtPointer(QWidget* parent): QWidget(parent), Pointer() {
	QtPointer::instance = this;
}

QtPointer::~QtPointer() {
}

void QtPointer::updateDevice() {
	Pointer::updateDevice();
	// We check the mouse button events.
	getCursorPreviousButtons(0) = getCursorButtons(0);
	Qt::MouseButtons buttons = QApplication::mouseButtons();

	getCursorButtons(0)[CursorButton::LEFT] = buttons.testFlag(Qt::LeftButton);
	getCursorButtons(0)[CursorButton::RIGHT] = buttons.testFlag(Qt::RightButton);
	getCursorButtons(0)[CursorButton::MIDDLE] = buttons.testFlag(Qt::MiddleButton) || buttons.testFlag(Qt::MidButton);
	getCursorButtons(0)[CursorButton::OTHER_BUTTON_1] = buttons.testFlag(Qt::XButton1);
	getCursorButtons(0)[CursorButton::OTHER_BUTTON_2] = buttons.testFlag(Qt::XButton2);

	for(CursorButton::Enum i = 0; i < CursorButton::NB_BUTTONS; ++i) {
		if(isButtonPressed(i)) {
			buttonPress(PointerButtonSignalData(state, 0, i));
		} else if(isButtonHeld(i)) {
			buttonHold(PointerButtonSignalData(state, 0, i));
		} else if(isButtonReleased(i)) {
			buttonRelease(PointerButtonSignalData(state, 0, i));
		}
	}

	// We check the mouse move events.
	QPoint cursorPosition = this->parentWidget()->mapFromGlobal(QCursor::pos());
	getCursorPreviousPosition(0) = getCursorPosition(0);
	getCursorPosition(0) = Vector2(cursorPosition.x(), cursorPosition.y());
	if(hasMoved()) {
		Pointer::move.shoot(PointerSignalData(state, 0));
	}
}
