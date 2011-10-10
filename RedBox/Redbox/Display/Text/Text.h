/**
 * @file
 * @ingroup TextDisplay
 */
#ifndef RB_TEXT_H
#define RB_TEXT_H

#include "Collidable.h"
#include "GraphicString.h"
#include "Layerable.h"

namespace RedBox {
	/**
	 * Represents a graphic string that can be added to a state.
	 * @ingroup TextDisplay
	 */
	class Text : public GraphicString<Collidable>, public Layerable {
	public:
		/**
		 * Parameterized constructor. Initializes the graphic string with a
		 * font, an alignment, a direction and a starting position.
		 * @param fontKey Key for the font to use in the ResourceManager.
		 * @param newAlignment Graphic string's text alignment.
		 * @param newDirection Graphic string's text direction.
		 * @param startingPosition Starting position (upper left corner).
		 * @see RedBox::ResourceManager
		 * @see RedBox::GraphicString::font
		 * @see RedBox::GraphicString::alignment
		 * @see RedBox::GraphicString::direction
		 */
		explicit Text(const std::string &fontKey,
		              TextAlignment newAlignment = TextAlignment::LEFT,
		              TextDirection newDirection = TextDirection::LEFT_TO_RIGHT,
		              const Vector2 &startingPosition = Vector2());

		/**
		 * Parameterized constructor. Initializes the graphic string with a
		 * font, a text, an alignment, a direction and a starting position.
		 * @param newFont Pointer to the font to use to display the string.
		 * @param newAlignment Graphic string's text alignment.
		 * @param newDirection Graphic string's text direction.
		 * @param startingPosition Starting position (upper left corner).
		 * @see RedBox::GraphicString::font
		 * @see RedBox::GraphicString::alignment
		 * @see RedBox::GraphicString::direction
		 */
		explicit Text(Font *newFont,
		              TextAlignment newAlignment = TextAlignment::LEFT,
		              TextDirection newDirection = TextDirection::LEFT_TO_RIGHT,
		              const Vector2 &startingPosition = Vector2());

		/**
		 * Parameterized constructor. Initializes the graphic string with a
		 * font, a text, an alignment, a direction and a starting position.
		 * @param fontKey Key for the font to use in the ResourceManager.
		 * @param newText UTF8 string to use as the string's text.
		 * @param newAlignment Graphic string's text alignment.
		 * @param newDirection Graphic string's text direction.
		 * @param startingPosition Starting position (upper left corner).
		 * @see RedBox::ResourceManager
		 * @see RedBox::GraphicString::font
		 * @see RedBox::GraphicString::text
		 * @see RedBox::GraphicString::alignment
		 * @see RedBox::GraphicString::direction
		 */
		Text(const std::string &fontKey,
		     const std::string &newText,
		     TextAlignment newAlignment = TextAlignment::LEFT,
		     TextDirection newDirection = TextDirection::LEFT_TO_RIGHT,
		     const Vector2 &startingPosition = Vector2());

		/**
		 * Parameterized constructor. Initializes the graphic string with a
		 * font, a text, an alignment, a direction and a starting position.
		 * @param newFont Pointer to the font to use to display the string.
		 * @param newText UTF8 string to use as the string's text.
		 * @param newAlignment Graphic string's text alignment.
		 * @param newDirection Graphic string's text direction.
		 * @param startingPosition Starting position (upper left corner).
		 * @see RedBox::GraphicString::font
		 * @see RedBox::GraphicString::text
		 * @see RedBox::GraphicString::alignment
		 * @see RedBox::GraphicString::direction
		 */
		Text(Font *newFont,
		     const std::string &newText,
		     TextAlignment newAlignment = TextAlignment::LEFT,
		     TextDirection newDirection = TextDirection::LEFT_TO_RIGHT,
		     const Vector2 &startingPosition = Vector2());

		/**
		 * Parameterized constructor. Initializes the graphic string with a
		 * font, a text, an alignment, a direction and a starting position.
		 * @param fontKey Key for the font to use in the ResourceManager.
		 * @param newText Unicode string to use as the string's text.
		 * @param newAlignment Graphic string's text alignment.
		 * @param newDirection Graphic string's text direction.
		 * @param startingPosition Starting position (upper left corner).
		 * @see RedBox::ResourceManager
		 * @see RedBox::GraphicString::font
		 * @see RedBox::GraphicString::text
		 * @see RedBox::GraphicString::alignment
		 * @see RedBox::GraphicString::direction
		 */
		Text(const std::string &fontKey,
		     const String32 &newText,
		     TextAlignment newAlignment = TextAlignment::LEFT,
		     TextDirection newDirection = TextDirection::LEFT_TO_RIGHT,
		     const Vector2 &startingPosition = Vector2());

		/**
		 * Parameterized constructor. Initializes the graphic string with a
		 * font, a text, an alignment, a direction and a starting position.
		 * @param newFont Pointer to the font to use to display the string.
		 * @param newText Unicode string to use as the string's text.
		 * @param newAlignment Graphic string's text alignment.
		 * @param newDirection Graphic string's text direction.
		 * @param startingPosition Starting position (upper left corner).
		 * @see RedBox::GraphicString::font
		 * @see RedBox::GraphicString::text
		 * @see RedBox::GraphicString::alignment
		 * @see RedBox::GraphicString::direction
		 */
		Text(Font *newFont,
		     const String32 &newText,
		     TextAlignment newAlignment = TextAlignment::LEFT,
		     TextDirection newDirection = TextDirection::LEFT_TO_RIGHT,
		     const Vector2 &startingPosition = Vector2());

		/**
		 * Copy constructor.
		 * @param src Text to make a copy of.
		 */
		Text(const Text &src);

		/**
		 * Destructor.
		 */
		virtual ~Text();

		/**
		 * Assignment operator.
		 * @param src Text to make a copy of.
		 * @return Reference to the modified Text.
		 */
		Text &operator=(const Text &src);
	};

}

#endif // RB_TEXT_H
