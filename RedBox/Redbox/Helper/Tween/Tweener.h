/**
 * @file
 * @ingroup Helper
 */
#ifndef RB_TWEENER_H
#define RB_TWEENER_H

#include "Ease.h"

namespace RedBox {
	/**
	 * Base class for all tweeners of tweenable types.
	 * @see RedBox::Tween
	 * @see template <typename T> RedBox::TTweener<T>
	 * @ingroup Helper
	 */
	class Tweener {
		friend class Tween;
	protected:
		/**
		 * Parameterized constructor.
		 * @param newTime Time the tweening must take.
		 * @param newEase Type of ease to apply to the tweening.
		 * @see RedBox::Tweener::time
		 * @see RedBox::Tweener::ease
		 */
		Tweener(double newTime, Ease newEase);
	private:
		/**
		 * Time counter used to count how much time is left until the end of
		 * the tweening.
		 */
		double timer;

		/// Time the tweening must take to arrive at its final value.
		double time;

		/// Type of ease to apply to the tweening.
		Ease ease;

		/**
		 * Updates the tweened value and removes itself from the Tween manager
		 * when done.
		 */
		void update();

		/**
		 * Sets the tweening's value using a ratio.
		 * @param p Ratio from 0.0f to 1.0f used to know the point at which the
		 * tweening is between the starting value and the ending value.
		 */
		virtual void setValue(float p) = 0;
	};
}

#endif
