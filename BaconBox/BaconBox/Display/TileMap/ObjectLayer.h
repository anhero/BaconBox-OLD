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
#include "Color.h"

namespace BaconBox {
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
		/// Type that contains the pointers to the line objects.
		typedef std::list<LineObject *> LineContainer;

		/// Type that contains the pointers to the polygon objects.
		typedef std::list<PolygonObject *> PolygonContainer;

		/// Type that contains the pointers to the rectangle objects.
		typedef std::list<RectangleObject *> RectangleContainer;

		/// Type that contains the pointers to the tile objects.
		typedef std::list<TileObject *> TileContainer;

		/**
		 * Gets the instance as an object layer, if it is one.
		 * @return Pointer to the instance as an object layer, NULL if it's not
		 * an object layer.
		 */
		ObjectLayer *asObjectLayer();

		/**
		 * Gets the instance as an object layer, if it is one.
		 * @return Pointer to the instance as an object layer, NULL if it's not
		 * an object layer.
		 */
		const ObjectLayer *asObjectLayer() const;

		/**
		 * Gets the color used to display objects.
		 * @return Color used to display the objects in this layer.
		 * @see BaconBox::ObjectLayer::color
		 */
		const Color &getColor() const;

		/**
		 * Sets the color used to display objects.
		 * @param newColor New color used to display the objects in this layer.
		 * @see BaconBox::ObjectLayer::color
		 */
		void setColor(const Color &newColor);

		/**
		 * Gets the line objects.
		 * @return Const reference to the list of pointers to line objects.
		 * @see BaconBox::ObjectLayer::lines
		 */
		const LineContainer &getLines() const;

		/**
		 * Gets the polygon objects.
		 * @return Const reference to the list of pointers to polygon objects.
		 * @see BaconBox::ObjectLayer::objects
		 */
		const PolygonContainer &getPolygons() const;

		/**
		 * Gets the rectangle objects.
		 * @return Const reference to the list of pointers to rectangle objects.
		 * @see BaconBox::ObjectLayer::rectangles
		 */
		const RectangleContainer &getRectangles() const;

		/**
		 * Gets the tile objects.
		 * @return Const reference to the list of pointers to tile objects.
		 * @see BaconBox::ObjectLayer::tiles
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
		 * @param newPolygonName Name of the new polygon object to create.
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
		 * @param polygonName Name of the polygon object to remove.
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
		 * Adds a rectangle to the object layer.
		 * @param newRectangleName Name of the new rectangle object to create.
		 * @param newPosition Starting position of the new rectangle object to
		 * create.
		 * @param newSize Width and height of the new rectangle.
		 * @param overwrite Determines wether or or not the existing rectangle
		 * should be overwritten if there is already a rectangle object with the
		 * same name as the new rectangle object.
		 * @return Pointer to the rectangle created, never NULL. If it was asked
		 * not to overwrite and a rectangle with the same name already existed,
		 * a pointer to the existing one is returned.
		 */
		RectangleObject *addRectangle(const std::string &newRectangleName = std::string(),
		                              const Vector2 &newPosition = Vector2(),
		                              const Vector2 &newSize = Vector2(),
		                              bool overwrite = false);

		/**
		 * Removes a rectangle by its name. Does nothing if no rectangle has
		 * that name.
		 * @param rectangleName Name of the rectangle object to remove.
		 */
		void removeRectangle(const std::string &rectangleName);

		/**
		 * Removes a rectangle. If the rectangle object is not in this object
		 * layer, this function does nothing.
		 * @param toRemove Pointer to the rectangle object to remove from the
		 * layer.
		 */
		void removeRectangle(const RectangleObject *toRemove);

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

		/**
		 * Adds a tile to the object layer.
		 * @param newTileName Name of the new tile object to create.
		 * @param newPosition Starting position of the new tile object to
		 * create.
		 * @param newTileId Tile id of the new tile object. If the id doesn't
		 * fit within the tile map's tilesets, it is set to 0.
		 * @param overwrite Determines wether or or not the existing tile should
		 * be overwritten if there is already a tile object with the same name
		 * as the new tile object.
		 * @return Pointer to the tile created, never NULL. If it was asked
		 * not to overwrite and a tile with the same name already existed, a
		 * pointer to the existing one is returned.
		 */
		TileObject *addTile(const std::string &newTileName = std::string(),
		                    const Vector2 &newPosition = Vector2(),
		                    unsigned int newTileId = 0u,
		                    bool overwrite = false);

		/**
		 * Removes a tile by its name. Does nothing if no tile has that name.
		 * @param tileName Name of the tile object to remove.
		 */
		void removeTile(const std::string &tileName);

		/**
		 * Removes a tile. If the tile object is not in this object layer, this
		 * function does nothing.
		 * @param toRemove Pointer to the tile object to remove from the layer.
		 */
		void removeTile(const TileObject *toRemove);
	private:
		/// Type that maps the line objects by their name.
		typedef std::map<std::string, LineObject *> LineNameMap;

		/// Type that maps the polygon objects by their name.
		typedef std::map<std::string, PolygonObject *> PolygonNameMap;

		/// Type that maps the polygon objects by their name.
		typedef std::map<std::string, RectangleObject *> RectangleNameMap;

		/// Type that maps the tile objects by their name.
		typedef std::map<std::string, TileObject *> TileNameMap;

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

		/**
		 * Paremeterized constructor.
		 * @param newName Name of the layer, can be empty.
		 * @param newParentMap Reference to the map that contains this layer.
		 * @param newOpacity Opacity of the layer.
		 * @param newVisible Wether or not the layer is visible.
		 * @see BaconBox::TileMapEntity::name
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
		 * Applies the destruction id's of a tileset.
		 * @param toDestroy Range of tile id's to destroy. All tile id's in this
		 * range are reset to 0. All tile id's above the range are reduced by
		 * the range's length. Affects all the tile objects.
		 */
		void applyTilesetDestruction(const TileIdRange &toDestroy);

		/**
		 * Gets a duplicate of the object layer.
		 * @param newParentMap Reference to the map that contains the clone.
		 * @return Pointer to a duplicate of the object layer. The caller is
		 * responsible for deleting this instance.
		 */
		ObjectLayer *clone(const TileMap &newParentMap) const;

		/**
		 * Color used to display the objects in this group. Mainly used for
		 * Tiled.
		 */
		Color color;

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
		 * @see BaconBox::ObjectLayer::refreshAllNames()
		 * @see BaconBox::ObjectLayer::refreshLineNames()
		 */
		mutable LineNameMap lineNames;

		/**
		 * Boolean used internally to determine if the map of lines by their
		 * name is correctly synchronized.
		 */
		mutable bool dirtyLineNames;

		/**
		 * Polygon names mapped to their respective polygon. Must be
		 * manually refreshed by calling the corresponding name refreshing
		 * function. Polygons that have an empty string as a name will not be
		 * mapped.
		 * @see BaconBox::ObjectLayer::refreshAllNames()
		 * @see BaconBox::ObjectLayer::refreshPolygonNames()
		 */
		mutable PolygonNameMap polygonNames;

		/**
		 * Boolean used internally to determine if the map of polygons by their
		 * name is correctly synchronized.
		 */
		mutable bool dirtyPolygonNames;

		/**
		 * Rectangle names mapped to their respective rectangle. Must be
		 * manually refreshed by calling the corresponding name refreshing
		 * functions. Rectangles that have an empty string as a name will not be
		 * mapped.
		 * @see BaconBox::ObjectLayer::refreshAllNames()
		 * @see BaconBox::ObjectLayer::refreshRectangleNames()
		 */
		mutable RectangleNameMap rectangleNames;

		/**
		 * Boolean used internally to determine if the map of rectangles by
		 * their name is correctly synchronized.
		 */
		mutable bool dirtyRectangleNames;

		/**
		 * Tile names mapped to their respective tile object. Must be manually
		 * refreshed by calling the corresponding name refreshing functions.
		 * Tile objects that have an empty string as a name will not be mapped.
		 * @see BaconBox::ObjectLayer::refreshAllNames()
		 * @see BaconBox::ObjectLayer::refreshTileNames()
		 */
		mutable TileNameMap tileNames;

		/**
		 * Boolean used internally to determine if the map of tiles by their
		 * name is correctly synchronized.
		 */
		mutable bool dirtyTileNames;
	};

}

#endif // RB_OBJECT_LAYER_H
