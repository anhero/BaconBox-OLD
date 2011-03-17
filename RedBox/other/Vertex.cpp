#include "Vertex.h"

#include "Sprite.h"
#include "RenderStep.h"
#ifdef RB_PHYSICS_ENABLED
#include "GraphicBody.h"
#include "Edge.h"
#include "Link.h"
#endif

using namespace RedBox;

#ifdef RB_PHYSICS_ENABLED
Vertex::Vertex(): parentSprite(NULL), parentGraphicBody(NULL)
#else
Vertex::Vertex(): parentSprite(NULL)
#endif
{
    position.setXPtr(NULL);
    position.setYPtr(NULL);
#ifdef RB_PHYSICS_ENABLED
	oldPosition.setXPtr(NULL);
	oldPosition.setXPtr(NULL);
#endif
}
#ifdef RB_PHYSICS_ENABLED
Vertex::Vertex(float posX, float posY, Sprite* newParentSprite,
			   GraphicBody* newParentGraphicBody): 
parentSprite(newParentSprite), parentGraphicBody(newParentGraphicBody)
#else
Vertex::Vertex(float posX, float posY, Sprite* newParentSprite): 
parentSprite(newParentSprite)
#endif
{
	position.setX(posX);
	position.setY(posY);
#ifdef RB_PHYSICS_ENABLED
	oldPosition.setX(posX);
	oldPosition.setY(posY);
#endif
}

#ifdef RB_PHYSICS_ENABLED
Vertex::Vertex(float* posX, float* posY, Sprite* newParentSprite,
			   GraphicBody* newParentGraphicBody): 
parentSprite(newParentSprite), parentGraphicBody(newParentGraphicBody)
#else
Vertex::Vertex(float* posX, float* posY, Sprite* newParentSprite): 
parentSprite(newParentSprite)
#endif
{
	position.setIsPtr(true);
	position.setXPtr(posX);
	position.setYPtr(posY);
}

#ifdef RB_PHYSICS_ENABLED
Vertex::Vertex(const Vertex& src): position(src.position),
parentRenderSteps(src.parentRenderSteps), parentSprite(src.parentSprite),
parentEdges(src.parentEdges), parentLinks(src.parentLinks),
parentGraphicBody(src.parentGraphicBody), oldPosition(src.oldPosition),
acceleration(src.acceleration) {
}
#else
Vertex::Vertex(const Vertex& src): position(src.position),
parentRenderSteps(src.parentRenderSteps), parentSprite(src.parentSprite) {
}
#endif
Vertex::~Vertex() {
#ifdef RB_PHYSICS_ENABLED
	clearLinks();
	clearEdges();
#endif
}

Vertex& Vertex::operator=(const Vertex &src) {
    copyFrom(src);
    return *this;
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

Sprite* Vertex::getParentSprite() {
    return parentSprite;
}

void Vertex::setParentSprite(Sprite* newParentSprite) {
    parentSprite = newParentSprite;
}

void Vertex::warnOfParentSpriteDeletion() {
#ifdef RB_PHYSICS_ENABLED		
	parentLinks.clear();
	parentEdges.clear();
#endif
}

#ifdef RB_PHYSICS_ENABLED
std::vector<Edge*>& Vertex::getParentEdges() {
    return parentEdges;
}

std::vector<Link*>& Vertex::getParentLinks() {
    return parentLinks;
}

GraphicBody* Vertex::getParentGraphicBody() {
    return parentGraphicBody;
}

void Vertex::setParentGraphicBody(GraphicBody* newParentGraphicBody) {
    parentGraphicBody = newParentGraphicBody;
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
	for(std::vector<Link*>::iterator i = parentLinks.begin(); i != parentLinks.end(); i++) {
		if(*i)
			delete *(i);
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
#endif

void Vertex::copyFrom(const Vertex& src) {
    clean();
    if(this != &src && &src) {
        position = src.position;
#ifdef RB_PHYSICS_ENABLED		
        parentEdges = src.parentEdges;
        parentLinks = src.parentLinks;
#endif
        parentRenderSteps = src.parentRenderSteps;
        parentSprite = src.parentSprite;
#ifdef RB_PHYSICS_ENABLED		
        parentGraphicBody = src.parentGraphicBody;
#endif
    } else {
        position = Vec2();
    }
}

void Vertex::clean() {
#ifdef RB_PHYSICS_ENABLED		
    parentEdges.clear();
#endif
    parentRenderSteps.clear();
    parentSprite = NULL;
#ifdef RB_PHYSICS_ENABLED		
    parentGraphicBody = NULL;
    clearLinks();
#endif
}

namespace RedBox {
	std::ostream& operator<<(std::ostream& output, const Vertex& v) {
		output << "{position: " << v.position << ", parentRenderSteps: [";
		for(std::vector<RenderStep*>::const_iterator i = v.parentRenderSteps.begin();
			i != v.parentRenderSteps.end();
			i++) {
			if(i != v.parentRenderSteps.begin()) {
				output << ", ";
			}
			output << *i;
		}
		output << "], parentSprite: " << v.parentSprite;
#ifdef RB_PHYSICS_ENABLED
		output << ", parentEdges: [";
		for(std::vector<Edge*>::const_iterator i = v.parentEdges.begin();
			i != v.parentEdges.end();
			i++) {
			if( i != v.parentEdges.begin()) {
				output << ", ";
			}
			output << *i;
		}
		output << "], parentLinks: [";
		for(std::vector<Link*>::const_iterator i = v.parentLinks.begin();
			i != v.parentLinks.end();
			i++) {
			if( i != v.parentLinks.begin()) {
				output << ", ";
			}
			output << *i;
		}
		output << "], parentGraphicBody: " << v.parentGraphicBody <<
		", oldPosition: " << v.oldPosition << ", acceleration: " <<
		v.acceleration;
#endif
		output << "}";
		return output;
	}
}
