/**
 * @file
 * @ingroup TileMap
 */
#ifndef RB_RECTANGLE_OBJECT_H
#define RB_RECTANGLE_OBJECT_H

#include "TileMapObject.h"
#include "Vector2.h"

namespace RedBox {
	/**
	 * Represents a rectangle object in an object layer in a tile map.
	 * @ingroup TileMap
	 * @see RedBox::ObjectLayer
	 */
	class RectangleObject : public TileMapObject {
	public:
		/**
		 * Default and parameterized constructor.
		 * @param newName Name of the rectangle object, if it has one.
		 * @param newPosition Position of the rectangle object in the layer (in
		 * pixels).
		 * @param newSize New size of the rectangle object (in pixels).
		 */
		explicit RectangleObject(const std::string &newName = std::string(),
		                         const Vector2 &newPosition = Vector2(),
		                         const Vector2 &newSize = Vector2());
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

		/**
		 * Gets the body's size. Can be overloaded for performance.
		 * @return Vector2 containing the width and height of the body.
		 */
		const Vector2 getSize() const;

		/**
		 * Sets the size of the rectangle object.
		 * @param newSize New width and height of the rectangle object.
		 * @see RedBox::RectangleObject::size
		 */
		void setSize(const Vector2 &newSize);

		/**
		 * Sets the size of the rectangle object.
		 * @param newWidth New width of the rectangle object.
		 * @param newHeight New height of the rectangle object.
		 * @see RedBox::RectangleObject::size
		 */
		void setSize(float newWidth, float newHeight);

		/**
		 * Gets the body's width.
		 * @return Width in pixels (by default).
		 */
		float getWidth() const;

		/**
		 * Sets the width of the rectangle object.
		 * @param newWidth New width of the rectangle object.
		 * @see RedBox::RectangleObject::size
		 */
		void setWidth(float newWidth);

		/**
		 * Gets the body's height.
		 * @return Height in pixels (by default).
		 */
		float getHeight() const;

		/**
		 * Sets the height of the rectangle object.
		 * @param newHeight New height of the rectangle object.
		 * @see RedBox::RectangleObject::size
		 */
		void setHeight(float newHeight);
	private:
		/// Width and height of the rectangle object.
		Vector2 size;
	};

}

#endif // RB_RECTANGLE_OBJECT_H
