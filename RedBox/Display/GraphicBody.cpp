#ifdef RB_PHYSICS_ENABLED
#include "GraphicBody.h"

using namespace RedBox;

void GraphicBody::clean() {
    for(std::list<Sprite*>::iterator i = sprites.begin(); i != sprites.end(); i++) {
        delete (*i);
    }
    sprites.clear();
    for(std::list<Link*>::iterator i = links.begin(); i != links.end(); i++) {
        delete (*i);
    }	
    links.clear();
}

void GraphicBody::copyFrom(const GraphicBody& src) {
    clean();
    if(this != &src && &src) {
		links = src.links;
		sprites = src.sprites;
    } else {
    }
}

GraphicBody::GraphicBody(): Renderable() {
}

GraphicBody::GraphicBody(const GraphicBody& src): Renderable(src) {
}

GraphicBody::~GraphicBody() {
    clean();
}

GraphicBody& GraphicBody::operator=(const GraphicBody& src) {
    Renderable::operator=(src);
    copyFrom(src);
    return *this;
}

void GraphicBody::render() {
    //TODO: Everything in this function...
}

void GraphicBody::update() {
}

Sprite* GraphicBody::addSprite(Sprite* sprite) {
    if(!containsSprite(sprite)) {
		sprites.push_back(sprite);
    }
    return sprite;
}
void GraphicBody::removeSprite(Sprite* sprite, bool andDelete) {
    std::list<Sprite*>::iterator i = sprites.begin();
    bool notFound = true;
    // Search for the sprite to remove.
    while(notFound && i != sprites.end()) {
        if(*i == sprite) {
            notFound = false;
            if(andDelete) {
                delete sprite;
            }
            i = sprites.erase(i);
        } else {
            i++;
        }
    }
}
Link* GraphicBody::addLink(Link* link) {
    if(!containsLink(link)) {
        links.push_back(link);
    }
    return link;
}
void GraphicBody::removeLink(Link* link, bool andDelete){
    std::list<Link*>::iterator i = links.begin();
    bool notFound = true;
    // Search for the link to remove.
    while(notFound && i != links.end()) {
        if(*i == link) {
            notFound = false;
            if(andDelete) {
                delete link;
            }
            i = links.erase(i);
        } else {
            i++;
        }
    }
}

bool GraphicBody::containsSprite(Sprite* sprite) {
    bool notFound = true;
    std::list<Sprite*>::iterator i = sprites.begin();
    while(notFound && i != sprites.end()) {
        if(sprite == *i)
            notFound = false;
        i++;
    }
    return !notFound;
}

bool GraphicBody::containsLink(Link* link) {
    bool notFound = true;
    std::list<Link*>::iterator i = links.begin();
    while(notFound && i != links.end()) {
        if(sprite == *i)
            notFound = false;
        i++;
    }
    return !notFound;
}
#endif