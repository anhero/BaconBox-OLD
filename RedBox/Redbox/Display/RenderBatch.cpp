#if 0
#include "RenderBatch.h"
#include <limits>

#include "CArray.h"
#include "Console.h"
#include "GraphicDriver.h"

namespace RedBox {

	RenderBatch::RenderBatch(): textureCoord(NULL), vertices(NULL),
		colors(NULL), verticesCount(0), spritesCount(0) {

	}

	RenderBatch::~RenderBatch() {
		for (std::set<Sprite *>::iterator i = sprites.begin(); i != sprites.end(); ++i) {
			removeSprite(*i);
		}

<<<<<<< local
		if (textureCoord != NULL) {
			delete [] textureCoord;
		}
=======
    for (std::set<Sprite*>::iterator i = sprites.begin(); i != sprites.end(); ++i) {
        (*i)->update();
    }
    
}
>>>>>>> other

<<<<<<< local
		if (vertices != NULL) {
			delete [] vertices;
		}
=======
void RenderBatch::render(){
    //If the user add/remove some sprites to the batch, we need to reconstruct it.
    if (spritesCount != sprites.size()) {        
        reconstruct();
    }
    for (std::set<Sprite*>::iterator i = sprites.begin(); i != sprites.end(); ++i) {
        (*i)->getRenderInfo().updateBatchPointer();
    }
    if (renderModes.isSet(RenderMode::INVERSE_MASKED)&& renderModes.isSet(RenderMode::TEXTURE)) {
        maskBody->mask();
        
        GraphicDriver::drawMaskedBatchWithTextureAndColor(CArray<Vector2>(vertices, verticesCount), CArray<Vector2>(textureCoord, verticesCount), CArray<unsigned short>(&(indices[0]), indices.size()), textureInfo, CArray<unsigned char>(&(colors[0]), verticesCount*colorChannelCount), true);
        maskBody->unmask();
        
    }
    else if(renderModes.isSet(RenderMode::MASKED) && renderModes.isSet(RenderMode::TEXTURE)){
        maskBody->mask();
        GraphicDriver::drawMaskedBatchWithTextureAndColor(CArray<Vector2>(vertices, verticesCount), CArray<Vector2>(textureCoord, verticesCount), CArray<unsigned short>(&(indices[0]), indices.size()), textureInfo, CArray<unsigned char>(&(colors[0]), verticesCount*colorChannelCount), false);
        maskBody->unmask();
    }
    else if (renderModes.isSet(RenderMode::TEXTURE)){
        GraphicDriver::drawBatchWithTextureAndColor(CArray<Vector2>(vertices, verticesCount), CArray<Vector2>(textureCoord, verticesCount), CArray<unsigned short>(&(indices[0]), indices.size()), textureInfo, CArray<unsigned char>(&(colors[0]), verticesCount*colorChannelCount));
    }
    
}
>>>>>>> other

		if (colors != NULL) {
			delete [] colors;
		}



	}

	void RenderBatch::reconstruct() {
		if (verticesCount > 0) {
			colorChannelCount = 0;

			if (textureInfo.colorFormat == ColorFormat::RGBA) {
				colorChannelCount = 4;

			} else if (textureInfo.colorFormat == ColorFormat::ALPHA) {
				colorChannelCount = 1;
			}


			unsigned int indicesIterator = 0;
			unsigned int verticesIterator = 0;

			Vector2 *tempTextureCoord = new Vector2[verticesCount];
			Vector2 *tempVertices = new Vector2[verticesCount];
			unsigned char *tempColors = new unsigned char[verticesCount * colorChannelCount];
			spritesCount = sprites.size();
			indices.clear();

			for (std::set<Sprite *>::iterator i = sprites.begin(); i != sprites.end(); ++i) {

				unsigned int verticesCount = (*i)->getVertices().getVerticesCount();

				//Indices array construction
				for (unsigned int triangleIterator = 0; triangleIterator < (verticesCount - 2); triangleIterator++) {
					indices.push_back(indicesIterator);
					indices.push_back(indicesIterator);
					indices.push_back(indicesIterator + triangleIterator + 1);
					indices.push_back(indicesIterator + triangleIterator + 2);
					indices.push_back(indicesIterator + triangleIterator + 2);
				}

				indicesIterator += (*i)->getVertices().getVerticesCount();



				std::vector<Vector2 *> currentVertices = (*i)->getVertices().getVertices();

				//Colors array construction
				for (unsigned int j = 0 ; j < verticesCount; j++) {
					for (unsigned int k = 0; k < colorChannelCount; k++) {
						tempColors[(verticesIterator + j)*colorChannelCount + k] = (*i)->getMainColor().getComponents()[k];
					}
				}








				//Vertices and texture coord array construction


				std::vector<std::vector<Vector2> > currentTexCoord = (*i)->getRenderInfo().getTexCoords();


				unsigned int currentFrame = (*i)->getRenderInfo().getCurrentFrame();




				unsigned int tempVerticesIterator = verticesIterator;

				for (unsigned int j = 0; j < verticesCount;) {
					tempVertices[verticesIterator] = *(currentVertices[j]);
					tempTextureCoord[verticesIterator] = (*i)->getRenderInfo().getTexCoords()[currentFrame][j];
					j++;
					verticesIterator++;
				}

				(*i)->setBatchPointer((&tempVertices[tempVerticesIterator]), (&tempTextureCoord[tempVerticesIterator]), &(tempColors[tempVerticesIterator * colorChannelCount]));

			}

			if (textureCoord != NULL) {
				delete [] textureCoord;
			}

			textureCoord = tempTextureCoord;

			if (vertices != NULL) {
				delete [] vertices;
			}

			vertices = tempVertices;

			if (colors != NULL) {
				delete [] colors;
			}

			colors = tempColors;

		}

	}

	void RenderBatch::update() {


		for (std::set<Sprite *>::iterator i = sprites.begin(); i != sprites.end(); ++i) {
			(*i)->update();
		}
	}

	void RenderBatch::render() {
		//If the user add/remove some sprites to the batch, we need to reconstruct it.
		if (spritesCount != sprites.size()) {
			reconstruct();
		}

		for (std::set<Sprite *>::iterator i = sprites.begin(); i != sprites.end(); ++i) {
			(*i)->getRenderInfo().updateBatchPointer();
		}

		if (renderModes.isSet(RenderMode::INVERSE_MASKED) && renderModes.isSet(RenderMode::TEXTURE)) {
			maskBody->mask();

			GraphicDriver::drawMaskedBatchWithTextureAndColor(CArray<Vector2>(vertices, verticesCount), CArray<Vector2>(textureCoord, verticesCount), CArray<unsigned short>(&(indices[0]), indices.size()), textureInfo, CArray<unsigned char>(&(colors[0]), verticesCount * colorChannelCount), true);
			maskBody->unmask();

		} else if (renderModes.isSet(RenderMode::MASKED) && renderModes.isSet(RenderMode::TEXTURE)) {
			maskBody->mask();
			GraphicDriver::drawMaskedBatchWithTextureAndColor(CArray<Vector2>(vertices, verticesCount), CArray<Vector2>(textureCoord, verticesCount), CArray<unsigned short>(&(indices[0]), indices.size()), textureInfo, CArray<unsigned char>(&(colors[0]), verticesCount * colorChannelCount), false);
			maskBody->unmask();

		} else if (renderModes.isSet(RenderMode::TEXTURE)) {
			GraphicDriver::drawBatchWithTextureAndColor(CArray<Vector2>(vertices, verticesCount), CArray<Vector2>(textureCoord, verticesCount), CArray<unsigned short>(&(indices[0]), indices.size()), textureInfo, CArray<unsigned char>(&(colors[0]), verticesCount * colorChannelCount));
		}

	}

	void RenderBatch::mask() {
		//If the user add/remove some sprites to the batch, we need to reconstruct it.
		if (spritesCount != sprites.size()) {
			reconstruct();
		}

		for (std::set<Sprite *>::iterator i = sprites.begin(); i != sprites.end(); ++i) {
			(*i)->getRenderInfo().updateBatchPointer();
		}

		GraphicDriver::drawMaskBatchWithTextureAndColor(CArray<Vector2>(vertices, verticesCount), CArray<Vector2>(textureCoord, verticesCount), CArray<unsigned short>(&(indices[0]), indices.size()), textureInfo, CArray<unsigned char>(&(colors[0]), verticesCount * colorChannelCount));
	}

	void RenderBatch::unmask() {
		GraphicDriver::unmaskBatch(CArray<Vector2>(vertices, verticesCount), CArray<unsigned short>(&(indices[0]), indices.size()));
	}

	void RenderBatch::removeSprite(Sprite *aSprite) {
		sprites.erase(aSprite);
		aSprite->setInternalBatchPointer();

	}

	void RenderBatch::setMask(GraphicBody *newMask, bool inversed) {
		if (newMask) {
			maskBody = newMask;
			renderModes.set(RenderMode::MASKED, false);
			renderModes.set(RenderMode::INVERSE_MASKED, false);

			if (inversed) {
				renderModes.set(RenderMode::INVERSE_MASKED, true);

			} else {
				renderModes.set(RenderMode::MASKED, true);
			}
		}
	}

	GraphicBody  *RenderBatch::clone() const {
		return NULL;
	}

	float RenderBatch::getWidth() const {
		return 0.0f;
	}

	float RenderBatch::getHeight() const {
		return 0.0f;
	}

	GraphicBody *RenderBatch::getMask() {
		return maskBody;
	}

	void RenderBatch::addSprite(Sprite *aSprite) {
		if (sprites.empty()) {
			textureInfo.textureId = aSprite->getRenderInfo().getTexInfo()->textureId;
			renderModes = aSprite->getRenderModes();

			if (verticesCount + aSprite->getVertices().getVerticesCount() < std::numeric_limits<unsigned short>::max()) {
				verticesCount += aSprite->getVertices().getVerticesCount();
				sprites.insert(aSprite);

			} else {
				Console::print("You are trying to pack too much vertices in a single batch");
			}

			if (renderModes.isSet(RenderMode::MASKED) || renderModes.isSet(RenderMode::INVERSE_MASKED)) {
				maskBody = aSprite->getRenderInfo().getMask();
			}

		} else if (textureInfo.textureId == (aSprite->getRenderInfo().getTexInfo())->textureId &&
		           renderModes.areSet(aSprite->getRenderModes()) &&
		           renderModes.count() == aSprite->getRenderModes().count()) {
			if (verticesCount + aSprite->getVertices().getVerticesCount() < std::numeric_limits<unsigned short>::max()) {
				verticesCount += aSprite->getVertices().getVerticesCount();
				sprites.insert(aSprite);

			} else {
				Console::print("You are trying to pack too much vertices in a single batch");
			}

		} else {
			Console::print("Can't add sprites with different rendering mode and textures in the same RenderBatch");
		}

	}
}

#endif
