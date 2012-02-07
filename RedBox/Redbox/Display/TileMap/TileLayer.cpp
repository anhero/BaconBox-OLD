#include "TileLayer.h"

namespace RedBox {
	TileLayer::TileLayer() : name(), width(0u), height(0u), visible(true),
		color(Color::WHITE), properties(), data() {
	}

	TileLayer::TileLayer(const TileLayer &src) : name(src.name), width(src.width),
	    height(src.height), visible(src.visible), color(src.color),
	    properties(src.properties), data(src.data) {
	}

	TileLayer &TileLayer::operator=(const TileLayer &src) {
		if (this != &src) {
			name = src.name;
			width = src.width;
			height = src.height;
			visible = src.visible;
			properties = src.properties;
			data = src.data;
			color = src.color;
		}

		return *this;
	}

	const std::string &TileLayer::getName() const {
		return name;
	}

	void TileLayer::setName(const std::string &newName) {
		name = newName;
	}

	TileLayer::DataVector::value_type &TileLayer::operator[](TileLayer::DataVector::size_type index) {
		return data[index];
	}

	TileLayer::DataVector::value_type TileLayer::operator[](TileLayer::DataVector::size_type index) const {
		return data[index];
	}

	PropertyMap::mapped_type &TileLayer::operator[](const PropertyMap::key_type &key) {
		return properties[key];
	}

	unsigned int TileLayer::getWidth() const {
		return width;
	}

	void TileLayer::setWidth(unsigned int newWidth) {
		width = newWidth;
		data.resize(width * height, 0u);
	}

	unsigned int TileLayer::getHeight() const {
		return height;
	}

	void TileLayer::setHeight(unsigned int newHeight) {
		height = newHeight;
		data.resize(width * height, 0u);
	}

	void TileLayer::setSize(unsigned int newWidth, unsigned int newHeight) {
		width = newWidth;
		height = newHeight;
		data.resize(width * height, 0u);
	}

	bool TileLayer::isVisible() const {
		return visible;
	}

	void TileLayer::setVisible(bool newVisible) {
		visible = newVisible;
	}

	const Color &TileLayer::getColor() const {
		return color;
	}

	void TileLayer::setColor(const Color &newColor) {
		color = newColor;
	}

	uint8_t TileLayer::getAlpha() const {
		return color.getAlpha();
	}

	void TileLayer::setAlpha(int32_t newAlpha) {
		color.setAlpha(newAlpha);
	}

	const PropertyMap &TileLayer::getProperties() const {
		return properties;
	}

	void TileLayer::addProperty(const PropertyMap::key_type &newKey,
	                            const PropertyMap::mapped_type &newValue,
	                            bool overwrite) {
		this->addProperty(std::make_pair(newKey, newValue), overwrite);
	}

	void TileLayer::addProperty(const PropertyMap::value_type &newProperty,
	                            bool overwrite) {
		std::pair<PropertyMap::iterator, bool> inserted = properties.insert(newProperty);

		if (overwrite && !inserted.second) {
			inserted.first->second = newProperty.second;
		}
	}

	const TileLayer::DataVector &TileLayer::getData() const {
		return data;
	}

	TileLayer::DataVector::value_type &TileLayer::getDataAt(TileLayer::DataVector::size_type index) {
		return data[index];
	}

	TileLayer::DataVector::value_type TileLayer::getDataAt(TileLayer::DataVector::size_type index) const {
		return data[index];
	}
}
