/**
 * @file
 * @ingroup Display
 */
#ifndef RB_CAMERA_H
#define RB_CAMERA_H

#include "Color.h"
#include "Vector2.h"
#include "SafeEnum.h"
#include "Renderable.h"
#include "Collidable.h"
#include "Disableable.h"
#include "StandardVerticesArray.h"
#include "Shapable.h"

namespace RedBox {
	/**
	 * Represent the camera. This class prepare the scene to mimic a the effect of a camera.
	 * If we "move" this object to the right, every object will shift
	 * to the left before rendering.
	 * @ingroup Display
	 */
	class Camera : public Collidable, public Disableable,
		public Shapable<StandardVerticesArray> {
		friend class State;
	public:
		struct ShakeAxesDef {
			enum type {
			    BOTH_AXES,
			    HORIZONTAL_AXIS,
			    VERTICAL_AXIS
			};
		};

		/**
		 * The possible axes on which the camera can shake.
		 */
		typedef SafeEnum<ShakeAxesDef> ShakeAxes;

		/**
		 * Default constructor.
		 */
		Camera();

		/**
		 * Copy constructor.
		 * @param src Camera to make a copy of.
		 */
		Camera(const Camera &src);

		/**
		 * Assignation operator overload.
		 * @param src Camera to make a copy of.
		 * @return Camera resulting of the copy.
		 */
		Camera &operator=(const Camera &src);

		/**
		 * Gets the camera's size.
		 * @return Vector2 containing the width and height of the camera.
		 */
		const Vector2 getSize() const;

		/**
		 * Gets the camera's width.
		 * @return Width in pixels (by default).
		 */
		float getWidth() const;

		/**
		 * Gets the camera's height.
		 * @return Height in pixels (by default).
		 */
		float getHeight() const;

		/**
		 * Moves the camera horizontally and vertically.
		 * @param xDelta Value to add to the camera's horizontal position
		 * (in pixels). Positive value moves the Positionable to the right and a
		 * negative value moves the camera to the left.
		 * @param yDelta Value to add to the camera's vertical position (in
		 * pixels). Positive value moves the camera down and a negative
		 * value moves the camera up.
		 * @see RedBox::Positionable::move(const Vector2& delta);
		 * @see RedBox::Positionable::position
		 */
		virtual void move(float xDelta, float yDelta);

		using Collidable::scaleFromPoint;

		/**
		 * Scales the camera from a specific point.
		 * @param xScaling Horizontal scaling to apply. For example, if
		 * 2.0f is passed, everything will look twice as wide.
		 * @param yScaling Vertical scaling to apply. For example, if 2.0f is
		 * passed, everything will look twice as high.
		 * @param fromPoint Anchor point from which to apply the scaling.
		 * @see RedBox::Transformable::scaling
		 */
		void scaleFromPoint(float xScaling, float yScaling,
		                    const Vector2 &fromPoint);

		/**
		 * Rotates the camera from a point.
		 * @param rotationAngle Angle to rotate the camera.
		 * @param rotationPoint Origin point on which to apply the rotation.
		 * @see RedBox::Transformable::angle
		 */
		void rotateFromPoint(float rotationAngle,
		                     const Vector2 &rotationPoint);

		/**
		 * Gets the camera's background color.
		 * @return Camera's background color.
		 * @see RedBox::Camera::backgroundColor
		 */
		const Color &getBackgroundColor() const;

		/**
		 * Sets the camera's background color.
		 * @param newBackgroundColor Camera's new background color.
		 * @see RedBox::Camera::backgroundColor
		 */
		void setBackgroundColor(const Color &newBackgroundColor);

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
		           bool forceReset = true,
		           ShakeAxes axes = ShakeAxes::BOTH_AXES);

		/**
		 * Converts screen coordinates to world coordinates.
		 * @param positionOnScreen Position relative to the camera's position to
		 * convert to world coordinates.
		 * @return 2D vector containing the world coordinates equivalent to the
		 * given parameter.
		 * @see RedBox::Camera::position
		 */
		const Vector2 screenToWorld(const Vector2 &positionOnScreen) const;

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
		const Vector2 screenToWorld(float x, float y) const;

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
		const Vector2 worldToScreen(const Vector2 &positionInWorld) const;

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
		const Vector2 worldToScreen(float x, float y) const;

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
		 * Makes the given body collide within the camera.
		 * @param collidable Pointer to the collidable body that needs to stay
		 * within the camera.
		 */
		bool collideInside(Collidable *collidable);

	private:
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
		Vector2 offset;

		/**
		 * Updates the camera's shaking.
		 */
		void update();

		/**
		 * Prepare the scene according to the camera's position, angle and zoom
		 * factor
		 */
		void render();

		/**
		 * Does nothing.
		 */
		void mask();

		/**
		 * Does nothing
		 */
		void unmask();

		/**
		 * Does nothing
		 * @return NULL.
		 */
		Maskable *getMask() const;

		/**
		 * Does nothing.
		 * @param newMask Useless.
		 * @param inverted Useless.
		 */
		void setMask(Maskable *newMask, bool inverted = false);
	};
}

#endif
