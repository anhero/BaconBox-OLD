#include "TmxTileMapReader.h"

#include <fstream>

#include <tinyxml.h>

#include "TileMap.h"

namespace RedBox {
	TmxTileMapReader::TmxTileMapReader() : TileMapReader(), errorMessage() {
	}

	TmxTileMapReader::~TmxTileMapReader() {
	}

	TileMap *elementToTileMap(TiXmlDocument &document, std::string &errorMessage);

	void readProperties(const TiXmlElement &element, TileMapEntity &entity);

	TileMap *TmxTileMapReader::read(const std::string &fileName) {
		TileMap *result = NULL;

		// We make sure the file has the right extension.
		if (supportsFile(fileName)) {
			std::ifstream tmxFile;
			// We open the tmx file.
			tmxFile.open(fileName.c_str());

			// We make sure the file opened correctly.
			if (tmxFile.is_open()) {
				// We initialize the document.
				TiXmlDocument document;
				// We read the document from the stream.
				tmxFile >> document;

				// We close the file.
				tmxFile.close();

				// We convert the tmx document into a tile map.
				result = elementToTileMap(document, errorMessage);

			} else {
				errorMessage = "TmxTileMapReader: failed to to open the tmx file. Is the file path correct?";
			}

		} else {
			errorMessage = "TmxTileMapReader: tried to read a tile map from a non-supported file format.";
		}

		return result;
	}

	TileMap *elementToTileMap(TiXmlDocument &document, std::string &errorMessage) {
		static const std::string ROOT_VALUE("map");
		static const char *ORIENTATION_ATTRIBUTE_NAME = "orientation";
		static const std::string MAP_ORIENTATION("orthogonal");
		static const char *NAME_ATTRIBUTE = "name";
		static const char *WIDTH_NAME = "width";
		static const char *HEIGHT_NAME = "height";
		static const char *TILE_WIDTH_NAME = "tilewidth";
		static const char *TILE_HEIGHT_NAME = "tileheight";

		TileMap *result = NULL;

		// We get the root element.
		TiXmlElement *root = document.RootElement();

		// We make sure the document has a root element.
		if (root) {
			// We make sure the root element is a map.
			if (root->Value() == ROOT_VALUE) {
				// We make sure the map is orthogonal.
				const char *tmpAttribute = root->Attribute(ORIENTATION_ATTRIBUTE_NAME);

				if (tmpAttribute && std::string(tmpAttribute) == MAP_ORIENTATION) {
					// We initialize the tile map with its name, if it has one.
					tmpAttribute = root->Attribute(NAME_ATTRIBUTE);
					result = new TileMap((tmpAttribute) ? (std::string(tmpAttribute)) : (std::string()));

					// We get ready to read its size and tile size.
					int tmpInt = 0;
					double tmpDouble = 0.0;

					// We start by reading the width.
					if (root->Attribute(WIDTH_NAME, &tmpInt)) {
						result->setWidthInTiles(tmpInt);
						tmpInt = 0;

						// We read the height.
						if (root->Attribute(HEIGHT_NAME, &tmpInt)) {
							result->setHeightInTiles(tmpInt);
							tmpInt = 0;

							// We read the tile width.
							if (root->Attribute(TILE_WIDTH_NAME, &tmpDouble)) {
								result->setTileWidth(static_cast<float>(tmpDouble));
								tmpDouble = 0.0;

								// We read the tile height.
								if (root->Attribute(TILE_HEIGHT_NAME, &tmpDouble)) {
									result->setTileHeight(static_cast<float>(tmpDouble));
									tmpDouble = 0.0;

								} else {
									errorMessage = "TmxTileMapReader: the map must have a tileheight attribute.";
									delete result;
									result = NULL;
								}

							} else {
								errorMessage = "TmxTileMapReader: the map must have a tilewidth attribute.";
								delete result;
								result = NULL;
							}

						} else {
							errorMessage = "TmxTileMapReader: the map must have a height attribute.";
							delete result;
							result = NULL;
						}

					} else {
						errorMessage = "TmxTileMapReader: the map must have a width attribute.";
						delete result;
						result = NULL;
					}

				} else {
					errorMessage = "TmxTileMapReader: the tmx file's map is not orthogonal. Check that the orientation attribute of the map is defined and that it is set to orthogonal.";
				}

			} else {
				errorMessage = "TmxTileMapReader: the tmx file's root element is not a map.";
			}

		} else {
			errorMessage = "TmxTileMapReader: the tmx file does not contain a root element.";
		}

		return result;
	}

	void readProperties(const TiXmlElement &element, TileMapEntity &entity)	{
		static const char *NAME_ATTRIBUTE = "name";
		static const std::string PROPERTY_VALUE("property");
		static const char *VALUE_NAME = "value";

		// We set the name of the entity if it has one.
		const char *tmpAttribute = element.Attribute(NAME_ATTRIBUTE);

		if (tmpAttribute) {
			entity.setName(std::string(tmpAttribute));
		}

		// We loop through the entity's children to read the properties.
		const TiXmlNode *i = NULL;
		const TiXmlElement *child = NULL;
		const char *tmpValue = NULL;

		while ((i = element.IterateChildren(i))) {
			// A property must be an element, it must have "property" as its
			// value and must have two attributes: "name" and "value".
			if ((child = i->ToElement()) && child->Value() == PROPERTY_VALUE &&
			    (tmpAttribute = child->Attribute(NAME_ATTRIBUTE)) &&
			    (tmpValue = child->Attribute(VALUE_NAME))) {
				// We set the property to the entity.
				entity.getProperties()[std::string(tmpAttribute)] = std::string(tmpValue);
			}
		}
	}

	bool TmxTileMapReader::supportsFile(const std::string &fileName) const {
		static const std::string FILE_EXTENSION = "tmx";
		return fileName.substr(fileName.find_last_of('.') + 1) == FILE_EXTENSION;
	}

	const std::string TmxTileMapReader::getErrorMessage() const {
		return errorMessage;
	}

	void TmxTileMapReader::clearErrorMessage() {
		errorMessage.clear();
	}
}
