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

	LineObject *ObjectLayer::getLine(const std::string &lineName) {
		if (dirtyLineNames) {
			refreshNames(lines, lineNames);
		}

		return getObject(lineNames, lineName);
	}

	const LineObject *ObjectLayer::getLine(const std::string &lineName) const {
		if (dirtyLineNames) {
			refreshNames(lines, lineNames);
		}

		return getObject(lineNames, lineName);
	}

	PolygonObject *ObjectLayer::getPolygon(const std::string &polygonName) {
		if (dirtyPolygonNames) {
			refreshNames(polygons, polygonNames);
		}

		return getObject(polygonNames, polygonName);
	}

	const PolygonObject *ObjectLayer::getPolygon(const std::string &polygonName) const {
		if (dirtyPolygonNames) {
			refreshNames(polygons, polygonNames);
		}

		return getObject(polygonNames, polygonName);
	}

	RectangleObject *ObjectLayer::getRectangle(const std::string &rectangleName) {
		if (dirtyRectangleNames) {
			refreshNames(rectangles, rectangleNames);
		}

		return getObject(rectangleNames, rectangleName);
	}

	const RectangleObject *ObjectLayer::getRectangle(const std::string &rectangleName) const {
		if (dirtyRectangleNames) {
			refreshNames(rectangles, rectangleNames);
		}

		return getObject(rectangleNames, rectangleName);
	}

	TileObject *ObjectLayer::getTile(const std::string &tileName) {
		if (dirtyTileNames) {
			refreshNames(tiles, tileNames);
		}

		return getObject(tileNames, tileName);
	}

	const TileObject *ObjectLayer::getTile(const std::string &tileName) const {
		if (dirtyTileNames) {
			refreshNames(tiles, tileNames);
		}

		return getObject(tileNames, tileName);
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
