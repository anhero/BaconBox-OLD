#include "RectangleObject.h"

namespace RedBox {
	const Vector2 RectangleObject::getSize() const {
		return size;
	}

	void RectangleObject::setSize(const Vector2 &newSize) {
		size = newSize;
	}

	void RectangleObject::setSize(float newWidth, float newHeight) {
		size.setXY(newWidth, newHeight);
	}

	float RectangleObject::getWidth() const {
		return size.getX();
	}

	void RectangleObject::setWidth(float newWidth) {
		size.setX(newWidth);
	}

	float RectangleObject::getHeight() const {
		return size.getY();
	}

	void RectangleObject::setHeight(float newHeight) {
		size.setY(newHeight);
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
