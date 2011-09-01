#ifndef RB_SLIDER_H
#define RB_SLIDER_H

#include "GraphicBody.h"
#include "MathHelper.h"
#include "Console.h"

#include <sigly.h>

namespace RedBox {
	template <typename T>
	class Slider : public GraphicBody {
	public:
		typedef T ValueType;

		/// Signal sent when the slider's value changes.
		sigly::Signal1<ValueType> valueChange;

		/**
		 * Default constructor.
		 */
		Slider() : GraphicBody(), minimumValue(), maximumValue(),
			currentValue() {
		}

		/**
		 * Parameterized constructor. Sets the minimum and maximum value.
		 * Clamps the current value to be within the possible range.
		 * @param newMinimumValue Range's minimum value.
		 * @param newMaximumValue Range's maximum value.
		 * @see RedBox::Slider<T>::minimumValue
		 * @see RedBox::Slider<T>::maximumValue
		 * @see RedBox::Slider<T>::setMinimumMaximumValue(ValueType newMinimumValue, ValueType newMaximumValue)
		 */
		Slider(ValueType newMinimumValue, ValueType newMaximumValue) :
			GraphicBody(), minimumValue(), maximumValue(), currentValue() {
			setMinimumMaximumValue(newMinimumValue, newMaximumValue);
		}

		/**
		 * Parameterized constructor. Sets the minimum, maximum and current
		 * value. Clamps the current value to be within the possible range.
		 * @param newMinimumValue Range's minimum value.
		 * @param newMaximumValue Range's maximum value.
		 * @param startingValue Starting current value.
		 * @see RedBox::Slider<T>::minimumValue
		 * @see RedBox::Slider<T>::maximumValue
		 * @see RedBox::Slider<T>::setMinimumMaximumValue(ValueType newMinimumValue, ValueType newMaximumValue)
		 */
		Slider(ValueType newMinimumValue, ValueType newMaximumValue,
		       ValueType startingValue) : GraphicBody(),
			minimumValue(), maximumValue(),
			currentValue(startingValue) {
			setMinimumMaximumValue(newMinimumValue, newMaximumValue);
		}

		/**
		 * Copy constructor.
		 * @param src Slider to make a copy of.
		 */
		Slider(const Slider<ValueType>& src) : GraphicBody(src),
			minimumValue(src.minimumValue), maximumValue(src.maximumValue),
			currentValue(src.currentValue) {
		}

		/**
		 * Destructor.
		 */
		virtual ~Slider() {
		}

		/**
		 * Assignment operator overload.
		 * @param src Slider to make a copy of.
		 * @return Reference to the modified slider.
		 */
		Slider<ValueType>& operator=(const Slider<ValueType>& src) {
			this->GraphicBody::operator=(src);

			if(this != &src) {
				minimumValue = src.minimumValue;
				maximumValue = src.maximumValue;
				currentValue = src.currentValue;
			}

			return *this;
		}

		/**
		 * Gets the minimum value.
		 * @return Minimum value.
		 * @see RedBox::Slider::minimumValue
		 */
		ValueType getMinimumValue() const {
			return minimumValue;
		}

		/**
		 * Sets the minimum value. Makes sure the current value stays within
		 * the range. If the new minimum value is higher than the maximum
		 * value, it is set at the maximum value. Whatever the new minimum
		 * value, the current value is clamped to stay within the range.
		 * @param newMinimumValue New minimum value for the slider's range.
		 * @see RedBox::Slider<T>::minimumValue
		 */
		void setMinimumValue(ValueType newMinimumValue) {
			if(newMinimumValue > maximumValue) {
				newMinimumValue = maximumValue;
				Console::println("Tried to set a slider's minimum value higher than its maximum value.");
				Console::printTrace();
			}

			minimumValue = newMinimumValue;
			setCurrentValue(currentValue);
		}

		/**
		 * Gets the maximum value.
		 * @return Maximum value.
		 * @see RedBox::Slider<T>::minimumValue
		 */
		ValueType getMaximumValue() const {
			return maximumValue;
		}

		/**
		 * Sets the maximum value. Makes sure the current value stays within
		 * the range. If the new maximum value is lower than the maximum
		 * value, it is set at the minimum value. Whatever the new minimum
		 * value, the current value is clamped to stay within the range.
		 * @param newMaximumValue New maximum value for the slider's range.
		 * see RedBox::Slider<T>::maximumValue
		 */
		void setMaximumValue(ValueType newMaximumValue) {
			if(newMaximumValue < minimumValue) {
				newMaximumValue = minimumValue;
				Console::println("Tried to set a slider's maximum value lower than its minimum value.");
				Console::printTrace();
			}

			maximumValue = newMaximumValue;
			setCurrentValue(currentValue);
		}

		/**
		 * Sets the minimum and the maximum value. If the minimum value is
		 * higher than the maximum value, it sets the maximum value to the
		 * minimum value. Whatever the new minimum and maximum values, the
		 * current value stays clamped within the range.
		 * @param newMinimumValue New minimum value for the slider's range.
		 * @param newMaximumValue New maximum value for the slider's range.
		 * @see RedBox::Slider<T>::minimumValue
		 * @see RedBox::Slider<T>::maximumValue
		 */
		void setMinimumMaximumValue(ValueType newMinimumValue,
		                            ValueType newMaximumValue) {
			if(newMinimumValue > newMaximumValue) {
				newMaximumValue = newMinimumValue;
			}

			minimumValue = newMinimumValue;
			maximumValue = newMaximumValue;
			setCurrentValue(currentValue);
		}

		/**
		 * Gets the slider's current value. Always stays within the slider's
		 * range.
		 * @return Current value.
		 * @see RedBox::Slider<T>::currentValue
		 */
		ValueType getCurrentValue() const {
			return currentValue;
		}

		/**
		 * Sets the slider's current value. Clamps the given current value to
		 * make the current value stay within the slider's range.
		 * @param newCurrentValue New current value.
		 * @see RedBox::Slider<T>::currentValue
		 */
		virtual void setCurrentValue(ValueType newCurrentValue) {
			ValueType oldValue = currentValue;
			currentValue = MathHelper::clamp(newCurrentValue, minimumValue,
			                                 maximumValue);

			if(oldValue != currentValue) {
				valueChange(currentValue);
			}
		}
	private:
		/**
		 * Minimum value the slider can contain. Always lower than or equal to
		 * the maximum value.
		 */
		ValueType minimumValue;

		/**
		 * Maximum value the slider can contain. Always higher than or equal to
		 * minimum value.
		 */
		ValueType maximumValue;

		/**
		 * Current value the slider contains, always stays between the minimum
		 * and the maximum value.
		 */
		ValueType currentValue;
	};
}

#endif
