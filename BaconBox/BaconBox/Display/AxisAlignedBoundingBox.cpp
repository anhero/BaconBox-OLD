#include "AxisAlignedBoundingBox.h"

#include <algorithm>

namespace BaconBox {
	AxisAlignedBoundingBox::AxisAlignedBoundingBox() : position(), size() {
	}

	AxisAlignedBoundingBox::AxisAlignedBoundingBox(const Vector2 &newPosition,
	                                               const Vector2 &newSize) :
		position(newPosition), size(newSize) {
	}

	AxisAlignedBoundingBox::AxisAlignedBoundingBox(const AxisAlignedBoundingBox &src) :
		position(src.position), size(src.size) {
	}

	AxisAlignedBoundingBox &AxisAlignedBoundingBox::operator=(const AxisAlignedBoundingBox &src) {
		if (this != &src) {
			position = src.position;
			size = src.size;
		}

		return *this;
	}

	bool AxisAlignedBoundingBox::operator==(const AxisAlignedBoundingBox &other) const {
		return position == other.position && size == other.size;
	}

	bool AxisAlignedBoundingBox::operator!=(const AxisAlignedBoundingBox &other) const {
		return !(*this == other);
	}

	Vector2 &AxisAlignedBoundingBox::getPosition() {
		return position;
	}

	const Vector2 &AxisAlignedBoundingBox::getPosition() const {
		return position;
	}

	void AxisAlignedBoundingBox::setPosition(const Vector2 &newPosition) {
		position = newPosition;
	}

	void AxisAlignedBoundingBox::setPosition(float newXPosition, float newYPosition) {
		position.x = newXPosition;
		position.y = newYPosition;
	}

	void AxisAlignedBoundingBox::move(const Vector2 &delta) {
		position += delta;
	}

	void AxisAlignedBoundingBox::move(float xDelta, float yDelta) {
		position.x += xDelta;
		position.y += yDelta;
	}

	float AxisAlignedBoundingBox::getXPosition() const {
		return position.x;
	}

	void AxisAlignedBoundingBox::setXPosition(float newXPosition) {
		position.x = newXPosition;
	}

	void AxisAlignedBoundingBox::moveX(float xDelta) {
		position.x += xDelta;
	}

	float AxisAlignedBoundingBox::getYPosition() const {
		return position.y;
	}

	void AxisAlignedBoundingBox::setYPosition(float newYPosition) {
		position.y = newYPosition;
	}

	void AxisAlignedBoundingBox::moveY(float yDelta) {
		position.y += yDelta;
	}

	const Vector2 AxisAlignedBoundingBox::getPositionCenter() const {
		return Vector2(position + size * 0.5f);
	}

	float AxisAlignedBoundingBox::getXPositionCenter() const {
		return position.x + size.x * 0.5f;
	}

	float AxisAlignedBoundingBox::getYPositionCenter() const {
		return position.y + size.y * 0.5f;
	}

	Vector2 &AxisAlignedBoundingBox::getSize() {
		return size;
	}

	const Vector2 &AxisAlignedBoundingBox::getSize() const {
		return size;
	}

	void AxisAlignedBoundingBox::setSize(const Vector2 &newSize) {
		size = newSize;
	}

	void AxisAlignedBoundingBox::setSize(float newWidth, float newHeight) {
		size.x = newWidth;
		size.y = newHeight;
	}

	float AxisAlignedBoundingBox::getWidth() const {
		return size.x;
	}

	void AxisAlignedBoundingBox::setWidth(float newWidth) {
		size.x = newWidth;
	}

	float AxisAlignedBoundingBox::getHeight() const {
		return size.y;
	}

	void AxisAlignedBoundingBox::setHeight(float newHeight) {
		size.y = newHeight;
	}

	float AxisAlignedBoundingBox::getLeft() const {
		return position.x;
	}

	float AxisAlignedBoundingBox::getRight() const {
		return position.x + size.x;
	}

	float AxisAlignedBoundingBox::getTop() const {
		return position.y;
	}

	float AxisAlignedBoundingBox::getBottom() const {
		return position.y + size.y;
	}

	bool AxisAlignedBoundingBox::overlaps(const AxisAlignedBoundingBox &other) const {
		return getRight() > other.getLeft() && getLeft() < other.getRight() &&
		       getBottom() > other.getTop() && getTop() < other.getBottom();
	}

	bool AxisAlignedBoundingBox::overlaps(const Vector2 &point) const {
		return overlaps(point.x, point.y);
	}

	bool AxisAlignedBoundingBox::overlaps(float xPoint, float yPoint) const {
		return xPoint >= getLeft() && xPoint <= getRight() &&
		       yPoint >= getTop() && yPoint <= getBottom();
	}

	bool AxisAlignedBoundingBox::overlapsHorizontalLine(float yPosition,
	                                                    float lowerXBoundary,
	                                                    float higherXBoundary) const {
		// If the boundaries are reversed.
		if (lowerXBoundary > higherXBoundary) {
			// We swap them.
			float tmp = lowerXBoundary;
			lowerXBoundary = higherXBoundary;
			higherXBoundary = tmp;
		}

		return getBottom() > yPosition && getTop() < yPosition &&
		       getRight() > lowerXBoundary && getLeft() < higherXBoundary;
	}

	bool AxisAlignedBoundingBox::overlapsHorizontalLine(float yPosition) const {
		return getBottom() > yPosition && getTop() < yPosition;
	}

	bool AxisAlignedBoundingBox::overlapsVerticalLine(float xPosition,
	                                                  float lowerYBoundary,
	                                                  float higherYBoundary) const {
		// If the boundaries are reversed.
		if (lowerYBoundary > higherYBoundary) {
			// We swap them.
			float tmp = lowerYBoundary;
			lowerYBoundary = higherYBoundary;
			higherYBoundary = tmp;
		}

		return getRight() > xPosition && getLeft() < xPosition &&
		       getBottom() > lowerYBoundary && getTop() < higherYBoundary;
	}

	bool AxisAlignedBoundingBox::overlapsVerticalLine(float xPosition) const {
		return getRight() > xPosition && getLeft() < xPosition;
	}

	bool AxisAlignedBoundingBox::isCompletelyInside(const AxisAlignedBoundingBox &other) const {
		return this->getLeft() >= other.getLeft() &&
		       this->getRight() <= other.getRight() &&
		       this->getTop() >= other.getTop() &&
		       this->getBottom() <= other.getBottom();
	}
}
