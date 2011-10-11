#include "Text.h"

namespace RedBox {
	Text::Text(const std::string &fontKey,
	           TextAlignment newAlignment,
	           TextDirection newDirection,
	           const Vector2 &startingPosition) :
		GraphicString<Collidable>(fontKey, newAlignment, newDirection,
		                          startingPosition), Layerable() {
	}

	Text::Text(Font *newFont,
	           TextAlignment newAlignment,
	           TextDirection newDirection,
	           const Vector2 &startingPosition) :
		GraphicString<Collidable>(newFont, newAlignment, newDirection,
		                          startingPosition), Layerable() {
	}

	Text::Text(const std::string &fontKey,
	           const std::string &newText,
	           TextAlignment newAlignment,
	           TextDirection newDirection,
	           const Vector2 &startingPosition) :
		GraphicString<Collidable>(fontKey, newText, newAlignment, newDirection,
		                          startingPosition), Layerable() {
	}

	Text::Text(Font *newFont,
	           const std::string &newText,
	           TextAlignment newAlignment,
	           TextDirection newDirection,
	           const Vector2 &startingPosition) :
		GraphicString<Collidable>(newFont, newText, newAlignment, newDirection,
		                          startingPosition), Layerable() {
	}

	Text::Text(const std::string &fontKey,
	           const String32 &newText,
	           TextAlignment newAlignment,
	           TextDirection newDirection,
	           const Vector2 &startingPosition) :
		GraphicString<Collidable>(fontKey, newText, newAlignment, newDirection,
		                          startingPosition), Layerable() {
	}

	Text::Text(Font *newFont,
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
