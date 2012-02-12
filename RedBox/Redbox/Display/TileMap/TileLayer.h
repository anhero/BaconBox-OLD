/**
 * @file
 * @ingroup TileMap
 */
#ifndef RB_TILE_LAYER_H
#define RB_TILE_LAYER_H

#include <stdint.h>

#include <vector>

#include "TileMapLayer.h"
#include "TileCoordinate.h"

namespace RedBox {
	class TileLayer : public TileMapLayer {
	public:
		typedef std::vector<unsigned int> DataContainer;

		explicit TileLayer(const std::string &newName = std::string());

		TileLayer(const TileLayer &src);

		~TileLayer();

		TileLayer &operator=(const TileLayer &src);

		void setColor(const Color &newColor);

		void render();

		void mask();

		void unmask();

		Maskable *getMask() const;

		void setMask(Maskable *newMask, bool inverted = false);

		void update();

		float getWidth() const;

		float getHeight() const;

		const TileCoordinate &getSizeInTiles() const;

		void setSizeInTiles(const TileCoordinate &newSizeInTiles);

		int getWidthInTiles() const;

		void setWidthInTiles(int newWidthInTiles);

		int getHeightInTiles() const;

		void setHeightInTiles(int newHeightInTiles);

		TileLayer *asTileLayer();

		const TileLayer *asTileLayer() const;

		TileLayer *clone() const;

		unsigned int getTileId(const TileCoordinate &tileCoordinate) const;

		unsigned int getTileId(int xTileCoordinate, int yTileCoordinate) const;

		void setTileId(const TileCoordinate &tileCoordinate, unsigned int newTileId);

		void setTileId(int xTileCoordinate, int yTileCoordinate, unsigned int newTileId);
	private:
		TileCoordinate sizeInTiles;

		DataContainer data;

		int32_t opacity;

		bool visible;
	};
}

#endif // RB_TILE_LAYER_H
