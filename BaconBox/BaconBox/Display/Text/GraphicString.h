/**
 * @file
 * @ingroup TextDisplay
 */
#ifndef RB_GRAPHIC_STRING_H
#define RB_GRAPHIC_STRING_H

#include <cassert>

#include <list>
#include <utility>

#include "BaconBox/Display/Text/Font.h"
#include "BaconBox/Display/Text/GlyphInformation.h"
#include "BaconBox/Helper/UTFConvert.h"
#include "BaconBox/Display/Maskable.h"
#include "BaconBox/Display/Text/TextDirection.h"
#include "BaconBox/Display/Text/TextAlignment.h"
#include "BaconBox/Display/Colorable.h"
#include "BaconBox/Display/InanimateGraphicElement.h"
#include "BaconBox/Display/RBString32.h"
#include "BaconBox/Display/StandardVertexArray.h"
#include "BaconBox/Helper/StaticAssert.h"
#include "BaconBox/Helper/IsBaseOf.h"
#include "BaconBox/Display/Transformable.h"
#include "BaconBox/Display/Text/FontPointer.h"
#include "BaconBox/Console.h"

namespace BaconBox {
	/**
	 * A GraphicString is a body object used to display text.
	 * @tparam T Either Transformable or Collidable.
	 * @ingroup TextDisplay
	 */
	template <typename T>
	class GraphicString : virtual public Maskable, public T,
		public Colorable {
	public:
		/**
		 * Parameterized constructor. Initializes the graphic string with a
		 * font, an alignment, a direction and a starting position.
		 * @param newFont Font pointer to use as the text's font.
		 * @param newAlignment Graphic string's text alignment.
		 * @param newDirection Graphic string's text direction.
		 * @param startingPosition Starting position (upper left corner).
		 * @see BaconBox::GraphicString::font
		 * @see BaconBox::GraphicString::alignment
		 * @see BaconBox::GraphicString::direction
		 */
		explicit GraphicString(FontPointer newFont,
		                       TextAlignment newAlignment = TextAlignment::LEFT,
		                       TextDirection newDirection = TextDirection::LEFT_TO_RIGHT,
		                       const Vector2 &startingPosition = Vector2()) :
			Maskable(), T(startingPosition), Colorable(Color::BLACK),
			font(newFont.pointer), text(),
			alignment(newAlignment), direction(newDirection), characters(),
			vertices(4, startingPosition), currentMask(NULL) {
			initialize();
		}

		/**
		 * Parameterized constructor. Initializes the graphic string with a
		 * font, a text, an alignment, a direction and a starting position.
		 * @param newFont Font pointer to use as the text's font.
		 * @param newText UTF8 string to use as the string's text.
		 * @param newAlignment Graphic string's text alignment.
		 * @param newDirection Graphic string's text direction.
		 * @param startingPosition Starting position (upper left corner).
		 * @see BaconBox::GraphicString::font
		 * @see BaconBox::GraphicString::text
		 * @see BaconBox::GraphicString::alignment
		 * @see BaconBox::GraphicString::direction
		 */
		GraphicString(FontPointer newFont,
		              const std::string &newText,
		              TextAlignment newAlignment = TextAlignment::LEFT,
		              TextDirection newDirection = TextDirection::LEFT_TO_RIGHT,
		              const Vector2 &startingPosition = Vector2()) :
			Maskable(), T(startingPosition), Colorable(Color::BLACK),
			font(newFont.pointer), text(UTFConvert::decodeUTF8(newText)),
			alignment(newAlignment), direction(newDirection), characters(),
			vertices(4, startingPosition), currentMask(NULL) {
			initialize();
		}

		/**
		 * Parameterized constructor. Initializes the graphic string with a
		 * font, a text, an alignment, a direction and a starting position.
		 * @param newFont Font pointer to use as the text's font.
		 * @param newText Unicode string to use as the string's text.
		 * @param newAlignment Graphic string's text alignment.
		 * @param newDirection Graphic string's text direction.
		 * @param startingPosition Starting position (upper left corner).
		 * @see BaconBox::GraphicString::font
		 * @see BaconBox::GraphicString::text
		 * @see BaconBox::GraphicString::alignment
		 * @see BaconBox::GraphicString::direction
		 */
		GraphicString(FontPointer newFont,
		              const String32 &newText,
		              TextAlignment newAlignment = TextAlignment::LEFT,
		              TextDirection newDirection = TextDirection::LEFT_TO_RIGHT,
		              const Vector2 &startingPosition = Vector2()) :
			Maskable(), T(startingPosition), Colorable(Color::BLACK),
			font(newFont.pointer), text(newText),
			alignment(newAlignment), direction(newDirection), characters(),
			vertices(4, startingPosition), currentMask(NULL) {
			initialize();
		}

		/**
		 * Copy constructor.
		 * @param src GraphicString to make a copy of.
		 */
		GraphicString(const GraphicString<T> &src) : Maskable(src),
			T(src), Colorable(src), font(src.font), text(src.text),
			alignment(src.alignment), direction(src.direction),
			characters(src.characters), vertices(src.vertices),
			currentMask(src.currentMask) {
		}

		/**
		 * Destructor.
		 */
		virtual ~GraphicString() {
			clearCharacters();
		}

		/**
		 * Assignment operator overloading.
		 * @param src GraphicString to make a copy of.
		 * @return Reference to the modified GraphicString.
		 */
		GraphicString &operator=(const GraphicString &src) {
			this->T::operator=(src);
			this->Colorable::operator=(src);

			if (this != &src) {
				font = src.font;
				text = src.text;
				alignment = src.alignment;
				direction = src.direction;
				clearCharacters();
				characters.clear();

				for (GlyphList::const_iterator i = src.characters.begin();
				     i != src.characters.end(); ++i) {
					characters.push_back(std::make_pair(i->first, ((i->second) ? (new InanimateGraphicElement<Transformable>(*i->second)) : (i->second))));
				}

				vertices = src.vertices;
			}

			return *this;
		}

		/**
		 * Renders the body in the context.
		 */
		virtual void render() {
			for (GlyphList::const_iterator i = characters.begin();
			     i != characters.end(); ++i) {
				if (i->second) {
					i->second->render();
				}
			}
		}

		/**
		 * Similar to the render function except that it will only
		 * render to the alpha component of the color buffer. It is used to mask
		 * the next rendered renderable body (if the next renderable body is set
		 * as a masked renderable body).
		 */
		virtual void mask() {
			for (GlyphList::const_iterator i = characters.begin();
			     i != characters.end(); ++i) {
				if (i->second) {
					i->second->mask();
				}
			}
		}

		/**
		 * Undo what the mask function did. This function must be once after the
		 * masked renderable body has been rendered.
		 */
		virtual void unmask() {
			for (GlyphList::const_iterator i = characters.begin();
			     i != characters.end(); ++i) {
				if (i->second) {
					i->second->unmask();
				}
			}
		}

		/**
		 * Gets the renderable body masking the current renderable body.
		 * @return Pointer to the renderable body's mask.
		 */
		virtual Maskable *getMask() const {
			return currentMask;
		}

		/**
		 * Sets the renderable body used to mask the parent renderstep.
		 * @param newMask A mask sprite.
		 * @param inverted Sets this parameter to true if you want to invert
		 * the effect of the mask. False by default.
		 */
		virtual void setMask(Maskable *newMask, bool inverted = false) {
			currentMask = newMask;

			for (GlyphList::const_iterator i = characters.begin();
			     i != characters.end(); ++i) {
				if (i->second) {
					i->second->setMask(newMask, inverted);
				}
			}
		}

		using Collidable::move;

		/**
		 * Moves the Positionable horizontally and vertically.
		 * @param xDelta Value to add to the Positionable's horizontal position
		 * (in pixels). Positive value moves the Positionable to the right and a
		 * negative value moves the Positionable to the left.
		 * @param yDelta Value to add to the Positionable's vertical position (in
		 * pixels). Positive value moves the Positionable down and a negative
		 * value moves the Positionable up.
		 * @see BaconBox::Positionable::move(const Vector2& delta);
		 * @see BaconBox::Positionable::position
		 */
		virtual void move(float xDelta, float yDelta) {
			this->Collidable::move(xDelta, yDelta);

			for (GlyphList::const_iterator i = characters.begin();
			     i != characters.end(); ++i) {
				if (i->second) {
					i->second->move(xDelta, yDelta);
				}
			}

			vertices.move(xDelta, yDelta);
		}

		/**
		 * Gets the body's size. Can be overloaded for performance.
		 * @return Vector2 containing the width and height of the body.
		 */
		virtual const Vector2 getSize() const {
			return vertices.getSize();
		}

		/**
		 * Gets the body's width.
		 * @return Width in pixels (by default).
		 */
		virtual float getWidth() const {
			return vertices.getWidth();
		}

		/**
		 * Gets the body's height.
		 * @return Height in pixels (by default).
		 */
		virtual float getHeight() const {
			return vertices.getHeight();
		}

		using Collidable::scaleFromPoint;

		/**
		 * Scales the body from a specific point.
		 * @param xScaling Horizontal scaling to apply. For example, if
		 * 2.0f is passed, the body will be twice as wide.
		 * @param yScaling Vertical scaling to apply. For example, if 2.0f is
		 * passed, the body will be twice as high.
		 * @param fromPoint Anchor point from which to apply the scaling.
		 * @see BaconBox::Transformable::scaling
		 */
		virtual void scaleFromPoint(float xScaling, float yScaling,
		                            const Vector2 &fromPoint) {
			this->Collidable::scaleFromPoint(xScaling, yScaling, fromPoint);

			for (GlyphList::const_iterator i = characters.begin();
			     i != characters.end(); ++i) {
				if (i->second) {
					i->second->scaleFromPoint(xScaling, yScaling, fromPoint);
				}
			}

			vertices.scaleFromPoint(xScaling, yScaling, fromPoint);
			refreshPosition();
		}

		/**
		 * Rotates the graphic body from a point.
		 * @param rotationAngle Angle to rotate the graphic body.
		 * @param rotationPoint Origin point on which to apply the rotation.
		 * @see BaconBox::Transformable::angle
		 */
		virtual void rotateFromPoint(float rotationAngle,
		                             const Vector2 &rotationPoint) {
			this->Collidable::rotateFromPoint(rotationAngle, rotationPoint);

			for (GlyphList::const_iterator i = characters.begin();
			     i != characters.end(); ++i) {
				if (i->second) {
					i->second->rotateFromPoint(rotationAngle, rotationPoint);
				}
			}

			vertices.rotateFromPoint(rotationAngle, rotationPoint);
			refreshPosition();
		}

		/**
		 * Sets the body's color.
		 * @param newColor New color.
		 * @see BaconBox::Colorable::color
		 */
		virtual void setColor(const Color &newColor) {
			this->Colorable::setColor(newColor);

			for (GlyphList::const_iterator i = characters.begin();
			     i != characters.end(); ++i) {
				if (i->second) {
					i->second->setColor(newColor);
				}
			}
		}

		/**
		 * Gets the graphic string's font.
		 * @return Pointer to the graphic string's font.
		 * @see BaconBox::GraphicString::font
		 */
		Font *getFont() const {
			return font;
		}

		/**
		 * Sets the graphic string's font and refreshes the text to use the
		 * given font. Does nothing and keeps the old font if the new font is
		 * NULL.
		 * @param newFont Pointer to the new font to use.
		 */
		void setFont(FontPointer newFont) {
			// We make sure the new font is valid.
			if (newFont.pointer) {
				font = newFont.pointer;
			}
		}

		/**
		 * Gets the graphic string's text in UTF8.
		 * @return A copy of the graphic string's UTF32 string in UTF8 format.
		 * @see BaconBox::GraphicString::text
		 */
		std::string getText() const {
			return UTFConvert::encodeToUTF8(text);
		}

		/**
		 * Sets the graphic string's text.
		 * @param newText UTF8 string to use as the graphic string's text.
		 * Converts it to UTF32 to store it.
		 * @see BaconBox::GraphicString::text
		 */
		void setText(const std::string newText) {
			setUtf32Text(UTFConvert::decodeUTF8(newText));
		}

		/**
		 * Gets the graphic string's text in UTF32.
		 * @return String used by the graphic string as the text.
		 * @see BaconBox::GraphicString::text
		 */
		const String32 &getUtf32Text() const {
			return text;
		}

		/**
		 * Sets the graphic string's text.
		 * @param newText UTF32 string to use as the graphic string's text.
		 * @see BaconBox::GraphicString::text
		 */
		void setUtf32Text(const String32 &newText) {
			if (text != newText) {
				text = newText;
				buildString();
			}
		}

		/**
		 * Gets the graphic string's text alignment.
		 * @return Current text alignment
		 * @see BaconBox::GraphicString::alignment
		 */
		TextAlignment getAlignment() const {
			return alignment;
		}


		/**
		 * Sets the graphic string's text alignment. Doesn't change the already
		 * displayed text, will be used the next time the text is changed.
		 * @param newAlignment New text alignment to use.
		 * @see BaconBox::GraphicString::alignment
		 */
		void setAlignment(TextAlignment newAlignment) {
			alignment = newAlignment;
		}

		/**
		 * Gets the graphic string's text direction.
		 * @return Current text direction.
		 * @see BaconBox::GraphicString::direction
		 */
		TextDirection getDirection() const {
			return direction;
		}

		/**
		 * Sets the graphic string's text direction. Refreshes the already
		 * displayed text.
		 * @param newDirection New text direction to use.
		 * @see BaconBox::GraphicString::direction
		 */
		void setDirection(TextDirection newDirection) {
			if (direction != newDirection) {
				direction = newDirection;
				buildString();
			}
		}
	private:
		/// Makes sure the body type is derived from the Manageable class.
		typedef typename StaticAssert<IsBaseOf<Positionable, T>::RESULT>::Result IsAtLeastTransformable;

		/// Type used to represent the list of displayed glyphs.
		typedef std::list<std::pair<const GlyphInformation *, InanimateGraphicElement<Transformable> *> > GlyphList;

		/// Rendering font.
		Font *font;

		/// Unicode values of the GraphicString
		String32 text;

		/// Alignment of the string (Left, right, center)
		TextAlignment alignment;

		/**
		 * Rendering direction of the string (Left to right, right to left, up
		 * to down)
		 */
		TextDirection direction;

		/// List of sprite representing each glyph.
		GlyphList characters;

		/// Vertices representing the graphic string's rectangle.
		StandardVertexArray vertices;

		/// Pointer to the current mask.
		Maskable *currentMask;

		/**
		 * Initializes the graphic string.
		 */
		void initialize() {
			Vector2 tmp(this->getPosition());
			buildString();
			this->move(tmp - this->getPosition());
		}

		/**
		 * Builds the graphic string's list of glyphs.
		 * @see BaconBox::GraphicString::characters;
		 */
		void buildString() {
			Vector2 alignmentPosition;
			assert(vertices.getNbVertices() == 4);

			if (alignment == TextAlignment::LEFT) {
				StandardVertexArray::ConstIterator i = vertices.getBegin();
				Vector2 tmp = *i;
				i += 2;
				alignmentPosition = tmp + (*i - tmp) * 0.5f;

			} else if (alignment == TextAlignment::RIGHT) {
				StandardVertexArray::ConstIterator i = vertices.getBegin();
				++i;
				Vector2 tmp = *i;
				i += 2;
				alignmentPosition = tmp + (*i - tmp) * 0.5f;

			} else {
				alignmentPosition = vertices.getCentroid();
			}

			clearCharacters();
			characters.clear();

			// We make sure the font is valid.
			if (font) {
				// We check the text direction.
				if (direction == TextDirection::LEFT_TO_RIGHT) {
					// We generate the list of glyphs (one for each of the text's
					// characters).
					const GlyphInformation *newGlyph;
					InanimateGraphicElement<Transformable> *newGraphic;

					for (String32::const_iterator i = text.begin();
					     i != text.end(); ++i) {
						newGlyph = font->getGlyphInformation(*i);

						if (newGlyph->size.x > 0.0f) {
							newGraphic = new InanimateGraphicElement<Transformable>(newGlyph->textureInformation, Vector2(0.0f, 0.0f), newGlyph->size, Vector2(1.0f, 1.0f));
							newGraphic->setScaling(this->getScaling());
							newGraphic->setColor(getColor());

						} else {
							newGraphic = NULL;
						}

						characters.push_back(std::make_pair(newGlyph, newGraphic));
					}

				} else if (direction == TextDirection::RIGHT_TO_LEFT) {
					const GlyphInformation *newGlyph;
					InanimateGraphicElement<Transformable> *newGraphic;

					for (String32::const_reverse_iterator i = text.rbegin();
					     i != text.rend(); ++i) {
						newGlyph = font->getGlyphInformation(*i);

						if (newGlyph->size.x > 0.0f) {
							newGraphic = new InanimateGraphicElement<Transformable>(newGlyph->textureInformation, Vector2(0.0f, 0.0f), newGlyph->size, Vector2(1.0f, 1.0f));
							newGraphic->setScaling(this->getScaling());
							newGraphic->setColor(getColor());

						} else {
							newGraphic = NULL;
						}

						characters.push_back(std::make_pair(newGlyph, newGraphic));
					}
				}

				float lineHeight = static_cast<float>(font->getLineHeight());

				bool started = false;
				float tmpX = 0, xMin = 0, xMax = 0, yMin = 0, yMax = 0;
				Vector2 tmpMax;

				for (GlyphList::iterator i = characters.begin();
				     i != characters.end(); ++i) {
					// We have to check for NULL pointers because spaces
					// do not have graphics.
					if (i->second) {
						i->second->setPosition(tmpX + i->first->horizontalBearing.x * this->getXScaling(),
						                       (lineHeight + (i->first->size.y - i->first->horizontalBearing.y) - i->first->size.y * this->getYScaling()));

						tmpMax = i->second->getVertices().getMaximumXY();

						if (started) {
							if (i->second->getXPosition() < xMin) {
								xMin = i->second->getXPosition();
							}

							if (tmpMax.x > xMax) {
								xMax = tmpMax.x;
							}

							if (i->second->getYPosition() < yMin) {
								yMin = i->second->getYPosition();
							}

							if (tmpMax.y > yMax) {
								yMax = tmpMax.y;
							}

						} else {
							started = true;
							tmpMax = i->second->getVertices().getMaximumXY();
							xMin = i->second->getXPosition();
							xMax = tmpMax.x;
							yMin = i->second->getYPosition();
							yMax = tmpMax.y;
						}
					}

					tmpX += i->first->advance.x * this->getXScaling();
				}

				if (!started) {
					xMin = xMax = this->getXPosition();
					yMin = yMax = this->getYPosition();
				}

				// We set the vertices.
				StandardVertexArray::Iterator it = vertices.getBegin();
				it->x = xMin;
				it->y = yMin;
				++it;
				it->x = xMax;
				it->y = yMin;
				++it;
				it->x = xMin;
				it->y = yMax;
				++it;
				it->x = xMax;
				it->y = yMax;

				// We check the text alignment.

				Vector2 delta;

				if (alignment == TextAlignment::LEFT) {
					// We find the delta we have to apply to align the text
					// with the alignment position.
					it = vertices.getBegin();
					delta = *it;
					it += 2;
					delta = alignmentPosition - (delta + (*it - delta) * 0.5f);

				} else if (alignment == TextAlignment::RIGHT) {
					// We find the delta we have to apply to align the text
					// with the alignment position.
					it = vertices.getBegin();
					++it;
					delta = *it;
					it += 2;
					delta = alignmentPosition - (delta + (*it - delta) * 0.5f);

				} else if (alignment == TextAlignment::CENTER) {
					delta = alignmentPosition - vertices.getCentroid();
				}

				// We apply this delta and the rotation to the vertices and
				// the graphics.
				vertices.move(delta.x, delta.y);
				vertices.rotateFromPoint(this->getAngle(), alignmentPosition);

				for (GlyphList::iterator i = characters.begin();
				     i != characters.end(); ++i) {
					if (i->second) {
						i->second->move(delta);
						i->second->rotateFromPoint(this->getAngle(), alignmentPosition);
					}
				}

				// We update the collidable's stored position.
				refreshPosition();

			}
		}

		/**
		 * Refreshes the collidable's position using the graphic string's.
		 * vertices.
		 */
		void refreshPosition() {
			Vector2 delta = vertices.getMinimumXY() - this->getPosition();
			this->Collidable::move(delta.x, delta.y);
		}

		/**
		 * Clears the characters attribute.
		 * @see BaconBox::GraphicString::characters
		 */
		void clearCharacters() {
			for (GlyphList::iterator i = characters.begin();
			     i != characters.end(); ++i) {
				if (i->second) {
					delete i->second;
				}
			}
		}
	};
}

#endif // RB_GRAPHIC_STRING_H
