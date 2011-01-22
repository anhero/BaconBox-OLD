#include "Sprite.h"

using namespace RedBox;



Sprite::Sprite(): Renderable() {
}

Sprite::Sprite(const Sprite& src):Renderable(src), edges(src.edges), 
vertices(src.vertices), renderSteps(src.renderSteps) {
    //copyFrom(src);
}

Sprite::~Sprite() {
    clean();
}

Sprite& Sprite::operator=(const Sprite& src) {
    Renderable::operator=(src);
    copyFrom(src);
    return *this;
}

void Sprite::render() {
}

void Sprite::createEdge(Vertex* firstVertex, Vertex* secondVertex) {
    // We make sure the pointers to the vertices given are valid.
    // They have to be different and they have to be part of the vertices group.
    if(firstVertex != secondVertex && vertices.containsVertices(firstVertex, secondVertex)) {
        // We add the edge to the list.
        edges.push_back(Edge(firstVertex, secondVertex));
    }
}

void Sprite::createVertex(float x, float y) {
    vertices.addVertex(x, y);
}

void Sprite::warnVerticesOfDeletion() {
    vertices.warnVerticesOfDeletion();
}

void setParentGraphicBody(GraphicBody* body) {
	
}

void Sprite::clean() {
    renderSteps.clear();
	vertices.warnVerticesOfDeletion();
    vertices.clear();
    edges.clear();
}

void Sprite::copyFrom(const Sprite& src) {
    if(this != &src && &src) {
        renderSteps = src.renderSteps;
        vertices = src.vertices;
        edges = src.edges;
    } else {
        clean();
    }
}

void Sprite::removeEdge(Edge* edge) {
	bool notFound = true;
	std::vector<Edge>::iterator i = edges.begin();
	// We search for the edge to delete.
	while(notFound && i != edges.end()) {
        // If we found it.
        if(edge == &(*i)) {
			// We make sure to stop the loop.
            notFound = false;
            // We remove it from the list.
            edges.erase(i);
        } else {
            // If we haven't found it, we go to the next one.
            i++;
        }
	}       
}