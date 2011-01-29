#include "Sprite.h"

using namespace RedBox;



Sprite::Sprite(): Renderable() {
}

#ifdef RB_PHYSICS_ENABLED
Sprite::Sprite(const Sprite& src):Renderable(src), edges(src.edges), 
vertices(src.vertices), renderSteps(src.renderSteps) 
#else
Sprite::Sprite(const Sprite& src):Renderable(src), vertices(src.vertices), 
renderSteps(src.renderSteps) 
#endif
{
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

void Sprite::update() {
}

void Sprite::createVertex(float x, float y) {
    vertices.addVertex(x, y);
}

void Sprite::warnVerticesOfDeletion() {
    vertices.warnVerticesOfDeletion();
}

#ifdef RB_PHYSICS_ENABLED
void Sprite::createEdge(Vertex* firstVertex, Vertex* secondVertex) {
    // We make sure the pointers to the vertices given are valid.
    // They have to be different and they have to be part of the vertices group.
    if(firstVertex != secondVertex && vertices.containsVertices(firstVertex, secondVertex)) {
        // We add the edge to the list.
        edges.push_back(Edge(firstVertex, secondVertex));
    }
}

vertices.setParentGraphicBody(body);
}
#endif

void Sprite::clean() {
    renderSteps.clear();
	vertices.warnVerticesOfDeletion();
#ifdef RB_PHYSICS_ENABLED
    edges.clear();
#endif
}

void Sprite::copyFrom(const Sprite& src) {
    if(this != &src && &src) {
        renderSteps = src.renderSteps;
        vertices = src.vertices;
#ifdef RB_PHYSICS_ENABLED
        edges = src.edges;
#endif
    } else {
        clean();
    }
}
#ifdef RB_PHYSICS_ENABLED
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
#endif
