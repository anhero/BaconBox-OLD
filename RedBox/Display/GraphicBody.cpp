#include "GraphicBody.h"

using namespace RedBox;
GraphicBody::~GraphicBody(){
    int nbOfSprites = sprites.size();
    for(int i = 0; i < nbOfSprites; i++){
        sprites[i]->warnVertexBodyOfDeletion();
        delete sprite[i];
    }
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