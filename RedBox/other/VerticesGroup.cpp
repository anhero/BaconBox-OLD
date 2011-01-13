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
            vertices[i].position.setIsPtr(true);
            vertices[i].position.setYPtr(&(verticesData[i*2+1]));
            vertices[i].position.setXPtr(&(verticesData[i*2]));
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
        vertices[i].position.setIsPtr(true);
        vertices[i].position.setYPtr(&(verticesData[i*2+1]));
        vertices[i].position.setXPtr(&(verticesData[i*2]));
    }
}

std::vector<Vertex>& VerticesGroup::getVertices() {
    return vertices;
}
std::vector<float>& VerticesGroup::getVerticesData() {
    return verticesData;
}
