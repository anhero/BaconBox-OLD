/**
 * @file
 * @ingroup Display
 */
#ifndef RB_COLOR_H
#define RB_COLOR_H

#include <iostream>

namespace RedBox {
	/**
	 * Simple class that represents a color in an RGBA format. Each component
	 * ranges from 0 to 255.
	 * @ingroup Display
	 */
	class Color {
		friend std::ostream& operator<<(std::ostream& output, const Color& color);
	public:
		/// Number of components each color has.
		static const unsigned int NB_COMPONENTS = 4;
		/// Maximum value a component can have.
		static const unsigned int MAX_COMPONENT_VALUE = 255;
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
		Color(unsigned int red, unsigned int green,
			  unsigned int blue, unsigned int alpha);

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
		 * Gets the color's red component.
		 * @return Red component
		 */
		unsigned int getRed() const;

		/**
		 * Gets the color's green component.
		 * @return Green component
		 */
		unsigned int getGreen() const;

		/**
		 * Gets the color's blue component.
		 * @return Blue component
		 */
		unsigned int getBlue() const;

		/**
		 * Gets the color's alpha component.
		 * @return Alpha component
		 */
		unsigned int getAlpha() const;

		/**
		 * Sets the color's red component. Takes care of validating the value
		 * so that it isn't over 255. If it is over 255, it is set at 255.
		 * @param red New red component.
		 */
		void setRed(unsigned int red);

		/**
		 * Sets the color's green component. Takes care of validating the
		 * value so that it isn't over 255. If it is over 255, it is set at
		 * 255.
		 * @param green New green component.
		 */
		void setGreen(unsigned int green);

		/**
		 * Sets the color's blue component. Takes care of validating the value
		 * so that it isn't over 255. If it is over 255, it is set at 255.
		 * @param blue New blue component.
		 */
		void setBlue(unsigned int blue);

		/**
		 * Sets the color's alpha component. Takes care of validating the
		 * value so that it isn't over 255. If it is over 255, it is set at
		 * 255.
		 * @param alpha New alpha component.
		 */
		void setAlpha(unsigned int alpha);

		/**
		 * Sets the color's red, green and blue components. Simply calls
		 * setRed(), setGreen() and setBlue().
		 * @param red New red component.
		 * @param green New green component.
		 * @param blue New blue component.
		 */
		void setRGB(unsigned int red, unsigned int green, unsigned int blue);

		/**
		 * Sets the color's red, green and blue components. Simply calls
		 * setRed(), setGreen() and setBlue().
		 * @param red New red component.
		 * @param green New green component.
		 * @param blue New blue component.
		 * @param alpha New alpha component.
		 */
		void setRGBA(unsigned int red, unsigned int green, unsigned int blue,
					 unsigned int alpha);
	private:
		/// Color components.
		unsigned int colors[NB_COMPONENTS];
	};
}

#endif
