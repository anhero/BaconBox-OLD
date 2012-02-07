/**
 * @file
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

		LineContainer &getLines();
		const LineContainer &getLines() const;

		PolygonContainer &getPolygons();
		const PolygonContainer &getPolygons() const;

		RectangleContainer &getRectangles();
		const RectangleContainer &getRectangles() const;

		TileContainer &getTiles();
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

		LineContainer lines;
		PolygonContainer polygons;
		RectangleContainer rectangles;
		TileContainer tiles;

		LineNameMap lineNames;
		PolygonNameMap polygonNames;
		RectangleNameMap rectangleNames;
		TileNameMap tileNames;
	};

}

#endif // RB_OBJECT_LAYER_H
