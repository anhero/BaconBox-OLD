/**
 * @file
 * @ingroup Helper
 */
#ifndef RB_STEP_TWEEN_H
#define RB_STEP_TWEEN_H

#include "BaconBox/Helper/Ease.h"
#include "BaconBox/Helper/MathHelper.h"

namespace BaconBox {
	/**
	 * Represents a class for tweens that uses a number of steps instead of
	 * time.
	 * @tparam T Type to tween
	 * @ingroup Helper
	 */
	template <typename T>
	class StepTween {
	public:
		/// Typedef for the type to tween.
		typedef T ValueType;

		/**
		 * Default constructor.
		 */
		StepTween() : startValue(), endValue(), step(0), tweening(false),
			nbSteps(0), ease(Ease::LINEAR) {
		}

		/**
		 * Parameterized constructor.
		 * @param newStartValue Start value to use for the tweening.
		 * @param newEndValue End value to use for the tweening.
		 * @param newNbSteps Number of steps to take to reach the end value.
		 * @param newEase Type of easing to use to calculate the current
		 * value.
		 */
		StepTween(T newStartValue, T newEndValue, unsigned int newNbSteps,
		          Ease newEase) : startValue(newStartValue),
			endValue(newEndValue), step(0), tweening(false),
			nbSteps(newNbSteps), ease(newEase) {
		}

		/**
		 * Copy constructor.
		 * @param src Step tween to make a copy of.
		 */
		StepTween(const StepTween<ValueType> &src) : startValue(src.startValue),
			endValue(src.endValue), step(src.step), tweening(src.tweening),
			nbSteps(src.nbSteps), ease(src.ease) {}

		/**
		 * Assignment operator overload.
		 * @param src Step tween to copy.
		 * @return Reference to the modified instance.
		 */
		StepTween<ValueType> &operator=(const StepTween<ValueType> &src) {
			if (this != &src) {
				startValue = src.startValue;
				endValue = src.endValue;
				step = src.step;
				tweening = src.tweening;
				nbSteps = src.nbSteps;
				ease = src.ease;
			}

			return *this;
		}

		/**
		 * Gets the current step.
		 * @return Current step the tween is at.
		 * @see BaconBox::StepTween::step
		 */
		unsigned int getStep() const {
			return step;
		}

		/**
		 * Updates the step tween. Increments the step by one if it's currently
		 * tweening and stops the tweening if the step reaches the current
		 * number of steps.
		 */
		void update() {
			if (tweening) {
				++step;

				if (step == nbSteps) {
					tweening = false;
				}
			}
		}

		/**
		 * Starts the tween.
		 */
		void start() {
			tweening = step < nbSteps;
		}

		/**
		 * Stops the tween and sets the step at 0.
		 */
		void stop() {
			step = 0;
			pause();
		}

		/**
		 * Stops the tweening, but remembers the current step.
		 */
		void pause() {
			tweening = false;
		}

		/**
		 * Sets the step at 0 and starts the tween.
		 */
		void restart() {
			step = 0;
			start();
		}

		/**
		 * Checks if the tween is paused.
		 * @return True if the tween is paused, false if not.
		 */
		bool isPaused() const {
			return !tweening && step > 0;
		}

		/**
		 * Checks if the tween is stopped.
		 * @return True if the tween isn't tweening and the step is currently at
		 * 0, false if not.
		 */
		bool isStopped() const {
			return !tweening && step == 0;
		}

		/**
		 * Checks if the tweening is done.
		 * @return True if the step is the same as the number of steps, false if
		 * not.
		 */
		bool isDone() const {
			return step == nbSteps;
		}

		/**
		 * Checks if the tween is currently tweening.
		 * @return True if the tween is currently tweening, false if not.
		 */
		bool isTweening() const {
			return tweening;
		}

		/**
		 * Starts or pauses the tweening.
		 * @param newTweening Set this to true to start the tweening. Does
		 * nothing if the tweening is done.
		 */
		void setTweening(bool newTweening) {
			tweening = newTweening && step < nbSteps;
		}

		/**
		 * Gets the number of steps the tweening takes.
		 */
		unsigned int getNbSteps() const {
			return nbSteps;
		}

		/**
		 * Sets the number of steps the tweening takes.
		 * @param newNbSteps New number of steps to set.
		 */
		void setNbSteps(unsigned int newNbSteps) {
			nbSteps = newNbSteps;

			if (step > nbSteps) {
				step = nbSteps;
			}
		}

		/**
		 * Gets the type of easing.
		 * @return Type of easing to use to calculate the tweening's value.
		 */
		Ease getEase() const {
			return ease;
		}

		/**
		 * Sets the type of easing.
		 * @param newEase
		 */
		void setEase(Ease newEase) {
			ease = newEase;
		}

		/**
		 * Gets the tween's starting value.
		 * @return Starting value.
		 * @see BaconBox::StepTween<T>::startValue
		 */
		ValueType getStartValue() const {
			return startValue;
		}

		/**
		 * Sets the starting value.
		 * @param newStartValue New starting value.
		 * @see BaconBox::StepTween<T>::startValue
		 */
		void setStartValue(ValueType newStartValue) {
			startValue = newStartValue;
		}

		/**
		 * Gets the ending value.
		 * @return Ending value.
		 * @see BaconBox::StepTween<T>::endValue
		 */
		ValueType getEndValue() const {
			return endValue;
		}

		/**
		 * Sets the ending value.
		 * @param newEndValue New ending value.
		 * @see BaconBox::StepTween<T>::endValue
		 */
		void setEndValue(ValueType newEndValue) {
			endValue = newEndValue;
		}

		/**
		 * Gets the current eased value.
		 * @return Value eased using the tween's type of easing. If the tween
		 * is done, it always returns the end value.
		 */
		ValueType getValue() const {
			if (nbSteps == 0 || step == nbSteps) {
				return endValue;

			} else {
				return (endValue - startValue) * MathHelper::ease(static_cast<float>(step) / static_cast<float>(nbSteps), ease) + startValue;
			}
		}
	private:
		/// Value at the start of the tweening.
		ValueType startValue;

		/// Value to reach at the last step.
		ValueType endValue;

		/// Current step, always from 0 to nbSteps.
		unsigned int step;

		/// Set to true when the tween is tweening.
		bool tweening;

		/// Number of steps it takes to reach the end value.
		unsigned int nbSteps;

		/// Type of easing to calculate. LINEAR by default.
		Ease ease;
	};
}

#endif
