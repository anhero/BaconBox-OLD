#include "VerticesGroup.h"

using namespace RedBox;

VerticesGroup::VerticesGroup() {
}

VerticesGroup::~VerticesGroup() {
}

VerticesGroup::VerticesGroup(const VerticesGroup& src) {
    copyFrom(src);
}

void VerticesGroup::copyFrom(const VerticesGroup& src) {
    // We make sure the recieved VertexGroup isn't the instance and isn't null.
	if(this != &src && &src) {
        // Free all of the instance's allocated memory.
        clean();
        verticesData = src.verticesData;
        vertices.resize(src.vertices.size());
        for(int i = vertices.size(); i >= 0; i--) {
            vertices[i].getPosition().setIsPtr(true);
            vertices[i].getPosition().setYPtr(&(verticesData[i*2+1]));
            vertices[i].getPosition().setXPtr(&(verticesData[i*2]));
        }
	}
}

void VerticesGroup::clean() {
    verticesData.clear();
    vertices.clear();
}

VerticesGroup& VerticesGroup::operator=(const VerticesGroup& src) {
	copyFrom(src);
	return *this;
}

void VerticesGroup::addVertex(float x, float y) {
    verticesData.resize(verticesData.size() + 2);
    verticesData[verticesData.size()-1] = y;
    verticesData[verticesData.size()-2] = x;
    vertices.resize(vertices.size() + 1);
    for(int i = vertices.size(); i >= 0; i--) {
        vertices[i].getPosition().setIsPtr(true);
        vertices[i].getPosition().setYPtr(&(verticesData[i*2+1]));
        vertices[i].getPosition().setXPtr(&(verticesData[i*2]));
    }
}

std::vector<Vertex>& VerticesGroup::getVertices() {
    return vertices;
}
std::vector<float>& VerticesGroup::getVerticesData() {
    return verticesData;
}

bool VerticesGroup::containsVertices(Vertex* firstVertex, Vertex* secondVertex) {
    std::vector<Vertex>::iterator i = vertices.begin();
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
    for(std::vector<Vertex>::iterator i = vertices.begin(); i != vertices.end(); i++) {
        i->dontDeleteLinks();
    }
}

void Vertex::setParentGraphicBody(GraphicBody* body) {
    for(std::vector<Vertex>::iterator i = vertices.begin(); i != vertices.end(); i++) {
        i->setParentGraphicBody(body);
    }
}

void Vertex::setParentSprite(Sprite* sprite) {
    for(std::vector<Vertex>::iterator i = vertices.begin(); i != vertices.end(); i++) {
        i->setParentSprite(sprite);
    }
}