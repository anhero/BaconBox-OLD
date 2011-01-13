#ifndef __BAR_H
#define __BAR_H
#include <string>
#include <cmath>

#include "GraphicObject.h"
#include "TimeHelper.h"
#include "MathMacro.h"

namespace RedBox {
	/**
	 * @class GenericBar
	 *
	 * Represents a bar used for showing a value (like a health bar, an ammo 
	 * bar, etc.).
	 * @see RedBox::GraphicObject
	 * @author Adam Labranche <adam.labranche@illogicalstudios.com>
	 */
	class GenericBar : public GraphicObject {
	private:
		/**
		 * The bar's value.
		 */
		int value;
		/**
		 * The value currently shown on screen (used for animating the bar).
		 */
		int shownValue;
		/**
		 * The last time the value was incremented/decremented (used for
		 * animating the bar).
		 */
		double lastIncrement;
		/**
		 * The maximum value the bar can have.
		 */
		int maxValue;
		/**
		 * The maximum length the bar can have (in pixels).
		 */
		double maxBarLength;
		/**
		 * The delay between each animation of the bar.
		 */
		double delay;
		/**
		 * The graphic used for representing the current value.
		 */
		OpenGLDrawer* valueBar;
		// The default delay.
		static const double DEFAULT_DELAY = 0.02;
		// The maximum pixels the bar can be resized per update.
		static const double MAX_VALUE_MOVE = 10;
		// The division of the value for each frame of animation.
		static const double VALUE_ANIM_DIV = 4;
		// The maximum difference between the shown value and the current value to use for animation.
		static const int MAX_VALUE_DIFF = 40;
		/**
		 * The X positionning correction to be added to the valueBar to make it
		 * fit the bar's frame.
		 */
		double xCorr;
		/**
		 * The Y positionning correction to be added to the valueBar to make it
		 * fit the bar's frame.
		 */
		double yCorr;
		/**
		 * Whether the frame has to be on top or not.
		 */
		bool frameOnTop;
		/**
		 * Cleans allocated memory.
		 */
		void clean();
		/**
		 * Make the instance a copy of the passed GenericBar.
		 * @param src The GenericBar to copy.
		 */
		void copyFrom(const GenericBar& src);
		/**
		 * Updates the bar's position, takes care of adjusting the position
		 * accordint to the bar's angle.
		 */
		void refreshBarPosition();
		/**
		 * Whether or not to resize the frame height instead of the height when
		 * showing the bar's value.
		 */
		bool usingFrameHeight;
	public:
		/**
		 * The default constructor.
		 */
		GenericBar();
		/**
		 * The parametrized constructor.
		 * @param newMaxValue The starting max value.
		 * @param newMaxBarLength The maximum length in pixel of the bar shown.
		 * @param barImgPath The full path to the graphic used for the bar.
		 * @param barWidth The bar's width in pixels.
		 * @param barFrameWidth The bar's frame width in pixels.
		 * @param newXCorr The horizontal corrective positionning.
		 * @param newYCorr The vertical corrective positionning.
		 * @param newFrameOnTop Whether or not the bar's frame is shown on top.
		 * @param newPixelsPerValue The number of pixels per value.
		 * @param newDelay The delay between each frame of animation.
		 */
		GenericBar(int newMaxValue, double newMaxBarLength, 
			const std::string& barImgPath, double barWidth, 
			int barFrameWidth, double newXCorr, double newYCorr,
			bool newFrameOnTop = true, int newPixelsPerValue = 1,
			double newDelay = 0.02);
		/**
		 * The copy constructor.
		 */
		GenericBar(const GenericBar& src);
		/**
		 * The destructor.
		 */
		virtual ~GenericBar();
		/**
		 * The assignation operator overloaded.
		 * @param src The GenericBar to copy.
		 * @return A reference to the current instance.
		 */
		GenericBar& operator=(const GenericBar& src);
		/**
		 * Updates the bar's animation.
		 */
		virtual void update();
		/**
		 * Render the frame and the value bar in the right order.
		 */
		virtual void render();
		/**
		 * Gets the bar's maximum value.
		 * @return The maximum value.
		 */
		int getMaxValue() const;
		/**
		 * Sets the bar's maximum value.
		 * @param newMaxValue New maximum value.
		 */
		void setMaxValue(int newMaxValue);
		/**
		 * Gets the current value.
		 * @return The current value.
		 */
		int getValue() const;
		/**
		 * Sets the current value. Animation will automatically be done after
		 * setting the new value.
		 * @param newValue The new bar's value.
		 */
		void setValue(int newValue);
		/**
		 * The addition assignation operator overloaded. Used to change the
		 * bar's value.
		 * @param aValue The value to add to the current value.
		 * @return A reference to the current instance.
		 */
		GenericBar& operator+=(int aValue);
		/**
		 * The substraction assignation operator overloaded. Used to change the
		 * bar's value.
		 * @param aValue The value to substract from the current value.
		 * @return A reference to the current instance.
		 */
		GenericBar& operator-=(int aValue);
		/**
		 * Sets the bar's position.
		 * @param x The new x position, represents the bar's center.
		 * @param y The new y position, represents the bar's center.
		 */
		void setPosition(double x, double y);
		/**
		 * Sets the bar's x position.
		 * @param x The new x position, represents the bar's center.
		 */
		void setXPosition(double x);
		/**
		 * Sets the bar's y position.
		 * @param y The new y position, represents the bar's center.
		 */
		void setYPosition(double y);
		/**
		 * Sets the position correction.
		 * Sets the number of pixels to add to the positionning of the value bar
		 * to make it fit with the bar's frame.
		 * @param newXCorr Number of pixels to add to the value bar's x
		 * position.
		 * @param newYCorr Number of pixels to add to the value bar's y
		 * position.
		 */
		void setPositionCorrection(double newXCorr, double newYCorr);
		/**
		 * Sets the x position correction.
		 * Sets the number of pixels to add to the value bar's x position to
		 * make it fit with the bar's frame.
		 * @param newXCorr Number of pixels to add to the value bar's x
		 * position.
		 */
		void setXPositionCorrection(double newXCorr);
		/**
		 * Sets the y position correction.
		 * Sets the number of pixels to add to the value bar's y position to
		 * make it fit with the bar's frame.
		 * @param newXCorr Number of pixels to add to the value bar's y
		 * position.
		 */
		void setYPositionCorrection(double newYCorr);
		/**
		 * Gets the x position correction.
		 * Gets the number of pixels being added to the value bar's x position
		 * to make it fit with the bar's frame.
		 * @return Number of pixels being added to the value bar's x position.
		 */
		double getXPositionCorrection() const;
		/**
		 * Gets the y position correction.
		 * Gets the number of pixels being added to the value bar's y position
		 * to make it fit with the bar's frame.
		 * @return Number of pixels being added to the value bar's y position.
		 */
		double getYPositionCorrection() const;
		/**
		 * Sets the bar's rotation angle.
		 * Makes sure the two graphic objects are always well aligned
		 * considering the x and y position corrections.
		 * @param angle New angle to apply to the bar.
		 */
		void setAngle(double angle);
		/**
		 * Sets the frame to be shown over the value bar.
		 */
		void setFrameOnTop();
		/**
		 * Sets the frame to be shown under the value bar.
		 */
		void setBarOnTop();
		/**
		 * Makes the bar use the frame height to resize the value bar when the
		 * value changes.
		 */
		void useFrameHeight();
		/**
		 * Makes the bar use the height to resize the value bar when the value
		 * changes.
		 */
		void useHeight();
	};
}

#endif