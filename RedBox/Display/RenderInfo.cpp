#include "RenderInfo.h"
#include <cmath>
#include "Debug.h"
using namespace RedBox;

RenderInfo::RenderInfo(): texInfo(NULL) {
	color[0] = 0;
	color[1] = 0;
	color[2] = 0;
	color[3] = 0;
}

RenderInfo::RenderInfo(TextureInfo* newTexInfo, 
					   VerticesGroup* vertices,
					   int* newColor
					   unsigned int nbFrames,
					   float factor):
texCoords(std::vector< std::vector<float> >(nbFrames)), texInfo(newTexInfo) {
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
	loadTexCoords(vertices, nbFrames, factor);
}

void RenderInfo::loadTexCoords(VerticesGroup* vertices,
							   unsigned int nbFrames,
							   float factor,
							   TextureInfo* newTexInfo) {
	if(newTexInfo) {
		texInfo = newTexInfo;
	}
	if(texInfo && vertices && nbFrames > 0) {
		std::pair<float, float> widthHeight = vertices->getWidthHeight();
		
		float imgWidth = static_cast<float>(texInfo->imageWidth) * factor, 
		imgHeight = static_cast<float>(texInfo->imageHeight) * factor;
		
		unsigned int nbFramesHorMax = static_cast<unsigned int>(fabs(imgWidth / widthHeight.first)), 
		nbFramesVerMax = static_cast<unsigned int>(fabs(imgHeight / widthHeight.second));
		
		if(nbFrames < nbFramesHorMax * nbFramesVerMax) {
			texCoords.resize(nbFrames, std::vector<float>(8, 0.0f));
			unsigned int currentFrame = 0;
			for(std::vector<std::vector<float> >::iterator i = texCoords.begin(); i++) {
				// Upper left corner.
				(*i)[0] = static_cast<float>(currentFrame % nbFramesHorMax) * widthHeight.first;
				(*i)[1] = static_cast<float>(currentFrame / nbFramesHorMax) * widthHeight.second;
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
				++currentFrame;
			}
		} else {
			$ECHO("Attempted to construct a RenderInfo with a number of frames too high: " << nbFrames);
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
		$ECHO("Failed to add the animation named : ");
		$ECHO(name);
	}
}

void RenderInfo::addAnimation(const std::string& name,
				  const AnimationParameters& newAnimation) {
	if(!(animations.insert(std::pair<std::string, AnimationParameters>(name, newAnimation)).second)) {
		$ECHO("Failed to add the animation named : ");
		$ECHO(name);
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
