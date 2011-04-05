#include "PlatformFlagger.h"

#ifdef RB_PHYSICS_ENABLED
#include "Edge.h"

#include "Vertex.h"

using namespace RedBox;

Edge::Edge(): distance(0.0f), v1(NULL), v2(NULL) {
}

Edge::Edge(Vertex* newV1, Vertex* newV2): v1(newV1), v2(newV2) {
    recalculateDistance();
}

Edge::Edge(const Edge& src): v1(src.v1), v2(src.v2), distance(src.distance) {
}

Edge::~Edge() {
}

void Edge::copyFrom(const Edge& src) {
    if(this != &src && &src) {
        distance = src.distance;
        v1 = src.v1;
        v2 = src.v2;
    }
}

Edge& Edge::operator=(const Edge& src) {
    copyFrom(src);
    return *this;
}

Vertex* Edge::getV1() {
    return v1;
}

Vertex* Edge::getV2() {
    return v2;
}

void Edge::setV1(Vertex* newV1) {
    v1 = newV1;
    recalculateDistance();
}

void Edge::setV2(Vertex* newV2) {
    v2 = newV2;
    recalculateDistance();
}

float Edge::recalculateDistance() {
    // We make sure the vertices are valid.
    if(v1 != NULL && v2 != NULL) {
        // Get the horizontal and vertical distances between the two vertices.
        float x = fabs(v2->getPosition().getX() - v1->getPosition().getX());
        float y = fabs(v2->getPosition().getY() - v1->getPosition().getY());
        // Use the pythagorean theorem to get the distance between the two
        // vertices.
        distance = sqrtf( x*x + y*y );
    } else {
        // If the vertices aren't both valid, the edge has a length of 0.
        distance = 0.0f;
    }
    return distance;
}

float Edge::getDistance() const {
    return distance;
}

namespace RedBox {
	std::ostream& operator<<(std::ostream& output, const Edge& e) {
		output << "{v1: " << e.v1 << ", v2:" << e.v2 << ", distance:" <<
		e.distance << "}";
		return output;
	}
}
#endif
