#include "VerticesGroup.h"

#include "Console.h"

#include <cassert>

using namespace RedBox;

VerticesGroup::VerticesGroup() : Object() {
}

VerticesGroup::VerticesGroup(const VerticesGroup& src) : Object(src),
	vertices(src.vertices) {
}

VerticesGroup& VerticesGroup::operator=(const VerticesGroup& src) {
	Object::operator=(src);

	if(this != &src) {
		vertices = src.vertices;
	}

	return *this;
}

void VerticesGroup::addVertex(float x, float y) {
	// We add the new vertex to the list.
	vertices.push_back(Vector2(x, y));
}

void VerticesGroup::addVertices(unsigned int nbVertices, ...) {
	if(nbVertices) {
		va_list verticesCoords;
		va_start(verticesCoords, nbVertices);

		float x, y;

		for(unsigned int i = 0; i < nbVertices; ++i) {
			x = static_cast<float>(va_arg(verticesCoords, double));
			y = static_cast<float>(va_arg(verticesCoords, double));
			vertices.push_back(Vector2(x, y));
		}

		va_end(verticesCoords);
	}
}

std::vector<Vector2>& VerticesGroup::getVertices() {
	return vertices;
}

const std::vector<Vector2>& VerticesGroup::getVertices() const {
	return vertices;
}

Vector2 VerticesGroup::getSize() const {
	if(vertices.empty()) {
		Console::print("Tried to get the width and the height of an empty VerticesGroup.");
		return Vector2();
	} else {

		float minX = vertices.front().getX(),
			  minY = vertices.front().getY(),
			  maxX = vertices.front().getX(),
			  maxY = vertices.front().getY();

		// We find the minimum and the maximum coordinates.
		for(std::vector<Vector2>::const_iterator i = vertices.begin();
			i != vertices.end(); ++i) {
			if(i->getX() < minX) {
				minX = i->getX();
			} else if(i->getX() > maxX) {
				maxX = i->getX();
			}

			if(i->getY() < minY) {
				minY = i->getY();
			} else if(i->getY() > maxY) {
				maxY = i->getY();
			}
		}

		// We return the width and the height.
		return Vector2(maxX - minX, maxY - minY);
	}
}

float VerticesGroup::getWidth() const {
	if(vertices.empty()) {
		Console::print("Tried to get the width of an empty VerticesGroup.");
		return 0.0f;
	}

	float minX = vertices.front().getX(),
	      maxX = vertices.front().getX();

	// We find the smallest and the highest x position.
	for(std::vector<Vector2>::const_iterator i = vertices.begin();
	    i != vertices.end(); ++i) {
		if(i->getX() < minX) {
			minX = i->getX();
		} else if(i->getX() > maxX) {
			maxX = i->getX();
		}
	}

	// We return their difference which results in the width.
	return maxX - minX;
}

float VerticesGroup::getHeight() const {
	if(vertices.empty()) {
		Console::print("Tried to get the height of an empty VerticesGroup.");
		return 0.0f;
	}

	float minY = vertices.front().getY(),
	      maxY = vertices.front().getY();

	// We find the smallest and the highest y position.
	for(std::vector<Vector2>::const_iterator i = vertices.begin();
	    i != vertices.end(); ++i) {
		if(i->getY() < minY) {
			minY = i->getY();
		} else if(i->getY() > maxY) {
			maxY = i->getY();
		}
	}

	// We return their difference which results in the height.
	return maxY - minY;
}

Vector2 VerticesGroup::getPosition() const {
	if(vertices.empty()) {
		Console::print("Tried to get the position of an empty VerticesGroup.");
		return Vector2();
	}

	Vector2 result(vertices.front().getX(),
	               vertices.front().getY());

	// We find the smallest vertical and horizontal position.
	for(std::vector<Vector2>::const_iterator i = vertices.begin();
	    i != vertices.end(); ++i) {
		if(i->getX() < result.getX()) {
			result.setX(i->getX());
		}

		if(i->getY() < result.getY()) {
			result.setY(i->getY());
		}
	}

	return result;
}

Vector2 VerticesGroup::getPositionCenter() const {
	if(vertices.size() == 0) {
		Console::print("Tried to get the position of the center of an empty VerticesGroup.");
		return Vector2();
	}

	float minX = vertices.front().getX(),
	      minY = vertices.front().getY(),
	      maxX = vertices.front().getX(),
	      maxY = vertices.front().getY();

	// We find the minimum and the maximum coordinates.
	for(std::vector<Vector2>::const_iterator i = vertices.begin();
	    i != vertices.end(); ++i) {
		if(i->getX() < minX) {
			minX = i->getX();
		} else if(i->getX() > maxX) {
			maxX = i->getX();
		}

		if(i->getY() < minY) {
			minY = i->getY();
		} else if(i->getY() > maxY) {
			maxY = i->getY();
		}
	}

	// We return the width and the height.
	return Vector2(minX + (maxX - minX) * 0.5f, minY + (maxY - minY) * 0.5f);
}

void VerticesGroup::setPosition(float newXPosition, float newYPosition) {
	move(Vector2(newXPosition, newYPosition) - getPosition());
}

void VerticesGroup::move(float deltaX, float deltaY) {
	if(vertices.empty()) {
		Console::print("Tried to move an empty vertices group.");
	}

	for(std::vector<Vector2>::iterator i = vertices.begin();
	    i != vertices.end(); ++i) {
		i->addToXY(deltaX, deltaY);
	}
}

void VerticesGroup::move(const Vector2& delta) {
	move(delta.getX(), delta.getY());
}

float VerticesGroup::getXPosition() const {
	if(vertices.empty()) {
		Console::print("Tried to get the horizontal position of an empty VerticesGroup.");
		return 0.0f;
	} else {
		float result = vertices.front().getX();

		// We find the smallest horizontal position.
		for(std::vector<Vector2>::const_iterator i = vertices.begin();
			i != vertices.end(); ++i) {
			if(i->getX() < result) {
				result = i->getX();
			}
		}

		return result;
	}
}
float VerticesGroup::getXPositionCenter() const {
	if(vertices.empty()) {
		Console::print("Tried to get the horizontal position of an empty VerticesGroup.");
		return 0.0f;
	}

	float minX = vertices.front().getX(),
	      maxX = vertices.front().getX();

	// We find the smallest and the highest x position.
	for(std::vector<Vector2>::const_iterator i = vertices.begin();
	    i != vertices.end(); ++i) {
		if(i->getX() < minX) {
			minX = i->getX();
		} else if(i->getX() > maxX) {
			maxX = i->getX();
		}
	}

	// We return their difference which results in the width.
	return minX + (maxX - minX) * 0.5f;
}

void VerticesGroup::setXPosition(float newXPosition) {
	moveX(newXPosition - getXPosition());
}

void VerticesGroup::moveX(float deltaX) {
	move(deltaX, 0.0f);
}

float VerticesGroup::getYPosition() const {
	if(vertices.empty()) {
		Console::print("Tried to get the vertical position of an empty VerticesGroup.");
		return 0.0f;
	}

	float result = vertices.front().getY();

	// We find the smallest vertical position.
	for(std::vector<Vector2>::const_iterator i = vertices.begin();
	    i != vertices.end(); ++i) {
		if(i->getY() < result) {
			result = i->getY();
		}
	}

	return result;
}

float VerticesGroup::getYPositionCenter() const {
	if(vertices.empty()) {
		Console::print("Tried to get the height of an empty VerticesGroup.");
		return 0.0f;
	}

	float minY = vertices.front().getY(),
	      maxY = vertices.front().getY();

	// We find the smallest and the highest y position.
	for(std::vector<Vector2>::const_iterator i = vertices.begin();
	    i != vertices.end(); ++i) {
		if(i->getY() < minY) {
			minY = i->getY();
		} else if(i->getY() > maxY) {
			maxY = i->getY();
		}
	}

	// We return their difference which results in the height.
	return minY + (maxY - minY) * 0.5f;
}

void VerticesGroup::setYPosition(float newYPosition) {
	moveY(newYPosition - getYPosition());
}

void VerticesGroup::moveY(float deltaY) {
	move(0.0f, deltaY);
}

void VerticesGroup::scale(const Vector2& factor) {
	Vector2 position = getPositionCenter();

	for(std::vector<Vector2>::iterator i = vertices.begin();
	    i != vertices.end(); ++i) {
		i->subtractFromXY(position);
		i->scalarMultiplication(factor.getX(), factor.getY());
		i->addToXY(position);
	}
}

void VerticesGroup::rotate(float angle, const Vector2& fromPoint) {
	for(std::vector<Vector2>::iterator i = vertices.begin();
	    i != vertices.end(); ++i) {
		i->subtractFromXY(fromPoint);
		i->rotate(angle);
		i->addToXY(fromPoint);
	}
}

namespace RedBox {
	std::ostream& operator<<(std::ostream& output, const VerticesGroup& v) {
		output << "{vertices: [";

		for(std::vector<Vector2>::const_iterator i = v.vertices.begin();
		    i != v.vertices.end();
		    ++i) {
			if(i != v.vertices.begin()) {
				output << ", ";
			}

			output << *i;
		}

		output << "]}";
		return output;
	}
}
