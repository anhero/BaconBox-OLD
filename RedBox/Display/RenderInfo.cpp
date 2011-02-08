#include "RenderInfo.h"
#include "Debug.h"
using namespace RedBox;

RenderInfo::RenderInfo(): texInfo(NULL) {
	color[0] = 0;
	color[1] = 0;
	color[2] = 0;
	color[3] = 0;
}

RenderInfo::RenderInfo(TextureInfo* newTexInfo, VerticesGroup* vertices, int* newColor) {
	texInfo = newTexInfo;
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
	if(vertices) {
		// TODO: Load the texCoords array.
	}
}
void RenderInfo::addAnimation(const std::string& name,
							  const std::vector<unsigned int> frames,
							  double timePerFrame,
							  int nbLoops) {
	// We add the animation to the map and we check if it was successfully
	// added.
	if(!(animations.insert(std::pair<std::string, AnimationParameters>(name, AnimationParameters(frames, timePerFrame, nbLoops))).second)) {
		$ECHO("Failed to add the animation named : ");
		$ECHO(name);
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
