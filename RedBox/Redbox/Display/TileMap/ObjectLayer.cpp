#include "ObjectLayer.h"

#include <algorithm>

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

	LineObject *ObjectLayer::addLine(const std::string &newLineName,
	                                 const Vector2 &newPosition,
	                                 bool overwrite) {
		LineObject *result = getLine(newLineName);

		if (result) {
			if (overwrite) {
				removeLine(result);
				addLine(newLineName, newPosition, false);
			}

		} else {
			lines.push_back(new LineObject(newLineName, newPosition, *this));

			if (!newLineName.empty()) {
				dirtyLineNames = true;
			}

			result = lines.back();
		}

		return result;
	}

	void ObjectLayer::removeLine(const std::string &lineName) {
		removeLine(getLine(lineName));
	}

	void ObjectLayer::removeLine(const LineObject *toRemove) {
		if (toRemove) {
			LineContainer::iterator found = std::find(lines.begin(), lines.end(), toRemove);

			if (found != lines.end()) {
				if (!toRemove->getName().empty()) {
					dirtyLineNames = true;
				}

				delete *found;
				lines.erase(found);
			}
		}
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

	PolygonObject *ObjectLayer::addPolygon(const std::string &newPolygonName,
	                                       const Vector2 &newPosition,
	                                       bool overwrite) {
		PolygonObject *result = getPolygon(newPolygonName);

		if (result) {
			if (overwrite) {
				removePolygon(result);
				addPolygon(newPolygonName, newPosition, false);
			}

		} else {
			polygons.push_back(new PolygonObject(newPolygonName, newPosition, *this));

			if (!newPolygonName.empty()) {
				dirtyPolygonNames = true;
			}

			result = polygons.back();
		}

		return result;
	}

	void ObjectLayer::removePolygon(const std::string &polygonName) {
		removePolygon(getPolygon(polygonName));
	}

	void ObjectLayer::removePolygon(const PolygonObject *toRemove) {
		if (toRemove) {
			PolygonContainer::iterator found = std::find(polygons.begin(), polygons.end(), toRemove);

			if (found != polygons.end()) {
				if (!toRemove->getName().empty()) {
					dirtyPolygonNames = true;
				}

				delete *found;
				polygons.erase(found);
			}
		}
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

	RectangleObject *ObjectLayer::addRectangle(const std::string &newRectangleName,
	                                           const Vector2 &newPosition,
	                                           const Vector2 &newSize,
	                                           bool overwrite) {
		RectangleObject *result = getRectangle(newRectangleName);

		if (result) {
			if (overwrite) {
				removeRectangle(result);
				addRectangle(newRectangleName, newPosition, newSize, false);
			}

		} else {
			rectangles.push_back(new RectangleObject(newRectangleName, newPosition, *this, newSize));

			if (!newRectangleName.empty()) {
				dirtyRectangleNames = true;
			}

			result = rectangles.back();
		}

		return result;
	}

	void ObjectLayer::removeRectangle(const std::string &rectangleName) {
		removeRectangle(getRectangle(rectangleName));
	}

	void ObjectLayer::removeRectangle(const RectangleObject *toRemove) {
		if (toRemove) {
			RectangleContainer::iterator found = std::find(rectangles.begin(), rectangles.end(), toRemove);

			if (found != rectangles.end()) {
				if (!toRemove->getName().empty()) {
					dirtyRectangleNames = true;
				}

				delete *found;
				rectangles.erase(found);
			}
		}
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
		tiles(), lineNames(), dirtyLineNames(true), polygonNames(),
		dirtyPolygonNames(true), rectangleNames(), dirtyRectangleNames(true),
		tileNames(), dirtyTileNames(true) {
		// We copy the line objects.
		for (LineContainer::const_iterator i = src.lines.begin();
		     i != src.lines.end(); ++i) {
			lines.push_back(new LineObject(*(*i), *this));
		}

		// We copy the polygon objects.
		for (PolygonContainer::const_iterator i = src.polygons.begin();
		     i != src.polygons.end(); ++i) {
			polygons.push_back(new PolygonObject(*(*i), *this));
		}

		// We copy the rectangle objects.
		for (RectangleContainer::const_iterator i = src.rectangles.begin();
		     i != src.rectangles.end(); ++i) {
			rectangles.push_back(new RectangleObject(*(*i), *this));
		}

		// We copy the tile objects.
		for (TileContainer::const_iterator i = src.tiles.begin();
		     i != src.tiles.end(); ++i) {
			tiles.push_back(new TileObject(*(*i), *this));
		}
	}

	ObjectLayer::~ObjectLayer() {
	}
}
