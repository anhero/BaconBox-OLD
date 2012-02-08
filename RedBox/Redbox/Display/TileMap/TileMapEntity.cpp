#include "TileMapEntity.h"

namespace RedBox {
	TileMapEntity::TileMapEntity(const std::string &newName) : name(newName),
		properties() {
	}

	TileMapEntity::TileMapEntity(const TileMapEntity &src) : name(src.name),
		properties(src.properties) {
	}

	TileMapEntity::~TileMapEntity() {
	}

	TileMapEntity &TileMapEntity::operator=(const TileMapEntity &src) {
		if (this != &src) {
			name = src.name;
			properties = src.properties;
		}

		return *this;
	}

	PropertyMap &TileMapEntity::getProperties() {
		return properties;
	}

	const PropertyMap &TileMapEntity::getProperties() const {
		return properties;
	}

	const std::string &TileMapEntity::getName() const {
		return name;
	}

	void TileMapEntity::setName(const std::string &newName) {
		name = newName;
	}
}
