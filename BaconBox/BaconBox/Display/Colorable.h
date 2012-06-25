/**
 * @file
 * @ingroup Display
 */
#ifndef RB_Colorable_H
#define RB_Colorable_H

#include "Color.h"

namespace BaconBox {
	/**
	 * All bodies that can be Colorable are derived from this class.
	 * @ingroup Display
	 */
	class Colorable {
	public:
		/**
		 * Default and parameterized constructor. Initializes the Colorable with
		 * a specific color.
		 */
		explicit Colorable(const Color &newColor = Color::WHITE);

		/**
		 * Copy constructor.
		 * @param src Colorable to make a copy of.
		 */
		Colorable(const Colorable &src);

		/**
		 * Destructor.
		 */
		virtual ~Colorable();

		/**
		 * Assignment operator.
		 * @param src Colorable to make a copy of.
		 * @return Reference to the modified Colorable.
		 */
		Colorable &operator=(const Colorable &src);

		/**
		 * Gets the body's color.
		 * @return Current color.
		 * @see BaconBox::Colorable::color
		 */
		const Color &getColor() const;

		/**
		 * Sets the body's color.
		 * @param newColor New color.
		 * @see BaconBox::Colorable::color
		 */
		virtual void setColor(const Color &newColor);

		/**
		 * Gets the body's alpha value.
		 * @return New alpha value.
		 * @see BaconBox::Colorable::color
		 */
		uint8_t getAlpha() const;

		/**
		 * Sets the body's alpha value.
		 * @param newAlpha New alpha value (clamped between 0 and 255).
		 * @see BaconBox::Colorable::color
		 */
		void setAlpha(int32_t newAlpha);
	private:
		/// Body's color (white by default).
		Color color;
	};

}

#endif
