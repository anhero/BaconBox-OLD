#include "RectangleObject.h"

#include "ObjectLayer.h"

namespace BaconBox {
	void RectangleObject::setName(const std::string &newName) {
		if (!parentLayer.getRectangle(newName)) {
			this->TileMapObject::setName(newName);
			parentLayer.dirtyRectangleNames = true;
		}
	}

	const Vector2 RectangleObject::getSize() const {
		return size;
	}

	void RectangleObject::setSize(const Vector2 &newSize) {
		size = newSize;
	}

	void RectangleObject::setSize(float newWidth, float newHeight) {
		size.x = newWidth;
		size.y = newHeight;
	}

	float RectangleObject::getWidth() const {
		return size.x;
	}

	void RectangleObject::setWidth(float newWidth) {
		size.x = newWidth;
	}

	float RectangleObject::getHeight() const {
		return size.y;
	}

	void RectangleObject::setHeight(float newHeight) {
		size.y = newHeight;
	}

	RectangleObject::RectangleObject(const std::string &newName,
	                                 const Vector2 &newPosition,
	                                 const ObjectLayer &newParentLayer,
	                                 const Vector2 &newSize) :
		TileMapObject(newName, newPosition, newParentLayer), size(newSize) {
	}

	RectangleObject::RectangleObject(const RectangleObject &src,
	                                 const ObjectLayer &newParentLayer) :
		TileMapObject(src, newParentLayer), size(src.size) {
	}

	RectangleObject::~RectangleObject() {
	}
}
