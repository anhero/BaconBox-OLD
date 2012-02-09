/**
 * @file
 * @ingroup TileMap
 */
#ifndef RB_TILE_LAYER_H
#define RB_TILE_LAYER_H

#include <map>

#include "TileMapLayer.h"
#include "TileCoordinate.h"

namespace RedBox {
	class TileLayer : public TileMapLayer {
	public:
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
	private:
		TileCoordinate sizeInTiles;
	};
}

#endif // RB_TILE_LAYER_H
