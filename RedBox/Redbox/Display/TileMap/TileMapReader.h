/**
 * @file
 * @ingroup TileMap
 */
#ifndef RB_TILE_MAP_READER_H
#define RB_TILE_MAP_READER_H

#include <string>

namespace RedBox {
	class TileMap;

	/**
	 * Abstract base class of tile map readers. Different tile map readers must
	 * be implemented for each tile map file formats.
	 * @ingroup TileMap
	 */
	class TileMapReader {
	public:
		/**
		 * Destructor.
		 */
		virtual ~TileMapReader();

		/**
		 * Reads a tile map from a file.
		 * @param fileName Path to the file to read.
		 * @return Pointer to the new instance of a tile map. The caller has
		 * to take care to delete it when he's done with it. Returns NULL if
		 * the reading has failed.
		 */
		virtual TileMap *read(const std::string &fileName) = 0;

		/**
		 * Checks wether or not the file given is supported by the reader.
		 * Usually, would check the file extension.
		 * @param fileName Path to the file to check.
		 * @return True if the reader supports the file format, false if not.
		 */
		virtual bool supportsFile(const std::string &fileName) const = 0;

		/**
		 * Gets a string containing the error message.
		 * @return String containing the error message if an error occured while
		 * trying to read a tile map.
		 */
		virtual const std::string getErrorString() = 0;
	};
}

#endif // RB_TILE_MAP_READER_H
