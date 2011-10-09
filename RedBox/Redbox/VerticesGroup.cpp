#include "VerticesGroup.h"

#include "Console.h"

#include <cassert>

using namespace RedBox;

VerticesGroup::VerticesGroup() : Object(), inBatch(false), verticesCount(0){
}

VerticesGroup::VerticesGroup(const VerticesGroup& src) : Object(src), inBatch(false), verticesCount(0) {
    for (unsigned int i = 0; i < src.vertices.size(); i++) {
        internalVertices.push_back(Vector2(*(src.vertices[i])));
    }
    reconstructFrontVertices();
}

VerticesGroup& VerticesGroup::operator=(const VerticesGroup& src) {
	Object::operator=(src);
    
	if(this != &src) {
        

		for (unsigned int i = 0; i < src.vertices.size(); i++) {
            internalVertices.push_back(Vector2(*(src.vertices[i])));
        }
        reconstructFrontVertices();
        
	}
	return *this;
}



void VerticesGroup::reconstructFrontVertices(){
    vertices.clear();
    verticesCount = internalVertices.size();
    for (unsigned int i =0; i < verticesCount; i++) {
        vertices.push_back(&internalVertices[i]);
    }
    
}




unsigned int VerticesGroup::getVerticesCount() const {
	return verticesCount;
}


void VerticesGroup::addVertex(float x, float y) {
	// We add the new vertex to the list.
    if (!inBatch) {
        internalVertices.push_back(Vector2(x,y));
        reconstructFrontVertices();
    }
    else{
        Console::print("You are trying to add vertices to a sprite in a renderbatch. This operation is not supported at the moment");
    }
	
}

void VerticesGroup::addVertices(unsigned int nbVertices, ...) {
	if(nbVertices) {
        if (!inBatch) {
            va_list verticesCoords;
            va_start(verticesCoords, nbVertices);
            float x, y;
            
            for(unsigned int i = 0; i < nbVertices; ++i) {
                x = static_cast<float>(va_arg(verticesCoords, double));
                y = static_cast<float>(va_arg(verticesCoords, double));
                internalVertices.push_back(Vector2(x, y));
            }
            
            va_end(verticesCoords);
            reconstructFrontVertices();
            
        }
        else{
            Console::print("You are trying to add vertices to a sprite in a renderbatch. This operation is not supported at the moment");
        }
	}
}

std::vector<Vector2*>& VerticesGroup::getVertices() {
	return vertices;
}

const std::vector<Vector2*>& VerticesGroup::getVertices() const {
	return vertices;
}

Vector2 VerticesGroup::getSize() const {
	if(verticesCount == 0) {
		Console::println("Tried to get the width and the height of an empty VerticesGroup.");
		return Vector2();
        
	} else {
		float minX = vertices[0]->getX(),
        minY = vertices[0]->getY(),
        maxX = vertices[0]->getX(),
        maxY = vertices[0]->getY();
        
		// We find the minimum and the maximum coordinates.
		for(unsigned int i = 0; i < verticesCount; ++i) {
			if(vertices[i]->getX() < minX) {
				minX = vertices[i]->getX();
                
			} else if(vertices[i]->getX() > maxX) {
				maxX = vertices[i]->getX();
			}
            
			if(vertices[i]->getY() < minY) {
				minY = vertices[i]->getY();
                
			} else if(vertices[i]->getY() > maxY) {
				maxY = vertices[i]->getY();
			}
		}
        
		// We return the width and the height.
		return Vector2(maxX - minX, maxY - minY);
	}
}

float VerticesGroup::getWidth() const {
	if(verticesCount == 0) {
		Console::println("Tried to get the width of an empty VerticesGroup.");
		return 0.0f;
	}
    
	float minX = vertices[0]->getX(),
    maxX = vertices[0]->getX();
    
	// We find the smallest and the highest x position.
	for(unsigned int i = 0; i < verticesCount; ++i) {
		if(vertices[i]->getX() < minX) {
			minX = vertices[i]->getX();
            
		} else if(vertices[i]->getX() > maxX) {
			maxX = vertices[i]->getX();
		}
	}
    
	// We return their difference which results in the width.
	return maxX - minX;
}

float VerticesGroup::getHeight() const {
	if(verticesCount == 0) {
		Console::println("Tried to get the height of an empty VerticesGroup.");
		return 0.0f;
	}
    
	float minY = vertices[0]->getY(),
    maxY = vertices[0]->getY();
    
	// We find the smallest and the highest y position.
	for(unsigned int i = 0; i < verticesCount; ++i) {
		if(vertices[i]->getY() < minY) {
			minY = vertices[i]->getY();
            
		} else if(vertices[i]->getY() > maxY) {
			maxY = vertices[i]->getY();
		}
	}
    
	// We return their difference which results in the height.
	return maxY - minY;
}

Vector2 VerticesGroup::getPosition() const {
	if(verticesCount == 0) {
		Console::println("Tried to get the position of an empty VerticesGroup.");
		return Vector2();
	}
    
	Vector2 result(vertices[0]->getX(),
	               vertices[0]->getY());
    
	// We find the smallest vertical and horizontal position.
	for(unsigned int i = 0; i < verticesCount; ++i) {
		if(vertices[i]->getX() < result.getX()) {
			result.setX(vertices[i]->getX());
		}
        
		if(vertices[i]->getY() < result.getY()) {
			result.setY(vertices[i]->getY());
		}
	}
    
	return result;
}

void VerticesGroup::setBatchPointer(Vector2 * verticesPointer){
    vertices.clear();
    for (unsigned int i =0; i < verticesCount; i++) {
        vertices.push_back(&(verticesPointer[i]));
    }
}


void VerticesGroup::setInternalBatchPointer(){
    std::vector<Vector2*> tempVertices;
    for (unsigned int i = 0; i < verticesCount; ++i) {
        tempVertices.push_back(vertices[i]);
    }
    vertices = tempVertices;
}
Vector2 & VerticesGroup::operator[](unsigned int iterator){ 
    return *(vertices[iterator]);
}


Vector2 VerticesGroup::getPositionCenter() const {
	if(verticesCount == 0) {
		Console::println("Tried to get the position of the center of an empty VerticesGroup.");
		return Vector2();
	}
    
	float minX = vertices[0]->getX(),
    minY = vertices[0]->getY(),
    maxX = vertices[0]->getX(),
    maxY = vertices[0]->getY();
    
	// We find the minimum and the maximum coordinates.
	for(unsigned int i = 0; i < verticesCount; ++i) {
		if(vertices[i]->getX() < minX) {
			minX = vertices[i]->getX();
            
		} else if(vertices[i]->getX() > maxX) {
			maxX = vertices[i]->getX();
		}
        
		if(vertices[i]->getY() < minY) {
			minY = vertices[i]->getY();
            
		} else if(vertices[i]->getY() > maxY) {
			maxY = vertices[i]->getY();
		}
	}
    
	// We return the width and the height.
	return Vector2(minX + (maxX - minX) * 0.5f, minY + (maxY - minY) * 0.5f);
}

void VerticesGroup::setPosition(float newXPosition, float newYPosition) {
	move(Vector2(newXPosition, newYPosition) - getPosition());
}

void VerticesGroup::move(float deltaX, float deltaY) {
	if(verticesCount == 0) {
		Console::println("Tried to move an empty vertices group.");
	}
    
	for(unsigned int i = 0; i < verticesCount; ++i) {
		vertices[i]->addToXY(deltaX, deltaY);
	}
}

void VerticesGroup::move(const Vector2& delta) {
	move(delta.getX(), delta.getY());
}

float VerticesGroup::getXPosition() const {
	if(verticesCount == 0) {
		Console::println("Tried to get the horizontal position of an empty VerticesGroup.");
		return 0.0f;
        
	} else {
		float result = vertices[0]->getX();
        
		// We find the smallest horizontal position.
		for(unsigned int i = 0; i < verticesCount; ++i) {
			if(vertices[i]->getX() < result) {
				result = vertices[i]->getX();
			}
		}
        
		return result;
	}
}
float VerticesGroup::getXPositionCenter() const {
	if(verticesCount == 0) {
		Console::println("Tried to get the horizontal position of an empty VerticesGroup.");
		return 0.0f;
	}
    
	float minX = vertices[0]->getX(),
    maxX = vertices[0]->getX();
    
	// We find the smallest and the highest x position.
	for(unsigned int i = 0; i < verticesCount; ++i) {
		if(vertices[i]->getX() < minX) {
			minX = vertices[i]->getX();
            
		} else if(vertices[i]->getX() > maxX) {
			maxX = vertices[i]->getX();
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
	if(verticesCount == 0) {
		Console::println("Tried to get the vertical position of an empty VerticesGroup.");
		return 0.0f;
	}
    
	float result = vertices[0]->getY();
    
	// We find the smallest vertical position.
	for(unsigned int i = 0; i < verticesCount; ++i) {
		if(vertices[i]->getY() < result) {
			result = vertices[i]->getY();
		}
	}
    
	return result;
}

float VerticesGroup::getYPositionCenter() const {
	if(verticesCount == 0) {
		Console::println("Tried to get the height of an empty VerticesGroup.");
		return 0.0f;
	}
    
	float minY = vertices[0]->getY(),
    maxY = vertices[0]->getY();
    
	// We find the smallest and the highest y position.
	for(unsigned int i = 0; i < verticesCount; ++i) {
		if(vertices[i]->getY() < minY) {
			minY = vertices[i]->getY();
            
		} else if(vertices[i]->getY() > maxY) {
			maxY = vertices[i]->getY();
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
	for(unsigned int i = 0; i < verticesCount; ++i) {
		vertices[i]->subtractFromXY(fromPoint);
		vertices[i]->scalarMultiplication(factor);
		vertices[i]->addToXY(fromPoint);
	}
}

void VerticesGroup::rotate(float angle, const Vector2& fromPoint) {
	for(unsigned int i = 0; i < verticesCount; ++i) {
		vertices[i]->subtractFromXY(fromPoint);
		vertices[i]->rotate(angle);
		vertices[i]->addToXY(fromPoint);
	}
}

namespace RedBox {
	std::ostream& operator<<(std::ostream& output, const VerticesGroup& v) {
		output << "{vertices: [";
        
		for(unsigned int i = 0; i < v.verticesCount; i++) {
			if(i != 0) {
				output << ", ";
			}
            
			output << v.vertices[i];
		}
        
		output << "]}";
		return output;
	}
}
