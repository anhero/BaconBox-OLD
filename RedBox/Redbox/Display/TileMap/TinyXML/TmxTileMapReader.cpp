#include "TmxTileMapReader.h"

#include <fstream>
#include <sstream>

#include <tinyxml.h>

#include "TileMap.h"
#include "ResourceManager.h"
#include "Color.h"

namespace RedBox {
	const char *NAME_ATTRIBUTE = "name";

	TmxTileMapReader::TmxTileMapReader() : TileMapReader(), errorMessage() {
	}

	TmxTileMapReader::~TmxTileMapReader() {
	}

	TileMap *elementToTileMap(const std::string &currentFolder,
	                          TiXmlDocument &document,
	                          std::string &errorMessage);

	void elementToMapChild(const std::string &currentFolder,
	                       const TiXmlElement &element,
	                       TileMap *&map, std::string &errorMessage);

	template <typename T>
	void addPropertyFromElement(const TiXmlElement &element,
	                            T *&entity, std::string &errorMessage);

	void addTilesetFromElement(const std::string &currentFolder,
	                           const TiXmlElement &element,
	                           TileMap *&map, std::string &errorMessage);

	void addTileLayerFromElement(const TiXmlElement &element,
	                             TileMap *&map, std::string &errorMessage);

	void addObjectLayerFromElement(const TiXmlElement &element,
	                               TileMap *&map, std::string &errorMessage);

	const std::string readNameFromElement(const TiXmlElement &element,
	                                      TileMapEntity &entity);

	TextureInformation *loadTextureFromElement(const std::string &currentFolder,
	                                           const TiXmlElement &element);

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

									// We read the map's children.
									const TiXmlNode *i = NULL;

									while (result && (i = root->IterateChildren(i))) {
										if (i->ToElement()) {
											elementToMapChild(currentFolder, *i->ToElement(), result, errorMessage);
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

	void elementToMapChild(const std::string &currentFolder,
	                       const TiXmlElement &element,
	                       TileMap *&map, std::string &errorMessage) {
		static const std::string PROPERTY_VALUE("property");
		static const std::string TILESET_VALUE("tileset");
		static const std::string TILE_LAYER_VALUE("layer");
		static const std::string OBJECT_LAYER_VALUE("objectgroup");

		if (element.Value() == PROPERTY_VALUE) {
			addPropertyFromElement(element, map, errorMessage);

		} else if (element.Value() == TILESET_VALUE) {
			addTilesetFromElement(currentFolder, element, map, errorMessage);

		} else if (element.Value() == TILE_LAYER_VALUE) {
			addTileLayerFromElement(element, map, errorMessage);

		} else if (element.Value() == OBJECT_LAYER_VALUE) {
			addObjectLayerFromElement(element, map, errorMessage);
		}
	}

	template <typename T>
	void addPropertyFromElement(const TiXmlElement &element,
	                            T *&entity,
	                            std::string &errorMessage) {
		static const char *VALUE_NAME = "value";

		// We get the name attribute of the property.
		const char *tmpName = element.Attribute(NAME_ATTRIBUTE);

		// We make sure the property has a name.
		if (tmpName) {
			const char *tmpValue = element.Attribute(VALUE_NAME);

			// We make sure the property has a value.
			if (tmpValue) {
				// We add the property to the entity.
				entity->getProperties()[std::string(tmpName)] = std::string(tmpValue);
			}

		} else {
			errorMessage = "TmxTileMapReader: Property does not have a name attribute. Make sure every property has a name attribute.";
			delete entity;
			entity = NULL;
		}
	}

	void addTilesetFromElement(const std::string &currentFolder,
	                           const TiXmlElement &element,
	                           TileMap *&map,
	                           std::string &errorMessage) {
	}

	void addTileLayerFromElement(const TiXmlElement &element,
	                             TileMap *&map,
	                             std::string &errorMessage) {
	}

	void addObjectLayerFromElement(const TiXmlElement &element,
	                               TileMap *&map,
	                               std::string &errorMessage) {
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

	const std::string readNameFromElement(const TiXmlElement &element, TileMapEntity &entity) {

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
