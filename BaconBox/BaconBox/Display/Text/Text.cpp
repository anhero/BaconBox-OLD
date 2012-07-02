#include "BaconBox/Display/Text/Text.h"

namespace BaconBox {
	Text::Text(FontPointer newFont,
	           TextAlignment newAlignment,
	           TextDirection newDirection,
	           const Vector2 &startingPosition) :
		GraphicString<Collidable>(newFont, newAlignment, newDirection,
		                          startingPosition), Layerable() {
	}

	Text::Text(FontPointer newFont,
	           const std::string &newText,
	           TextAlignment newAlignment,
	           TextDirection newDirection,
	           const Vector2 &startingPosition) :
		GraphicString<Collidable>(newFont, newText, newAlignment, newDirection,
		                          startingPosition), Layerable() {
	}

	Text::Text(FontPointer newFont,
	           const String32 &newText,
	           TextAlignment newAlignment,
	           TextDirection newDirection,
	           const Vector2 &startingPosition) :
		GraphicString<Collidable>(newFont, newText, newAlignment, newDirection,
		                          startingPosition), Layerable() {
	}

	Text::Text(const Text &src) : GraphicString<Collidable>(src), Layerable(src) {
	}

	Text::~Text() {
	}

	Text &Text::operator=(const Text &src) {
		this->GraphicString<Collidable>::operator=(src);
		this->Layerable::operator=(src);
		return *this;
	}
}
