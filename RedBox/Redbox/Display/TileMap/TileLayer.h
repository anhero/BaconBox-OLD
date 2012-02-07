/**
 * @file
 * @ingroup TileMap
 */
#ifndef RB_MAP_LAYER_H
#define RB_MAP_LAYER_H

#include <string>
#include <vector>

#include "PropertyMap.h"

namespace RedBox {
	/**
	 * Represents a layer of a tile map.
	 * @ingroup TileMap
	 */
	class TileLayer {
	public:
		/// Type used to contain the data about the tile indexes.
		typedef std::vector<unsigned int> DataVector;

		/**
		 * Default constructor. Constructs an empty layer with a size of (0, 0)
		 * and no name.
		 */
		TileLayer();

		/**
		 * Copy constructor.
		 * @param src Map layer to make a copy of.
		 */
		TileLayer(const TileLayer &src);

		/**
		 * Assignment operator overload.
		 * @param src Map layer to copy.
		 * @return Reference to the modified map layer.
		 */
		TileLayer &operator=(const TileLayer &src);

		/**
		 * Gets the name of the map layer.
		 * @return Name of the map layer.
		 */
		const std::string &getName() const;

		/**
		 * Sets the name of the map layer.
		 * @parma newName New name of the map layer.
		 */
		void setName(const std::string &newName);

		/**
		 * Access a tile's data. No bounds checking is done. Undefined
		 * behaviour happens if you go out bounds.
		 * @param index Index of the tile to get the data.
		 * @return Reference to the tile number.
		 */
		DataVector::value_type &operator[](DataVector::size_type index);

		/**
		 * Access a tile's data. No bounds checking is done. Undefined
		 * behaviour happens if you go out bounds.
		 * @param index Index of the tile to get the data.
		 * @return Tile number.
		 */
		DataVector::value_type operator[](DataVector::size_type index) const;

		/**
		 * Gets or sets the value of a property.
		 * @param key Name of the property to get the value of.
		 * @return Reference to the value of the asked property.
		 */
		PropertyMap::mapped_type &operator[](const PropertyMap::key_type &key);

		/**
		 * Gets the width of the layer, in tiles.
		 * @return Width of the layer, in tiles.
		 */
		unsigned int getWidth() const;

		/**
		 * Sets the width of the map layer. Resizes the array of tile data.
		 * @param newWidth New width.
		 */
		void setWidth(unsigned int newWidth);

		/**
		 * Gets the height of the layer, in tiles.
		 * @return Height of the layer, in tiles.
		 */
		unsigned int getHeight() const;

		/**
		 * Sets the height of the map layer. Resizes the array of tile data.
		 * @param newHeight New height.
		 */
		void setHeight(unsigned int newHeight);

		/**
		 * Sets the size of the map layer. Resizes the array of tile data.
		 * @param newWidth New width (in tiles).
		 * @param newHeight New height (in tiles).
		 */
		void setSize(unsigned int newWidth, unsigned int newHeight);

		/**
		 * Checks wether or not the map layer is visible.
		 * @return True if the map layer is visible, false if not.
		 */
		bool isVisible() const;

		/**
		 * Sets wether or not the map layer is visible.
		 * @param newVisible Set this parameter to true if you want the layer to
		 * be visible, false if not.
		 */
		void setVisible(bool newVisible);

		/**
		 * Gets the map of properties.
		 * @return Map layer's properties.
		 */
		const PropertyMap &getProperties() const;

		/**
		 * Adds a property to the map layer.
		 * @param newKey Name of the property to add.
		 * @param newValue New value of the property to add.
		 * @param overwrite Set this parameter to true to overwrite the
		 * property's existing value if it already exists.
		 */
		void addProperty(const PropertyMap::key_type &newKey,
		                 const PropertyMap::mapped_type &newValue,
		                 bool overwrite = false);

		/**
		 * Adds a property to the map layer.
		 * @param newProperty Pair containing the key and the value to add
		 * to the map layer's properties.
		 * @param overwrite Set this parameter to true to overwrite the
		 * property's existing value if it already exists.
		 */
		void addProperty(const PropertyMap::value_type &newProperty,
		                 bool overwrite = false);

		/**
		 * Removes a property from the map layer.
		 * @param keyToRemove Key of the property to remove.
		 */
		void removeProperty(const PropertyMap::key_type &keyToRemove);

		/**
		 * Gets the vector containing all the tiles' data.
		 * @return Const reference to the vector containing all the tiles' data.
		 */
		const DataVector &getData() const;

		/**
		 * Gets the data of a tile at a certain index in the tile array.
		 * @param index Index of the tile in the vector.
		 */
		DataVector::value_type &getDataAt(DataVector::size_type index);

		/**
		 * Gets the data of a tile at a certain index in the tile array.
		 * @param index Index of the tile in the vector.
		 */
		DataVector::value_type getDataAt(DataVector::size_type index) const;
	private:
		/// Name of the map layer.
		std::string name;

		/// Width of the map layer (in tiles).
		unsigned int width;

		/// Height of the map layer (in tiles).
		unsigned int height;

		/// Set to true to make the layer invisible.
		bool visible;

		/// Contains the layer's properties.
		PropertyMap properties;

		/// Vector containing all of the tiles' id's.
		DataVector data;
	};
}

#endif
