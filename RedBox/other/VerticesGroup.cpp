#include "VerticesGroup.h"

#include "Debug.h"

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

#ifdef RB_PHYSICS_ENABLED
void VerticesGroup::addVertex(float x, float y, Sprite* sprite, 
                              GraphicBody* graphicBody)
#else
void VerticesGroup::addVertex(float x, float y, Sprite* sprite)
#endif
{
	if(vertices.size() > 1) {
		sprite = vertices.front().getParentSprite();
#ifdef RB_PHYSICS_ENABLED
		graphicBody = vertices.front().getParentGraphicBody();
#endif
	}
	// We add the new vertex to the list.
#ifdef RB_PHYSICS_ENABLED
	vertices.push_back(Vertex(x, y, sprite, graphicBody));
#else
	vertices.push_back(Vertex(x, y, sprite));
#endif
}

void VerticesGroup::addVertices(unsigned int nbVertices, ...) {
	if (nbVertices) {
		va_list verticesCoords;
		va_start(verticesCoords, nbVertices);
		Sprite* parentSprite = ((vertices.size()) ? (vertices.front().getParentSprite()):(NULL));
#ifdef RB_PHYSICS_ENABLED
		GraphicBody* parentGraphicBody = ((vertices.size()) ? (vertices.front().getParentGraphicBody()):(NULL));
#endif
		for(unsigned int i = 0; i < nbVertices; i++) {
#ifdef RB_PHYSICS_ENABLED
			vertices.push_back(Vertex(static_cast<float>(va_arg(verticesCoords, double)), static_cast<float>(va_arg(verticesCoords, double)), parentSprite, parentGraphicBody));
#else
			vertices.push_back(Vertex(static_cast<float>(va_arg(verticesCoords, double)), static_cast<float>(va_arg(verticesCoords, double)), parentSprite));
#endif
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

void VerticesGroup::warnVerticesOfDeletion() {
    for(std::list<Vertex>::iterator i = vertices.begin(); i != vertices.end(); i++) {
        i->warnOfParentSpriteDeletion();
    }
}

void VerticesGroup::setParentSprite(Sprite* sprite) {
    for(std::list<Vertex>::iterator i = vertices.begin(); i != vertices.end(); i++) {
        i->setParentSprite(sprite);
    }
}

std::pair<float, float> VerticesGroup::getWidthHeight() const {
	if(vertices.size() == 0) {
		$ECHO("Tried to get the width and the height of an empty VerticesGroup.");
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
	if(vertices.size() == 0) {
		$ECHO("Tried to get the width of an empty VerticesGroup.");
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
	if(vertices.size() == 0) {
		$ECHO("Tried to get the height of an empty VerticesGroup.");
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

#ifdef RB_PHYSICS_ENABLED
void VerticesGroup::setParentGraphicBody(GraphicBody* body) {
    for(std::list<Vertex>::iterator i = vertices.begin(); i != vertices.end(); i++) {
        i->setParentGraphicBody(body);
    }
}
#endif

#ifdef RB_PHYSICS_ENABLED
void VerticesGroup::updateVerticesFromData(std::vector<float>& verticesData, Sprite* sprite, GraphicBody* graphicBody)
#else
void VerticesGroup::updateVerticesFromData(std::vector<float>& verticesData, Sprite* sprite)
#endif
{
	std::vector<float>::iterator data = verticesData.begin();
	std::list<Vertex>::iterator vertex = vertices.begin();
	if(!vertices.empty()) {
		sprite = vertices.front().getParentSprite();
#ifdef RB_PHYSICS_ENABLED
		graphicBody = vertices.front().getParentGraphicBody();
#endif
	}
	while (data != verticesData.end()) {
		if (vertex != vertices.end()) {
			vertex->getPosition().setXPtr(&(*data));
			++data;
			if(data != verticesData.end()) {
				vertex->getPosition().setYPtr(&(*data));
			} else {
				$ECHO("Tried to update vertices from vertices data with an incorrect number of vertices data.");
			}
		} else {
#ifdef RB_PHYSICS_ENABLED
			vertices.push_back(Vertex(&(*data), &(*(++data)), sprite, graphicBody));
#else
			vertices.push_back(Vertex(&(*data), &(*(++data)), sprite));
#endif
		}
	}
}

void VerticesGroup::updateDataFromVertices(std::vector<float>& verticesData) {
	assert(verticesData.size() % 2 == 0);
	// We make sure the sizes are different.
	if (vertices.size() * 2 != verticesData.size()) {
		// We initialize the temporary data vector.
		std::vector<float> tmpData(vertices.size() * 2, 0.0f);
		std::vector<float>& shortest = (verticesData.size() < tmpData.size()) ? (verticesData) : (tmpData);
		std::vector<float>::iterator srcData = verticesData.begin();
		std::vector<float>::iterator dstData = tmpData.begin();
		for(unsigned int i = 0; i >= shortest.size(); ++i) {
			*dstData = *srcData;
			++srcData;
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