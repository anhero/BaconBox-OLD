#include "ObjectLayer.h"

#include "TileObject.h"
#include "LineObject.h"
#include "PolygonObject.h"
#include "RectangleObject.h"

namespace RedBox {
	const ObjectLayer::LineContainer &ObjectLayer::getLines() const {
		return lines;
	}

	const ObjectLayer::PolygonContainer &ObjectLayer::getPolygons() const {
		return polygons;
	}

	const ObjectLayer::RectangleContainer &ObjectLayer::getRectangles() const {
		return rectangles;
	}

	const ObjectLayer::TileContainer &ObjectLayer::getTiles() const {
		return tiles;
	}

	ObjectLayer::ObjectLayer(const std::string &newName,
	                         const TileMap &newParentMap,
	                         int32_t newOpacity,
	                         bool newVisible) :
		TileMapLayer(newName, newParentMap, newOpacity, newVisible), lines(),
		polygons(), rectangles(), tiles(), lineNames(), dirtyLineNames(false),
		polygonNames(), dirtyPolygonNames(false), rectangleNames(),
		dirtyRectangleNames(false), tileNames(), dirtyTileNames(false) {
	}

	ObjectLayer::ObjectLayer(const ObjectLayer &src,
	                         const TileMap &newParentMap) :
		TileMapLayer(src, newParentMap), lines(), polygons(), rectangles(),
		tiles(), lineNames(), dirtyLineNames(false), polygonNames(),
		dirtyPolygonNames(false), rectangleNames(), dirtyRectangleNames(false),
		tileNames(), dirtyTileNames(false) {
	}

	ObjectLayer::~ObjectLayer() {
	}
}
