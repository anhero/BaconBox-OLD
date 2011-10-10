#include "Positionable.h"

namespace RedBox {
	Positionable::Positionable() : position() {
	}

	Positionable::Positionable(const Vector2 &newPosition) :
		position(newPosition) {
	}

	Positionable::Positionable(const Positionable &src) :
		position(src.position) {
	}

	Positionable::~Positionable() {
	}

	Positionable &Positionable::operator=(const Positionable &src) {
		if (this != &src) {
			position = src.position;
		}

		return *this;
	}

	const Vector2 &Positionable::getPosition() const {
		return position;
	}

	void Positionable::setPosition(const Vector2 &newPosition) {
		move(newPosition - position);
	}

	void Positionable::setPosition(float newXPosition, float newYPosition) {
		move(newXPosition - position.getX(), newYPosition - position.getY());
	}

	void Positionable::move(const Vector2 &delta) {
		move(delta.getX(), delta.getY());
	}

	void Positionable::move(float xDelta, float yDelta) {
		position.addToXY(xDelta, yDelta);
	}

	float Positionable::getXPosition() const {
		return position.getX();
	}

	void Positionable::setXPosition(float newXPosition) {
		move(newXPosition - position.getX(), 0.0f);
	}

	void Positionable::moveX(float xDelta) {
		move(xDelta, 0.0f);
	}

	float Positionable::getYPosition() const {
		return position.getY();
	}

	void Positionable::setYPosition(float newYPosition) {
		move(0.0f, newYPosition - position.getY());
	}

	void Positionable::moveY(float yDelta) {
		move(0.0f, yDelta);
	}

	const Vector2 Positionable::getPositionCenter() const {
		return Vector2(getXPosition() + getWidth() * 0.5f, getYPosition() + getHeight() * 0.5f);
	}

	float Positionable::getXPositionCenter() const {
		return getXPosition() + getWidth() * 0.5f;
	}

	float Positionable::getYPositionCenter() const {
		return getYPosition() + getHeight() * 0.5f;
	}

	const Vector2 Positionable::getCentroid() const {
		return Vector2(getXPosition() + getWidth() * 0.5f, getYPosition() + getHeight() * 0.5f);
	}

	float Positionable::getXCentroid() const {
		return getCentroid().getX();
	}

	float Positionable::getYCentroid() const {
		return getCentroid().getY();
	}

	const Vector2 Positionable::getSize() const {
		return Vector2(getWidth(), getHeight());
	}
}
