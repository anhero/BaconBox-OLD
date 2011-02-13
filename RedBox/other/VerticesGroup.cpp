#include "VerticesGroup.h"

#include "Debug.h"

#include <cfloat>

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
	// We resize the verticesData and add its new floats.
    verticesData.resize(verticesData.size() + 2);
    verticesData[verticesData.size()-1] = y;
    verticesData[verticesData.size()-2] = x;
    
	// We reset the pointers correctly.
	resetPointers();
	
	if(vertices.size() > 1) {
		sprite = vertices.front().getParentSprite();
#ifdef RB_PHYSICS_ENABLED
		graphicBody = vertices.front().getParentGraphicBody();
#endif
	}
	// We add the new vertex to the list.
	vertices.push_back(Vertex());
	vertices.back().getPosition().setIsPtr(true);
	vertices.back().getPosition().setXPtr(&(verticesData[verticesData.size()-2]));
	vertices.back().getPosition().setYPtr(&(verticesData[verticesData.size()-1]));
	vertices.back().setParentSprite(sprite);
#ifdef RB_PHYSICS_ENABLED
	vertices.back().setParentGraphicBody(graphicBody);
#endif
}

void VerticesGroup::addVertices(unsigned int nbVertices, ...) {
	va_list verticesCoords;
	va_start(verticesCoords, nbVertices);
	// We resize the verticesData vector.
	unsigned int initialSize = verticesData.size();
	verticesData.resize(verticesData.size() + nbVertices * 2);
	for(unsigned int i = 0; i < nbVertices; i++) {
		verticesData[i * 2 + initialSize] = va_arg(verticesCoords, float);
		verticesData[i * 2 + 1 + initialSize] = va_arg(verticesCoords, float);
	}
	va_end(verticesCoords);
	
	// We reset the pointers correctly.
	resetPointers();
	
	Sprite* parentSprite = ((vertices.size()) ? (vertices.front().getParentSprite()):(NULL));
#ifdef RB_PHYSICS_ENABLED
	GraphicBody* parentGraphicBody = ((vertices.size()) ? (vertices.front().getParentGraphicBody()):(NULL));
#endif
	for(unsigned int i = 0; i < nbVertices; i++) {
		vertices.push_back(Vertex());
		vertices.back().getPosition().setIsPtr(true);
		vertices.back().getPosition().setXPtr(&(verticesData[i * 2 + initialSize]));
		vertices.back().getPosition().setYPtr(&(verticesData[i * 2 + 1 + initialSize]));
		vertices.back().setParentSprite(parentSprite);
#ifdef RB_PHYSICS_ENABLED
		vertices.back().setParentGraphicBody(parentGraphicBody);
#endif
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
	// We remove the vertex's data from the vector.
	if(xPtr != NULL) {
		std::vector<float>::iterator i = verticesData.begin();
		while(i != verticesData.end()) {
			if(xPtr == &(*i)) {
				i = verticesData.erase(i);
				verticesData.erase(i);
			}
		}
	}
	// We re-set the pointers.
	resetPointers();
}

std::list<Vertex>& VerticesGroup::getVertices() {
    return vertices;
}
std::vector<float>& VerticesGroup::getVerticesData() {
    return verticesData;
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

void VerticesGroup::resetPointers() {
    // We reset the vertices' pointers to the correct new floats.
	int i = 0;
	std::list<Vertex>::iterator itr = vertices.begin();
	while(i < vertices.size() && itr != vertices.end()) {
        itr->getPosition().setIsPtr(true);
        itr->getPosition().setYPtr(&(verticesData[i*2+1]));
        itr->getPosition().setXPtr(&(verticesData[i*2]));
		i++;
		itr++;
	}
}

void VerticesGroup::copyFrom(const VerticesGroup& src) {
    // We make sure the recieved VertexGroup isn't the instance and isn't null.
	if(this != &src && &src) {
        // Free all of the instance's allocated memory.
        clean();
        verticesData = src.verticesData;
        vertices.resize(src.vertices.size());
		int i = 0;
		for(std::list<Vertex>::iterator itr = vertices.begin(); itr != vertices.end(); i++) {
			itr->getPosition().setIsPtr(true);
			itr->getPosition().setYPtr(&(verticesData[i*2+1]));
			itr->getPosition().setXPtr(&(verticesData[i*2]));
			i++;
		}
	}
}

void VerticesGroup::clean() {
    verticesData.clear();
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
		output << "], verticesData: [";
		for(std::vector<float>::const_iterator i = v.verticesData.begin();
			i != v.verticesData.end();
			i++) {
			if(i != v.verticesData.begin()) {
				output << ", ";
			}
			output << *i;
		}
		output << "]}";
		return output;
	}
}