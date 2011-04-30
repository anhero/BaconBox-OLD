#include "VerticesGroup.h"

#include "Debug.h"

#include "PlatformFlagger.h"

#include <iostream>

#include <cfloat>
#include <cassert>


using namespace RedBox;

VerticesGroup::VerticesGroup() {
}

VerticesGroup::VerticesGroup(const VerticesGroup& src) {
    copyFrom(src);
}

VerticesGroup::~VerticesGroup() {
}

VerticesGroup& VerticesGroup::operator=(const VerticesGroup& src) {
	copyFrom(src);
	return *this;
}


void VerticesGroup::addVertex(float x, float y)
{
	// We add the new vertex to the list.
	vertices.push_back(Vertex(x, y));
}

void VerticesGroup::addVertices(unsigned int nbVertices, ...) {
	if (nbVertices) {
		va_list verticesCoords;
		va_start(verticesCoords, nbVertices);

		float x, y;
		for(unsigned int i = 0; i < nbVertices; i++) {
			x = static_cast<float>(va_arg(verticesCoords, double));
			y = static_cast<float>(va_arg(verticesCoords, double));
			vertices.push_back(Vertex(x, y));
		}
		va_end(verticesCoords);
	}
}

void VerticesGroup::deleteVertex(Vertex* vertexToDelete) {
	// We remove the vertex from the list, but we take note of its pointer to
	// its x value.
	float* xPtr = NULL;
	std::list<Vertex>::iterator itr = vertices.begin();
	while(itr != vertices.end()) {
		if(vertexToDelete == &(*itr)) {
			xPtr = itr->getPosition().getXPtr();
			vertices.erase(itr);
			itr = vertices.end();
		} else {
			itr++;
		}
	}
}

std::list<Vertex>& VerticesGroup::getVertices() {
    return vertices;
}

bool VerticesGroup::containsVertices(Vertex* firstVertex, Vertex* secondVertex) {
    std::list<Vertex>::iterator i = vertices.begin();
    bool firstNotFound = true, secondNotFound = true;
    while((firstNotFound || secondNotFound) && i != vertices.end()) {
        if(&(*i) == firstVertex) {
            firstNotFound = false;
        }
        if(&(*i) == secondVertex) {
            secondNotFound = false;
        }
        i++;
    }
    return !(firstNotFound || secondNotFound);
}



std::pair<float, float> VerticesGroup::getWidthHeight() const {
	if(vertices.size() == 0) {
		RB_ECHO("Tried to get the width and the height of an empty VerticesGroup.");
		return std::pair<float, float>(0.0f, 0.0f);
	}
	std::pair<float, float>(FLT_MAX, FLT_MIN);
	float minX = FLT_MAX, minY = FLT_MAX, maxX = FLT_MIN, maxY = FLT_MIN;
	// We find the minimum and the maximum coordinates.
	for(std::list<Vertex>::const_iterator i = vertices.begin(); i != vertices.end(); i++) {
		if(i->getXPosition() < minX) {
			minX = i->getXPosition();
		}
		if(i->getXPosition() > maxX) {
			maxX = i->getXPosition();
		}
		if(i->getYPosition() < minY) {
			minY = i->getYPosition();
		}
		if(i->getYPosition() > maxY) {
			maxY = i->getYPosition();
		}
	}
	// We return the width and the height.
	return std::pair<float, float>(maxX - minX, maxY - minY);
}

float VerticesGroup::getWidth() const {
	if(vertices.empty()) {
		RB_ECHO("Tried to get the width of an empty VerticesGroup.");
		return 0.0f;
	}
	float minX = FLT_MAX, maxX = FLT_MIN;
	// We find the smallest and the highest x position.
	for(std::list<Vertex>::const_iterator i = vertices.begin(); i != vertices.end(); i++) {
		if(i->getXPosition() < minX) {
			minX = i->getXPosition();
		}
		if(i->getXPosition() > maxX) {
			maxX = i->getXPosition();
		}
	}
	// We return their difference which results in the width.
	return maxX - minX;
}

float VerticesGroup::getHeight() const {
	if(vertices.empty()) {
		RB_ECHO("Tried to get the height of an empty VerticesGroup.");
		return 0.0f;
	}
	float minY = FLT_MAX, maxY = FLT_MIN;
	// We find the smallest and the highest y position.
	for(std::list<Vertex>::const_iterator i = vertices.begin(); i != vertices.end(); i++) {
		if(i->getYPosition() < minY) {
			minY = i->getYPosition();
		}
		if(i->getYPosition() > maxY) {
			maxY = i->getYPosition();
		}
	}
	// We return their difference which results in the height.
	return maxY - minY;
}

float VerticesGroup::getXPosition() const {
	if(vertices.empty()) {
		RB_ECHO("Tried to get the horizontal position of an empty VerticesGroup.");
		return 0.0f;
	}
	float result = FLT_MAX;
	// We find the smallest horizontal position.
	for(std::list<Vertex>::const_iterator i = vertices.begin();
		i != vertices.end(); i++) {
		if(i->getXPosition() < result) {
			result = i->getXPosition();
		}
	}
	return result;
}

float VerticesGroup::getYPosition() const {
	if(vertices.empty()) {
		RB_ECHO("Tried to get the vertical position of an empty VerticesGroup.");
		return 0.0f;
	}
	float result = FLT_MAX;
	// We find the smallest vertical position.
	for(std::list<Vertex>::const_iterator i = vertices.begin();
		i != vertices.end(); i++) {
		if(i->getYPosition() < result) {
			result = i->getYPosition();
		}
	}
	return result;
}

std::pair<float, float> VerticesGroup::getPosition() const {
	if(vertices.empty()) {
		RB_ECHO("Tried to get the position of an empty VerticesGroup.");
		return std::pair<float, float>(0.0f, 0.0f);
	}
	std::pair<float, float> result(FLT_MAX, FLT_MAX);
	// We find the smallest vertical and horizontal position.
	for(std::list<Vertex>::const_iterator i = vertices.begin();
		i != vertices.end(); i++) {
		if(i->getXPosition() < result.first) {
			result.first = i->getXPosition();
		}
		if(i->getYPosition() < result.second) {
			result.second = i->getYPosition();
		}
	}
	return result;
}

void VerticesGroup::setXPosition(float x) {
	Vec2 vec(x - getXPosition(), 0.0f);
	for (std::list<Vertex>::iterator i = vertices.begin(); i != vertices.end(); i++) {
		i->getPosition() += vec;

	}
}

void VerticesGroup::setYPosition(float y) {
	Vec2 vec(0.0f, y - getYPosition());
	for (std::list<Vertex>::iterator i = vertices.begin(); i != vertices.end(); i++) {
		i->getPosition() += vec;

	}
}

void VerticesGroup::setPosition(float x, float y) {
	// We calculate the vector we'll add to every vertices.
	std::pair<float, float> position = getPosition();
	Vec2 vec(x - position.first, y - position.second);
	for (std::list<Vertex>::iterator i = vertices.begin(); i != vertices.end(); i++) {
		i->getPosition() += vec;
	}
}

void VerticesGroup::moveX(float deltaX) {
	move(deltaX, 0.0f);
}

void VerticesGroup::moveY(float deltaY) {
	move(0.0f, deltaY);
}

void VerticesGroup::move(float deltaX, float deltaY) {
	if (vertices.empty()) {
		RB_ECHO("Tried to move an empty vertices group.");
	}
	// We create the vector we'll add to every vertices.
	Vec2 deltaVec(deltaX, deltaY);
	for(std::list<Vertex>::iterator i = vertices.begin();
		i != vertices.end(); i++) {
		i->getPosition() += deltaVec;
	}
}





void VerticesGroup::updateDataFromVertices(std::vector<float>& verticesData) {
	assert(verticesData.size() % 2 == 0);
	// We make sure the sizes are different.
	if (vertices.size() * 2 != verticesData.size()) {
		// First, we make a temporary copy of the vertices data.
		std::vector<float> tmpData(vertices.size() * 2, 0.0f);
		std::vector<float>& shortest = (verticesData.size() < tmpData.size()) ? (verticesData) : (tmpData);
		std::vector<float>::iterator srcData = verticesData.begin();
		std::vector<float>::iterator dstData = tmpData.begin();
		std::list<Vertex>::iterator srcVertex = vertices.begin();
		for(unsigned int i = 0; i < shortest.size(); ++i) {
			*dstData = *srcData;
			++srcData;
			++dstData;
			if(i % 2 == 1) {
				++srcVertex;
			}
		}
		// Next, if the vertices data became larger, we finish filling it up.
		while (dstData != tmpData.end()) {
			*dstData = srcVertex->getXPosition();
			++dstData;
			*dstData = srcVertex->getYPosition();
			++dstData;
			++srcVertex;
		}
		// We copy the temporary values in the real vertices data.
		verticesData = tmpData;
		// We synchronize the vertices with the data.
		dstData = verticesData.begin();
		for(srcVertex = vertices.begin(); srcVertex != vertices.end();
			srcVertex++) {
			srcVertex->getPosition().setIsPtr(true);
			srcVertex->getPosition().setXPtr(&(*dstData));
			++dstData;
			srcVertex->getPosition().setYPtr(&(*dstData));
			++dstData;
		}
	}
}

void VerticesGroup::resetPointers() {
    // We reset the vertices' pointers to the correct new floats.
}

void VerticesGroup::copyFrom(const VerticesGroup& src) {
    // We make sure the recieved VertexGroup isn't the instance and isn't null.
	if(this != &src && &src) {
		vertices.clear();
		vertices = src.vertices;
	}
}

void VerticesGroup::clean() {
    vertices.clear();
}

namespace RedBox {
	std::ostream& operator<<(std::ostream& output, const VerticesGroup& v) {
		output << "{vertices: [";
		for(std::list<Vertex>::const_iterator i = v.vertices.begin();
			i != v.vertices.end();
			i++) {
			if(i != v.vertices.begin()) {
				output << ", ";
			}
			output << *i;
		}
		output << "]}";
		return output;
	}
}
