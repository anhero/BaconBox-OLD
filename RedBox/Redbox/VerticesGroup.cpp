#include "VerticesGroup.h"

#include "Console.h"

#include <cassert>

using namespace RedBox;

VerticesGroup::VerticesGroup() : Object(), vertices(NULL, 0), inBatch(false) {
}

VerticesGroup::VerticesGroup(const VerticesGroup& src) : Object(src),
	internalVertices(src.internalVertices), inBatch(src.inBatch) {
	if(!inBatch) {
		vertices.array = &(internalVertices[0]);
		vertices.elementCount = internalVertices.size();
	}
}

VerticesGroup& VerticesGroup::operator=(const VerticesGroup& src) {
	Object::operator=(src);

	if(this != &src) {
		internalVertices = src.internalVertices;
		inBatch = src.inBatch;

		if(!inBatch) {
			vertices.array = &(internalVertices[0]);
			vertices.elementCount = internalVertices.size();
		}
	}

	return *this;
}

unsigned int VerticesGroup::getVerticesCount() const {
	return vertices.elementCount;
}
void VerticesGroup::addVertex(float x, float y) {
	// We add the new vertex to the list.
	internalVertices.push_back(Vector2(x, y));
	vertices.elementCount = internalVertices.size();
	vertices.array = &(internalVertices[0]);
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
		vertices.elementCount = internalVertices.size();
		vertices.array = &(internalVertices[0]);
	}
}

CArray<Vector2>& VerticesGroup::getVertices() {
	return vertices;
}

const CArray<Vector2>& VerticesGroup::getVertices() const {
	return vertices;
}

Vector2 VerticesGroup::getSize() const {
	if(vertices.elementCount == 0) {
		Console::println("Tried to get the width and the height of an empty VerticesGroup.");
		return Vector2();

	} else {
		float minX = vertices.array[0].getX(),
		      minY = vertices.array[0].getY(),
		      maxX = vertices.array[0].getX(),
		      maxY = vertices.array[0].getY();

		// We find the minimum and the maximum coordinates.
		for(unsigned int i = 0; i < vertices.elementCount; ++i) {
			if(vertices.array[i].getX() < minX) {
				minX = vertices.array[i].getX();

			} else if(vertices.array[i].getX() > maxX) {
				maxX = vertices.array[i].getX();
			}

			if(vertices.array[i].getY() < minY) {
				minY = vertices.array[i].getY();

			} else if(vertices.array[i].getY() > maxY) {
				maxY = vertices.array[i].getY();
			}
		}

		// We return the width and the height.
		return Vector2(maxX - minX, maxY - minY);
	}
}

float VerticesGroup::getWidth() const {
	if(vertices.elementCount == 0) {
		Console::println("Tried to get the width of an empty VerticesGroup.");
		return 0.0f;
	}

	float minX = vertices.array[0].getX(),
	      maxX = vertices.array[0].getX();

	// We find the smallest and the highest x position.
	for(unsigned int i = 0; i < vertices.elementCount; ++i) {
		if(vertices.array[i].getX() < minX) {
			minX = vertices.array[i].getX();

		} else if(vertices.array[i].getX() > maxX) {
			maxX = vertices.array[i].getX();
		}
	}

	// We return their difference which results in the width.
	return maxX - minX;
}

float VerticesGroup::getHeight() const {
	if(vertices.elementCount == 0) {
		Console::println("Tried to get the height of an empty VerticesGroup.");
		return 0.0f;
	}

	float minY = vertices.array[0].getY(),
	      maxY = vertices.array[0].getY();

	// We find the smallest and the highest y position.
	for(unsigned int i = 0; i < vertices.elementCount; ++i) {
		if(vertices.array[i].getY() < minY) {
			minY = vertices.array[i].getY();

		} else if(vertices.array[i].getY() > maxY) {
			maxY = vertices.array[i].getY();
		}
	}

	// We return their difference which results in the height.
	return maxY - minY;
}

Vector2 VerticesGroup::getPosition() const {
	if(vertices.elementCount == 0) {
		Console::println("Tried to get the position of an empty VerticesGroup.");
		return Vector2();
	}

	Vector2 result(vertices.array[0].getX(),
	               vertices.array[0].getY());

	// We find the smallest vertical and horizontal position.
	for(unsigned int i = 0; i < vertices.elementCount; ++i) {
		if(vertices.array[i].getX() < result.getX()) {
			result.setX(vertices.array[i].getX());
		}

		if(vertices.array[i].getY() < result.getY()) {
			result.setY(vertices.array[i].getY());
		}
	}

	return result;
}

void VerticesGroup::setBatchPointer(Vector2 * verticesPointer){
    vertices.array = verticesPointer;
}


void VerticesGroup::setInternalBatchPointer(){
    std::vector<Vector2> tempVertices;
    for (unsigned int i = 0; i < vertices.elementCount; ++i) {
        tempVertices.push_back(vertices[i]);
    }
    
    internalVertices = tempVertices;
    vertices.array = &(internalVertices[0]);
}
Vector2 & VerticesGroup::operator[](unsigned int iterator){ 
    return vertices[iterator];
}


Vector2 VerticesGroup::getPositionCenter() const {
	if(vertices.elementCount == 0) {
		Console::println("Tried to get the position of the center of an empty VerticesGroup.");
		return Vector2();
	}

	float minX = vertices.array[0].getX(),
	      minY = vertices.array[0].getY(),
	      maxX = vertices.array[0].getX(),
	      maxY = vertices.array[0].getY();

	// We find the minimum and the maximum coordinates.
	for(unsigned int i = 0; i < vertices.elementCount; ++i) {
		if(vertices.array[i].getX() < minX) {
			minX = vertices.array[i].getX();

		} else if(vertices.array[i].getX() > maxX) {
			maxX = vertices.array[i].getX();
		}

		if(vertices.array[i].getY() < minY) {
			minY = vertices.array[i].getY();

		} else if(vertices.array[i].getY() > maxY) {
			maxY = vertices.array[i].getY();
		}
	}

	// We return the width and the height.
	return Vector2(minX + (maxX - minX) * 0.5f, minY + (maxY - minY) * 0.5f);
}

void VerticesGroup::setPosition(float newXPosition, float newYPosition) {
	move(Vector2(newXPosition, newYPosition) - getPosition());
}

void VerticesGroup::move(float deltaX, float deltaY) {
	if(vertices.elementCount == 0) {
		Console::println("Tried to move an empty vertices group.");
	}

	for(unsigned int i = 0; i < vertices.elementCount; ++i) {
		vertices.array[i].addToXY(deltaX, deltaY);
	}
}

void VerticesGroup::move(const Vector2& delta) {
	move(delta.getX(), delta.getY());
}

float VerticesGroup::getXPosition() const {
	if(vertices.array == 0) {
		Console::println("Tried to get the horizontal position of an empty VerticesGroup.");
		return 0.0f;

	} else {
		float result = vertices.array[0].getX();

		// We find the smallest horizontal position.
		for(unsigned int i = 0; i < vertices.elementCount; ++i) {
			if(vertices.array[i].getX() < result) {
				result = vertices.array[i].getX();
			}
		}

		return result;
	}
}
float VerticesGroup::getXPositionCenter() const {
	if(vertices.array == 0) {
		Console::println("Tried to get the horizontal position of an empty VerticesGroup.");
		return 0.0f;
	}

	float minX = vertices.array[0].getX(),
	      maxX = vertices.array[0].getX();

	// We find the smallest and the highest x position.
	for(unsigned int i = 0; i < vertices.elementCount; ++i) {
		if(vertices.array[i].getX() < minX) {
			minX = vertices.array[i].getX();

		} else if(vertices.array[i].getX() > maxX) {
			maxX = vertices.array[i].getX();
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
	if(vertices.array == 0) {
		Console::println("Tried to get the vertical position of an empty VerticesGroup.");
		return 0.0f;
	}

	float result = vertices.array[0].getY();

	// We find the smallest vertical position.
	for(unsigned int i = 0; i < vertices.elementCount; ++i) {
		if(vertices.array[i].getY() < result) {
			result = vertices.array[i].getY();
		}
	}

	return result;
}

float VerticesGroup::getYPositionCenter() const {
	if(vertices.array == 0) {
		Console::println("Tried to get the height of an empty VerticesGroup.");
		return 0.0f;
	}

	float minY = vertices.array[0].getY(),
	      maxY = vertices.array[0].getY();

	// We find the smallest and the highest y position.
	for(unsigned int i = 0; i < vertices.elementCount; ++i) {
		if(vertices.array[i].getY() < minY) {
			minY = vertices.array[i].getY();

		} else if(vertices.array[i].getY() > maxY) {
			maxY = vertices.array[i].getY();
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

void VerticesGroup::scale(const Vector2& factor, const Vector2& fromPoint) {
	for(unsigned int i = 0; i < vertices.elementCount; ++i) {
		vertices.array[i].subtractFromXY(fromPoint);
		vertices.array[i].scalarMultiplication(factor);
		vertices.array[i].addToXY(fromPoint);
	}
}

void VerticesGroup::rotate(float angle, const Vector2& fromPoint) {
	for(unsigned int i = 0; i < vertices.elementCount; ++i) {
		vertices.array[i].subtractFromXY(fromPoint);
		vertices.array[i].rotate(angle);
		vertices.array[i].addToXY(fromPoint);
	}
}

namespace RedBox {
	std::ostream& operator<<(std::ostream& output, const VerticesGroup& v) {
		output << "{vertices: [";

		for(unsigned int i = 0; i < v.vertices.elementCount; i++) {
			if(i != 0) {
				output << ", ";
			}

			output << v.vertices.array[i];
		}

		output << "]}";
		return output;
	}
}
