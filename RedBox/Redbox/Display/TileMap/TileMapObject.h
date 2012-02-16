/**
 * @file
 * @ingroup TileMap
 */
#ifndef RB_TILE_MAP_OBJECT_H
#define RB_TILE_MAP_OBJECT_H

#include "Vector2.h"
#include "TileMapEntity.h"

namespace RedBox {
	/**
	 * Base class for objects in an object layer for a tile map.
	 * @ingroup TileMap
	 */
	class TileMapObject : public TileMapEntity {
	public:
		/**
		 * Default and parameterized constructor.
		 * @param newName Name of the tile map object, if it has one.
		 * @param newPosition Position of the tile map object in the layer (in
		 * pixels).
		 * @see RedBox::TileMapObject::position
		 */
		explicit TileMapObject(const std::string &newName = std::string(),
							   const Vector2 &newPosition = Vector2());

		/**
		 * Parameterized constructor.
		 * @param newName Name of the tile map object, if it has one.
		 * @param newXPosition Horizontal position of the tile map object on the
		 * object layer (in pixels).
		 * @param newYPosition Vertical position of the tile map object on the
		 * object layer (in pixels).
		 * @see RedBox::TileMapObject::position
		 */
		TileMapObject(const std::string &newName,
					  float newXPosition,
					  float newYPosition);

		/**
		 * Copy constructor.
		 * @param src Tile map object to make a copy of.
		 */
		TileMapObject(const TileMapObject &src);

		/**
		 * Destructor.
		 */
		virtual ~TileMapObject();

		/**
		 * Assignment operator.
		 * @param src Tile map object to copy.
		 * @return Reference to the modified tile map object.
		 */
		TileMapObject &operator=(const TileMapObject &src);

		/**
		 * Gets the object's position
		 * @return Position of the object relative to the tile map.
		 * @see RedBox::TileMapObject::position
		 */
		const Vector2 &getPosition() const;

		/**
		 * Sets the object's position.
		 * @param newPosition New position of the object relative to the tile
		 * map.
		 * @see RedBox::TileMapObject::position
		 */
		void setPosition(const Vector2 &newPosition);

		/**
		 * Sets the object's position.
		 * @param newXPosition New horizontal position of the object relative to
		 * the tile map.
		 * @param nweYPosition New vertical position of the object relative to
		 * the tile map.
		 * @see RedBox::TileMapObject::position
		 */
		void setPosition(float newXPosition, float newYPosition);

		/**
		 * Gets the object's horizontal position.
		 * @return Horizontal position of the object relative to the tile map.
		 * @see RedBox::TileMapObject::position
		 */
		float getXPosition() const;

		/**
		 * Sets the object's horizontal position.
		 * @param newXPosition New horizontal position of the object relative to
		 * the tile map.
		 * @see RedBox::TileMapObject::position
		 */
		void setXPosition(float newXPosition);

		/**
		 * Gets the object's vertical position.
		 * @return Vertical position of the object relative to the tile map.
		 * @see RedBox::TileMapObject::position
		 */
		float getYPosition() const;


		/**
		 * Sets the object's vertical position.
		 * @param newYPosition New vertical position of the object relative to
		 * the tile map.
		 * @see RedBox::TileMapObject::position
		 */
		void setYPosition(float newYPosition);
	private:
		/// Position of the object relative to the tile map.
		Vector2 position;
	};

}

#endif // RB_TILE_MAP_OBJECT_H
