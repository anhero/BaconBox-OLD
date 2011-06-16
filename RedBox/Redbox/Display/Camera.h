/**
 * @file
 * @ingroup Display
 */
#ifndef RB_CAMERA_H
#define RB_CAMERA_H

#include "Body.h"
#include "Color.h"
#include "Vec2.h"

namespace RedBox{
	/** 
	 * Represent the camera. This class prepare the scene to mimic a the effect of a camera. 
	 * If we "move" this object to the right, every object will shift
	 * to the left before rendering.
     * @ingroup Display
     */
	class Camera : public Body {
		friend class State;
	public:
		/**
		 * The possible axes on which the camera can shake.
		 */
		enum ShakeAxes {
			BOTH_AXES,
			HORIZONTAL_AXIS,
			VERTICAL_AXIS
		};

		/**
		 * Default constructor.
		 */
		Camera();

		/**
		 * Parameterized constructor specifying its width and height.
		 * @param newWidth Camera's initial width.
		 * @param newHeight Camera's initial height.
		 */
		Camera(unsigned int newWidth, unsigned int newHeight);

		/**
		 * Copy constructor.
		 * @param Camera to make a copy of.
		 */
		Camera(const Camera& src);

		/**
		 * Assignation operator overload.
		 * @param src Camera to make a copy of.
		 * @return Camera resulting of the copy.
		 */
		Camera& operator=(const Camera& src);
		
		/**
		 * Gets the camera's position.
		 * @return Vector containing the camera's position.
		 * @see RedBox::Camera::position
		 */
		const Vec2& getPosition() const;

		/**
		 * Sets camera's position.
		 * @param x Set the horizontal position of the camera.
		 * @param y Set the vertical position of the camera.
		 * @see RedBox::Camera::position
		 */
		void setPosition(float x, float y);

		/**
		 * Sets the camera's position.
		 * @param newPosition Camera's new position.
		 * @see RedBox::Camera::position
		 */
		void setPosition(const Vec2& newPosition);
		
		/**
		 * Moves the camera.
		 * @param x Value to move the camera on the x axis.
		 * @param y Value to move the camera on the y axis.
		 * @see RedBox::Camera::position
		 */
		void move(float x, float y);

		/**
		 * Move the camera.
		 * @param moveVector 2D vector containing the number of pixels to move
		 * the camera.
		 * @see RedBox::Camera::position
		 */
		void move(const Vec2& moveVector);

		/**
		 * Gets the camera's horizontal position.
		 * @return Camera's horizontal position.
		 * @see RedBox::Camera::position
		 */
		float getXPosition() const;

		/**
		 * Sets the camera's horizontal position.
		 * @param newXPosition New horizontal position.
		 * @see RedBox::Camera::position
		 */
		void setXPosition(float newXPosition);

		/**
		 * Move the camera horizontally.
		 * @param x Number of pixels to move the camera horizontally.
		 * @see RedBox::Camera::position
		 */
		void moveX(float x);

		/**
		 * Gets the camera's vertical position.
		 * @return Camera's vertical position.
		 * @see RedBox::Camera::position
		 */
		float getYPosition() const;

		/**
		 * Sets the camera's vertical position.
		 * @param newYPosition New vertical position.
		 * @see RedBox::Camera::position
		 */
		void setYPosition(float newYPosition);

		/**
		 * Move the camera vertically.
		 * @param y Number of pixels to move the camera vertically.
		 * @see RedBox::Camera::position
		 */
		void moveY(float y);

		/**
		 * Gets the camera's current rotation angle.
		 * @return Camera's angle.
		 * @see RedBox::Camera::angle
		 */
		float getAngle() const;

		/**
		 * Sets the camera's angle.
		 * @param newAngle Camera's new angle.
		 * @see RedBox::Camera::angle
		 */
		void setAngle(float newAngle);

		/**
		 * Rotate the camera counter-clockwise with the given degree value.
		 * @param rotationAngle Angle to have to camera rotate
		 * counter-clockwise.
		 * @see RedBox::Camera::angle
		 */
		void rotateLeft(float rotationAngle);
		
		/**
		 * Rotate the camera clockwise with the given degree value.
		 * @param rotationAngle Angle to have to camera rotate clockwise.
		 * @see RedBox::Camera::angle
		 */
		void rotateRight(float rotationAngle);

		/**
		 * Resets the camera's angle to the default value (0 degrees).
		 * @see RedBox::Camera::angle
		 */
		void resetAngle();

		/**
		 * Gets the camera's background color.
		 * @return Camera's background color.
		 * @see RedBox::Camera::backgroundColor
		 */
		const Color& getBackgroundColor() const;

		/**
		 * Sets the camera's background color.
		 * @param newBackgroundColor Camera's new background color.
		 * @see RedBox::Camera::backgroundColor
		 */
		void setBackgroundColor(const Color& newBackgroundColor);
		
		/**
		 * Gets the zoom factor.
		 * @return Camera's zoom factor. less than 1 is zoomed out, more than
		 * 1 is zoomed in.
		 * @see RedBox::Camera::zoomFactor
		 */
		float getZoomFactor() const;

		/**
		 * Sets the zoom factor with the given value.
		 * @param newZoomFactor 1.0 is the default, less than 1 zooms out, more
		 * than 1 zooms in.
		 * @see RedBox::Camera::zoomFactor
		 */
		void setZoomFactor(float newZoomFactor);

		/**
		 * Multiply the zoom factor by the given value.
		 * @param factor 1 does nothing, less than 1 zooms out, more than 1
		 * zooms in.
		 * @see RedBox::Camera::zoomFactor
		 */
		void zoom(float factor);
		
		/**
		 * Resets the zoom factor to the default value (1.0).
		 * @see RedBox::Camera::zoomFactor
		 */
		void resetZoom();
		
		/**
		 * Makes the camera shake like an earthquake.
		 * @param intensity Intensity of the camera shaking. This is not in
		 * pixels, this is a ratio of the screen size. So an intensity of
		 * will start by shaking the camera by its size * 0.05f and will
		 * gradually lower until the shaking is done. This is set at 0.05f by
		 * default.
		 * @param duration Duration of the shaking (in seconds). The intensity
		 * lowers linearly. This is set at 0.5 seconds by default.
		 * @param forceReset Forces the shaking to be reset with the given
		 * parameters. Even if forceReset is set to false, a shaking with
		 * higher intensity will override the lower one.
		 * @param axes Axis on which the screen shaking happens. By default,
		 * the camera shakes on both axes.
		 */
		void shake(float intensity = 0.05f, double duration = 0.5,
				   bool forceReset = true, ShakeAxes axes = BOTH_AXES);

		/**
		 * Converts screen coordinates to world coordinates.
		 * @param positionOnScreen Position relative to the camera's position to
		 * convert to world coordinates.
		 * @return 2D vector containing the world coordinates equivalent to the
		 * given parameter.
		 * @see RedBox::Camera::position
		 */
		Vec2 screenToWorld(const Vec2& positionOnScreen) const;

		/**
		 * Converts screen coordinates to world coordinates.
		 * @param x Horizontal position relative to the camera's position to
		 * convert to world coordinates.
		 * @param y Vertical position relative to the camera's position to
		 * convert to world coordinates.
		 * @return 2D vector containing the world coordinates equivalent to the
		 * given parameters.
		 * @see RedBox::Camera::position
		 */
		Vec2 screenToWorld(float x, float y) const;

		/**
		 * Converts an horizontal screen coordinate to world coordinate.
		 * @param x Horizontal position relative to the camera's position to
		 * convert to world coordinates.
		 * @return Horizontal world coordinate equivalent to the given screen
		 * coordinate.
		 */
		float screenToWorldX(float x) const;

		/**
		 * Converts a vertical screen coordinate to world coordinate.
		 * @param y Vertical position relative to the camera's position to
		 * convert to world coordinates.
		 * @return Vertical world coordinate equivalent to the given screen
		 * coordinate.
		 */
		float screenToWorldY(float y) const;

		/**
		 * Converts world coordinates to screen coordinates.
		 * @param positionInWorld Absolute position unrelated to the camera's
		 * position that needs to be converted into a position relative to the
		 * camera's position.
		 * @return 2D vector containing the screen coordinates equivalent to the
		 * given parameter.
		 * @see RedBox::Camera::position
		 */
		Vec2 worldToScreen(const Vec2& positionInWorld) const;

		/**
		 * Converts world coordinates to screen coordinates.
		 * @param x Absolute horizontal position unrelated to the camera's
		 * position that needs to be converted into a position relative to the
		 * camera's position.
		 * @param y Absolute vertical position unrelated to the camera's
		 * position that needs to be converted into a position relative to the
		 * camera's position.
		 * @return 2D vector containing the screen coordinates equivalent to the
		 * given parameter.
		 * @see RedBox::Camera::position
		 */
		Vec2 worldToScreen(float x, float y) const;

		/**
		 * Converts an horizontal world coordinate to a screen coordinate.
		 * @param x Absolute horizontal position unrelated to the camera's
		 * position that needs to be converted into a position relative to the
		 * camera's position.
		 * @return Horizontal screen coordinate equivalent to the given world
		 * coordinate.
		 * @see RedBox::Camera::position
		 */
		float worldToScreenX(float x) const;

		/**
		 * Converts a vertical world coordinate to a screen coordinate.
		 * @param y Absolute vertical position unrelated to the camera's
		 * position that needs to be converted into a position relative to the
		 * camera's position.
		 * @return Vertical screen coordinate equivalent to the given world
		 * coordinate.
		 * @see RedBox::Camera::position
		 */
		float worldToScreenY(float y) const;

		/**
		 * Gets the camera's width (not considering the zoom factor).
		 * @return Camera's width.
		 */
		unsigned int getWidth() const;

		/**
		 * Gets the camera's height (not considering the zoom factor).
		 * @return Camera's height.
		 */
		unsigned int getHeight() const;

	private:
		/// Camera's position.
		Vec2 position;

		/// Angle of the camera.
		float angle;
		
		/// Zoom factor (1 does nothing, less than 1 zoom out, more than 1 zoom in)
		float zoomFactor;

		/// Background color for the camera.
		Color backgroundColor;

		/**
		 * Camera shaking intensity. Value between 0.0f and 1.0f. A ratio of
		 * the screen size.
		 */
		float shakeIntensity;

		/// Time at which the shaking started.
		double shakeStart;

		/// Time the shaking must take before stopping.
		double shakeDuration;

		/// Axis on which the shaking takes place.
		ShakeAxes shakeAxes;

		/// Offset used when the camera is shaking.
		Vec2 offset;

		/**
		 * Updates the camera's shaking.
		 */
		void update();

		/**
		 * Prepare the scene according to the camera's position, angle and zoom
		 * factor
		 */
		void render();
	};
}

#endif
