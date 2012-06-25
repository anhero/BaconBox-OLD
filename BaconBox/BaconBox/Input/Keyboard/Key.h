/**
 * @file
 * @ingroup Input
 */
#ifndef RB_KEY_H
#define RB_KEY_H
namespace BaconBox {
	/**
	 * Key codes for keyboard input.
	 */
	namespace Key {
		typedef int Enum;
		
		/**
		 * Get the char from a key.
		 * @param key Key to get the char of. Must be an alphabet letter (A-Z
		 * key codes).
		 * @return Char equivalent to the key. If the key received is not a
		 * letter from A to Z, it returns the null character '\0'.
		 */
		char toChar(Enum key);
		
		const Enum INVALID = -1;
		const Enum A = 0;
		const Enum ADD = 1;
		const Enum APPS = 2;
		const Enum ATTN = 3;
		const Enum B = 4;
		const Enum BACKSPACE = 5;
		const Enum BROWSER_BACK = 6;
		const Enum BROWSER_FAVORITES = 7;
		const Enum BROWSER_FORWARD = 8;
		const Enum BROWSER_HOME = 9;
		const Enum BROWSER_REFRESH = 10;
		const Enum BROWSER_SEARCH = 11;
		const Enum BROWSER_STOP = 12;
		const Enum C = 13;
		const Enum CAPS_LOCK = 14;
		const Enum CHAT_PAD_GREEN = 15;
		const Enum CHAT_PAD_ORANGE = 16;
		const Enum CRSEL = 17;
		const Enum D = 18;
		const Enum D0 = 19;
		const Enum D1 = 20;
		const Enum D2 = 21;
		const Enum D3 = 22;
		const Enum D4 = 23;
		const Enum D5 = 24;
		const Enum D6 = 25;
		const Enum D7 = 26;
		const Enum D8 = 27;
		const Enum D9 = 28;
		const Enum DECIMAL = 29;
		const Enum DELETEKEY = 30;
		const Enum DIVIDE = 31;
		const Enum DOWN = 32;
		const Enum E = 33;
		const Enum END = 34;
		const Enum ENTER = 35;
		const Enum ERASE_EOF = 36;
		const Enum ESCAPE = 37;
		const Enum EXECUTE = 38;
		const Enum EXSEL = 39;
		const Enum F = 40;
		const Enum F1 = 41;
		const Enum F10 = 42;
		const Enum F11 = 43;
		const Enum F12 = 44;
		const Enum F13 = 45;
		const Enum F14 = 46;
		const Enum F15 = 47;
		const Enum F16 = 48;
		const Enum F17 = 49;
		const Enum F18 = 50;
		const Enum F19 = 51;
		const Enum F2 = 52;
		const Enum F20 = 53;
		const Enum F21 = 54;
		const Enum F22 = 55;
		const Enum F23 = 56;
		const Enum F24 = 57;
		const Enum F3 = 58;
		const Enum F4 = 59;
		const Enum F5 = 60;
		const Enum F6 = 61;
		const Enum F7 = 62;
		const Enum F8 = 63;
		const Enum F9 = 64;
		const Enum G = 65;
		const Enum H = 66;
		const Enum HELP = 67;
		const Enum HOME = 68;
		const Enum I = 69;
		const Enum IME_CONVERT = 70;
		const Enum IME_NO_CONVERT = 71;
		const Enum INSERT = 72;
		const Enum J = 73;
		const Enum K = 74;
		const Enum KANA = 75;
		const Enum KANJI = 76;
		const Enum L = 77;
		const Enum LAUNCH_APPLICATION_1 = 78;
		const Enum LAUNCH_APPLICATION_2 = 79;
		const Enum LAUNCH_MAIL = 80;
		const Enum LEFT = 81;
		const Enum LEFT_ALT = 82;
		const Enum LEFT_CONTROL = 83;
		const Enum LEFT_SHIFT = 84;
		const Enum LEFT_WINDOWS = 85;
		const Enum M = 86;
		const Enum MEDIA_NEXT_TRACK = 87;
		const Enum MEDIA_PLAY_PAUSE = 88;
		const Enum MEDIA_PREVIOUS_TRACK = 89;
		const Enum MEDIA_STOP = 90;
		const Enum MULTIPLY = 91;
		const Enum N = 92;
		const Enum NONE = 93;
		const Enum NUM_LOCK = 94;
		const Enum NUM_PAD_0 = 95;
		const Enum NUM_PAD_1 = 96;
		const Enum NUM_PAD_2 = 97;
		const Enum NUM_PAD_3 = 98;
		const Enum NUM_PAD_4 = 99;
		const Enum NUM_PAD_5 = 100;
		const Enum NUM_PAD_6 = 101;
		const Enum NUM_PAD_7 = 102;
		const Enum NUM_PAD_8 = 103;
		const Enum NUM_PAD_9 = 104;
		const Enum O = 105;
		const Enum EXCLAM = 106;
		const Enum AUTO = 107;
		const Enum BACKSLASH = 108;
		const Enum CLEAR = 109;
		const Enum CLOSE_BRACKETS = 110;
		const Enum COMMA = 111;
		const Enum COPY = 112;
		const Enum ENL_W = 113;
		const Enum MINUS = 114;
		const Enum OPEN_BRACKETS = 115;
		const Enum PERIOD = 116;
		const Enum PIPE = 117;
		const Enum PLUS = 118;
		const Enum QUESTION = 119;
		const Enum QUOTES = 120;
		const Enum SEMICOLON = 121;
		const Enum TILDE = 122;
		const Enum P = 123;
		const Enum PA_1 = 124;
		const Enum PAGE_DOWN = 125;
		const Enum PAGE_UP = 126;
		const Enum PAUSE = 127;
		const Enum PLAY = 128;
		const Enum PRINT = 129;
		const Enum PRINT_SCREEN = 130;
		const Enum PROCESS_KEY = 131;
		const Enum Q = 132;
		const Enum R = 133;
		const Enum RIGHT = 134;
		const Enum RIGHT_ALT = 135;
		const Enum RIGHT_CONTROL = 136;
		const Enum RIGHT_SHIFT = 137;
		const Enum RIGHT_WINDOWS = 138;
		const Enum S = 139;
		const Enum SCROLL = 140;
		const Enum SELECT = 141;
		const Enum SELECT_MEDIA = 142;
		const Enum SEPARATOR = 143;
		const Enum SLEEP = 144;
		const Enum SPACE = 145;
		const Enum SUBTRACT = 146;
		const Enum T = 147;
		const Enum TAB = 148;
		const Enum U = 149;
		const Enum UP = 150;
		const Enum V = 151;
		const Enum VOLUME_DOWN = 152;
		const Enum VOLUME_MUTE = 153;
		const Enum VOLUME_UP = 154;
		const Enum W = 155;
		const Enum X = 156;
		const Enum Y = 157;
		const Enum Z = 158;
		const Enum ZOOM = 159;
		const Enum SYSREQ = 160;
		const Enum NUMBER_SIGN = 161;
		const Enum DOLLAR = 162;
		const Enum PERCENT = 163;
		const Enum AMPERSAND = 164;
		const Enum APOSTROPHE = 165;
		const Enum OPEN_PAREN = 166;
		const Enum CLOSE_PAREN = 167;
		const Enum ASTERISK = 168;
		const Enum SLASH = 169;
		const Enum COLON = 170;
		const Enum LESS = 171;
		const Enum EQUAL = 172;
		const Enum GREATER = 173;
		const Enum AT = 174;
		const Enum CIRCUMFLEX = 175;
		const Enum UNDERSCORE = 176;
		const Enum OPEN_QUOTE = 177;
		const Enum OPEN_BRACE = 178;
		const Enum CLOSE_BRACE = 179;
		const Enum BAR = 180;
		const Enum NBSP = 181;
		const Enum GRAVE = 182;
		const Enum POWER = 183;
		const Enum NUM_PAD_ENTER = 184;
		const Enum NUM_PAD_PERIOD = 185;
		const Enum NUM_PAD_EQUAL = 186;
		const Enum UNDO = 187;
		const Enum REDO = 188;
		const Enum CUT = 189;
		const Enum PASTE = 190;
		const Enum FIND = 191;
		const Enum CANCEL = 192;
		const Enum EJECT = 193;
		const int NB_KEYS = 194;
	}
}
 #endif
