/**
 * @file
 * @ingroup TileMap
 */
#ifndef RB_TMX_TILE_MAP_READER_H
#define RB_TMX_TILE_MAP_READER_H

#include "TileMapReader.h"

namespace RedBox {
	class TmxTileMapReader : public TileMapReader {
	public:
		/**
		 * Default constructor.
		 */
		TmxTileMapReader();

		/**
		 * Destructor.
		 */
		~TmxTileMapReader();

		/**
		 * Reads a tile map from a file.
		 * @param fileName Path to the file to read.
		 * @return Pointer to the new instance of a tile map. The caller has
		 * to take care to delete it when he's done with it. Returns NULL if
		 * the reading has failed.
		 */
		TileMap *read(const std::string &fileName);

		/**
		 * Checks wether or not the file given is supported by the reader.
		 * Checks if the file name ends with ".tmx".
		 * @param fileName Path to the file to check.
		 * @return True if the reader supports the file format, false if not.
		 */
		bool supportsFile(const std::string &fileName) const;

		/**
		 * Gets a string containing the error message.
		 * @return String containing the error message if an error occured while
		 * trying to read a tile map.
		 */
		const std::string getErrorMessage() const;
	private:
		/// String containing the error message.
		std::string errorMessage;
	};
}

#endif
