#include "RenderInfo.h"

#include <cmath>

#include "Debug.h"
#include "MathHelper.h"
#include "VerticesGroup.h"

using namespace RedBox;

RenderInfo::RenderInfo(): texInfo(NULL), currentFrame(0) {
	color[0] = 0;
	color[1] = 0;
	color[2] = 0;
	color[3] = 0;
}

RenderInfo::RenderInfo(TextureInfo* newTexInfo, 
					   VerticesGroup* vertices,
					   unsigned int nbFrames,
					   float factor,
					   float offsetX,
					   float offsetY,
					   int* newColor):
texCoords(std::vector< std::vector<float> >(nbFrames)), texInfo(newTexInfo),
currentFrame(0) {
	if(newColor) {
		color[0] = newColor[0];
		color[1] = newColor[1];
		color[2] = newColor[2];
		color[3] = newColor[3];
	} else {
		color[0] = 0;
		color[1] = 0;
		color[2] = 0;
		color[3] = 0;
	}
	loadTexCoords(vertices, nbFrames, factor, offsetX, offsetY);
}

void RenderInfo::loadTexCoords(VerticesGroup* vertices,
							   unsigned int nbFrames,
							   float factor,
							   float offsetX,
							   float offsetY,
							   TextureInfo* newTexInfo) {
	// We check if we also reassign the texInfo.
	if(newTexInfo) {
		texInfo = newTexInfo;
	}
	// We check if the texInfo, the vertices and the number of frames are valid.
	if(texInfo && vertices && nbFrames > 0) {
		// We get the width and the height of the of the vertices group.
		std::pair<float, float> widthHeight = vertices->getWidthHeight();
		// We make sure the width and the height are valid.
		if(widthHeight.first != 0.0f && widthHeight.second != 0.0f) {
			// We get the image width as a float and we consider the factor.
			float imgWidth = static_cast<float>(texInfo->imageWidth) * factor, 
			imgHeight = static_cast<float>(texInfo->imageHeight) * factor;
			// We calculate the maximum number of frames the image can contain
			// horizontally and vertically. We take into account the vertical
			// offset.
			float nbFramesHorMax = floor(imgWidth / widthHeight.first),
			nbFramesVerMax = floor((imgHeight - offsetY) / widthHeight.second);
			
			// We check if the number of frames asked fits within the image. We
			// take into account the horizontal offset.
			if(nbFrames < nbFramesHorMax * nbFramesVerMax - floor((imgWidth - offsetX) / widthHeight.first)) {
				texCoords.resize(nbFrames, std::vector<float>(8, 0.0f));
				// Calculates at which frame we start, only affected by the
				// horizontal offset because the vertical one will be added
				// at each frame.
				float currentFrame = offsetX / widthHeight.first;
				for(std::vector< std::vector<float> >::iterator i = texCoords.begin(); i != texCoords.end(); i++) {
					// Upper left corner.
					(*i)[0] = MathHelper::modFloat(currentFrame, nbFramesHorMax) * widthHeight.first;
					// Here we do not forget to add the vertical offset.
					(*i)[1] = floor(floor(currentFrame) / nbFramesHorMax) * widthHeight.second + offsetY;
					// Upper right corner.
					(*i)[2] = (*i)[0] + widthHeight.first;
					(*i)[3] = (*i)[1];
					// Lower right corner.
					(*i)[4] = (*i)[2];
					(*i)[5] = (*i)[1] + widthHeight.second;
					// Lower left corner.
					(*i)[6] = (*i)[0];
					(*i)[7] = (*i)[5];
					// Increment the frame counter.
					currentFrame += 1.0f;
				}
			} else {
				$ECHO("Attempted to construct a RenderInfo with a number of frames too high: " << nbFrames);
			}
		}
	} else {
		// On affiche les erreurs.
		$ECHO("Attempted to load texture coordinates with incorrect parameters: ");
		if(!newTexInfo) {
			$ECHO("    - Texture information pointer is invalid: " << texInfo);
		}
		if(!vertices) {
			$ECHO("    - VerticesGroup pointer given is invalid : " << vertices);
		}
		if(nbFrames == 0) {
			$ECHO("    - Number of frames must be of at least 1.");
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
		$ECHO("Failed to add the animation named : " << name);
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
		$ECHO("Failed to add the animation named : " << name);
	}
}

void RenderInfo::addAnimation(const std::string& name,
							  const AnimationParameters& newAnimation) {
	if(!(animations.insert(std::pair<std::string, AnimationParameters>(name, newAnimation)).second)) {
		$ECHO("Failed to add the animation named : " << name);
	}
}
int* RenderInfo::getColor() {
	return color;
}
int RenderInfo::getRedValue() const {
	return color[0];
}
int RenderInfo::getGreenValue() const {
	return color[1];
}
int RenderInfo::getBlueValue() const {
	return color[2];
}
int RenderInfo::getAlphaValue() const {
	return color[3];
}
TextureInfo& RenderInfo::getTexInfo() {
	return *texInfo;
}
std::vector<std::vector<float> >& RenderInfo::getTexCoords() {
	return texCoords;
}
void RenderInfo::setRGBA(int red, int green, int blue, int alpha) {
	color[0] = red;
	color[1] = green;
	color[2] = blue;
	color[3] = alpha;
}
void RenderInfo::setRedValue(int red) {
	color[0] = red;
}
void RenderInfo::setGreenValue(int green) {
	color[1] = green;
}
void RenderInfo::setBlueValue(int blue) {
	color[2] = blue;
}
void RenderInfo::setAlphaValue(int alpha) {
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
		$ECHO("Tried to get a non-existing animation: " << name);
		return NULL;
	}
}

void RenderInfo::setCurrentFrame(unsigned int newCurrentFrame) {
	if(newCurrentFrame >= texCoords.size()) {
		currentFrame = newCurrentFrame;
	} else {
		$ECHO("Tried to set the current frame that is too high: " << newCurrentFrame);
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
		r.color[2] << ", " << r.color[3] << "], texInfo: " << r.texInfo << "(" << 
		(*(r.texInfo)) << "), texCoords: [";
		
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