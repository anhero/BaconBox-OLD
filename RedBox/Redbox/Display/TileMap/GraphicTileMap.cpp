#include "GraphicTileMap.h"

namespace RedBox {
	GraphicTileMap::GraphicTileMap(const Vector2 &startingPosition) :
		Transformable(startingPosition) {
	}

	GraphicTileMap::GraphicTileMap(const TileMap &map,
	                               const Vector2 &startingPosition) :
		Transformable(startingPosition) {
		construct(map);
	}

	GraphicTileMap::GraphicTileMap(const GraphicTileMap &src) :
		Transformable(src), layers(src.layers.size(), NULL) {
		Container::iterator dstLayer = layers.begin();
		Container::const_iterator srcLayer = src.layers.begin();

		while (dstLayer != layers.end()) {
			*dstLayer = (*srcLayer)->clone();
			++dstLayer;
			++srcLayer;
		}
	}

	GraphicTileMap::~GraphicTileMap() {
		free();
	}

	GraphicTileMap &GraphicTileMap::operator=(const GraphicTileMap &src) {
		this->Transformable::operator=(src);

		if (this != &src) {
			free();
			layers.clear();

			layers.resize(src.layers.size(), NULL);

			Container::iterator dstLayer = layers.begin();
			Container::const_iterator srcLayer = src.layers.begin();

			while (dstLayer != layers.end()) {
				*dstLayer = (*srcLayer)->clone();
				++dstLayer;
				++srcLayer;
			}
		}

		return *this;
	}
}
