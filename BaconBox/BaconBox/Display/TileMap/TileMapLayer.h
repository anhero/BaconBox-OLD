/**
 * @file
 * @ingroup TileMap
 */
#ifndef RB_TILE_MAP_LAYER_H
#define RB_TILE_MAP_LAYER_H

#include <stdint.h>

#include "TileMapEntity.h"
#include "TileIdRange.h"

namespace BaconBox {
	class ObjectLayer;
	class TileLayer;
	class TileMap;

	/**
	 * Represents a tile map layer. ObjectLayer and TileLayer are derived from
	 * this class.
	 * @see BaconBox::TileLayer
	 * @see BaconBox::ObjectLayer
	 * @see BaconBox::TileMap
	 * @ingroup TileMap
	 */
	class TileMapLayer : public TileMapEntity {
		friend class TileMap;
	public:

		/**
		 * Sets the name of the tile map layer. Does nothing if there is already
		 * a layer with the same name in the parent tile map.
		 * @param newName New name to give to the tile map layer.
		 * @see BaconBox::TileMapEntity::name
		 */
		void setName(const std::string &newName);

		/**
		 * Gets the instance as an object layer, if it is one.
		 * @return Pointer to the instance as an object layer, NULL if it's not
		 * an object layer.
		 */
		virtual ObjectLayer *asObjectLayer();

		/**
		 * Gets the instance as an object layer, if it is one.
		 * @return Pointer to the instance as an object layer, NULL if it's not
		 * an object layer.
		 */
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

		/**
		 * Gets the opacity of the tile layer.
		 * @return Opacity of the tile layer, can be from 0 to 255.
		 */
		uint8_t getOpacity() const;

		/**
		 * Sets the opacity of the tile layer.
		 * @param newOpacity New opacity of the tile layer, can be from 0 to
		 * 255. If the given value is out of those bounds, it is set to the
		 * closer bound (to 0 if it's a negative value, to 255 if it's higher
		 * than 255).
		 */
		void setOpacity(int32_t newOpacity);

		/**
		 * Checks wether or not the tile layer is visible.
		 * @return True if the tile layer is visible, false if not.
		 * @see BaconBox::TileLayer::visible
		 */
		bool isVisible() const;

		/**
		 * Sets wether or not the tile layer is visible.
		 * @param newVisible New boolean value to set if the tile layer is
		 * visible or not.
		 * @see BaconBox::TileLayer::visible
		 */
		void setVisible(bool newVisible);
		
		/// Const reference to the parent map that contains this layer.
		const TileMap &parentMap;
	protected:
		/**
		 * Paremeterized constructor.
		 * @param newName Name of the layer, can be empty.
		 * @param newParentMap Reference to the map that contains this layer.
		 * @param newOpacity Opacity of the layer.
		 * @param newVisible Wether or not the layer is visible.
		 * @see BaconBox::TileMapEntity::name
		 */
		TileMapLayer(const std::string &newName,
		             const TileMap &newParentMap,
		             int32_t newOpacity,
		             bool newVisible);

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
		 * Applies the destructiof id's of a tileset.
		 * @param toDestroy Range of tile id's to destroy. All tile id's in this
		 * range are reset to 0. All tile id's above the range are reduced by
		 * the range's length.
		 */
		virtual void applyTilesetDestruction(const TileIdRange &toDestroy) = 0;

		/**
		 * Gets a duplicate of the tile map layer.
		 * @param newParentMap Reference to the map that contains the clone.
		 * @return Pointer to a duplicate of the tile map layer. The caller is
		 * responsible for deleting this instance.
		 */
		virtual TileMapLayer *clone(const TileMap &newParentMap) const = 0;
	private:
		TileMapLayer(const TileMapLayer &src);
		TileMapLayer &operator=(const TileMapLayer &src);

		/// Opacity of the tile layer.
		uint8_t opacity;

		/// Used to determine wether or not the tile layer is visible.
		bool visible;
	};
}

#endif
