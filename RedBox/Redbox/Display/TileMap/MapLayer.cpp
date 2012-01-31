#include "MapLayer.h"

namespace RedBox {
	MapLayer::MapLayer() : name(), width(0u), height(0u), visible(true),
		properties(), data() {
	}

	MapLayer::MapLayer(const MapLayer &src) : name(src.name), width(src.width),
		height(src.height), visible(src.visible), properties(src.properties),
		data(src.data) {
	}

	MapLayer &MapLayer::operator=(const MapLayer &src) {
		if (this != &src) {
			name = src.name;
			width = src.width;
			height = src.height;
			visible = src.visible;
			properties = src.properties;
			data = src.data;
		}

		return *this;
	}

	const std::string &MapLayer::getName() const {
		return name;
	}

	void MapLayer::setName(const std::string &newName) {
		name = newName;
	}

	MapLayer::DataVector::value_type &MapLayer::operator[](MapLayer::DataVector::size_type index) {
		return data[index];
	}

	MapLayer::DataVector::value_type MapLayer::operator[](MapLayer::DataVector::size_type index) const {
		return data[index];
	}

	PropertyMap::mapped_type &MapLayer::operator[](const PropertyMap::key_type &key) {
		return properties[key];
	}

	unsigned int MapLayer::getWidth() const {
		return width;
	}

	void MapLayer::setWidth(unsigned int newWidth) {
		width = newWidth;
		data.resize(width * height, 0u);
	}

	unsigned int MapLayer::getHeight() const {
		return height;
	}

	void MapLayer::setHeight(unsigned int newHeight) {
		height = newHeight;
		data.resize(width * height, 0u);
	}

	void MapLayer::setSize(unsigned int newWidth, unsigned int newHeight) {
		width = newWidth;
		height = newHeight;
		data.resize(width * height, 0u);
	}

	bool MapLayer::isVisible() const {
		return visible;
	}

	void MapLayer::setVisible(bool newVisible) {
		visible = newVisible;
	}

	const PropertyMap &MapLayer::getProperties() const {
		return properties;
	}

	void MapLayer::addProperty(const PropertyMap::key_type &newKey,
	                           const PropertyMap::mapped_type &newValue,
	                           bool overwrite) {
		this->addProperty(std::make_pair(newKey, newValue), overwrite);
	}

	void MapLayer::addProperty(const PropertyMap::value_type &newProperty,
	                           bool overwrite) {
		std::pair<PropertyMap::iterator, bool> inserted = properties.insert(newProperty);

		if (overwrite && !inserted.second) {
			inserted.first->second = newProperty.second;
		}
	}

	const MapLayer::DataVector &MapLayer::getData() const {
		return data;
	}

	MapLayer::DataVector::value_type &MapLayer::getDataAt(MapLayer::DataVector::size_type index) {
		return data[index];
	}

	MapLayer::DataVector::value_type MapLayer::getDataAt(MapLayer::DataVector::size_type index) const {
		return data[index];
	}
}
