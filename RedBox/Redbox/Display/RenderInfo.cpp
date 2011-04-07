#include "RenderInfo.h"

#include <cmath>

#include "TextureInfo.h"
#include "VerticesGroup.h"
#include "Debug.h"
#include "MathHelper.h"

using namespace RedBox;

RenderInfo::RenderInfo(): texInfo(NULL), currentFrame(0) {
	color[0] = 255;
	color[1] = 255;
	color[2] = 255;
	color[3] = 255;
}

RenderInfo::RenderInfo(TextureInfo* newTexInfo,
					   VerticesGroup* vertices,
					   unsigned int frameWidth,
					   unsigned int frameHeight,
					   unsigned int nbFrames,
					   int* newColor):
texInfo(newTexInfo), texCoords(std::vector< std::vector<float> >(nbFrames)),
currentFrame(0) {
	if(newColor) {
		color[0] = newColor[0];
		color[1] = newColor[1];
		color[2] = newColor[2];
		color[3] = newColor[3];
	} else {
		color[0] = 255;
		color[1] = 255;
		color[2] = 255;
		color[3] = 255;
	}
	loadTexCoords(vertices, frameWidth, frameHeight, nbFrames);
}

void RenderInfo::loadTexCoords(VerticesGroup* vertices,
							   unsigned int frameWidth,
							   unsigned int frameHeight,
							   unsigned int nbFrames,
							   TextureInfo* newTexInfo) {
	
	// We check if we also reassign the texInfo.
	if(newTexInfo) {
		texInfo = newTexInfo;
	}
	
	// We check if the texInfo, the vertices and the number of frames are valid.
	if(texInfo && vertices && nbFrames > 0) {
		
		// We make sure the width and the height of the texture are valid.
		if(texInfo->imageWidth && texInfo->imageHeight && texInfo->poweredWidth
		   && texInfo->poweredHeight && frameWidth && frameHeight) {
			unsigned int framesPerLine = texInfo->imageWidth / frameWidth;
			
			// We check if the image can fit enough frames.
			if(framesPerLine * (texInfo->imageHeight / frameHeight)) {
				
				float realFrameWidth = static_cast<float>(frameWidth) / static_cast<float>(texInfo->poweredWidth);
				float realFrameHeight = static_cast<float>(frameHeight) / static_cast<float>(texInfo->poweredHeight);
				float realWidth = static_cast<float>(texInfo->imageWidth) / static_cast<float>(texInfo->poweredWidth);
				texCoords.resize(nbFrames);
				float offsetX = 0.0f, offsetY = 0.0f;
				std::pair<float, float> position = vertices->getPosition();
				// We get the width and the height of the of the vertices group.
				std::pair<float, float> size = vertices->getWidthHeight();
				unsigned int tmpSize = vertices->getVertices().size(), j = 0;
				std::list<Vertex>& tmpVertices = vertices->getVertices();
				
				// For each frame to load.
				for (std::vector<std::vector<float> >::iterator i = texCoords.begin();
					 i != texCoords.end(); i++) {
					
					// We set the number of coordinates.
					i->resize(tmpSize * 2);
					j = 0;
					
					for (std::list<Vertex>::iterator j2 = tmpVertices.begin(); j2 != tmpVertices.end(); j2++) {
						(*i)[j] = offsetX + (j2->getXPosition() - position.first / size.first) / static_cast<float>(texInfo->poweredWidth);
						++j;
						(*i)[j] = offsetY + (j2->getYPosition() - position.second / size.second) / static_cast<float>(texInfo->poweredHeight);
						++j;
					}
					
					offsetX += realFrameWidth;
					
					if(offsetX > realWidth) {
						offsetX = 0.0f;
						offsetY += realFrameHeight;
					}
				}
			} else {
				RB_ECHO("Attempted to construct a RenderInfo with a number of frames too high: " << nbFrames);
			}
		}
	} else {
		// On affiche les erreurs.
		RB_ECHO("Attempted to load texture coordinates with incorrect parameters: ");
		if(!newTexInfo) {
			RB_ECHO("    - Texture information pointer is invalid: " << texInfo);
		}
		if(!vertices) {
			RB_ECHO("    - VerticesGroup pointer given is invalid : " << vertices);
		}
		if(nbFrames == 0) {
			RB_ECHO("    - Number of frames must be of at least 1.");
		}
	}
}

void RenderInfo::addAnimation(const std::string& name,
							  const std::vector<unsigned int> frames,
							  double timePerFrame,
							  int nbLoops) {
	// We add the animation to the map and we check if it was successfully
	// added.
	if(!(animations.insert(std::pair<std::string, AnimationParameters>(name, AnimationParameters(frames, timePerFrame, nbLoops))).second)) {
		RB_ECHO("Failed to add the animation named : " << name);
	}
}

void RenderInfo::addAnimation(const std::string& name,
							  double timePerFrame,
							  int nbLoops,
							  unsigned int nbFrames,
							  unsigned int firstFrame, ... ) {
	std::pair<std::map<std::string, AnimationParameters>::iterator, bool> insertionResult;
	// We make sure it is trying to add an animation with at least one frame.
	// We also insert the new animation in the map if possible and continue
	// only if it didn't already exist.
	if(nbFrames >= 1 && 
	   (insertionResult = animations.insert(std::pair<std::string, AnimationParameters>(name, AnimationParameters(std::vector<unsigned int>(nbFrames), timePerFrame, nbLoops)))).second) {
		// We set the frame numbers to the added animation using the variable
		// parameters.
		va_list frames;
		va_start(frames, firstFrame);
		for(std::vector<unsigned int>::iterator i = ++(insertionResult.first->second.frames.begin());
			i != insertionResult.first->second.frames.end();
			i++) {
			*i = va_arg(frames, unsigned int);
		}
		va_end(frames);
	} else {
		RB_ECHO("Failed to add the animation named : " << name);
	}
}

void RenderInfo::addAnimation(const std::string& name,
							  const AnimationParameters& newAnimation) {
	if(!(animations.insert(std::pair<std::string, AnimationParameters>(name, newAnimation)).second)) {
		RB_ECHO("Failed to add the animation named : " << name);
	}
}
unsigned char* RenderInfo::getColor() {
	return color;
}
unsigned char RenderInfo::getRedValue() const {
	return color[0];
}
unsigned char RenderInfo::getGreenValue() const {
	return color[1];
}
unsigned char RenderInfo::getBlueValue() const {
	return color[2];
}
unsigned char RenderInfo::getAlphaValue() const {
	return color[3];
}
TextureInfo& RenderInfo::getTexInfo() {
	return *texInfo;
}
std::vector<std::vector<float> >& RenderInfo::getTexCoords() {
	return texCoords;
}
void RenderInfo::setRGBA(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha) {
	color[0] = red;
	color[1] = green;
	color[2] = blue;
	color[3] = alpha;
}
void RenderInfo::setRedValue(unsigned char red) {
	color[0] = red;
}
void RenderInfo::setGreenValue(unsigned char green) {
	color[1] = green;
}
void RenderInfo::setBlueValue(unsigned char blue) {
	color[2] = blue;
}
void RenderInfo::setAlphaValue(unsigned char alpha) {
	color[3] = alpha;
}
void RenderInfo::setTexInfo(TextureInfo* newTexInfo) {
	texInfo = newTexInfo;
}
bool RenderInfo::animationExists(const std::string& name) const {
	if(animations.find(name) == animations.end()) {
		return false;
	} else {
		return true;
	}
}
AnimationParameters* RenderInfo::getAnimationParameters(const std::string& name) {
	if(animationExists(name)) {
		return &(animations[name]);
	} else {
		RB_ECHO("Tried to get a non-existing animation: " << name);
		return NULL;
	}
}

void RenderInfo::setCurrentFrame(unsigned int newCurrentFrame) {
	if(newCurrentFrame >= texCoords.size()) {
		currentFrame = newCurrentFrame;
	} else {
		RB_ECHO("Tried to set the current frame that is too high: " << newCurrentFrame);
	}
}

unsigned int RenderInfo::getCurrentFrame() const {
	return currentFrame;
}

bool RenderInfo::isAnimated() const {
	return !(animations.empty());
}

void RenderInfo::incrementFrame() {
	if(texCoords.size() <= currentFrame) currentFrame = 0;
	else ++currentFrame;
}

namespace RedBox {
	std::ostream& operator<<(std::ostream& output, const RenderInfo& r) {
		output << "{color: [" << r.color[0] << ", " << r.color[1] << ", " <<
		r.color[2] << ", " << r.color[3] << "], texInfo: " << r.texInfo <<
		", texCoords: [";
		
		for(std::vector< std::vector<float> >::const_iterator i = r.texCoords.begin(); i != r.texCoords.end(); i++) {
			if(i != r.texCoords.begin()) {
				output << ", ";
			}
			output << "[";
			for(std::vector<float>::const_iterator j = i->begin(); j != i->end(); j++) {
				if(j != i->begin()) {
					output << ", ";
				}
				output << *j;
			}
			output << "]";
		}
		
		output << "], currentFrame: " << r.currentFrame << ", animations: [";
		
		for(std::map<std::string, AnimationParameters>::const_iterator i = r.animations.begin(); i != r.animations.end(); i++) {
			if(i != r.animations.begin()) {
				output << ", ";
			}
			output << "{first: " << i->first << ", second: " << i->second << "}";
		}
		output << "]}";
		return output;
	}
}