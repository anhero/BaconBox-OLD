#include "Vertex.h"

using namespace RedBox;

Vertex::Vertex(): parentGraphicBody(NULL), parentSprite(NULL), deleteLinks(true) {
    position.setXPtr(NULL);
    position.setYPtr(NULL);
#ifdef REDBOX_PHYSICS_ENABLED
	oldPosition.setXPtr(NULL);
	oldPosition.setXPtr(NULL);
#endif
}

Vertex::Vertex(float posX, float posY ): parentGraphicBody(NULL), 
parentSprite(NULL), deleteLinks(true) {
	position.setX(posX);
	position.setY(posY);
#ifdef REDBOX_PHYSICS_ENABLED
	oldPosition.setX(posX);
	oldPosition.setY(posY);
#endif
}

Vertex::Vertex(const Vertex& src): position(src.position), 
parentEdges(src.parentEdges), parentLinks(src.parentLinks), 
parentRenderSteps(src.parentRenderSteps), parentSprite(NULL), 
parentGraphicBody(NULL), deleteLinks(true) {
}

Vertex::~Vertex() {
    clearLinks();
    clearEdges();
}

void Vertex::copyFrom(const Vertex& src) {
    clean();
    if(this != &src && &src) {
        position = src.position;
        parentEdges = src.parentEdges;
        parentLinks = src.parentLinks;
        parentRenderSteps = src.parentRenderSteps;
        parentSprite = src.parentSprite;
        parentGraphicBody = src.parentGraphicBody;
    } else {
        position = Vec2();
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
    if(parentSprite) {
        clearEdges();
    }
}
void Vertex::deleteFromParentBody() {
    
}
Sprite* Vertex::getParentSprite() {
    return parentSprite;
}
GraphicBody* Vertex::getParentGraphicBody() {
    return parentGraphicBody;
}
void Vertex::setParentSprite(Sprite* newParentSprite) {
    parentSprite = newParentSprite;
}
void Vertex::setParentGraphicBody(GraphicBody* newParentGraphicBody) {
    parentGraphicBody = newParentGraphicBody;
}

void Vertex::dontDeleteLinks() {
    deleteLinks = false;
}

void Vertex::warnOfParentSpriteDeletion() {
    edges.clear();
}

Link* Vertex::addParentLink(Link* link) {
    if(!containsParentLink(link)) {
        parentLinks.push_back(link);
    }
    return link;
}

bool Vertex::containsParentLink(Link* link) {
    bool notFound = true;
    std::vector<Link*>::iterator i = parentLinks.begin();
    while(notFound && i != parentLinks.end()) {
        if(*i == link) {
            notFound = false;
        }
        i++;
    }
    return !notFound;
}

void Vertex::clearLinks() {
    if(deleteLinks) {
        for(std::vector<Link*>::iterator i = parentLinks.begin(); i != parentLinks.end(); i++) {
            if(*i)
                delete *(i);
        }
    }
    parentLinks.clear();
}

void Vertex::clearEdges() {
    // We check if the sprite isn't NULL.
    if(parentSprite) {
        // For each of the vertex's edges.
        for(std::vector<Edge*>::iterator i = parentEdges.begin(); i != parentEdges.end(); i++) {
            // We remove it from its parent sprite.
            parentSprite->removeEdge(*i);
        }
    }
}

void Vertex::clean() {
    parentEdges.clear();
    parentRenderSteps.clear();
    parentSprite = NULL;
    parentGraphicBody = NULL;
    clearLinks();
}

