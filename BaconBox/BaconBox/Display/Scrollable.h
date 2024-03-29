/**
 * @file
 * @ingroup Display
 */
#ifndef RB_SCROLLABLE_H
#define RB_SCROLLABLE_H

#include "BaconBox/Vector2.h"

namespace BaconBox {
	/**
	 * A body that is ordered by a manager using its scrollFactor (parallax)
	 * will be derived from this class.
	 * @ingroup Display
	 */
	class Scrollable {
	public:
		/**
		 * Default constructor.
		 */
		Scrollable();

		/**
		 * Copy constructor.
		 * @param src Scrollable to make a copy of.
		 */
		Scrollable(const Scrollable &src);

		/**
		 * Destructor.
		 */
		virtual ~Scrollable();

		/**
		 * Assignment operator.
		 * @param src Scrollable to make a copy of.
		 * @return Reference to the modified Scrollable.
		 */
		Scrollable &operator=(const Scrollable &src);

		/**
		 * Gets the body's scroll factor.
		 * @return Horizontal and vertical scroll factor. A value higher than 1
		 * means the body will move faster as if it were closer to the camera,
		 * between 1 and 0 means it will move as if it were far from the camera.
		 * @see BaconBox::Scrollable::scrollFactor
		 */
		const Vector2 &getScrollFactor() const;

		/**
		 * Sets the body's scroll factor.
		 * @param newScrollFactor New horizontal and vertical scroll factor. A
		 * value higher than 1 means the body will move faster as if it were
		 * closer to the camera and between 1 and 0 means it will move as
		 * if it were far from the camera.
		 * @see BaconBox::Scrollable::scrollFactor
		 */
		void setScrollFactor(const Vector2 &newScrollFactor);

		/**
		 * Sets the body's scroll factor.
		 * @param newXScrollFactor New horizontal scroll factor. A value higher
		 * than 1 means the body will move faster as if it were closer to the
		 * camera and between 1 and 0 means it will move as if it were far from
		 * the camera.
		 * @param newYScrollFactor New vertical scroll factor. A value higher
		 * than 1 means the body will move faster as if it were closer to the
		 * camera and between 1 and 0 means it will move as if it were far from
		 * the camera.
		 * @see BaconBox::Scrollable::scrollFactor
		 */
		virtual void setScrollFactor(float newXScrollFactor,
		                             float newYScrollFactor);

		/**
		 * Gets the body's horizontal scroll factor.
		 * @return Horizontal scroll factor. A value higher than 1 means the
		 * body will move faster as if it were closer to the camera, between 1
		 * and 0 means it will move as if it were far from the camera.
		 * @see BaconBox::Scrollable::scrollFactor
		 */
		float getXScrollFactor() const;

		/**
		 * Sets the body's horizontal scroll factor.
		 * @param newXScrollFactor New horizontal scroll factor. A value higher
		 * than 1 means the body will move faster as if it were closer to the
		 * camera and between 1 and 0 means it will move as if it were far from
		 * the camera.
		 * @see BaconBox::Scrollable::scrollFactor
		 */
		void setXScrollFactor(float newXScrollFactor);

		/**
		 * Gets the body's vertical scroll factor.
		 * @return Vertical scroll factor. A value higher than 1 means the
		 * body will move faster as if it were closer to the camera, between 1
		 * and 0 means it will move as if it were far from the camera.
		 * @see BaconBox::Scrollable::scrollFactor
		 */
		float getYScrollFactor() const;

		/**
		 * Sets the body's vertical scroll factor.
		 * @param newYScrollFactor New vertical scroll factor. A value higher
		 * than 1 means the body will move faster as if it were closer to the
		 * camera and between 1 and 0 means it will move as if it were far from
		 * the camera.
		 * @see BaconBox::Scrollable::scrollFactor
		 */
		void setYScrollFactor(float newYScrollFactor);

		/**
		 * Checks whether the scrollable body is a hud element or not.
		 * @return True if the body is a hud element, false if not.
		 * @see BaconBox::Scrollable::hud
		 */
		bool isHud() const;

		/**
		 * Sets whether the scrollable body is a hud element or not.
		 * @param newHud True to make the body a hud element, false to make it a
		 * normal body.
		 * @see BaconBox::Scrollable::hud
		 */
		virtual void setHud(bool newHud);
	private:
		/**
		 * Scroll factor. Factor applied to the bodies' coordinates to have
		 * parallax scrolling. Lower values means "farther" from the camera. An
		 * horizontal scroll factor of 0 would mean the body would not move
		 * horizontally whatever the camera does. A value higher than 1 means
		 * the body will move faster as if it were closer to the camera and
		 * between 1 and 0 means it will move as if it were far from the camera.
		 * By default, all bodies have a scroll factor of 1 both horizontally
		 * and vertically.
		 */
		Vector2 scrollFactor;

		/**
		 * Set to true if the scrollable item is a hud element. The scroll
		 * factor will be ignored and a hud element is not affected by the
		 * camera's position, rotation or scaling.
		 */
		bool hud;
	};

}

#endif
