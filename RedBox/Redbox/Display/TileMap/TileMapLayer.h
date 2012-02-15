/**
 * @file
 * @ingroup TileMap
 */
#ifndef RB_TILE_MAP_LAYER_H
#define RB_TILE_MAP_LAYER_H

#include "Layerable.h"
#include "Colorable.h"
#include "Positionable.h"
#include "TileMapEntity.h"

namespace RedBox {
	class ObjectLayer;
	class TileLayer;
	class TileMap;

	/**
	 * Represents a tile map layer. ObjectLayer and TileLayer are derived from
	 * this class.
	 * @see RedBox::TileLayer
	 * @see RedBox::ObjectLayer
	 * @see RedBox::TileMap
	 * @ingroup TileMap
	 */
	class TileMapLayer : public TileMapEntity {
		friend class TileMap;
	public:

		/**
		 * Sets the name of the tile map layer.
		 * @param newName New name to give to the tile map layer.
		 * @see RedBox::TileMapEntity::name
		 */
		void setName(const std::string &newName);

		virtual ObjectLayer *asObjectLayer();
		virtual const ObjectLayer *asObjectLayer() const;

		/**
		 * Gets the instance as a tile layer, if it is one.
		 * @return Pointer to the instance as a tile layer, NULL if it's not a
		 * tile layer.
		 */
		virtual TileLayer *asTileLayer();

		/**
		 * Gets the instance as a tile layer, if it is one.
		 * @return Pointer to the instance as a tile layer, NULL if it's not a
		 * tile layer.
		 */
		virtual const TileLayer *asTileLayer() const;
	protected:
		/**
		 * Paremeterized constructor.
		 * @param newParentMap Reference to the map that contains this layer.
		 * @param newName Name of the layer, can be empty.
		 * @see RedBox::TileMapEntity::name
		 */
		explicit TileMapLayer(const TileMap &newParentMap,
		                      const std::string &newName = std::string());

		/**
		 * Copy constructor.
		 * @param src Tile map layer to make a copy of.
		 * @param newParentMap Parent map of the tile map layer.
		 */
		TileMapLayer(const TileMapLayer &src, const TileMap &newParentMap);

		/**
		 * Destructor.
		 */
		virtual ~TileMapLayer();

		/**
		 * Gets a duplicate of the tile map layer.
		 * @param newParentMap Reference to the map that contains the clone.
		 * @return Pointer to a duplicate of the tile map layer. The caller is
		 * responsible for deleting this instance.
		 */
		virtual TileMapLayer *clone(const TileMap &newParentMap) const = 0;

		/// Const reference to the parent map that contains this layer.
		const TileMap &parentMap;
	private:
		TileMapLayer(const TileMapLayer &src);
		TileMapLayer &operator=(const TileMapLayer &src);
	};
}

#endif
