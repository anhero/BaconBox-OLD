/**
 * @file
 * @ingroup TileMap
 */
#ifndef RB_LINE_OBJECT_H
#define RB_LINE_OBJECT_H

#include "BaconBox/Display/TileMap/TileMapVertexArray.h"

namespace BaconBox {
	class LineObject : public TileMapVertexArray {
		friend class ObjectLayer;
	public:
		/**
		 * Sets the name of the line object. Does nothing if another line object
		 * with the same name exists in the parent layer.
		 * @param newName New name to give to the entity.
		 * @see BaconBox::TileMapEntity::name
		 */
		void setName(const std::string &newName);
	private:
		/**
		 * Default and parameterized constructor.
		 * @param newName Name of the polygon/line.
		 * @param newPosition Starting position of the tile map vertex array.
		 * @param newParentLayer Object layer that owns the tile map object.
		 */
		LineObject(const std::string &newName,
		           const Vector2 &newPosition,
		           const ObjectLayer &newParentLayer);

		/**
		 * Copy constructor
		 * @param src Tile map vertex array to make a copy of.
		 * @param newParentLayer Object layer that owns the tile map object.
		 */
		LineObject(const LineObject &src,
		           const ObjectLayer &newParentLayer);

		/**
		 * Destructor.
		 */
		virtual ~LineObject();
	};
}

#endif // RB_POLYGON_OBJECT_H
