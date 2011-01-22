#include "Vertex.h"

using namespace RedBox;

Vertex::Vertex() {
    position.setXPtr(NULL);
    position.setYPtr(NULL);
#ifdef REDBOX_PHYSICS_ENABLED
	oldPosition.setXPtr(NULL);
	oldPosition.setXPtr(NULL);
#endif
}

Vertex::Vertex(float posX, float posY ) {
	position.setX(posX);
	position.setY(posY);
#ifdef REDBOX_PHYSICS_ENABLED
	oldPosition.setX(posX);
	oldPosition.setY(posY);
#endif
}

Vertex::Vertex(const Vertex& src): position(src.position), parentEdges(src.parentEdges), parentLinks(src.parentLinks), parentRenderSteps(src.parentRenderSteps) {
}

Vertex::~Vertex() {
}

void Vertex::copyFrom(const Vertex& src) {
    if(this != &src && &src) {
        position = src.position;
        parentEdges = src.parentEdges;
        parentLinks = src.parentLinks;
        parentRenderSteps = src.parentRenderSteps;
    }
}

Vertex& Vertex::operator=(const Vertex &src) {
    copyFrom(src);
    return *this;
}

std::vector<Edge*>& Vertex::getParentEdges() {
    return parentEdges;
}
std::vector<Link*>& Vertex::getParentLinks() {
    return parentLinks;
}
std::vector<RenderStep*> Vertex::getParentRenderSteps() {
    return parentRenderSteps;
}
float Vertex::getXPosition() const {
    return position.getX();
}
float Vertex::getYPosition() const {
    return position.getY();
}
Vec2& Vertex::getPosition() {
    return position;
}
void Vertex::setXPosition(float xPos) {
    position.setX(xPos);
}
void Vertex::setYPosition(float yPos) {
    position.setY(yPos);
}
void Vertex::deleteFromParentSprite() {
}
void Vertex::deleteFromParentBody() {
}
