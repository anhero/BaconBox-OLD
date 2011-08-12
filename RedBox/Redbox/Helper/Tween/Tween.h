/**
 * @file
 * @ingroup Helper
 */
#ifndef RB_TWEEN_H
#define RB_TWEEN_H

#include <cassert>

#include <list>

#include "Tweener.h"

namespace RedBox {
	/**
	 * Templated tweener for any tweenable types (like integers, 2d vectors,
	 * floats, etc.)
	 * @ingroup Helper
	 */
	template <typename T>
	class TTweener : public Tweener {
		friend class Tween;
	private:
		/// Reference to the tweened value.
		T& value;

		/// Starting value.
		T start;

		/// Ending value.
		T end;

		/**
		 * Parameterized constructor.
		 * @param newValue Reference to the value to be tweened.
		 * @param newEnd Ending value to use.
		 * @param newTime Time the tweening needs to take.
		 * @param newEase Ease to apply to the tweening.
		 */
		TTweener(T& newValue, const T& newEnd, double newTime, Ease newEase);

		/**
		 * Sets the value using the given floating point number.
		 * @param p Value from 0.0f to 1.0f that is used to indicate at which
		 * point between the start and the end the value is.
		 */
		void setValue(float p);
	};

	/**
	 * Used to tween values.
	 * @ingroup Helper
	 */
	class Tween {
		friend class Tweener;
		friend class Engine;
	public:
		/**
		 * Eases a value using a specific type of easing.
		 * @param t Value to ease.
		 * @param easeType Type of easing to apply.
		 * @param b Value to add to the easing.
		 * @param c Force to apply on the easing.
		 * @param d Force to apply on the easing.
		 */
		static float ease(float t, Ease easeType, float b = 0.0f,
		                  float c = 1.0f, float d = 1.0f);

		/**
		 * Tweens a value to a specific end value.
		 * @param value Reference to the value to tween.
		 * @param end Value to tween to.
		 * @param time Time the tweening must take to get to the ending value.
		 * @param ease Type of easing to apply on the tweening.
		 */
		template <typename T>
		static void to(T& value, const T& end, double time, Ease ease) {
			getInstance().tweeners.push_back(new TTweener<T>(value, end, time,
			                                 ease));
		}

		/**
		 * Tweens a value from a starting value to an ending value.
		 * @param value Reference to the value to tween.
		 * @param start Value at which to tween from.
		 * @param end Value to tween to.
		 * @param time Time the tweening must take to tget to the ending value.
		 * @param ease Type of easing to apply on the tweening.
		 */
		template <typename T>
		static void fromTo(T& value, const T& start, const T& end, double time, Ease ease) {
			value = start;
			getInstance().tweeners.push_back(new TTweener<T>(value, end, time,
			                                 ease));
		}
	private:
		/// List of active tweeners that need updating.
		std::list<Tweener*> tweeners;

		/// List of tweeners that are done and need to be removed.
		std::list<Tweener*> tweenersToRemove;

		/**
		 * Gets the singleton instance.
		 * @return Reference to the singleton.
		 */
		static Tween& getInstance();

		/**
		 * Default constructor.
		 */
		Tween();

		/**
		 * Destructor. Deletes all the tweeners.
		 */
		~Tween();

		/**
		 * Updates all the tweeners and removes the tweeners that are done.
		 */
		void update();

		/**
		 * Removes a tweeners from the list of tweeners that need updating.
		 * This method is called by the tweeners when they are done.
		 * @see RedBox::Tweener::update()
		 */
		void remove(Tweener* tweener);
	};

	template <typename T>
	TTweener<T>::TTweener(T& newValue, const T& newEnd, double newTime, Ease newEase) :
		Tweener(newTime, newEase), value(newValue), start(newValue), end(newEnd) {
	}

	template <typename T>
	void TTweener<T>::setValue(float p) {
		value = (end - start) * p + start;
	}
}

#endif
