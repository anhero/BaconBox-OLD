/**
 * @file
 * @ingroup Display
 */
#ifndef RB_CAMERA_H
#define RB_CAMERA_H

#include "Object.h"
#include "Color.h"
#include "Vec2.h"

namespace RedBox{
	/** 
	 * Represent the camera. This class prepare the scene to mimic a the effect of a camera. 
	 * If we "move" this object to the right, every object will shift
	 * to the left before rendering.
     * @ingroup Display
     */
	class Camera : public Object {
	public:
		enum ShakeAxes {
			BOTH_AXES,
			HORIZONTAL_AXIS,
			VERTICAL_AXIS
		};

		///Default Constructor
		Camera();

		/**
		 * Copy constructor.
		 */
		Camera(const Camera& src);

		/**
		 * Assignation operator overload.
		 */
		Camera& operator=(const Camera& src);
		
		/**
		 * Moves the camera.
		 * @param x Value to move the camera on the x axis.
		 * @param y Value to move the camera on the y axis.
		 */
		void move(float x, float y);

		/**
		 * Move the camera.
		 * @param moveVector 2D vector containing the number of pixels to move
		 * the camera.
		 */
		void move(const Vec2& moveVector);

		/**
		 * Move the camera horizontally.
		 * @param x Number of pixels to move the camera horizontally.
		 */
		void moveX(float x);

		/**
		 * Move the camera vertically.
		 * @param y Number of pixels to move the camera vertically.
		 */
		void moveY(float y);
		
		/**
		 * Set the position of the camera.
		 * @param x Set the x position of the camera.
		 * @param y Set the y position of the camera.
		 */
		void setPosition(float x, float y);
		void setPosition(const Vec2& newPosition);
		
		/// Return the camera's position on the x axis
		float getXPosition() const;
		
		/// Return the camera's position on the y axis
		float getYPosition() const;

		const Vec2& getPosition() const;
		
		/// Reset the angle of the camera at the default value: 0
		void resetAngle();
		
		/// Set the angle of the camera to the given degree angle.
		void setAngle(float newAngle);
		
		/// Return the angle value of the camera in degree.
		float getAngle() const;
		
		/// Rotate the camera counter-clockwise with the given degree value.
		void rotateLeft(float rotationAngle);
		
		/// Rotate the camera cockwise with the given degree value.
		void rotateRight(float rotationAngle);

		/**
		 * Sets the camera's background color.
		 * @param newBackgroundColor Camera's new background color.
		 */
		void setBackgroundColor(const Color& newBackgroundColor);
		
		/**
		 * Gets the camera's background color.
		 * @return Camera's background color.
		 */
		const Color& getBackgroundColor() const;

		/**
		 * Multiply the zoom factor by the given value.
		 * @param factor 1 does nothing, less than 1 zoom out, more than 1
		 * zoom in.
		 */
		void zoom(float factor);
		
		/**
		 * Set the zoom factor with the given value.
		 * @param factor 1 does nothing, less than 1 zoom out, more than 1
		 * zoom in.
		 */
		void setZoom(float factor);

		/**
		 * Gets the zoom factor.
		 * @return Camera's zoom factor. less than 1 is zoomed out, more than
		 * 1 is zoomed in.
		 */
		float getZoom() const;
		
		/// Set the zoom factor to the default value: 1.
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
		 * Updates the camera's shaking.
		 */
		void update();

		/// Prepare the scene according to the position, angle and zoom factor of the camera.
		void render();

		Vec2 screenToWorld(const Vec2& positionOnScreen);

		Vec2 worldToScreen(const Vec2& positionInWorld);
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
	};
}

#endif
