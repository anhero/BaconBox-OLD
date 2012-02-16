#include "TileMapObject.h"

namespace RedBox {
	TileMapObject::TileMapObject(const std::string &newName,
								 const Vector2 &newPosition) :
		TileMapEntity(newName), position(newPosition) {
	}

	TileMapObject::TileMapObject(const std::string &newName,
								 float newXPosition,
								 float newYPosition) :
		TileMapEntity(newName), position(newXPosition, newYPosition) {
	}

	TileMapObject::TileMapObject(const TileMapObject &src) : TileMapEntity(src),
		position(src.position) {
	}

	TileMapObject::~TileMapObject() {
	}

	TileMapObject &TileMapObject::operator=(const TileMapObject &src) {
		this->TileMapEntity::operator=(src);

		if (this != &src) {
			position = src.position;
		}

		return *this;
	}

	const Vector2 &TileMapObject::getPosition() const {
		return position;
	}

	void TileMapObject::setPosition(const Vector2 &newPosition) {
		position = newPosition;
	}

	void TileMapObject::setPosition(float newXPosition, float newYPosition) {
		position.setXY(newXPosition, newYPosition);
	}

	float TileMapObject::getXPosition() const {
		return position.getX();
	}

	void TileMapObject::setXPosition(float newXPosition) {
		position.setX(newXPosition);
	}

	float TileMapObject::getYPosition() const {
		return position.getY();
	}

	void TileMapObject::setYPosition(float newYPosition) {
		position.setY(newYPosition);
	}
}
