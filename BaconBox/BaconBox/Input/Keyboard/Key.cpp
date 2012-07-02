#include "BaconBox/Input/Keyboard/Key.h"

namespace BaconBox {
	namespace Key {
		char toChar(Enum key) {
			char result = 0;
			switch (key) {
				case A:
					result = 'a';
					break;
				case B:
					result = 'b';
					break;
				case C:
					result = 'c';
					break;
				case D:
					result = 'd';
					break;
				case E:
					result = 'e';
					break;
				case F:
					result = 'f';
					break;
				case G:
					result = 'g';
					break;
				case H:
					result = 'h';
					break;
				case I:
					result = 'i';
					break;
				case J:
					result = 'j';
					break;
				case K:
					result = 'k';
					break;
				case L:
					result = 'l';
					break;
				case M:
					result = 'm';
					break;
				case N:
					result = 'n';
					break;
				case O:
					result = 'o';
					break;
				case P:
					result = 'p';
					break;
				case Q:
					result = 'q';
					break;
				case R:
					result = 'r';
					break;
				case S:
					result = 's';
					break;
				case T:
					result = 't';
					break;
				case U:
					result = 'u';
					break;
				case V:
					result = 'v';
					break;
				case W:
					result = 'w';
					break;
				case X:
					result = 'x';
					break;
				case Y:
					result = 'y';
					break;
				case Z:
					result = 'z';
					break;
				default:
					break;
			}
			return result;
		}
	}
}
