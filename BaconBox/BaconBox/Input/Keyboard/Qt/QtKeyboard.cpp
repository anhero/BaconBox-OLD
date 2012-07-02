#include "BaconBox/PlatformFlagger.h"

#ifdef RB_QT

#include "BaconBox/Input/Keyboard/Qt/QtKeyboard.h"

#include "BaconBox/Input/InputManager.h"

#include <QKeyEvent>

using namespace BaconBox;

QtKeyboard* QtKeyboard::instance = NULL;


void QtKeyboard::setParentWidget(QWidget* parent) {
	if(instance && parent) {
		instance->setParent(parent);
		instance->setEnabled(true);
		instance->grabKeyboard();
		instance->setFocus(Qt::OtherFocusReason);
		InputManager::getInstance().dontDeleteKeyboards();
	}
}

QtKeyboard::QtKeyboard(QWidget* parent) : Keyboard(), QWidget(parent), qtKeys(std::vector<bool>(Key::NB_KEYS, false)) {
	QtKeyboard::instance = this;
	fillMappings();
}

QtKeyboard::~QtKeyboard() {
}

void QtKeyboard::updateDevice() {
	Keyboard::updateDevice();
	getPreviousKeys() = getKeys();
	getKeys() = qtKeys;
	for(Key::Enum i = 0; i < Key::NB_KEYS;++i) {
		if(isKeyPressed(i)) {
			keyPress(KeySignalData(state, i));
		} else if(isKeyHeld(i)) {
			keyHold(KeySignalData(state, i));
		} else if(isKeyReleased(i)) {
			keyRelease(KeySignalData(state, i));
		}
	}
	for(std::map<std::string, std::set<Key::Enum> >::iterator i = getKeyMasks().begin(); i != getKeyMasks().end(); ++i) {
		if(isKeyMaskPressed(i->first)) {
			keyMaskPress(KeyMaskSignalData(state, i->first));
		} else if(isKeyMaskHeld(i->first)) {
			keyMaskHold(KeyMaskSignalData(state, i->first));
		} else if(isKeyMaskReleased(i->first)) {
			keyMaskRelease(KeyMaskSignalData(state, i->first));
		}
	}
}

void QtKeyboard::keyPressEvent(QKeyEvent* e) {
	Key::Enum keyPressed = getMapping(e->key());
	if(keyPressed != Key::INVALID) {
		qtKeys[keyPressed] = true;
	}
}

void QtKeyboard::keyReleaseEvent(QKeyEvent* e) {
	Key::Enum keyPressed = getMapping(e->key());
	if(keyPressed != Key::INVALID) {
		qtKeys[keyPressed] = false;
	}
}

void QtKeyboard::fillMappings() {
	if(mappings.empty()) {
		mappings[Qt::Key_Escape] = Key::ESCAPE;
		mappings[Qt::Key_Tab] = Key::TAB;
		mappings[Qt::Key_Backspace] = Key::BACKSPACE;
		mappings[Qt::Key_Return] = Key::ENTER;
		mappings[Qt::Key_Enter] = Key::ENTER;
		mappings[Qt::Key_Delete] = Key::DELETEKEY;
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
		mappings[Qt::Key_At] = Key::AT;
		mappings[Qt::Key_A] = Key::A;
		mappings[Qt::Key_B] = Key::B;
		mappings[Qt::Key_C] = Key::C;
		mappings[Qt::Key_D] = Key::D;
		mappings[Qt::Key_E] = Key::E;
		mappings[Qt::Key_F] = Key::F;
		mappings[Qt::Key_G] = Key::G;
		mappings[Qt::Key_H] = Key::H;
		mappings[Qt::Key_I] = Key::I;
		mappings[Qt::Key_J] = Key::J;
		mappings[Qt::Key_K] = Key::K;
		mappings[Qt::Key_L] = Key::L;
		mappings[Qt::Key_M] = Key::M;
		mappings[Qt::Key_N] = Key::N;
		mappings[Qt::Key_O] = Key::O;
		mappings[Qt::Key_P] = Key::P;
		mappings[Qt::Key_Q] = Key::Q;
		mappings[Qt::Key_R] = Key::R;
		mappings[Qt::Key_S] = Key::S;
		mappings[Qt::Key_T] = Key::T;
		mappings[Qt::Key_U] = Key::U;
		mappings[Qt::Key_V] = Key::V;
		mappings[Qt::Key_W] = Key::W;
		mappings[Qt::Key_X] = Key::X;
		mappings[Qt::Key_Y] = Key::Y;
		mappings[Qt::Key_Z] = Key::Z;
		mappings[Qt::Key_BracketLeft] = Key::OPEN_BRACKETS;
		mappings[Qt::Key_BracketRight] = Key::CLOSE_BRACKETS;
		mappings[Qt::Key_AsciiCircum] = Key::CIRCUMFLEX;
		mappings[Qt::Key_Underscore] = Key::UNDERSCORE;
		mappings[Qt::Key_QuoteLeft] = Key::OPEN_QUOTE;
		mappings[Qt::Key_BraceLeft] = Key::OPEN_BRACE;
		mappings[Qt::Key_Bar] = Key::BAR;
		mappings[Qt::Key_BraceRight] = Key::CLOSE_BRACE;
		mappings[Qt::Key_AsciiTilde] = Key::TILDE;
		mappings[Qt::Key_nobreakspace] = Key::NBSP;
		mappings[Qt::Key_periodcentered] = Key::PERIOD;
		mappings[Qt::Key_cedilla] = Key::CLOSE_BRACKETS;
		mappings[Qt::Key_Agrave] = Key::BACKSLASH;
		mappings[Qt::Key_Ccedilla] = Key::CLOSE_BRACKETS;
		mappings[Qt::Key_Egrave] = Key::APOSTROPHE;
		mappings[Qt::Key_Eacute] = Key::SLASH;
		mappings[Qt::Key_multiply] = Key::MULTIPLY;
		mappings[Qt::Key_division] = Key::DIVIDE;
		mappings[Qt::Key_Kanji] = Key::KANJI;
		mappings[Qt::Key_Back] = Key::BROWSER_BACK;
		mappings[Qt::Key_Forward] = Key::BROWSER_FORWARD;
		mappings[Qt::Key_Stop] = Key::BROWSER_STOP;
		mappings[Qt::Key_Refresh] = Key::BROWSER_REFRESH;
		mappings[Qt::Key_VolumeDown] = Key::VOLUME_DOWN;
		mappings[Qt::Key_VolumeUp] = Key::VOLUME_UP;
		mappings[Qt::Key_VolumeMute] = Key::VOLUME_MUTE;
		mappings[Qt::Key_MediaPlay] = Key::MEDIA_PLAY_PAUSE;
		mappings[Qt::Key_MediaStop] = Key::MEDIA_STOP;
		mappings[Qt::Key_MediaPrevious] = Key::MEDIA_PREVIOUS_TRACK;
		mappings[Qt::Key_MediaNext] = Key::MEDIA_NEXT_TRACK;
		mappings[Qt::Key_MediaPause] = Key::MEDIA_PLAY_PAUSE;
		mappings[Qt::Key_MediaTogglePlayPause] = Key::MEDIA_PLAY_PAUSE;
		mappings[Qt::Key_HomePage] = Key::BROWSER_HOME;
		mappings[Qt::Key_Favorites] = Key::BROWSER_FAVORITES;
		mappings[Qt::Key_Search] = Key::BROWSER_SEARCH;
		mappings[Qt::Key_LaunchMail] = Key::LAUNCH_MAIL;
		mappings[Qt::Key_LaunchMedia] = Key::SELECT_MEDIA;
		mappings[Qt::Key_Launch0] = Key::LAUNCH_APPLICATION_1;
		mappings[Qt::Key_Launch1] = Key::LAUNCH_APPLICATION_2;
		mappings[Qt::Key_Execute] = Key::EXECUTE;
		mappings[Qt::Key_Play] = Key::PLAY;
		mappings[Qt::Key_Sleep] = Key::SLEEP;
		mappings[Qt::Key_Zoom] = Key::ZOOM;
	}

}
Key::Enum QtKeyboard::getMapping(int qtKey) const {
	std::map<int, Key::Enum>::const_iterator mapping = mappings.find(qtKey);
	if(mapping == mappings.end()) {
		return Key::INVALID;
	} else {
		return mapping->second;
	}
}

#endif
