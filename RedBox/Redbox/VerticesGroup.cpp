#include "VerticesGroup.h"

#include "Console.h"

#include <cassert>

using namespace RedBox;

VerticesGroup::VerticesGroup() : Object(), verticesCount(0), inBatch(false) {
}

VerticesGroup::VerticesGroup(const VerticesGroup& src) : Object(src),
	vertices(src.vertices){
        if(!inBatch){
            vertices = &(internalVertices[0]);
            verticesCount = internalVertices.size();
        }
        
}

VerticesGroup& VerticesGroup::operator=(const VerticesGroup& src) {
	Object::operator=(src);

	if(this != &src) {
		vertices = src.vertices;
        if(!inBatch){
            vertices = &(vertices[0]);
            verticesCount = internalVertices.size();
        }
	}

	return *this;
}

int VerticesGroup::getVerticesCount() const{
    return verticesCount;
}
void VerticesGroup::addVertex(float x, float y) {
        // We add the new vertex to the list.
        internalVertices.push_back(Vector2(x, y));
        verticesCount = internalVertices.size();
        vertices = &(internalVertices[0]);
}

void VerticesGroup::addVertices(unsigned int nbVertices, ...) {
	if(nbVertices) {
		va_list verticesCoords;
		va_start(verticesCoords, nbVertices);

		float x, y;

		for(unsigned int i = 0; i < nbVertices; ++i) {
			x = static_cast<float>(va_arg(verticesCoords, double));
			y = static_cast<float>(va_arg(verticesCoords, double));
			internalVertices.push_back(Vector2(x, y));
		}

		va_end(verticesCoords);
        
        verticesCount = internalVertices.size();
        vertices = &(internalVertices[0]);
	}
}

Vector2* VerticesGroup::getVertices(int & verticesCount) {
    verticesCount = this->verticesCount;
	return vertices;
}

Vector2 VerticesGroup::getSize() const {
	if(verticesCount < 1) {
		Console::print("Tried to get the width and the height of an empty VerticesGroup.");
		return Vector2();
	} else {

		float minX = vertices[0].getX(),
			  minY = vertices[0].getY(),
			  maxX = vertices[0].getX(),
			  maxY = vertices[0].getY();

		// We find the minimum and the maximum coordinates.
		for(int i = 0; i < verticesCount; i++) {
			if(vertices[i].getX() < minX) {
				minX = vertices[i].getX();
			} else if(vertices[i].getX() > maxX) {
				maxX = vertices[i].getX();
			}

			if(vertices[i].getY() < minY) {
				minY = vertices[i].getY();
			} else if(vertices[i].getY() > maxY) {
				maxY = vertices[i].getY();
			}
		}

		// We return the width and the height.
		return Vector2(maxX - minX, maxY - minY);
	}
}

float VerticesGroup::getWidth() const {
	if(verticesCount == 0) {
		Console::print("Tried to get the width of an empty VerticesGroup.");
		return 0.0f;
	}

	float minX = vertices[0].getX(),
	      maxX = vertices[0].getX();

	// We find the smallest and the highest x position.
	for(int i = 0; i < verticesCount; i++) {
		if(vertices[i].getX() < minX) {
			minX = vertices[i].getX();
		} else if(vertices[i].getX() > maxX) {
			maxX = vertices[i].getX();
		}
	}

	// We return their difference which results in the width.
	return maxX - minX;
}

float VerticesGroup::getHeight() const {
	if(verticesCount == 0) {
		Console::print("Tried to get the height of an empty VerticesGroup.");
		return 0.0f;
	}

	float minY = vertices[0].getY(),
	      maxY = vertices[0].getY();

	// We find the smallest and the highest y position.
    for(int i = 0; i < verticesCount; i++) {
		if(vertices[i].getY() < minY) {
			minY = vertices[i].getY();
		} else if(vertices[i].getY() > maxY) {
			maxY = vertices[i].getY();
		}
	}

	// We return their difference which results in the height.
	return maxY - minY;
}

Vector2 VerticesGroup::getPosition() const {
	if(vertices == 0) {
		Console::print("Tried to get the position of an empty VerticesGroup.");
		return Vector2();
	}

	Vector2 result(vertices[0].getX(),
	               vertices[0].getY());

	// We find the smallest vertical and horizontal position.
    for(int i = 0; i < verticesCount; i++) {
		if(vertices[i].getX() < result.getX()) {
			result.setX(vertices[i].getX());
		}

		if(vertices[i].getY() < result.getY()) {
			result.setY(vertices[i].getY());
		}
	}

	return result;
}

Vector2 VerticesGroup::getPositionCenter() const {
	if(vertices == 0) {
		Console::print("Tried to get the position of the center of an empty VerticesGroup.");
		return Vector2();
	}

	float minX = vertices[0].getX(),
	      minY = vertices[0].getY(),
	      maxX = vertices[0].getX(),
	      maxY = vertices[0].getY();

	// We find the minimum and the maximum coordinates.
    for(int i = 0; i < verticesCount; i++) {
		if(vertices[i].getX() < minX) {
			minX = vertices[i].getX();
		} else if(vertices[i].getX() > maxX) {
			maxX = vertices[i].getX();
		}

		if(vertices[i].getY() < minY) {
			minY = vertices[i].getY();
		} else if(vertices[i].getY() > maxY) {
			maxY = vertices[i].getY();
		}
	}

	// We return the width and the height.
	return Vector2(minX + (maxX - minX) * 0.5f, minY + (maxY - minY) * 0.5f);
}

void VerticesGroup::setPosition(float newXPosition, float newYPosition) {
	move(Vector2(newXPosition, newYPosition) - getPosition());
}

void VerticesGroup::move(float deltaX, float deltaY) {
	if(vertices == 0) {
		Console::print("Tried to move an empty vertices group.");
	}

    for(int i = 0; i < verticesCount; i++) {
		vertices[i].addToXY(deltaX, deltaY);
	}
}

void VerticesGroup::move(const Vector2& delta) {
	move(delta.getX(), delta.getY());
}

float VerticesGroup::getXPosition() const {
	if(vertices == 0) {
		Console::print("Tried to get the horizontal position of an empty VerticesGroup.");
		return 0.0f;
	} else {
		float result = vertices[0].getX();

		// We find the smallest horizontal position.
        for(int i = 0; i < verticesCount; i++) {
			if(vertices[i].getX() < result) {
				result = vertices[i].getX();
			}
		}

		return result;
	}
}
float VerticesGroup::getXPositionCenter() const {
	if(vertices == 0) {
		Console::print("Tried to get the horizontal position of an empty VerticesGroup.");
		return 0.0f;
	}

	float minX = vertices[0].getX(),
	      maxX = vertices[0].getX();

	// We find the smallest and the highest x position.
    for(int i = 0; i < verticesCount; i++) {
		if(vertices[i].getX() < minX) {
			minX = vertices[i].getX();
		} else if(vertices[i].getX() > maxX) {
			maxX = vertices[i].getX();
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
	if(vertices == 0) {
		Console::print("Tried to get the vertical position of an empty VerticesGroup.");
		return 0.0f;
	}

	float result = vertices[0].getY();

	// We find the smallest vertical position.
    for(int i = 0; i < verticesCount; i++) {
		if(vertices[i].getY() < result) {
			result = vertices[i].getY();
		}
	}

	return result;
}

float VerticesGroup::getYPositionCenter() const {
	if(vertices == 0) {
		Console::print("Tried to get the height of an empty VerticesGroup.");
		return 0.0f;
	}

	float minY = vertices[0].getY(),
	      maxY = vertices[0].getY();

	// We find the smallest and the highest y position.
    for(int i = 0; i < verticesCount; i++) {
		if(vertices[i].getY() < minY) {
			minY = vertices[i].getY();
		} else if(vertices[i].getY() > maxY) {
			maxY = vertices[i].getY();
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

    for(int i = 0; i < verticesCount; i++) {
		vertices[i].subtractFromXY(position);
		vertices[i].scalarMultiplication(factor.getX(), factor.getY());
		vertices[i].addToXY(position);
	}
}

void VerticesGroup::rotate(float angle, const Vector2& fromPoint) {
    for(int i = 0; i < verticesCount; i++) {
		vertices[i].subtractFromXY(fromPoint);
		vertices[i].rotate(angle);
		vertices[i].addToXY(fromPoint);
	}
}

namespace RedBox {
	std::ostream& operator<<(std::ostream& output, const VerticesGroup& v) {
		output << "{vertices: [";

        for(int i = 0; i < v.verticesCount; i++) {
			if(i != 0) {
				output << ", ";
			}

			output << v.vertices[i];
		}

		output << "]}";
		return output;
	}
}
