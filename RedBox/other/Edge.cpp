#include "Edge.h"
#include "Vertex.h"

//using namespace RedBox;

RedBox::Edge::Edge(): v1(NULL), v2(NULL), distance(0.0f) {
}

RedBox::Edge::Edge(RedBox::Vertex* newV1, RedBox::Vertex* newV2): v1(newV1), v2(newV2) {
    recalculateDistance();
}

RedBox::Edge::Edge(const RedBox::Edge& src): v1(src.v1), v2(src.v2), distance(src.distance) {
}

RedBox::Edge::~Edge() {
}

void RedBox::Edge::copyFrom(const RedBox::Edge& src) {
    if(this != &src && &src) {
        distance = src.distance;
        v1 = src.v1;
        v2 = src.v2;
    }
}

RedBox::Edge& RedBox::Edge::operator=(const RedBox::Edge& src) {
    copyFrom(src);
    return *this;
}

RedBox::Vertex* RedBox::Edge::getV1() {
    return v1;
}

RedBox::Vertex* RedBox::Edge::getV2() {
    return v2;
}

void RedBox::Edge::setV1(RedBox::Vertex* newV1) {
    v1 = newV1;
    recalculateDistance();
}

void RedBox::Edge::setV2(RedBox::Vertex* newV2) {
    v2 = newV2;
    recalculateDistance();
}

float RedBox::Edge::recalculateDistance() {
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

float RedBox::Edge::getDistance() const {
    return distance;
}
std::ostream& RedBox::operator<<(std::ostream& output, const RedBox::Edge& e) {
    output << "Edge:{v1:" << e.v1 << "(" << e.v1->getPosition() << "), v2:" << e.v2 <<
    "(" << e.v2->getPosition() << "), distance:" << e.distance << "}";
    return output;
}
