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
std::vector<Vertex*>& Link::getVertices() {
    return vertices;
}
