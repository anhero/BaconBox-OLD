#if 0
/**
 * @file
 * @ingroup TileMap
 */
#ifndef RB_POLYGON_OBJECT_H
#define RB_POLYGON_OBJECT_H

#include "TileMapObject.h"
#include "StandardVertexArray.h"

namespace RedBox {
	/**
	 * Represents a polygon object in an object layer.
	 * @ingroup TileMap
	 */
	class PolygonObject : public TileMapObject {
	public:
		/**
		 * Default and parameterized constructor.
		 * @param newPosition Position of the polygon object in the layer (in
		 * pixels).
		 * @param newName Name of the polygon object, if it has one.
		 */
		explicit PolygonObject(const Vector2 &newPosition = Vector2(),
		                       const std::string &newName = std::string());

		/**
		 * Parameterized constructor.
		 * @param newXPosition Horizontal position of the polygon object on the
		 * object layer (in pixels).
		 * @param newYPosition Vertical position of the polygon object on the
		 * object layer (in pixels).
		 * @param newName Name of the polygon object, if it has one.
		 */
		PolygonObject(float newXPosition,
		              float newYPosition,
		              const std::string &newName = std::string());

		/**
		 * Copy constructor.
		 * @param src PolygonObject to make a copy of.
		 */
		PolygonObject(const PolygonObject &src);

		/**
		 * Destructor.
		 */
		~PolygonObject();

		/**
		 * Assignment operator.
		 * @param src PolygonObject to copy.
		 * @return Reference to the modified PolygonObject.
		 */
		PolygonObject &operator=(const PolygonObject &src);

		/// Vertices that make up the polygon.
		StandardVertexArray vertices;
	};

}

#endif // RB_POLYGON_OBJECT_H
#endif
