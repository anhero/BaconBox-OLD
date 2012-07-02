/**
 * @file
 * @ingroup Helper
 */
#ifndef RB_TWEEN_H
#define RB_TWEEN_H

#include "BaconBox/Helper/Stopwatch.h"
#include "BaconBox/Helper/Ease.h"
#include "BaconBox/Helper/MathHelper.h"

namespace BaconBox {
	/**
	 * Templated motion tween for any tweenable types (like integers, 2d
	 * vectors, floats, etc.). Can be used as a stopwatch to start it, pause it,
	 * stop it, etc.
	 * @ingroup Helper
	 * @tparam T Type of the value to be tweened.
	 */
	template <typename T>
	class Tween : public Stopwatch {
	public:
		/**
		 * Default constructor. Initializes a tween that will always return the
		 * type's default constructor's value as its tweened value.
		 */
		Tween() : Stopwatch(), startValue(), endValue(), duration(0.0),
			ease(Ease::LINEAR) {
		}

		/**
		 * Parameterized constructor.
		 * @param newStartValue Starting value for the tween.
		 * @param newEndValue Ending value for the tween.
		 * @param newDuration Duration in seconds the tween will last.
		 * @param newEase Type of easing to apply to the tweening.
		 * @see BaconBox::Tween<T>::startValue
		 * @see BaconBox::Tween<T>::endValue
		 * @see BaconBox::Tween<T>::duration
		 * @see BaconBox::Tween<T>::ease
		 */
		Tween(const T& newStartValue, const T& newEndValue, double newDuration, Ease newEase) : Stopwatch(),
			startValue(newStartValue), endValue(newEndValue), duration(newDuration), ease(newEase) {
		}

		/**
		 * Copy constructor.
		 * @param src Tween to copy.
		 */
		Tween(const Tween<T>& src) : Stopwatch(src), startValue(src.startValue),
			endValue(src.endValue), duration(src.duration), ease(src.ease) {
		}

		/**
		 * Assignment operator overload.
		 * @param src Tween to copy.
		 * @return Reference to the modified tween.
		 */
		Tween<T>& operator=(const Tween<T>& src) {
			this->Stopwatch::operator=(src);

			if(this != &src) {
				startValue = src.startValue;
				endValue = src.endValue;
				duration = src.duration;
				ease = src.ease;
			}

			return *this;
		}

		/**
		 * Gets the tween's starting value.
		 * @return Starting value.
		 * @see BaconBox::Tween<T>::startValue
		 */
		const T& getStartValue() const {
			return startValue;
		}

		/**
		 * Sets the starting value.
		 * @param newStartValue New starting value.
		 * @see BaconBox::Tween<T>::startValue
		 */
		void setStartValue(const T& newStartValue) {
			startValue = newStartValue;
		}

		/**
		 * Gets the ending value.
		 * @return Ending value.
		 * @see BaconBox::Tween<T>::endValue
		 */
		const T& getEndValue() const {
			return endValue;
		}

		/**
		 * Sets the ending value.
		 * @param newEndValue New ending value.
		 * @see BaconBox::Tween<T>::endValue
		 */
		void setEndValue(const T& newEndValue) {
			endValue = newEndValue;
		}

		/**
		 * Gets the tween's duration.
		 * @return Gets the tween's duration.
		 * @see BaconBox::Tween<T>::duration
		 */
		double getDuration() const {
			return duration;
		}

		/**
		 * Sets the tween's duration.
		 * @param newDuration New duration (in seconds).
		 * @see BaconBox::Tween<T>::duration
		 */
		void setDuration(double newDuration) {
			duration = newDuration;
		}

		/**
		 * Gets the tween's type of easing.
		 * @return Type of easing applied on the value.
		 * @see BaconBox::Tween<T>::ease
		 */
		Ease getEase() const {
			return ease;
		}

		/**
		 * Sets the tween's type of easing.
		 * @param newEase New type of easing to use.
		 * @see BaconBox::Tween<T>::ease
		 */
		void setEase(Ease newEase) {
			ease = newEase;
		}

		/**
		 * Gets the current eased value.
		 * @return Value eased using the tween's type of easing. If the tween
		 * is done, it always returns the end value.
		 */
		T getValue() const {
			double currentTime = this->getTime();

			if(duration == 0.0 || currentTime >= duration) {
				return endValue;

			} else {
				return (endValue - startValue) * MathHelper::ease(currentTime / duration, ease) + startValue;
			}
		}

		/**
		 * Checks if the tween is done.
		 * @return True if the tweening is equal to or past the end value,
		 * false if not.
		 */
		bool isDone() const {
			return getTime() >= duration;
		}
	private:
		/// Value at the start of the tweening.
		T startValue;

		/// Value to reach at the end of the tweening's duration.
		T endValue;

		/**
		 * Time the value takes to reach the end value. The value between the
		 * start value and the end value is eased using the tween's easing type.
		 */
		double duration;

		/**
		 * Type of ease to apply to the value.
		 */
		Ease ease;
	};
}

#endif
