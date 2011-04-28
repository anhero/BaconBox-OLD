/**
 * @file
 * @ingroup Display
 */

#ifndef RB_Camera_H
#define RB_Camera_H

#include "Color.h"

namespace RedBox{
	/** 
	 * Represent the camera. This class prepare the scene to mimic a the effect of a camera. 
	 * If we "move" this object to the right, every object will shift
	 * to the left before rendering.
     * @ingroup Display
     */
	class Camera{
	public:
		///Default Constructor
		Camera();
		
		/**
		 * Move the camera
		 * @param x Number of pixels to add to the current x 
		 * position of the camera.
		 * @param y Number of pixels to add to the current y 
		 * position of the camera.
		 */
		void move(int x, int y);
		
		/**
		 * Set the position of the camera.
		 * @param x Set the x position of the camera.
		 * @param y Set the y position of the camera.
		 */
		void setPosition(int x, int y);
		
		///Return the position of the camera on the x axis
		int getX();
		
		///Return the position of the camera on the y axis
		int getY();
		
		///Reset the angle of the camera at the default value: 0
		void resetAngle();
		
		///Set the angle of the camera to the given degree angle.
		void setAngle(int angle);
		
		///Return the angle value of the camera in degree.
		float getAngle();
		
		///Rotate the camera to the left with the given degree value.
		void rotateLeft(int angle);
		
		///Rotate the camera to the right with the given degree value.
		void rotateRight(int angle);

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
		 * @param factor 1 does nothing, less than 1 zoom out, more than 1 zoom in.
		 */
		void zoom(float factor);
		
		/**
		 * Set the zoom factor with the given value.
		 * @param factor 1 does nothing, less than 1 zoom out, more than 1 zoom in.
		 */
		void setZoom(float factor);
		
		///Set the zoom factor to the default value: 1.
		void resetZoom();
		
		///Prepare the scene according to the position, angle and zoom factor of the camera.
		void render();
	private:
		///Position on the x axis.
		int x;
		
		///Position on the y axis.
		int y;
		
		///Angle of the camera.
		int angle;
		
		///Zoom factor (1 does nothing, less than 1 zoom out, more than 1 zoom in)
		float zoomFactor;

		/// Background color for the camera.
		Color backgroundColor;
	};
}

#endif
