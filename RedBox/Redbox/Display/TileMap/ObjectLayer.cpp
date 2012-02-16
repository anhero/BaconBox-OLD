#if 0
#include "ObjectLayer.h"

namespace RedBox {
	ObjectLayer::ObjectLayer() : lines(), polygons(), rectangles(), tiles(),
		lineNames(), polygonNames(), rectangleNames(), tileNames(),
		visible(true), color(Color::WHITE) {
	}

	ObjectLayer::ObjectLayer(const ObjectLayer &src) : lines(src.lines),
		polygons(src.polygons), rectangles(src.rectangles), tiles(src.tiles),
		visible(src.visible), color(src.color) {
		refreshAllNames();
	}

	ObjectLayer &ObjectLayer::operator=(const ObjectLayer &src) {

		if (this != &src) {
			lines = src.lines;
			polygons = src.polygons;
			rectangles = src.rectangles;
			tiles = src.tiles;
			visible = src.visible;
			color = src.color;
			refreshAllNames();
		}

		return *this;
	}

	ObjectLayer::LineContainer &ObjectLayer::getLines() {
		return lines;
	}

	const ObjectLayer::LineContainer &ObjectLayer::getLines() const {
		return lines;
	}

	ObjectLayer::PolygonContainer &ObjectLayer::getPolygons() {
		return polygons;
	}

	const ObjectLayer::PolygonContainer &ObjectLayer::getPolygons() const {
		return polygons;
	}

	ObjectLayer::RectangleContainer &ObjectLayer::getRectangles() {
		return rectangles;
	}

	const ObjectLayer::RectangleContainer &ObjectLayer::getRectangles() const {
		return rectangles;
	}

	ObjectLayer::TileContainer &ObjectLayer::getTiles() {
		return tiles;
	}

	const ObjectLayer::TileContainer &ObjectLayer::getTiles() const {
		return tiles;
	}

	ObjectLayer::LineNameMap::mapped_type ObjectLayer::getLine(const LineNameMap::key_type &lineName) {
		LineNameMap::iterator found = lineNames.find(lineName);
		return (found != lineNames.end()) ? (found->second) : (NULL);
	}

	const ObjectLayer::LineNameMap::mapped_type ObjectLayer::getLine(const LineNameMap::key_type &lineName) const {
		LineNameMap::const_iterator found = lineNames.find(lineName);
		return (found != lineNames.end()) ? (found->second) : (NULL);
	}

	ObjectLayer::PolygonNameMap::mapped_type ObjectLayer::getPolygon(const PolygonNameMap::key_type &polygonName) {
		PolygonNameMap::iterator found = polygonNames.find(polygonName);
		return (found != polygonNames.end()) ? (found->second) : (NULL);
	}

	const ObjectLayer::PolygonNameMap::mapped_type ObjectLayer::getPolygon(const PolygonNameMap::key_type &polygonName) const {
		PolygonNameMap::const_iterator found = polygonNames.find(polygonName);
		return (found != polygonNames.end()) ? (found->second) : (NULL);
	}

	ObjectLayer::RectangleNameMap::mapped_type ObjectLayer::getRectangle(const RectangleNameMap::key_type &rectangleName) {
		RectangleNameMap::iterator found = rectangleNames.find(rectangleName);
		return (found != rectangleNames.end()) ? (found->second) : (NULL);
	}

	const ObjectLayer::RectangleNameMap::mapped_type ObjectLayer::getRectangle(const RectangleNameMap::key_type &rectangleName) const {
		RectangleNameMap::const_iterator found = rectangleNames.find(rectangleName);
		return (found != rectangleNames.end()) ? (found->second) : (NULL);
	}

	ObjectLayer::TileNameMap::mapped_type ObjectLayer::getTile(const TileNameMap::key_type &tileName) {
		TileNameMap::iterator found = tileNames.find(tileName);
		return (found != tileNames.end()) ? (found->second) : (NULL);
	}

	const ObjectLayer::TileNameMap::mapped_type ObjectLayer::getTile(const TileNameMap::key_type &tileName) const {
		TileNameMap::const_iterator found = tileNames.find(tileName);
		return (found != tileNames.end()) ? (found->second) : (NULL);
	}

	void ObjectLayer::refreshAllNames() {
		refreshLineNames();
		refreshPolygonNames();
		refreshRectangleNames();
		refreshTileNames();
	}

	void ObjectLayer::refreshLineNames() {
		refreshNames(lines, lineNames);
	}

	void ObjectLayer::refreshRectangleNames() {
		refreshNames(rectangles, rectangleNames);
	}

	void ObjectLayer::refreshPolygonNames() {
		refreshNames(polygons, polygonNames);
	}

	void ObjectLayer::refreshTileNames() {
		refreshNames(tiles, tileNames);
	}

	bool ObjectLayer::isVisible() const {
		return visible;
	}

	void ObjectLayer::setVisible(bool newVisible) {
		visible = newVisible;
	}

	const Color &ObjectLayer::getColor() const {
		return color;
	}

	void ObjectLayer::setColor(const Color &newColor) {
		color = newColor;
	}

	uint8_t ObjectLayer::getAlpha() const {
		return color.getAlpha();
	}

	void ObjectLayer::setAlpha(int32_t newAlpha) {
		color.setAlpha(newAlpha);
	}
}
#endif
