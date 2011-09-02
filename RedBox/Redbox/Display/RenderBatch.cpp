#include "RenderBatch.h"
#include "CArray.h"
#include "Console.h"
#include <limits>
#include "GraphicDriver.h"
using namespace RedBox;

RenderBatch::RenderBatch(): textureCoord(NULL), vertices(NULL), verticesCount(0), spritesCount(0){
    
}

RenderBatch::~RenderBatch(){
    for (std::set<Sprite*>::iterator i = sprites.begin(); i != sprites.end(); ++i) {
        removeSprite(*i);
    }
    
    if (textureCoord != NULL) {
        delete [] textureCoord;
    }
    if (vertices != NULL) {
        delete [] vertices;
    }
    
    

}

void RenderBatch::reconstruct(){
    if (verticesCount > 0) {
        
            
        unsigned int indicesIterator = 0;
        unsigned int verticesIterator = 0;
    
        Vector2 * tempTextureCoord = new Vector2[verticesCount];
        Vector2 * tempVertices = new Vector2[verticesCount];
        spritesCount = sprites.size();
        indices.clear();
        colors.clear();

        for (std::set<Sprite*>::iterator i = sprites.begin(); i != sprites.end(); ++i) {
            
            
            //Indices array construction
            for (unsigned int triangleIterator = 0; triangleIterator < ((*i)->getVertices().getVerticesCount() -2); triangleIterator++) {
                indices.push_back(indicesIterator);
                indices.push_back(indicesIterator);
                indices.push_back(indicesIterator + triangleIterator +1);
                indices.push_back(indicesIterator + triangleIterator +2);
                indices.push_back(indicesIterator + triangleIterator +2);
            }
            indicesIterator += (*i)->getVertices().getVerticesCount();

            
            
            CArray<Vector2> currentVertices = (*i)->getVertices().getVertices();

            //Colors array construction
            for (unsigned int j = 0 ; j < currentVertices.elementCount; j++ ) {
                for (unsigned int k = 0; k < 4; k++) {
                    colors.push_back((*i)->getMainColor().getComponents()[k]);
                }
            }
            
            
           
            
            
            
            //Vertices and texture coord array construction
            

            std::vector<std::vector<Vector2> > currentTexCoord = (*i)->getRenderInfo().getTexCoords();
            

            unsigned int currentFrame =  (*i)->getRenderInfo().getCurrentFrame();
            
            
            
            (*i)->setBatchPointer((&tempVertices[verticesIterator]), (&tempTextureCoord[verticesIterator]), &(colors[colors.size()- currentVertices.elementCount*4]));

            for (unsigned int j = 0; j < currentVertices.elementCount;) {
                tempVertices[verticesIterator] = currentVertices[j];
                tempTextureCoord[verticesIterator] = (*i)->getRenderInfo().getTexCoords()[currentFrame][j];
                j++;
                verticesIterator++;
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
    
    
    for (std::set<Sprite*>::iterator i = sprites.begin(); i != sprites.end(); ++i) {
        (*i)->update();
    }
}

void RenderBatch::render(){
    //If the user add/remove some sprites to the batch, we need to reconstruct it.
    if (spritesCount != sprites.size()) {        
        reconstruct();
    }
    for (std::set<Sprite*>::iterator i = sprites.begin(); i != sprites.end(); ++i) {
        (*i)->getRenderInfo().updateBatchPointer();
    }

    GraphicDriver::drawBatchWithTextureAndColor(CArray<Vector2>(vertices, verticesCount), CArray<Vector2>(textureCoord, verticesCount), CArray<unsigned short>(&(indices[0]), indices.size()), textureInfo, CArray<unsigned char>(&(colors[0]), colors.size()));
    
    //GraphicDriver::drawBatchWithTexture(CArray<Vector2>(vertices, verticesCount), CArray<Vector2>(textureCoord, verticesCount), CArray<unsigned short>(&(indices[0]), indices.size()), textureInfo);
}

void RenderBatch::mask(){
    //If the user add/remove some sprites to the batch, we need to reconstruct it.
    if (verticesCount != sprites.size()) {
        verticesCount = sprites.size();
        reconstruct();
    }
    for (std::set<Sprite*>::iterator i = sprites.begin(); i != sprites.end(); ++i) {
        (*i)->getRenderInfo().updateBatchPointer();
    }
    //TODO:Call drawer here
}

void RenderBatch::unmask(){
    //TODO: Call drawer here
}

void RenderBatch::removeSprite(Sprite * aSprite){
    sprites.erase(aSprite);
    aSprite->setInternalBatchPointer();
    
}

void RenderBatch::setMask(GraphicBody* newMask, bool inversed) {
    if(newMask) {
        maskBody = newMask;
		renderModes.set(RenderMode::MASKED, false);
		renderModes.set(RenderMode::INVERSE_MASKED, false);
        
		if(inversed) {
			renderModes.set(RenderMode::INVERSE_MASKED, true);
            
		} else {
			renderModes.set(RenderMode::MASKED, true);
		}
	}
}

GraphicBody*  RenderBatch::clone() const{
    return NULL;
}

float RenderBatch::getWidth() const{
    return 0.0f;
}

float RenderBatch::getHeight() const{
    return 0.0f;
}

GraphicBody* RenderBatch::getMask(){
    return maskBody;
}

void RenderBatch::addSprite(Sprite * aSprite){
    if (sprites.empty()) {
        textureInfo.textureId = aSprite->getRenderInfo().getTexInfo()->textureId;
        renderModes = aSprite->getRenderModes();
        if (verticesCount+ aSprite->getVertices().getVerticesCount() < std::numeric_limits<unsigned short>::max()) {
        verticesCount += aSprite->getVertices().getVerticesCount();
            sprites.insert(aSprite);
        }
        else{
            Console::print("You are trying to pack too much vertices in a single batch");
        }
        if(renderModes.isSet(RenderMode::MASKED) || renderModes.isSet(RenderMode::INVERSE_MASKED)){
            maskBody = aSprite->getRenderInfo().getMask();
        }
    }
    else if(textureInfo.textureId == (aSprite->getRenderInfo().getTexInfo())->textureId &&
            renderModes.areSet(aSprite->getRenderModes()) &&
            renderModes.count() == aSprite->getRenderModes().count()){
        if (verticesCount+ aSprite->getVertices().getVerticesCount() < std::numeric_limits<unsigned short>::max()) {
            verticesCount += aSprite->getVertices().getVerticesCount();
            sprites.insert(aSprite);
        }
        else{
            Console::print("You are trying to pack too much vertices in a single batch");
        }
    }
    else{
        Console::print("Can't add sprites with different rendering mode and textures in the same RenderBatch");
    }
    
}
