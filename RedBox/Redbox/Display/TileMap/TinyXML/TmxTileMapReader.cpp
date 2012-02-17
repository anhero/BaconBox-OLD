#include "TmxTileMapReader.h"

#include <tinyxml.h>

#include "TileMap.h"

namespace RedBox {

	TmxTileMapReader::TmxTileMapReader() : TileMapReader(), errorMessage() {
	}

	TileMap *TmxTileMapReader::read(const std::string &fileName) {
		TileMap *result = NULL;

		// We make sure the file has the right extension.
		if (supportsFile(fileName)) {
			result = new TileMap();

		} else {
			errorMessage = "TmxTileMapReader: tried to read a tile map from a non-supported file format.";
		}

		return result;
	}

	bool TmxTileMapReader::supportsFile(const std::string &fileName) const {
		static const std::string FILE_EXTENSION = "tmx";
		return fileName.substr(fileName.find_last_of('.') + 1) == FILE_EXTENSION;
	}

	const std::string TmxTileMapReader::getErrorMessage() const {
		return errorMessage;
	}
}
