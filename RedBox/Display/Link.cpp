#include "PlatformFlagger.h"

#ifdef RB_PHYSICS_ENABLED
#include "Link.h"

using namespace RedBox;

Link::Link():info(LinkData(0.0f,0.0f,0.0f,0.0f,0.0f)) {
}

Link::Link(const Link& src): info(src.info), vertices(src.vertices) {
}

Link::~Link() {
}

Link& Link::operator=(const Link& l) {
    copyFrom(l);
    return *this;
}

void Link::copyFrom(const Link& src) {
    if(this != &src && &src) {
        vertices = src.vertices;
        info = src.info;
    }
}

LinkData& Link::getInfo() {
    return info;
}
std::list<Vertex*>& Link::getVertices() {
    return vertices;
}
Vertex* Link::addVertex(Vertex* newVertex, Sprite* parentSprite, GraphicBody* parentGraphicBody) {
    if(!containsVertex(newVertex)) {
        vertices.push_back(newVertex);
        newVertex->setParentSprite(parentSprite);
        newVertex->setParentGraphicBody(parentGraphicBody);
        newVertex->addParentLink(this);
    }
    return newVertex;
}

bool Link::containsVertex(Vertex* vertex) {
    bool notFound = true;
    std::list<Vertex*>::iterator i = vertices.begin();
    while(notFound && i != vertices.end()) {
        if(vertex == *i) {
            notFound = false;
        }
        i++;
    }
    return !notFound;
}

std::ostream& RedBox::operator<<(std::ostream& output, const Link& l) {
	output << "{info: " << l.info << ", vertices: [";
	for(std::list<Vertex*>::const_iterator i = l.vertices.begin(); i != l.vertices.end(); i++) {
		if(i != l.vertices.begin()) {
			output << ", ";
		}
		output << *i;
	}
	output << "]}";
	return output;
}
#endif