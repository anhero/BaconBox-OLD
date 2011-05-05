#include "Vertex.h"

#include "PlatformFlagger.h"

#include "Sprite.h"

using namespace RedBox;

Vertex::Vertex() : Object(), position(Vec2()) {
}

Vertex::Vertex(float posX, float posY) : Object(), position(Vec2(posX, posY)) {
}

Vertex::Vertex(float* posX, float* posY) : Object(),
	position(Vec2(posX, posY)) {
}

Vertex::Vertex(const Vertex& src): Object(src), position(src.position) {
}

Vertex::~Vertex() {
}

Vertex& Vertex::operator=(const Vertex& src) {
	Object::operator=(src);
	copyFrom(src);
	return *this;
}

float Vertex::getXPosition() const {
	return position.getX();
}

float Vertex::getYPosition() const {
	return position.getY();
}

Vec2& Vertex::getPosition() {
	return position;
}

void Vertex::setXPosition(float xPos) {
	position.setX(xPos);
}

void Vertex::setYPosition(float yPos) {
	position.setY(yPos);
}

void Vertex::copyFrom(const Vertex& src) {
	if(this != &src && &src) {
		position = src.position;
	} else {
		position = Vec2();
	}
}

namespace RedBox {
	std::ostream& operator<<(std::ostream& output, const Vertex& v) {
		output << "{position: " << v.position << "}";
		return output;
	}
}
