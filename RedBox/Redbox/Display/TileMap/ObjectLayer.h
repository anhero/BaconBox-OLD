/**
 * @file
 * @ingroup TileMap
 */
#ifndef RB_OBJECT_LAYER_H
#define RB_OBJECT_LAYER_H

#include <map>
#include <list>

#include "TileObject.h"
#include "LineObject.h"
#include "PolygonObject.h"
#include "RectangleObject.h"

namespace RedBox {
	/**
	 * Represents a layer of objects in a tile map. Can contain lines, polygons,
	 * rectangles and tiles. The only object type to have a graphic is the tile.
	 * But, you could determine a custom system to recognize the objects and
	 * put graphics yourself in your game.
	 * @ingroup TileMap
	 */
	class ObjectLayer {
	public:
		typedef std::list<LineObject> LineContainer;
		typedef std::list<PolygonObject> PolygonContainer;
		typedef std::list<RectangleObject> RectangleContainer;
		typedef std::list<TileObject> TileContainer;

		typedef std::map<std::string, LineObject *> LineNameMap;
		typedef std::map<std::string, PolygonObject *> PolygonNameMap;
		typedef std::map<std::string, RectangleObject *> RectangleNameMap;
		typedef std::map<std::string, TileObject *> TileNameMap;

		/**
		 * Default constructor.
		 */
		ObjectLayer();

		/**
		 * Copy constructor.
		 * @param src ObjectLayer to make a copy of.
		 */
		ObjectLayer(const ObjectLayer &src);

		/**
		 * Assignment operator.
		 * @param src ObjectLayer to copy.
		 * @return Reference to the modified ObjectLayer.
		 */
		ObjectLayer &operator=(const ObjectLayer &src);

		/**
		 * Gets the line objects.
		 * @return Reference to the list of line objects.
		 * @see RedBox::ObjectLayer::lines
		 */
		LineContainer &getLines();

		/**
		 * Gets the line objects.
		 * @return Const reference to the list of line objects.
		 * @see RedBox::ObjectLayer::lines
		 */
		const LineContainer &getLines() const;

		/**
		 * Gets the polygon objects.
		 * @return Reference to the list of polygon objects.
		 * @see RedBox::ObjectLayer::objects
		 */
		PolygonContainer &getPolygons();

		/**
		 * Gets the polygon objects.
		 * @return Const reference to the list of polygon objects.
		 * @see RedBox::ObjectLayer::objects
		 */
		const PolygonContainer &getPolygons() const;

		/**
		 * Gets the rectangle objects.
		 * @return Reference to the list of rectangle objects.
		 * @see RedBox::ObjectLayer::rectangles
		 */
		RectangleContainer &getRectangles();

		/**
		 * Gets the rectangle objects.
		 * @return Const reference to the list of rectangle objects.
		 * @see RedBox::ObjectLayer::rectangles
		 */
		const RectangleContainer &getRectangles() const;

		/**
		 * Gets the tile objects.
		 * @return Reference to the list of tile objects.
		 * @see RedBox::ObjectLayer::tiles
		 */
		TileContainer &getTiles();

		/**
		 * Gets the tile objects.
		 * @return Const reference to the list of tile objects.
		 * @see RedBox::ObjectLayer::tiles
		 */
		const TileContainer &getTiles() const;

		LineNameMap::mapped_type getLine(const LineNameMap::key_type &lineName);
		const LineNameMap::mapped_type getLine(const LineNameMap::key_type &lineName) const;

		PolygonNameMap::mapped_type getPolygon(const PolygonNameMap::key_type &polygonName);
		const PolygonNameMap::mapped_type getPolygon(const PolygonNameMap::key_type &polygonName) const;

		RectangleNameMap::mapped_type getRectangle(const RectangleNameMap::key_type &rectangleName);
		const RectangleNameMap::mapped_type getRectangle(const RectangleNameMap::key_type &rectangleName) const;

		TileNameMap::mapped_type getTile(const TileNameMap::key_type &tileName);
		const TileNameMap::mapped_type getTile(const TileNameMap::key_type &tileName) const;

		void refreshAllNames();

		void refreshLineNames();

		void refreshRectangleNames();

		void refreshPolygonNames();

		void refreshTileNames();
	private:
		/**
		 * Refreshes the name map of a list of objects.
		 * @param objects List of objects to have their name mapped.
		 * @param nameMap Names mapped to their respective object.
		 * @tparam Type of object.
		 */
		template <typename T>
		static void refreshNames(std::list<T> &objects,
		                         std::map<std::string, T *> &nameMap) {
			// We makesure to clear out the existing name map.
			nameMap.clear();

			// We try to map the name of every objects.
			for (typename std::list<T>::iterator i = objects.begin();
			     i != objects.end(); ++i) {

				// We make sure it has a name before trying to insert it in the
				// name map.
				if (!i->name.empty()) {
					nameMap.insert(std::make_pair(i->name, &(*i)));
				}
			}
		}

		/// List of line objects in the layer.
		LineContainer lines;

		/// List of polygon objects in the layer.
		PolygonContainer polygons;

		/// List of rectangle objects in the layer.
		RectangleContainer rectangles;

		/// List of tile objects in the layer.
		TileContainer tiles;

		/**
		 * Line names mapped to their respective line. Must be manually
		 * refreshed by calling the corresponding name refreshing function.
		 * Lines that have an empty string as a name will not be mapped.
		 * @see RedBox::ObjectLayer::refreshAllNames()
		 * @see RedBox::ObjectLayer::refreshLineNames()
		 */
		LineNameMap lineNames;

		/**
		 * Polygon names mapped to their respective polygon. Must be
		 * manually refreshed by calling the corresponding name refreshing
		 * function. Polygons that have an empty string as a name will not be
		 * mapped.
		 * @see RedBox::ObjectLayer::refreshAllNames()
		 * @see RedBox::ObjectLayer::refreshPolygonNames()
		 */
		PolygonNameMap polygonNames;

		/**
		 * Rectangle names mapped to their respective rectangle. Must be
		 * manually refreshed by calling the corresponding name refreshing
		 * functions. Rectangles that have an empty string as a name will not be
		 * mapped.
		 * @see RedBox::ObjectLayer::refreshAllNames()
		 * @see RedBox::ObjectLayer::refreshRectangleNames()
		 */
		RectangleNameMap rectangleNames;

		/**
		 * Tile names mapped to their respective tile object. Must be manually
		 * refreshed by calling the corresponding name refreshing functions.
		 * Tile objects that have an empty string as a name will not be mapped.
		 * @see RedBox::ObjectLayer::refreshAllNames()
		 * @see RedBox::ObjectLayer::refreshTileNames()
		 */
		TileNameMap tileNames;
	};

}

#endif // RB_OBJECT_LAYER_H
