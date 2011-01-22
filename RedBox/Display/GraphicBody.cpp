#include "GraphicBody.h"

using namespace RedBox;

void GraphicBody::clean() {
    for(std::vector<Sprite*>::iterator i = sprites.begin(); i != sprites.end(); i++) {
        (*i)->warnVertexBodyOfDeletion();
        delete (*i);
    }
    sprites.clear();
    links.clear();
}

void GraphicBody::copyFrom(const GraphicBody& src) {
    clean();
    if(this != &src && &src) {
        renderSteps = src.renderSteps;
        vertices = src.vertices;
        edges = src.edges;
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

Sprite* GraphicBody::addSprite(Sprite* sprite){
    sprites.push_back(sprite);
    return sprite;
}
void GraphicBody::removeSprite(Sprite* sprite, bool andDelete = false){
    
}
Link* GraphicBody::addLink(Link * link){
    
}
void GraphicBody::removeLink(Link * link, bool andDelete = false){
    
}