/**
 * @file
 * @ingroup TileMap
 */
#ifndef RB_OBJECT_LAYER_H
#define RB_OBJECT_LAYER_H

#include <map>
#include <list>

#include "TileMapLayer.h"
#include "Vector2.h"

namespace RedBox {
	class TileObject;
	class LineObject;
	class PolygonObject;
	class RectangleObject;
	/**
	 * Represents a layer of objects in a tile map. Can contain lines, polygons,
	 * rectangles and tiles. The only object type to have a graphic is the tile.
	 * But, you could determine a custom system to recognize the objects and
	 * put graphics yourself in your game.
	 * @ingroup TileMap
	 */
	class ObjectLayer : public TileMapLayer {
		friend class TileObject;
		friend class LineObject;
		friend class PolygonObject;
		friend class RectangleObject;
		friend class TileMap;
	public:
		typedef std::list<LineObject *> LineContainer;
		typedef std::list<PolygonObject *> PolygonContainer;
		typedef std::list<RectangleObject *> RectangleContainer;
		typedef std::list<TileObject *> TileContainer;

		/**
		 * Gets the line objects.
		 * @return Const reference to the list of pointers to line objects.
		 * @see RedBox::ObjectLayer::lines
		 */
		const LineContainer &getLines() const;

		/**
		 * Gets the polygon objects.
		 * @return Const reference to the list of pointers to polygon objects.
		 * @see RedBox::ObjectLayer::objects
		 */
		const PolygonContainer &getPolygons() const;

		/**
		 * Gets the rectangle objects.
		 * @return Const reference to the list of pointers to rectangle objects.
		 * @see RedBox::ObjectLayer::rectangles
		 */
		const RectangleContainer &getRectangles() const;

		/**
		 * Gets the tile objects.
		 * @return Const reference to the list of pointers to tile objects.
		 * @see RedBox::ObjectLayer::tiles
		 */
		const TileContainer &getTiles() const;

		/**
		 * Gets a line object from its name. Only lines with a name can be
		 * found using this function.
		 * @param lineName Name of the line object to find.
		 * @return Pointer to the line object found, NULL if no line object was
		 * found with the given name.
		 */
		LineObject *getLine(const std::string &lineName);

		/**
		 * Gets a line object from its name. Only lines with a name can be
		 * found using this function.
		 * @param lineName Name of the line object to find.
		 * @return Pointer to the line object found, NULL if no line object was
		 * found with the given name.
		 */
		const LineObject *getLine(const std::string &lineName) const;

		/**
		 * Adds a line to the object layer.
		 * @param newLineName Name of the new line object to create.
		 * @param newPosition Starting position of the new line object to
		 * create.
		 * @param overwrite Determines wether or or not the existing line
		 * should be overwritten if there is already a line object with the
		 * same name as the new line object.
		 * @return Pointer to the line created, never NULL. If it was asked not
		 * to overwrite and a line with the same name already existed, a pointer
		 * to the existing one is returned.
		 */
		LineObject *addLine(const std::string &newLineName = std::string(),
		                    const Vector2 &newPosition = Vector2(),
		                    bool overwrite = false);

		/**
		 * Removes a line by its name. Does nothing if no line has that name.
		 * @param lineName Name of the line object to remove.
		 */
		void removeLine(const std::string &lineName);

		/**
		 * Removes a line. If the line object is not in this object layer, this
		 * function does nothing.
		 * @param toRemove Pointer to the line object to remove from the layer.
		 */
		void removeLine(const LineObject *toRemove);

		/**
		 * Gets a polygon object from its name. Only polygons with a name can be
		 * found using this function.
		 * @param polygonName Name of the polygon object to find.
		 * @return Pointer to the polygon object found, NULL if no polygon
		 * object was found with the given name.
		 */
		PolygonObject *getPolygon(const std::string &polygonName);

		/**
		 * Gets a polygon object from its name. Only polygons with a name can be
		 * found using this function.
		 * @param polygonName Name of the polygon object to find.
		 * @return Pointer to the polygon object found, NULL if no polygon
		 * object was found with the given name.
		 */
		const PolygonObject *getPolygon(const std::string &polygonName) const;

		/**
		 * Adds a polygon to the object layer.
		 * @param newLineName Name of the new polygon object to create.
		 * @param newPosition Starting position of the new polygon object to
		 * create.
		 * @param overwrite Determines wether or or not the existing polygon
		 * should be overwritten if there is already a polygon object with the
		 * same name as the new polygon object.
		 * @return Pointer to the polygon created, never NULL. If it was asked
		 * not to overwrite and a polygon with the same name already existed, a
		 * pointer to the existing one is returned.
		 */
		PolygonObject *addPolygon(const std::string &newPolygonName = std::string(),
		                          const Vector2 &newPosition = Vector2(),
		                          bool overwrite = false);

		/**
		 * Removes a polygon by its name. Does nothing if no polygon has that
		 * name.
		 * @param polygonName Name of the line object to remove.
		 */
		void removePolygon(const std::string &polygonName);

		/**
		 * Removes a polygon. If the polygon object is not in this object layer,
		 * this function does nothing.
		 * @param toRemove Pointer to the polygon object to remove from the
		 * layer.
		 */
		void removePolygon(const PolygonObject *toRemove);

		/**
		 * Gets a rectangle object from its name. Only rectangles with a name
		 * can be found using this function.
		 * @param rectangleName Name of the rectangle object to find.
		 * @return Pointer to the rectangle object found, NULL if no rectangle
		 * object was found with the given name.
		 */
		RectangleObject *getRectangle(const std::string &rectangleName);

		/**
		 * Gets a rectangle object from its name. Only rectangles with a name
		 * can be found using this function.
		 * @param rectangleName Name of the rectangle object to find.
		 * @return Pointer to the rectangle object found, NULL if no rectangle
		 * object was found with the given name.
		 */
		const RectangleObject *getRectangle(const std::string &rectangleName) const;

		/**
		 * Gets a tile object from its name. Only tiles with a name can be
		 * found using this function.
		 * @param tileName Name of the tile object to find.
		 * @return Pointer to the tile object found, NULL if no tile object was
		 * found with the given name.
		 */
		TileObject *getTile(const std::string &tileName);

		/**
		 * Gets a tile object from its name. Only tiles with a name can be
		 * found using this function.
		 * @param tileName Name of the tile object to find.
		 * @return Pointer to the tile object found, NULL if no tile object was
		 * found with the given name.
		 */
		const TileObject *getTile(const std::string &tileName) const;
	private:
		typedef std::map<std::string, LineObject *> LineNameMap;
		typedef std::map<std::string, PolygonObject *> PolygonNameMap;
		typedef std::map<std::string, RectangleObject *> RectangleNameMap;
		typedef std::map<std::string, TileObject *> TileNameMap;

		/**
		 * Paremeterized constructor.
		 * @param newName Name of the layer, can be empty.
		 * @param newParentMap Reference to the map that contains this layer.
		 * @param newOpacity Opacity of the layer.
		 * @param newVisible Wether or not the layer is visible.
		 * @see RedBox::TileMapEntity::name
		 */
		ObjectLayer(const std::string &newName,
		            const TileMap &newParentMap,
		            int32_t newOpacity,
		            bool newVisible);

		/**
		 * Copy constructor.
		 * @param src ObjectLayer to make a copy of.
		 * @param newParentMap Parent map of the tile layer.
		 */
		ObjectLayer(const ObjectLayer &src, const TileMap &newParentMap);

		/**
		 * Destructor.
		 */
		~ObjectLayer();

		/**
		 * Refreshes the name map of a list of objects.
		 * @param objects List of objects to have their name mapped.
		 * @param nameMap Names mapped to their respective object.
		 * @tparam Type of object.
		 */
		template <typename T>
		static void refreshNames(const std::list<T *> &objects,
		                         std::map<std::string, T *> &nameMap) {
			// We makesure to clear out the existing name map.
			nameMap.clear();

			// We try to map the name of every objects.
			for (typename std::list<T *>::const_iterator i = objects.begin();
			     i != objects.end(); ++i) {

				// We make sure it has a name before trying to insert it in the
				// name map.
				if (!(*i)->getName().empty()) {
					nameMap.insert(std::make_pair((*i)->getName(), *i));
				}
			}
		}

		/**
		 * Finds an object by its name in a name map.
		 * @param nameMap Map of objects by their name in which to search.
		 * @param objectName Name of the object to find.
		 * @tparam Type of the container that maps the object names to the
		 * object.
		 */
		template <typename T>
		static typename T::mapped_type getObject(T &nameMap,
		                                         const typename T::key_type &objectName) {
			typename T::iterator found = nameMap.find(objectName);

			if (found != nameMap.end()) {
				return found->second;

			} else {
				return NULL;
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
		mutable LineNameMap lineNames;

		mutable bool dirtyLineNames;

		/**
		 * Polygon names mapped to their respective polygon. Must be
		 * manually refreshed by calling the corresponding name refreshing
		 * function. Polygons that have an empty string as a name will not be
		 * mapped.
		 * @see RedBox::ObjectLayer::refreshAllNames()
		 * @see RedBox::ObjectLayer::refreshPolygonNames()
		 */
		mutable PolygonNameMap polygonNames;

		mutable bool dirtyPolygonNames;

		/**
		 * Rectangle names mapped to their respective rectangle. Must be
		 * manually refreshed by calling the corresponding name refreshing
		 * functions. Rectangles that have an empty string as a name will not be
		 * mapped.
		 * @see RedBox::ObjectLayer::refreshAllNames()
		 * @see RedBox::ObjectLayer::refreshRectangleNames()
		 */
		mutable RectangleNameMap rectangleNames;

		mutable bool dirtyRectangleNames;

		/**
		 * Tile names mapped to their respective tile object. Must be manually
		 * refreshed by calling the corresponding name refreshing functions.
		 * Tile objects that have an empty string as a name will not be mapped.
		 * @see RedBox::ObjectLayer::refreshAllNames()
		 * @see RedBox::ObjectLayer::refreshTileNames()
		 */
		mutable TileNameMap tileNames;

		mutable bool dirtyTileNames;
	};

}

#endif // RB_OBJECT_LAYER_H
