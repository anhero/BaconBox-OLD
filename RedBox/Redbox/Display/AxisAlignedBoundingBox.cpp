#include "AxisAlignedBoundingBox.h"

#include <algorithm>

namespace RedBox {
	AxisAlignedBoundingBox::AxisAlignedBoundingBox() : Positionable(), size() {
	}

	AxisAlignedBoundingBox::AxisAlignedBoundingBox(const Vector2 &newPosition,
	                                               const Vector2 &newSize) :
		Positionable(newPosition), size(newSize) {
	}

	AxisAlignedBoundingBox::AxisAlignedBoundingBox(const AxisAlignedBoundingBox &src) :
		Positionable(src), size(src.size) {
	}

	AxisAlignedBoundingBox::~AxisAlignedBoundingBox() {
	}

	AxisAlignedBoundingBox &AxisAlignedBoundingBox::operator=(const AxisAlignedBoundingBox &src) {
		this->Positionable::operator=(src);

		if (this != &src) {
			size = src.size;
		}

		return *this;
	}

	bool AxisAlignedBoundingBox::operator==(const AxisAlignedBoundingBox &other) const {
		return getPosition() == other.getPosition() && size == other.size;
	}

	bool AxisAlignedBoundingBox::operator!=(const AxisAlignedBoundingBox &other) const {
		return !(*this == other);
	}

	const Vector2 AxisAlignedBoundingBox::getSize() const {
		return size;
	}

	void AxisAlignedBoundingBox::setSize(const Vector2 &newSize) {
		size = newSize;
	}

	void AxisAlignedBoundingBox::setSize(float newWidth, float newHeight) {
		size.setXY(newWidth, newHeight);
	}

	float AxisAlignedBoundingBox::getWidth() const {
		return size.getX();
	}

	void AxisAlignedBoundingBox::setWidth(float newWidth) {
		size.setX(newWidth);
	}

	float AxisAlignedBoundingBox::getHeight() const {
		return size.getY();
	}

	void AxisAlignedBoundingBox::setHeight(float newHeight) {
		size.setY(newHeight);
	}

	float AxisAlignedBoundingBox::getLeft() const {
		return std::min(getXPosition(), getXPosition() + size.getX());
	}

	float AxisAlignedBoundingBox::getRight() const {
		return std::max(getXPosition(), getXPosition() + size.getX());
	}

	float AxisAlignedBoundingBox::getTop() const {
		return std::min(getYPosition(), getYPosition() + size.getY());
	}

	float AxisAlignedBoundingBox::getBottom() const {
		return std::max(getYPosition(), getYPosition() + size.getY());
	}

	bool AxisAlignedBoundingBox::overlaps(const AxisAlignedBoundingBox &other) const {
		return getRight() > other.getLeft() && getLeft() < other.getRight() &&
		       getBottom() > other.getTop() && getTop() < other.getBottom();
	}

	bool AxisAlignedBoundingBox::overlaps(const Vector2 &point) const {
		return overlaps(point.getX(), point.getY());
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
