/**
 * @file
 * @ingroup Display
 */
#ifndef RB_COLOR_H
#define RB_COLOR_H

#include <stdint.h>

#include <iostream>

#include "Object.h"

namespace RedBox {
	/**
	 * Simple class that represents a color in an RGBA format. Each component
	 * ranges from 0 to 255.
	 * @ingroup Display
	 */
	class Color : public Object {
		friend std::ostream& operator<<(std::ostream& output, const Color& color);
	public:
		/// Number of components each color has.
		static const unsigned int NB_COMPONENTS = 4;
		/// Maximum value a component can have.
		static const unsigned int MAX_COMPONENT_VALUE = 0xff;
		/// Black color (0, 0, 0, 255).
		static const Color BLACK;
		/// White color (255, 255, 255, 255).
		static const Color WHITE;
		/// Red color (255, 0, 0, 255).
		static const Color RED;
		/// Green color (0, 255, 0, 255).
		static const Color GREEN;
		/// Blue color (0, 0, 255, 255).
		static const Color BLUE;
		/// Yellow color (255, 255, 0, 255).
		static const Color YELLOW;
		/// Pink color (255, 0, 255, 255).
		static const Color PINK;
		/// Teal color (0, 255, 255, 255).
		static const Color TEAL;

		/// Enumeration for the indexes of the color's array of components.
		enum Component {
			R = 0,
			G,
			B,
			A
		};

		/**
		 * Default constructor. Initializes the color to BLACK.
		 */
		Color();

		/**
		 * Parameterized constructor. Simply calls setRGBA() with the given
		 * components.
		 * @param red Red component.
		 * @param green Green component.
		 * @param blue Blue component.
		 * @param alpha Alpha component.
		 */
		Color(uint8_t red, uint8_t green, uint8_t blue,
			  uint8_t alpha = MAX_COMPONENT_VALUE);

		/**
		 * Parameterized constructor with one parameter.
		 * @param rgba Color in the format 0x00000000.
		 */
		Color(uint32_t rgba);

		/**
		 * Copy constructor. Simply calls setRGBA() with the given color's
		 * components.
		 * @param src Color to make a copy of.
		 */
		Color(const Color& src);

		/**
		 * Assignation operator overload.
		 * @param src Color to make a copy of.
		 */
		Color& operator=(const Color& src);

		/**
		 * Comparison operator overlaod.
		 * @param other Other color to compare to.
		 */
		bool operator==(const Color& other);

		/**
		 * Comparison operator overlaod.
		 * @param other Other color to compare to.
		 */
		bool operator!=(const Color& other);

		/**
		 * Operator to cast the color into one component.
		 */
		operator uint32_t() const;

		/**
		 * Gets the color's red component.
		 * @return Red component
		 */
		uint8_t getRed() const;

		/**
		 * Gets the color's green component.
		 * @return Green component
		 */
		uint8_t getGreen() const;

		/**
		 * Gets the color's blue component.
		 * @return Blue component
		 */
		uint8_t getBlue() const;

		/**
		 * Gets the color's alpha component.
		 * @return Alpha component
		 */
		uint8_t getAlpha() const;

		/**
		 * Sets the color's red component. Takes care of validating the value
		 * so that it isn't over 255. Only the first 2 bytes from the value
		 * given are used.
		 * @param red New red component.
		 */
		void setRed(uint8_t red);

		/**
		 * Sets the color's green component. Takes care of validating the
		 * value so that it isn't over 255. Only the first 2 bytes from the
		 * value given are used.
		 * @param green New green component.
		 */
		void setGreen(uint8_t green);

		/**
		 * Sets the color's blue component. Takes care of validating the value
		 * so that it isn't over 255. Only the first 2 bytes from the value
		 * given are used.
		 * @param blue New blue component.
		 */
		void setBlue(uint8_t blue);

		/**
		 * Sets the color's alpha component. Takes care of validating the
		 * value so that it isn't over 255. Only the first 2 bytes from the
		 * value given are used.
		 * @param alpha New alpha component.
		 */
		void setAlpha(uint8_t alpha);

		/**
		 * Sets the color's red, green and blue components. Simply calls
		 * setRed(), setGreen() and setBlue().
		 * @param red New red component.
		 * @param green New green component.
		 * @param blue New blue component.
		 */
		void setRGB(uint8_t red, uint8_t green, uint8_t blue);

		/**
		 * Set the first 3 components with one integer.
		 * @param rgb Color in the format 0x000000.
		 */
		void setRGB(uint32_t rgb);
		
		/**
		 * Sets the color's red, green and blue components. Simply calls
		 * setRed(), setGreen() and setBlue().
		 * @param red New red component.
		 * @param green New green component.
		 * @param blue New blue component.
		 * @param alpha New alpha component.
		 */
		void setRGBA(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);
		
		/**
		 * Set the 4 components with one integer.
		 * @param rgba Color in the format 0x00000000.
		 */
		void setRGBA(uint32_t rgba);

		/**
		 * Directly gets the color's array of components.
		 * @return Array containing the four components in the order RGBA.
		 */
		const uint8_t* getComponents() const;
	private:
		/// Color components.
		uint8_t colors[NB_COMPONENTS];
	};
}

#endif
