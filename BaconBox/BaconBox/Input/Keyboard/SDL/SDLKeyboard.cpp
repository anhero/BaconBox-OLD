#include "BaconBox/PlatformFlagger.h"

#ifdef RB_SDL

#include "BaconBox/Input/Keyboard/SDL/SDLKeyboard.h"

#include <iostream>

#include <SDL2/SDL.h>

using namespace BaconBox;

SDLKeyboard::SDLKeyboard() : Keyboard(), mappings(std::vector<Key::Enum>(SDL_NUM_SCANCODES, Key::INVALID)) {
	fillMappings();
}

SDLKeyboard::~SDLKeyboard() {
}

void SDLKeyboard::updateDevice() {
	getPreviousKeys() = getKeys();
	Uint8* keyStates = SDL_GetKeyboardState(NULL);
	for(unsigned int i = 0; i < SDL_NUM_SCANCODES; ++i) {
		if(mappings[i] != Key::INVALID) {
			getKeys()[mappings[i]] = static_cast<bool>(keyStates[i]);
		}
	}

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

void SDLKeyboard::fillMappings() {
	mappings[SDL_SCANCODE_UNKNOWN] = Key::INVALID;
	
	/** 
	 *  \name Usage page 0x07
	 *  
	 *  These values are from usage page 0x07 (USB keyboard page).
	 */
	/*@{*/
	
	mappings[SDL_SCANCODE_A] = Key::A;
	mappings[SDL_SCANCODE_B] = Key::B;
	mappings[SDL_SCANCODE_C] = Key::C;
	mappings[SDL_SCANCODE_D] = Key::D;
	mappings[SDL_SCANCODE_E] = Key::E;
	mappings[SDL_SCANCODE_F] = Key::F;
	mappings[SDL_SCANCODE_G] = Key::G;
	mappings[SDL_SCANCODE_H] = Key::H;
	mappings[SDL_SCANCODE_I] = Key::I;
	mappings[SDL_SCANCODE_J] = Key::J;
	mappings[SDL_SCANCODE_K] = Key::K;
	mappings[SDL_SCANCODE_L] = Key::L;
	mappings[SDL_SCANCODE_M] = Key::M;
	mappings[SDL_SCANCODE_N] = Key::N;
	mappings[SDL_SCANCODE_O] = Key::O;
	mappings[SDL_SCANCODE_P] = Key::P;
	mappings[SDL_SCANCODE_Q] = Key::Q;
	mappings[SDL_SCANCODE_R] = Key::R;
	mappings[SDL_SCANCODE_S] = Key::S;
	mappings[SDL_SCANCODE_T] = Key::T;
	mappings[SDL_SCANCODE_U] = Key::U;
	mappings[SDL_SCANCODE_V] = Key::V;
	mappings[SDL_SCANCODE_W] = Key::W;
	mappings[SDL_SCANCODE_X] = Key::X;
	mappings[SDL_SCANCODE_Y] = Key::Y;
	mappings[SDL_SCANCODE_Z] = Key::Z;
	mappings[SDL_SCANCODE_1] = Key::D1;
	mappings[SDL_SCANCODE_2] = Key::D2;
	mappings[SDL_SCANCODE_3] = Key::D3;
	mappings[SDL_SCANCODE_4] = Key::D4;
	mappings[SDL_SCANCODE_5] = Key::D5;
	mappings[SDL_SCANCODE_6] = Key::D6;
	mappings[SDL_SCANCODE_7] = Key::D7;
	mappings[SDL_SCANCODE_8] = Key::D8;
	mappings[SDL_SCANCODE_9] = Key::D9;
	mappings[SDL_SCANCODE_0] = Key::D0;
	
	mappings[SDL_SCANCODE_RETURN] = Key::ENTER;
	mappings[SDL_SCANCODE_ESCAPE] = Key::ESCAPE;
	mappings[SDL_SCANCODE_BACKSPACE] = Key::BACKSPACE;
	mappings[SDL_SCANCODE_TAB] = Key::TAB;
	mappings[SDL_SCANCODE_SPACE] = Key::SPACE;
	
	mappings[SDL_SCANCODE_MINUS] = Key::MINUS;
	mappings[SDL_SCANCODE_EQUALS] = Key::EQUAL;
	mappings[SDL_SCANCODE_LEFTBRACKET] = Key::OPEN_BRACKETS;
	mappings[SDL_SCANCODE_RIGHTBRACKET] = Key::CLOSE_BRACKETS;
	mappings[SDL_SCANCODE_BACKSLASH] = Key::BACKSLASH; /**< Located at the lower left of the return 
														*   key on ISO keyboards and at the right end 
														*   of the QWERTY row on ANSI keyboards. 
														*   Produces REVERSE SOLIDUS (backslash) and 
														*   VERTICAL LINE in a US layoutKey::; REVERSE 
														*   SOLIDUS and VERTICAL LINE in a UK Mac 
														*   layoutKey::; NUMBER SIGN and TILDE in a UK 
														*   Windows layoutKey::; DOLLAR SIGN and POUND SIGN
														*   in a Swiss German layoutKey::; NUMBER SIGN and 
														*   APOSTROPHE in a German layoutKey::; GRAVE 
														*   ACCENT and POUND SIGN in a French Mac 
														*   layoutKey::; and ASTERISK and MICRO SIGN in a 
														*   French Windows layout.
														*/
	mappings[SDL_SCANCODE_NONUSHASH] = Key::NUMBER_SIGN;
	mappings[SDL_SCANCODE_SEMICOLON] = Key::SEMICOLON;
	mappings[SDL_SCANCODE_APOSTROPHE] = Key::APOSTROPHE;
	mappings[SDL_SCANCODE_GRAVE] = Key::GRAVE; /**< Located in the top left corner (on both ANSI 
												*   and ISO keyboards). Produces GRAVE ACCENT and 
												*   TILDE in a US Windows layout and in US and UK 
												*   Mac layouts on ANSI keyboardsKey::; GRAVE ACCENT 
												*   and NOT SIGN in a UK Windows layoutKey::; SECTION 
												*   SIGN and PLUS-MINUS SIGN in US and UK Mac 
												*   layouts on ISO keyboardsKey::; SECTION SIGN and 
												*   DEGREE SIGN in a Swiss German layout (Mac: 
												*   only on ISO keyboards)Key::; CIRCUMFLEX ACCENT and 
												*   DEGREE SIGN in a German layout (Mac: only on 
												*   ISO keyboards)Key::; SUPERSCRIPT TWO and TILDE in a
												*   French Windows layoutKey::; COMMERCIAL AT and 
												*   NUMBER SIGN in a French Mac layout on ISO 
												*   keyboardsKey::; and LESS-THAN SIGN and GREATER-THAN
												*   SIGN in a Swiss GermanKey::; German, or French Mac 
												*   layout on ANSI keyboards.
												*/
	mappings[SDL_SCANCODE_COMMA] = Key::COMMA;
	mappings[SDL_SCANCODE_PERIOD] = Key::PERIOD;
	mappings[SDL_SCANCODE_SLASH] = Key::SLASH;
	
	mappings[SDL_SCANCODE_CAPSLOCK] = Key::CAPS_LOCK;
	
	mappings[SDL_SCANCODE_F1] = Key::F1;
	mappings[SDL_SCANCODE_F2] = Key::F2;
	mappings[SDL_SCANCODE_F3] = Key::F3;
	mappings[SDL_SCANCODE_F4] = Key::F4;
	mappings[SDL_SCANCODE_F5] = Key::F5;
	mappings[SDL_SCANCODE_F6] = Key::F6;
	mappings[SDL_SCANCODE_F7] = Key::F7;
	mappings[SDL_SCANCODE_F8] = Key::F8;
	mappings[SDL_SCANCODE_F9] = Key::F9;
	mappings[SDL_SCANCODE_F10] = Key::F10;
	mappings[SDL_SCANCODE_F11] = Key::F11;
	mappings[SDL_SCANCODE_F12] = Key::F12;
	
	mappings[SDL_SCANCODE_PRINTSCREEN] = Key::PRINT_SCREEN;
	mappings[SDL_SCANCODE_SCROLLLOCK] = Key::SCROLL;
	mappings[SDL_SCANCODE_PAUSE] = Key::PAUSE;
	mappings[SDL_SCANCODE_INSERT] = Key::INSERT; /**< insert on PC, help on some Mac keyboards (but
												  does send code Key::; not 117) */
	mappings[SDL_SCANCODE_HOME] = Key::HOME;
	mappings[SDL_SCANCODE_PAGEUP] = Key::PAGE_UP;
	mappings[SDL_SCANCODE_DELETE] = Key::PAGE_DOWN;
	mappings[SDL_SCANCODE_END] = Key::END;
	mappings[SDL_SCANCODE_PAGEDOWN] = Key::PAGE_DOWN;
	mappings[SDL_SCANCODE_RIGHT] = Key::RIGHT;
	mappings[SDL_SCANCODE_LEFT] = Key::LEFT;
	mappings[SDL_SCANCODE_DOWN] = Key::DOWN;
	mappings[SDL_SCANCODE_UP] = Key::UP;
	
	mappings[SDL_SCANCODE_NUMLOCKCLEAR] = Key::NUM_LOCK; /**< num lock on PC, clear on Mac keyboards 
														  */
	mappings[SDL_SCANCODE_KP_DIVIDE] = Key::DIVIDE;
	mappings[SDL_SCANCODE_KP_MULTIPLY] = Key::MULTIPLY;
	//mappings[SDL_SCANCODE_KP_MINUS] = Key::MINUS;
	mappings[SDL_SCANCODE_KP_PLUS] = Key::PLUS;
	mappings[SDL_SCANCODE_KP_ENTER] = Key::NUM_PAD_ENTER;
	mappings[SDL_SCANCODE_KP_1] = Key::NUM_PAD_1;
	mappings[SDL_SCANCODE_KP_2] = Key::NUM_PAD_2;
	mappings[SDL_SCANCODE_KP_3] = Key::NUM_PAD_3;
	mappings[SDL_SCANCODE_KP_4] = Key::NUM_PAD_4;
	mappings[SDL_SCANCODE_KP_5] = Key::NUM_PAD_5;
	mappings[SDL_SCANCODE_KP_6] = Key::NUM_PAD_6;
	mappings[SDL_SCANCODE_KP_7] = Key::NUM_PAD_7;
	mappings[SDL_SCANCODE_KP_8] = Key::NUM_PAD_8;
	mappings[SDL_SCANCODE_KP_9] = Key::NUM_PAD_9;
	mappings[SDL_SCANCODE_KP_0] = Key::NUM_PAD_0;
	mappings[SDL_SCANCODE_KP_PERIOD] = Key::NUM_PAD_PERIOD;
	
	mappings[SDL_SCANCODE_NONUSBACKSLASH] = Key::TILDE; /**< This is the additional key that ISO 
															 *   keyboards have over ANSI onesKey::; 
															 *   located between left shift and Y. 
															 *   Produces GRAVE ACCENT and TILDE in a
															 *   US or UK Mac layoutKey::; REVERSE SOLIDUS
															 *   (backslash) and VERTICAL LINE in a 
															 *   US or UK Windows layoutKey::; and 
															 *   LESS-THAN SIGN and GREATER-THAN SIGN
															 *   in a Swiss GermanKey::; German, or French
															 *   layout. */
	mappings[SDL_SCANCODE_APPLICATION] = Key::APPS; /**< windows contextual menu, compose */
	mappings[SDL_SCANCODE_POWER] = Key::POWER; /**< The USB document says this is a status flag, 
												*   not a physical key - but some Mac keyboards 
												*   do have a power key. */
	mappings[SDL_SCANCODE_KP_EQUALS] = Key::NUM_PAD_EQUAL;
	mappings[SDL_SCANCODE_F13] = Key::F13;
	mappings[SDL_SCANCODE_F14] = Key::F14;
	mappings[SDL_SCANCODE_F15] = Key::F15;
	mappings[SDL_SCANCODE_F16] = Key::F16;
	mappings[SDL_SCANCODE_F17] = Key::F17;
	mappings[SDL_SCANCODE_F18] = Key::F18;
	mappings[SDL_SCANCODE_F19] = Key::F19;
	mappings[SDL_SCANCODE_F20] = Key::F20;
	mappings[SDL_SCANCODE_F21] = Key::F21;
	mappings[SDL_SCANCODE_F22] = Key::F22;
	mappings[SDL_SCANCODE_F23] = Key::F23;
	mappings[SDL_SCANCODE_F24] = Key::F24;
	mappings[SDL_SCANCODE_EXECUTE] = Key::EXECUTE;
	mappings[SDL_SCANCODE_HELP] = Key::HELP;
	//mappings[SDL_SCANCODE_MENU] = Key::;
	mappings[SDL_SCANCODE_SELECT] = Key::SELECT;
	mappings[SDL_SCANCODE_STOP] = Key::MEDIA_STOP;
	mappings[SDL_SCANCODE_AGAIN] = Key::REDO;   /**< redo */
	mappings[SDL_SCANCODE_UNDO] = Key::UNDO;
	mappings[SDL_SCANCODE_CUT] = Key::CUT;
	mappings[SDL_SCANCODE_COPY] = Key::COPY;
	mappings[SDL_SCANCODE_PASTE] = Key::PASTE;
	mappings[SDL_SCANCODE_FIND] = Key::FIND;
	mappings[SDL_SCANCODE_MUTE] = Key::VOLUME_MUTE;
	mappings[SDL_SCANCODE_VOLUMEUP] = Key::VOLUME_UP;
	mappings[SDL_SCANCODE_VOLUMEDOWN] = Key::VOLUME_DOWN;
	/* not sure whether there's a reason to enable these */
	/*     mappings[SDL_SCANCODE_LOCKINGCAPSLOCK] = Key::;  */
	/*     mappings[SDL_SCANCODE_LOCKINGNUMLOCK] = Key::; */
	/*     mappings[SDL_SCANCODE_LOCKINGSCROLLLOCK] = Key::; */
	//mappings[SDL_SCANCODE_KP_COMMA] = Key::COMMA;
	mappings[SDL_SCANCODE_KP_EQUALSAS400] = Key::NUM_PAD_EQUAL;
	
	/*mappings[SDL_SCANCODE_INTERNATIONAL1] = Key::; < used on Asian keyboards, see 
	 footnotes in USB doc */
	//mappings[SDL_SCANCODE_INTERNATIONAL2] = Key::;
	//mappings[SDL_SCANCODE_INTERNATIONAL3] = Key::; /**< Yen */
	//mappings[SDL_SCANCODE_INTERNATIONAL4] = Key::;
	//mappings[SDL_SCANCODE_INTERNATIONAL5] = Key::;
	//mappings[SDL_SCANCODE_INTERNATIONAL6] = Key::;
	//mappings[SDL_SCANCODE_INTERNATIONAL7] = Key::;
	//mappings[SDL_SCANCODE_INTERNATIONAL8] = Key::;
	//mappings[SDL_SCANCODE_INTERNATIONAL9] = Key::;
	//mappings[SDL_SCANCODE_LANG1] = Key::; /**< Hangul/English toggle */
	//mappings[SDL_SCANCODE_LANG2] = Key::; /**< Hanja conversion */
	//mappings[SDL_SCANCODE_LANG3] = Key::; /**< Katakana */
	//mappings[SDL_SCANCODE_LANG4] = Key::; /**< Hiragana */
	//mappings[SDL_SCANCODE_LANG5] = Key::; /**< Zenkaku/Hankaku */
	//mappings[SDL_SCANCODE_LANG6] = Key::; /**< reserved */
	//mappings[SDL_SCANCODE_LANG7] = Key::; /**< reserved */
	//mappings[SDL_SCANCODE_LANG8] = Key::; /**< reserved */
	//mappings[SDL_SCANCODE_LANG9] = Key::; /**< reserved */
	
	//mappings[SDL_SCANCODE_ALTERASE] = Key::; /**< Erase-Eaze */
	mappings[SDL_SCANCODE_SYSREQ] = Key::SYSREQ;
	mappings[SDL_SCANCODE_CANCEL] = Key::CANCEL;
	mappings[SDL_SCANCODE_CLEAR] = Key::CLEAR;
	//mappings[SDL_SCANCODE_PRIOR] = Key::;
	//mappings[SDL_SCANCODE_RETURN2] = Key::ENTER;
	mappings[SDL_SCANCODE_SEPARATOR] = Key::SEPARATOR;
	//mappings[SDL_SCANCODE_OUT] = Key::;
	//mappings[SDL_SCANCODE_OPER] = Key::;
	//mappings[SDL_SCANCODE_CLEARAGAIN] = Key::;
	mappings[SDL_SCANCODE_CRSEL] = Key::CRSEL;
	mappings[SDL_SCANCODE_EXSEL] = Key::EXSEL;
	
	//mappings[SDL_SCANCODE_KP_00] = Key::;
	//mappings[SDL_SCANCODE_KP_000] = Key::;
	//mappings[SDL_SCANCODE_THOUSANDSSEPARATOR] = Key::;
	//mappings[SDL_SCANCODE_DECIMALSEPARATOR] = Key::;
	//mappings[SDL_SCANCODE_CURRENCYUNIT] = Key::;
	//mappings[SDL_SCANCODE_CURRENCYSUBUNIT] = Key::;
	//mappings[SDL_SCANCODE_KP_LEFTPAREN] = Key::OPEN_PAREN;
	//mappings[SDL_SCANCODE_KP_RIGHTPAREN] = Key::CLOSE_PAREN;
	//mappings[SDL_SCANCODE_KP_LEFTBRACE] = Key::OPEN_BRACE;
	//mappings[SDL_SCANCODE_KP_RIGHTBRACE] = Key::CLOSE_BRACE;
	//mappings[SDL_SCANCODE_KP_TAB] = Key::TAB;
	//mappings[SDL_SCANCODE_KP_BACKSPACE] = Key::BACKSPACE;
	//mappings[SDL_SCANCODE_KP_A] = Key::A;
	//mappings[SDL_SCANCODE_KP_B] = Key::B;
	//mappings[SDL_SCANCODE_KP_C] = Key::C;
	//mappings[SDL_SCANCODE_KP_D] = Key::D;
	//mappings[SDL_SCANCODE_KP_E] = Key::E;
	//mappings[SDL_SCANCODE_KP_F] = Key::F;
	//mappings[SDL_SCANCODE_KP_XOR] = Key::;
	//mappings[SDL_SCANCODE_KP_POWER] = Key::POWER;
	mappings[SDL_SCANCODE_KP_PERCENT] = Key::PERCENT;
	mappings[SDL_SCANCODE_KP_LESS] = Key::LESS;
	mappings[SDL_SCANCODE_KP_GREATER] = Key::GREATER;
	mappings[SDL_SCANCODE_KP_AMPERSAND] = Key::AMPERSAND;
	//mappings[SDL_SCANCODE_KP_DBLAMPERSAND] = Key::;
	mappings[SDL_SCANCODE_KP_VERTICALBAR] = Key::PIPE;
	//mappings[SDL_SCANCODE_KP_DBLVERTICALBAR] = Key::;
	mappings[SDL_SCANCODE_KP_COLON] = Key::COLON;
	//mappings[SDL_SCANCODE_KP_HASH] = Key::NUMBER_SIGN;
	//mappings[SDL_SCANCODE_KP_SPACE] = Key::SPACE;
	mappings[SDL_SCANCODE_KP_AT] = Key::AT;
	mappings[SDL_SCANCODE_KP_EXCLAM] = Key::EXCLAM;
	//mappings[SDL_SCANCODE_KP_MEMSTORE] = Key::;
	//mappings[SDL_SCANCODE_KP_MEMRECALL] = Key::;
	//mappings[SDL_SCANCODE_KP_MEMCLEAR] = Key::;
	//mappings[SDL_SCANCODE_KP_MEMADD] = Key::;
	//mappings[SDL_SCANCODE_KP_MEMSUBTRACT] = Key::;
	//mappings[SDL_SCANCODE_KP_MEMMULTIPLY] = Key::;
	//mappings[SDL_SCANCODE_KP_MEMDIVIDE] = Key::;
	//mappings[SDL_SCANCODE_KP_PLUSMINUS] = Key::;
	mappings[SDL_SCANCODE_KP_CLEAR] = Key::CLEAR;
	//mappings[SDL_SCANCODE_KP_CLEARENTRY] = Key::;
	//mappings[SDL_SCANCODE_KP_BINARY] = Key::;
	//mappings[SDL_SCANCODE_KP_OCTAL] = Key::;
	//mappings[SDL_SCANCODE_KP_DECIMAL] = Key::;
	//mappings[SDL_SCANCODE_KP_HEXADECIMAL] = Key::;
	
	mappings[SDL_SCANCODE_LCTRL] = Key::LEFT_CONTROL;
	mappings[SDL_SCANCODE_LSHIFT] = Key::LEFT_SHIFT;
	mappings[SDL_SCANCODE_LALT] = Key::LEFT_ALT; /**< alt, option */
	mappings[SDL_SCANCODE_LGUI] = Key::LEFT_WINDOWS; /**< windows, command (apple), meta */
	mappings[SDL_SCANCODE_RCTRL] = Key::RIGHT_CONTROL;
	mappings[SDL_SCANCODE_RSHIFT] = Key::RIGHT_SHIFT;
	mappings[SDL_SCANCODE_RALT] = Key::RIGHT_ALT; /**< alt gr, option */
	mappings[SDL_SCANCODE_RGUI] = Key::RIGHT_WINDOWS; /**< windows, command (apple), meta */
	
	//mappings[SDL_SCANCODE_MODE] = Key::;    /**< I'm not sure if this is really not covered
	// *   by any of the aboveKey::; but since there's a
	// *   special KMOD_MODE for it I'm adding it here
	// */
	
	/*@}*//*Usage page 0x07*/
	
	/**
	 *  \name Usage page 0x0C
	 *  
	 *  These values are mapped from usage page 0x0C (USB consumer page).
	 */
	/*@{*/
	
	mappings[SDL_SCANCODE_AUDIONEXT] = Key::MEDIA_NEXT_TRACK;
	mappings[SDL_SCANCODE_AUDIOPREV] = Key::MEDIA_PREVIOUS_TRACK;
	mappings[SDL_SCANCODE_AUDIOSTOP] = Key::MEDIA_STOP;
	mappings[SDL_SCANCODE_AUDIOPLAY] = Key::MEDIA_PLAY_PAUSE;
	mappings[SDL_SCANCODE_AUDIOMUTE] = Key::VOLUME_MUTE;
	mappings[SDL_SCANCODE_MEDIASELECT] = Key::SELECT_MEDIA;
	mappings[SDL_SCANCODE_WWW] = Key::LAUNCH_APPLICATION_1;
	mappings[SDL_SCANCODE_MAIL] = Key::LAUNCH_MAIL;
	mappings[SDL_SCANCODE_CALCULATOR] = Key::LAUNCH_APPLICATION_2;
	//mappings[SDL_SCANCODE_COMPUTER] = Key::;
	mappings[SDL_SCANCODE_AC_SEARCH] = Key::BROWSER_SEARCH;
	mappings[SDL_SCANCODE_AC_HOME] = Key::BROWSER_HOME;
	mappings[SDL_SCANCODE_AC_BACK] = Key::BROWSER_BACK;
	mappings[SDL_SCANCODE_AC_FORWARD] = Key::BROWSER_FORWARD;
	mappings[SDL_SCANCODE_AC_STOP] = Key::BROWSER_STOP;
	mappings[SDL_SCANCODE_AC_REFRESH] = Key::BROWSER_REFRESH;
	mappings[SDL_SCANCODE_AC_BOOKMARKS] = Key::BROWSER_FAVORITES;
	
	/*@}*//*Usage page 0x0C*/
	
	/**
	 *  \name Walther keys
	 *  
	 *  These are values that Christian Walther added (for mac keyboard?).
	 */
	/*@{*/
	
	//mappings[SDL_SCANCODE_BRIGHTNESSDOWN] = Key::;
	//mappings[SDL_SCANCODE_BRIGHTNESSUP] = Key::;
	//mappings[SDL_SCANCODE_DISPLAYSWITCH] = Key::; /**< display mirroring/dual display
	// switchKey::; video mode switch */
	//mappings[SDL_SCANCODE_KBDILLUMTOGGLE] = Key::;
	//mappings[SDL_SCANCODE_KBDILLUMDOWN] = Key::;
	//mappings[SDL_SCANCODE_KBDILLUMUP] = Key::;
	mappings[SDL_SCANCODE_EJECT] = Key::EJECT;
	mappings[SDL_SCANCODE_SLEEP] = Key::SLEEP;
}

#endif
