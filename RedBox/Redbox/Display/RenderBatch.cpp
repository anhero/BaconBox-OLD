#include "RenderBatch.h"
#include "CArray.h"
#include "Console.h"

using namespace RedBox;

RenderBatch::RenderBatch(): textureCoord(NULL), vertices(NULL), verticesCount(0){
    
}

RenderBatch::~RenderBatch(){
    for (std::set<Sprite*>::iterator i = sprites.begin(); i != sprites.end(); ++i) {
        removeSprite(*i);
    }
    delete [] textureCoord;
    delete [] vertices;

}

void RenderBatch::reconstruct(){
    if (verticesCount > 0) {
        
        unsigned int j = 0;
        
        Vector2 * tempTextureCoord = new Vector2[verticesCount];
        
        
        Vector2 * tempVertices = new Vector2[verticesCount];
        
        for (std::set<Sprite*>::iterator i = sprites.begin(); i!= sprites.end(); ++i) {
            CArray<Vector2> currentVertices = (*i)->getVertices().getVertices();
            
            std::vector<std::vector<Vector2> > currentTexCoord = (*i)->getRenderInfo().getTexCoords();
        
            unsigned int currentFrame =  (*i)->getRenderInfo().getCurrentFrame();
            
            int currentMax = j + currentVertices.elementCount;
            (*i)->setBatchPointer((&tempVertices[j]), (&tempTextureCoord[j]));
            for (unsigned int k = 0; j < currentMax; j++) {
                tempTextureCoord[j] = currentTexCoord[currentFrame][k];
                tempVertices[j] = currentVertices.array[k];
                k++;
            }
        }
        
        if (textureCoord != NULL) {
            delete [] textureCoord;
        }
        textureCoord = tempTextureCoord;
        
        if (vertices != NULL) {
            delete [] vertices;
        }
        vertices = tempVertices;
    }
    
}

void RenderBatch::update(){
    //If the user add/remove some sprites to the batch, we need to reconstruct it.
    if (verticesCount != sprites.size()) {
        verticesCount = sprites.size();
        reconstruct();
    }
    
    for (std::set<Sprite*>::iterator i = sprites.begin(); i != sprites.end(); ++i) {
        (*i)->update();
    }
}

void RenderBatch::render(){
    for (std::set<Sprite*>::iterator i = sprites.begin(); i != sprites.end(); ++i) {
        (*i)->getRenderInfo().updateBatchPointer();
    }
    
    ///Call Drawer Here.
}

void RenderBatch::removeSprite(Sprite * aSprite){
    sprites.erase(aSprite);
    aSprite->setInternalBatchPointer();
    
}


void RenderBatch::addSprite(Sprite * aSprite){
    if (sprites.empty()) {
        textureInfo.textureId = aSprite->getRenderInfo().getTexInfo()->textureId;
        sprites.insert(aSprite);
    }
    else if(textureInfo.textureId == (aSprite->getRenderInfo().getTexInfo())->textureId){
        sprites.insert(aSprite);
    }
    else{
        Console::print("Can't add sprites with different textures in the same RenderBatch");
    }
    
}
