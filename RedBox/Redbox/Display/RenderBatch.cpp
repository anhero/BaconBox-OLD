#include "RenderBatch.h"
#include "CArray.h"
using namespace RedBox;

RenderBatch::RenderBatch(): textureCoord(NULL), vertices(NULL), verticesCount(0){
    
}

void RenderBatch::reconstruct(){
    if (verticesCount > 0) {
        
        unsigned int j = 0;
        
        Vector2 * tempTextureCoord = new Vector2[verticesCount];
        
        
        Vector2 * tempVertices = new Vector2[verticesCount];
        
        for (std::vector<Sprite*>::iterator i = sprites.begin(); i!= sprites.end(); ++i) {
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
            delete textureCoord;
        }
        textureCoord = tempTextureCoord;
        
        if (vertices != NULL) {
            delete vertices;
        }
        vertices = tempVertices;
    }
    
}
