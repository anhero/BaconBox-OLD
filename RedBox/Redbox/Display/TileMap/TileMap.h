/**
 * @file
 * @ingroup TileMap
 */
#ifndef RB_TILE_MAP_H
#define RB_TILE_MAP_H

#include <map>
#include <utility>
#include <string>
#include <vector>

#include "TileLayer.h"
#include "TileSet.h"

namespace RedBox {
	class TileMap {
	public:
		/**
		 * Contains the tile set informations mapped by their name. The first
		 * element of the pair is the first grid ID of the tile set.
		 */
		typedef std::map<std::string, std::pair<unsigned int, TileSet> > TileSetMap;

		/// Vector of map layers.
		typedef std::vector<TileLayer> TileLayerVector;
	private:
		/// Map's tile sets.
		TileSetMap tileSets;

		/// Map's layers.
		TileLayerVector layers;
	};
}

#endif
