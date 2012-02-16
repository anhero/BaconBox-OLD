#include "RectangleObject.h"

namespace RedBox {
	RectangleObject::RectangleObject(const std::string &newName,
	                                 const Vector2 &newPosition,
	                                 const Vector2 &newSize) :
		TileMapObject(newName, newPosition), size(newSize) {
	}

	RectangleObject::RectangleObject(const RectangleObject &src) :
		TileMapObject(src), size(src.size) {
	}

	RectangleObject::~RectangleObject() {
	}

	RectangleObject &RectangleObject::operator=(const RectangleObject &src) {
		this->TileMapObject::operator=(src);

		if (this != &src) {
			size = src.size;
		}

		return *this;
	}

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
}
