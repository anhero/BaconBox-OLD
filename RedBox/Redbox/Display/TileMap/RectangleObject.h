#if 0
/**
 * @file
 */
#ifndef RB_RECTANGLE_OBJECT_H
#define RB_RECTANGLE_OBJECT_H

#include "TileMapObject.h"
#include "Vector2.h"

namespace RedBox {
	class RectangleObject : public TileMapObject {
	public:
		/**
		 * Default and parameterized constructor.
		 * @param newSize New size of the rectangle object (in pixels).
		 * @param newPosition Position of the rectangle object in the layer (in
		 * pixels).
		 * @param newName Name of the rectangle object, if it has one.
		 */
		explicit RectangleObject(const Vector2 &newSize = Vector2(),
		                         const Vector2 &newPosition = Vector2(),
		                         const std::string &newName = std::string());

		/**
		 * Parameterized constructor.
		 * @param newWidth New width of the rectangle object (in pixels).
		 * @param newHeight New height of the rectangle object (in pixels).
		 * @param newPosition Position of the rectangle object in the layer (in
		 * pixels).
		 * @param newName Name of the rectangle object, if it has one.
		 */
		explicit RectangleObject(float newWidth, float newHeight,
		                         const Vector2 &newPosition = Vector2(),
		                         const std::string &newName = std::string());

		/**
		 * Default and parameterized constructor.
		 * @param newSize New size of the rectangle object (in pixels).
		 * @param newXPosition Horizontal position of the rectangle object on
		 * the object layer (in pixels).
		 * @param newYPosition Vertical position of the rectangle object on the
		 * object layer (in pixels).
		 * @param newName Name of the rectangle object, if it has one.
		 */
		explicit RectangleObject(const Vector2 &newSize,
		                         float newXPosition, float newYPosition,
		                         const std::string &newName = std::string());

		/**
		 * Parameterized constructor.
		 * @param newWidth New width of the rectangle object (in pixels).
		 * @param newHeight New height of the rectangle object (in pixels).
		 * @param newXPosition Horizontal position of the rectangle object on
		 * the object layer (in pixels).
		 * @param newYPosition Vertical position of the rectangle object on the
		 * object layer (in pixels).
		 * @param newName Name of the rectangle object, if it has one.
		 */
		explicit RectangleObject(float newWidth, float newHeight,
		                         float newXPosition, float newYPosition,
		                         const std::string &newName = std::string());

		/**
		 * Copy constructor.
		 * @param src RectangleObject to make a copy of.
		 */
		RectangleObject(const RectangleObject &src);

		/**
		 * Destructor.
		 */
		~RectangleObject();

		/**
		 * Assignment operator.
		 * @param src RectangleObject to copy.
		 * @return Reference to the modified RectangleObject.
		 */
		RectangleObject &operator=(const RectangleObject &src);

		/// Size of the rectangle object.
		Vector2 size;
	};

}

#endif // RB_RECTANGLE_OBJECT_H
#endif
