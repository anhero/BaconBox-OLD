/**
 * @file
 * @ingroup TileMap
 */
#ifndef RB_TILE_MAP_VERTEX_ARRAY_H
#define RB_TILE_MAP_VERTEX_ARRAY_H

#include "BaconBox/Display/TileMap/TileMapObject.h"
#include "BaconBox/Display/Shapable.h"
#include "BaconBox/Display/StandardVertexArray.h"

namespace BaconBox {
	/**
	 * Represents an array of vertices used in an object layer in a tile map.
	 * Used for line and polygon objects.
	 * @ingroup TileMap
	 */
	class TileMapVertexArray : public TileMapObject,
		public Shapable<StandardVertexArray> {
	public:
		using TileMapObject::move;

		/**
		 * Moves the Positionable horizontally and vertically.
		 * @param xDelta Value to add to the Positionable's horizontal position
		 * (in pixels). Positive value moves the Positionable to the right and a
		 * negative value moves the Positionable to the left.
		 * @param yDelta Value to add to the Positionable's vertical position (in
		 * pixels). Positive value moves the Positionable down and a negative
		 * value moves the Positionable up.
		 * @see BaconBox::Positionable::move(const Vector2& delta);
		 * @see BaconBox::Positionable::position
		 */
		void move(float xDelta, float yDelta);

		/**
		 * Gets the geometric center of the body. Same as the position center
		 * in symmetrical polygons, but must be overloaded for classes that
		 * support irregular polygons.
		 * @return Geometric center of the body (barycenter).
		 */
		const Vector2 getCentroid() const;

		/**
		 * Gets the body's size. Can be overloaded for performance.
		 * @return Vector2 containing the width and height of the body.
		 */
		const Vector2 getSize() const;

		/**
		 * Gets the body's width.
		 * @return Width in pixels (by default).
		 */
		float getWidth() const;

		/**
		 * Gets the body's height.
		 * @return Height in pixels (by default).
		 */
		float getHeight() const;
	protected:
		/**
		 * Default and parameterized constructor.
		 * @param newName Name of the polygon/line.
		 * @param newPosition Starting position of the tile map vertex array.
		 * @param newParentLayer Object layer that owns the tile map object.
		 */
		TileMapVertexArray(const std::string &newName,
		                   const Vector2 &newPosition,
		                   const ObjectLayer &newParentLayer);

		/**
		 * Copy constructor
		 * @param src Tile map vertex array to make a copy of.
		 * @param newParentLayer Object layer that owns the tile map object.
		 */
		TileMapVertexArray(const TileMapVertexArray &src,
		                   const ObjectLayer &newParentLayer);

		/**
		 * Destructor.
		 */
		virtual ~TileMapVertexArray();
	};
}

#endif
