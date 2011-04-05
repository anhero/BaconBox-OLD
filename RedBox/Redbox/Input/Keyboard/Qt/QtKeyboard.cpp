#include "PlatformFlagger.h"

#ifdef RB_QT

#include "QtKeyboard.h"

#include <iostream>

#include <QKeyEvent>

using namespace RedBox;

QtKeyboard* QtKeyboard::instance = NULL;


void QtKeyboard::setParentWidget(QWidget* parent) {
	if(instance && parent) {
		instance->setParent(parent);
		instance->setEnabled(true);
		instance->grabKeyboard();
		instance->setFocus(Qt::OtherFocusReason);
	} else {
		std::cout << "Damn it!" << std::endl;
	}
}

QtKeyboard::QtKeyboard(QWidget* parent) : Keyboard(), QWidget(parent) {
	QtKeyboard::instance = this;
}

QtKeyboard::~QtKeyboard() {
}

void QtKeyboard::updateDevice() {
}

void QtKeyboard::keyPressEvent(QKeyEvent* e) {
	std::cout << e->key() << std::endl;
}

void QtKeyboard::fillMappings() {
	if(mappings.empty()) {
		mappings[Qt::Key_Escape] = Key::ESCAPE;
		mappings[Qt::Key_Tab] = Key::TAB;
		mappings[Qt::Key_Backspace] = Key::BACKSPACE;
		mappings[Qt::Key_Return] = Key::ENTER;
		mappings[Qt::Key_Enter] = Key::ENTER;
		mappings[Qt::Key_Delete] = Key::DELETE;
		mappings[Qt::Key_Pause] = Key::PAUSE;
		mappings[Qt::Key_Print] = Key::PRINT;
		mappings[Qt::Key_SysReq] = Key::SYSREQ;
		mappings[Qt::Key_Clear] = Key::CLEAR;
		mappings[Qt::Key_Home] = Key::HOME;
		mappings[Qt::Key_End] = Key::END;
		mappings[Qt::Key_Left] = Key::LEFT;
		mappings[Qt::Key_Up] = Key::UP;
		mappings[Qt::Key_Right] = Key::RIGHT;
		mappings[Qt::Key_Down] = Key::DOWN;
		mappings[Qt::Key_PageUp] = Key::PAGE_UP;
		mappings[Qt::Key_PageDown] = Key::PAGE_DOWN;
		mappings[Qt::Key_Shift] = Key::LEFT_SHIFT;
		mappings[Qt::Key_Control] = Key::LEFT_CONTROL;
		mappings[Qt::Key_Meta] = Key::LEFT_WINDOWS;
		mappings[Qt::Key_Alt] = Key::LEFT_ALT;
		mappings[Qt::Key_AltGr] = Key::RIGHT_ALT;
		mappings[Qt::Key_CapsLock] = Key::CAPS_LOCK;
		mappings[Qt::Key_NumLock] = Key::NUM_LOCK;
		mappings[Qt::Key_ScrollLock] = Key::SCROLL;
		mappings[Qt::Key_F1] = Key::F1;
		mappings[Qt::Key_F2] = Key::F2;
		mappings[Qt::Key_F3] = Key::F3;
		mappings[Qt::Key_F4] = Key::F4;
		mappings[Qt::Key_F5] = Key::F5;
		mappings[Qt::Key_F6] = Key::F6;
		mappings[Qt::Key_F7] = Key::F7;
		mappings[Qt::Key_F8] = Key::F8;
		mappings[Qt::Key_F9] = Key::F9;
		mappings[Qt::Key_F10] = Key::F10;
		mappings[Qt::Key_F11] = Key::F11;
		mappings[Qt::Key_F12] = Key::F12;
		mappings[Qt::Key_F13] = Key::F13;
		mappings[Qt::Key_F14] = Key::F14;
		mappings[Qt::Key_F15] = Key::F15;
		mappings[Qt::Key_F16] = Key::F16;
		mappings[Qt::Key_F17] = Key::F17;
		mappings[Qt::Key_F18] = Key::F18;
		mappings[Qt::Key_F19] = Key::F19;
		mappings[Qt::Key_F20] = Key::F20;
		mappings[Qt::Key_F21] = Key::F21;
		mappings[Qt::Key_F22] = Key::F22;
		mappings[Qt::Key_F23] = Key::F23;
		mappings[Qt::Key_F24] = Key::F24;
		mappings[Qt::Key_F25] = Key::F24;
		mappings[Qt::Key_F26] = Key::F24;
		mappings[Qt::Key_F27] = Key::F24;
		mappings[Qt::Key_F28] = Key::F24;
		mappings[Qt::Key_F29] = Key::F24;
		mappings[Qt::Key_F30] = Key::F24;
		mappings[Qt::Key_F31] = Key::F24;
		mappings[Qt::Key_F32] = Key::F24;
		mappings[Qt::Key_F33] = Key::F24;
		mappings[Qt::Key_F34] = Key::F24;
		mappings[Qt::Key_F35] = Key::F24;
		mappings[Qt::Key_Super_L] = Key::LEFT_WINDOWS;
		mappings[Qt::Key_Super_R] = Key::RIGHT_WINDOWS;
		mappings[Qt::Key_Menu] = Key::ESCAPE;
		mappings[Qt::Key_Hyper_L] = Key::LEFT_WINDOWS;
		mappings[Qt::Key_Hyper_R] = Key::RIGHT_WINDOWS;
		mappings[Qt::Key_Help] = Key::HELP;
		mappings[Qt::Key_Direction_L] = Key::ESCAPE;
		mappings[Qt::Key_Direction_R] = Key::ESCAPE;
		mappings[Qt::Key_Space] = Key::SPACE;
		mappings[Qt::Key_Any] = mappings[Qt::Key_Space];
		mappings[Qt::Key_Exclam] = Key::EXCLAM;
		mappings[Qt::Key_QuoteDbl] = Key::QUOTES;
		mappings[Qt::Key_NumberSign] = Key::NUMBER_SIGN;
		mappings[Qt::Key_Dollar] = Key::DOLLAR;
		mappings[Qt::Key_Percent] = Key::PERCENT;
		mappings[Qt::Key_Ampersand] = Key::AMPERSAND;
		mappings[Qt::Key_Apostrophe] = Key::APOSTROPHE;
		mappings[Qt::Key_ParenLeft] = Key::OPEN_PAREN;
		mappings[Qt::Key_ParenRight] = Key::CLOSE_PAREN;
		mappings[Qt::Key_Asterisk] = Key::ASTERISK;
		mappings[Qt::Key_Plus] = Key::PLUS;
		mappings[Qt::Key_Comma] = Key::COMMA;
		mappings[Qt::Key_Minus] = Key::MINUS;
		mappings[Qt::Key_Period] = Key::PERIOD;
		mappings[Qt::Key_Slash] = Key::SLASH;
		mappings[Qt::Key_0] = Key::D0;
		mappings[Qt::Key_1] = Key::D1;
		mappings[Qt::Key_2] = Key::D2;
		mappings[Qt::Key_3] = Key::D3;
		mappings[Qt::Key_4] = Key::D4;
		mappings[Qt::Key_5] = Key::D5;
		mappings[Qt::Key_6] = Key::D6;
		mappings[Qt::Key_7] = Key::D7;
		mappings[Qt::Key_8] = Key::D8;
		mappings[Qt::Key_9] = Key::D9;
		mappings[Qt::Key_Colon] = Key::COLON;
		mappings[Qt::Key_Semicolon] = Key::SEMICOLON;
		mappings[Qt::Key_Less] = Key::LESS;
		mappings[Qt::Key_Equal] = Key::EQUAL;
		mappings[Qt::Key_Greater] = Key::GREATER;
		mappings[Qt::Key_Question] = Key::QUESTION;
	}
}

#endif
