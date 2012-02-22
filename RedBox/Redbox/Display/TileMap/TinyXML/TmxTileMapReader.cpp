#include "TmxTileMapReader.h"

#include <cstring>
#include <cstdlib>

#include <fstream>
#include <sstream>
#include <algorithm>
#include <list>

#include <tinyxml.h>
#include <zlib.h>

#include "TileMap.h"
#include "ResourceManager.h"
#include "Color.h"
#include "Tileset.h"
#include "TileLayer.h"
#include "ObjectLayer.h"
#include "Base64.h"
#include "Compression.h"
#include "StringHelper.h"

namespace RedBox {
	const char *NAME_ATTRIBUTE = "name";
	const char *TILE_WIDTH_NAME = "tilewidth";
	const char *TILE_HEIGHT_NAME = "tileheight";
	const char *OPACITY_NAME = "opacity";
	const char *VISIBLE_NAME = "visible";
	const std::string IMAGE_VALUE("image");
	const std::string PROPERTIES_VALUE("properties");

	TmxTileMapReader::TmxTileMapReader() : TileMapReader(), errorMessage() {
	}

	TmxTileMapReader::~TmxTileMapReader() {
	}

	TileMap *elementToTileMap(const std::string &currentFolder,
	                          TiXmlDocument &document,
	                          std::string &errorMessage);

	void elementToMapChild(const TiXmlElement &element,
	                       TileMap *&map, std::string &errorMessage);

	void addPropertiesFromElement(const TiXmlElement &element,
	                              TileMapEntity &entity);

	void addTilesetFromElement(const std::string &currentFolder,
	                           const TiXmlElement &element,
	                           TileMap *&map, std::string &errorMessage);

	void addTileLayerFromElement(const TiXmlElement &element,
	                             TileMap *&map, std::string &errorMessage);

	void addObjectLayerFromElement(const TiXmlElement &element,
	                               TileMap *&map, std::string &errorMessage);

	const std::string readNameFromElement(const TiXmlElement &element);

	TextureInformation *loadTextureFromElement(const std::string &currentFolder,
	                                           const TiXmlElement &element);

	bool decodeCSV(const std::string &data, std::string &result,
	               const TileCoordinate &expectedSize,
	               std::string &errorMessage);

	bool readDataFromElement(const TiXmlElement &element, std::string &result,
	                         const TileCoordinate &expectedSize,
	                         std::string &errorMessage);

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
				//fileName.substr(fileName.find_last_of('.') + 1) == FILE_EXTENSION;
				// We convert the tmx document into a tile map.
				result = elementToTileMap(fileName.substr(0, fileName.find_last_of('/') + 1), document, errorMessage);

			} else {
				errorMessage = "TmxTileMapReader: failed to to open the tmx file. Is the file path correct?";
			}

		} else {
			errorMessage = "TmxTileMapReader: tried to read a tile map from a non-supported file format.";
		}

		return result;
	}

	TileMap *elementToTileMap(const std::string &currentFolder,
	                          TiXmlDocument &document,
	                          std::string &errorMessage) {
		static const std::string ROOT_VALUE("map");
		static const char *ORIENTATION_ATTRIBUTE_NAME = "orientation";
		static const std::string MAP_ORIENTATION("orthogonal");
		static const char *WIDTH_NAME = "width";
		static const char *HEIGHT_NAME = "height";
		static const std::string TILESET_VALUE("tileset");

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

									// We read the map's children.
									const TiXmlNode *i = NULL;

									// We read the map's tileset first.
									while (result && (i = root->IterateChildren(i))) {
										if (i->ToElement()) {
											if (i->ToElement()->Value() == TILESET_VALUE) {
												addTilesetFromElement(currentFolder, *i->ToElement(), result, errorMessage);

											}
										}
									}

									// We then read the map's layers and
									// properties.
									while (result && (i = root->IterateChildren(i))) {
										if (i->ToElement()) {
											elementToMapChild(*i->ToElement(), result, errorMessage);
										}
									}

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

	void elementToMapChild(const TiXmlElement &element,
	                       TileMap *&map, std::string &errorMessage) {
		static const std::string TILE_LAYER_VALUE("layer");
		static const std::string OBJECT_LAYER_VALUE("objectgroup");

		if (element.Value() == PROPERTIES_VALUE) {
			addPropertiesFromElement(element, *map);

		} else if (element.Value() == TILE_LAYER_VALUE) {
			addTileLayerFromElement(element, map, errorMessage);

		} else if (element.Value() == OBJECT_LAYER_VALUE) {
			addObjectLayerFromElement(element, map, errorMessage);
		}
	}

	void addPropertiesFromElement(const TiXmlElement &element,
	                              TileMapEntity &entity) {
		const std::string PROPERTY_VALUE("property");
		static const char *VALUE_NAME = "value";

		const char *tmpName = NULL;

		const TiXmlNode *i = NULL;

		while ((i = element.IterateChildren(i))) {
			if (i->ToElement()) {

				// We get the name attribute of the property.
				tmpName = i->ToElement()->Attribute(NAME_ATTRIBUTE);

				// We make sure the property has a name.
				if (tmpName) {
					const char *tmpValue = i->ToElement()->Attribute(VALUE_NAME);

					// We make sure the property has a value.
					if (tmpValue) {
						// We add the property to the entity.
						entity.getProperties()[std::string(tmpName)] = std::string(tmpValue);
					}

				}
			}
		}
	}

	void addTilesetFromElement(const std::string &currentFolder,
	                           const TiXmlElement &element,
	                           TileMap *&map,
	                           std::string &errorMessage) {
		static const char *TILE_SPACING_NAME = "spacing";
		static const char *MARGIN_NAME = "margin";
		// We make sure the tile width is specified.
		double tmpTileWidth = 0.0;

		if (element.Attribute(TILE_WIDTH_NAME, &tmpTileWidth)) {
			double tmpTileHeight = 0.0;

			// We make sure the tile height is specified.
			if (element.Attribute(TILE_HEIGHT_NAME, &tmpTileHeight)) {
				// We get the tile spacing, if it has one.
				double tmpTileSpacing = 0.0;
				element.Attribute(TILE_SPACING_NAME, &tmpTileSpacing);

				// We get the margin, if it has one.
				double tmpMargin = 0.0;
				element.Attribute(MARGIN_NAME, &tmpMargin);

				// We load the tileset's texture.
				const TiXmlNode *i = NULL;
				bool notFound = true;
				TextureInformation *tmpTextureInformation = NULL;

				while (notFound && (i = element.IterateChildren(i))) {
					if (i->ToElement() && i->ToElement()->Value() == IMAGE_VALUE) {
						tmpTextureInformation = loadTextureFromElement(currentFolder, *i->ToElement());

						if (tmpTextureInformation) {
							notFound = false;
						}
					}
				}

				if (tmpTextureInformation) {
					// We add the tileset to the tile map.
					Tileset *newTileset = map->addTileset(readNameFromElement(element),
					                                      tmpTextureInformation,
					                                      Vector2(static_cast<float>(tmpTileWidth), static_cast<float>(tmpTileHeight)),
					                                      static_cast<float>(tmpTileSpacing),
					                                      static_cast<float>(tmpMargin));
					// We fill it with its properties.
					i = NULL;

					while ((i = element.IterateChildren(i))) {
						if (i->ToElement() && i->ToElement()->Value() == PROPERTIES_VALUE) {
							addPropertiesFromElement(*(i->ToElement()), *newTileset);
						}
					}

				} else {
					errorMessage = "TmxTileMapReader: Could not find any valid texture for the tileset. Make sure all tilesets have a valid <image>.";
					delete map;
					map = NULL;
				}

			} else {
				errorMessage = "TmxTileMapReader: Tileset does not have a tileheight defined. Make sure it does.";
				delete map;
				map = NULL;
			}

		} else {
			errorMessage = "TmxTileMapReader: Tileset does not have a tilewidth defined. Make sure it does.";
			delete map;
			map = NULL;
		}
	}

	void addTileLayerFromElement(const TiXmlElement &element,
	                             TileMap *&map,
	                             std::string &errorMessage) {
		static const std::string DATA_VALUE("data");
		static const char *ENCODING_NAME = "encoding";
		static const char *CSV_ENCODING = "csv";
		static const char *BASE_64_ENCODING = "base64";
		static const char *COMPRESSION_NAME = "compression";
		static const char *GZIP_COMPRESSION = "gzip";
		static const char *ZLIB_COMPRESSION = "zlib";
		TileLayer *newTileLayer = map->pushBackTileLayer(readNameFromElement(element));

		// We get the tile layer's opacity.
		double tmpOpacity = 0.0;

		if (element.Attribute(OPACITY_NAME, &tmpOpacity)) {
			newTileLayer->setOpacity(static_cast<int32_t>(tmpOpacity * static_cast<double>(Color::MAX_COMPONENT_VALUE)));
		}

		// We check if the layer is visible.
		int tmpVisible = 1;

		if (element.Attribute(VISIBLE_NAME, &tmpVisible)) {
			newTileLayer->setVisible(static_cast<bool>(tmpVisible));
		}

		const TiXmlNode *i = NULL;

		// We read the properties and the data.
		while (map && (i = element.IterateChildren(i))) {
			if (i->ToElement()) {
				// We read the properties.
				if (i->ToElement()->Value() == PROPERTIES_VALUE) {
					addPropertiesFromElement(*(i->ToElement()), *newTileLayer);

				} else if (i->ToElement()->Value() == DATA_VALUE) {
					const TiXmlElement *dataElement = i->ToElement();
					// We get the data.
					const char *tmpData = dataElement->GetText();

					std::string data;

					// If we have text data.
					if (tmpData) {
						data.append(tmpData);
						// We make sure to remove the white spaces at the
						// beginning and at the end if necessary.
						StringHelper::trim(data);
						// We check if the data is encoded.
						const char *tmpEncoding = dataElement->Attribute(ENCODING_NAME);

						if (tmpEncoding) {
							// We check the type of encoding.
							if (!strcmp(CSV_ENCODING, tmpEncoding)) {
								// Decode CSV
								std::string encoded(data);

								if (!decodeCSV(encoded, data, map->getSizeInTiles(),
								               errorMessage)) {
									delete map;
									map = NULL;
								}

							} else if (!strcmp(BASE_64_ENCODING, tmpEncoding)) {
								// Decode Base 64.
								std::string encoded(data);
								Base64::decode(encoded, data);

								// We check if the data is compressed.
								const char *tmpCompression = dataElement->Attribute(COMPRESSION_NAME);

								if (tmpCompression) {
									// We make sure the compression format is
									// valid.
									if (!strcmp(GZIP_COMPRESSION, tmpCompression) ||
									    !strcmp(ZLIB_COMPRESSION, tmpCompression)) {
										encoded = data;
										Compression::decompress(encoded, data);

									} else {
										errorMessage = "TmxTileMapReader: Tile layer data compressed in an unknown format.";
										delete map;
										map = NULL;
									}
								}

								// We make sure there is enough data.
								if (data.size() / 4 != static_cast<std::string::size_type>(map->getWidthInTiles()) * static_cast<std::string::size_type>(map->getHeightInTiles())) {
									errorMessage = "TmxTileMapReader: Tile layer data is not of the right size.";
									delete map;
									map = NULL;
								}
							}

						}

					} else {
						// We read the data from XML tags.
						if (!readDataFromElement(*dataElement, data,
						                         map->getSizeInTiles(),
						                         errorMessage)) {
							delete map;
							map = NULL;
						}
					}

					// We make sure the data was read successfully.
					if (map) {
						// We read the data and put it in the tile layer.
						std::string::size_type index = 0;
						int y = 0, x = 0;

						while (map && y < map->getHeightInTiles()) {
							x = 0;

							while (map && x < map->getWidthInTiles()) {
								if (index < data.size()) {
									newTileLayer->setTileId(x, y, *reinterpret_cast<unsigned int *>(&data[index]));
									index += 4;
									++x;

								} else {
									errorMessage = "TmxTileMapReader: Too much tile layer data.";
									delete map;
									map = NULL;
								}
							}

							++y;
						}
					}
				}
			}
		}
	}

	void addObjectLayerFromElement(const TiXmlElement &element,
	                               TileMap *&map,
	                               std::string &errorMessage) {
		// We add a new object layer.
		ObjectLayer *newObjectLayer = map->pushBackObjectLayer(readNameFromElement(element));
	}

	TextureInformation *loadTextureFromElement(const std::string &currentFolder,
	                                           const TiXmlElement &element) {
		static const char *SOURCE_NAME = "source";
		static const char *TRANSPARENT_COLOR_NAME = "trans";
		TextureInformation *result = NULL;

		// We check if there is a path for the texture.
		const char *tmpString = element.Attribute(SOURCE_NAME);

		if (tmpString) {
			std::string texturePath(currentFolder);
			std::string textureKey(tmpString);
			texturePath.append(tmpString);

			// We check if there is a transparent color to use.
			tmpString = element.Attribute(TRANSPARENT_COLOR_NAME);

			if (tmpString) {
				// We convert the hexadecimal color to an unsigned int.
				std::stringstream ss;
				ss << std::hex << std::string(tmpString).append("ff");
				unsigned int tmpColor;
				ss >> tmpColor;
				Color transparentColor(tmpColor);

				result = ResourceManager::loadTextureWithColorKey(textureKey,
				                                                  texturePath,
				                                                  transparentColor);

			} else {
				// No transparent color.
				result = ResourceManager::loadTexture(textureKey, texturePath);
			}
		}

		return result;
	}

	bool decodeCSV(const std::string &data, std::string &result,
	               const TileCoordinate &expectedSize,
	               std::string &errorMessage) {
		typedef std::list<std::string> TokenList;
		TokenList tiles;
		StringHelper::tokenize(data, tiles, std::string(","), true);
		bool success = true;

		if (tiles.size() == static_cast<TokenList::size_type>(expectedSize.getX()) *
		    static_cast<TokenList::size_type>(expectedSize.getY())) {
			result.resize(tiles.size() * 4);
			std::string::size_type index = 0;

			for (TokenList::const_iterator i = tiles.begin(); i != tiles.end();
			     ++i) {
				*reinterpret_cast<unsigned int *>(&result[index]) = static_cast<unsigned int>(strtoul(i->c_str(), NULL, 10));
				index += 4;
			}

		} else {
			success = false;
			errorMessage = "TmxTileMapReader: CSV layer not of the right size.";
		}

		return success;
	}

	bool readDataFromElement(const TiXmlElement &element, std::string &result,
	                         const TileCoordinate &expectedSize,
	                         std::string &errorMessage) {
		static const char *TILE_ID_NAME = "gid";
		static const std::string TILE_VALUE("tile");
		bool success = true;

		std::string::size_type tmpSize = 4 * static_cast<std::string::size_type>(expectedSize.getX()) * static_cast<std::string::size_type>(expectedSize.getY());

		result.resize(tmpSize);

		// We read all the child tile nodes.
		const TiXmlNode *i = NULL;
		std::string::size_type index = 0;

		const char *tmpTileId;

		while (success && (i = element.IterateChildren(i))) {
			if (i->ToElement() && i->ToElement()->ValueStr() == TILE_VALUE) {
				// We make sure the tile data has a tile id.
				tmpTileId = i->ToElement()->Attribute(TILE_ID_NAME);

				if (tmpTileId) {
					if (index < tmpSize) {
						*reinterpret_cast<unsigned int *>(&result[index]) = static_cast<unsigned int>(strtoul(tmpTileId, NULL, 10));
						index += 4;

					} else {
						success = false;
						errorMessage = "TmxTileMapReader: Too many tile tags for the tile data for the tile layer.";
					}
				}
			}
		}

		return success;
	}

	const std::string readNameFromElement(const TiXmlElement &element) {

		const char *tmpName = element.Attribute(NAME_ATTRIBUTE);
		return (tmpName) ? (std::string(tmpName)) : (std::string());
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
