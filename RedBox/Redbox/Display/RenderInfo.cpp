#include "RenderInfo.h"

#include <cmath>
#include <iostream>

#include "TextureInfo.h"
#include "VerticesGroup.h"
#include "Console.h"
#include "MathHelper.h"

using namespace RedBox;

RenderInfo::RenderInfo(): Object(), color(Color::WHITE), texInfo(NULL),
	currentFrame(0), currentNbLoops(0), defaultFrame(0) {
}

RenderInfo::RenderInfo(const RenderInfo& src) : Object(), color(src.color),
	texInfo(src.texInfo), texCoords(src.texCoords), currentFrame(src.currentFrame),
	currentNbLoops(src.currentNbLoops), defaultFrame(src.defaultFrame),
	animations(src.animations), currentAnimation(src.currentAnimation) {
}

RenderInfo::RenderInfo(TextureInfo* newTexInfo,
                       VerticesGroup* vertices,
                       unsigned int frameWidth,
                       unsigned int frameHeight,
                       unsigned int nbFrames,
                       const Color& newColor) : Object(), color(newColor),
	texInfo(newTexInfo), texCoords(std::vector< std::vector<float> >(nbFrames)),
	currentFrame(0), currentNbLoops(0), defaultFrame(0) {
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
				for(std::vector<std::vector<float> >::iterator i = texCoords.begin();
				        i != texCoords.end(); i++) {

					// We set the number of coordinates.
					i->resize(tmpSize * 2);
					j = 0;

					for(std::list<Vertex>::iterator j2 = tmpVertices.begin(); j2 != tmpVertices.end(); j2++) {
						(*i)[j] = offsetX + (j2->getXPosition() - position.first / size.first) / static_cast<float>(texInfo->poweredWidth);
						++j;
						(*i)[j] = offsetY + (j2->getYPosition() - position.second / size.second) / static_cast<float>(texInfo->poweredHeight);
						++j;
					}

					offsetX += realFrameWidth;

					if(offsetX >= realWidth) {
						offsetX = 0.0f;
						offsetY += realFrameHeight;
					}
				}
			} else {
				Console::Print("Attempted to construct a RenderInfo with a number of frames too high: " + nbFrames);
				Console::PrintTrace();
			}
		}
	} else {
		// On affiche les erreurs.
		Console::Print("Attempted to load texture coordinates with incorrect parameters: ");
		Console::PrintTrace();

		if(!newTexInfo) {
			Console::Print("    - Texture information pointer is invalid: " + Console::ToString(texInfo));
			Console::PrintTrace();
		}

		if(!vertices) {
			Console::Print("    - VerticesGroup pointer given is invalid : " + Console::ToString(vertices));
			Console::PrintTrace();
		}

		if(nbFrames == 0) {
			Console::Print("    - Number of frames must be of at least 1.");
			Console::PrintTrace();
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
		Console::Print("Failed to add the animation named : " + name);
		Console::PrintTrace();
	}
}

void RenderInfo::addAnimation(const std::string& name,
                              double timePerFrame,
                              int nbLoops,
                              unsigned int nbFrames, ...) {
	std::pair<std::map<std::string, AnimationParameters>::iterator, bool> insertionResult;

	// We make sure it is trying to add an animation with at least one frame.
	// We also insert the new animation in the map if possible and continue
	// only if it didn't already exist.
	if(nbFrames >= 1 &&
	        (insertionResult = animations.insert(std::pair<std::string, AnimationParameters>(name, AnimationParameters(std::vector<unsigned int>(nbFrames), timePerFrame, nbLoops)))).second) {
		// We set the frame numbers to the added animation using the variable
		// parameters.
		va_list frames;
		va_start(frames, nbFrames);

		for(std::vector<unsigned int>::iterator i = insertionResult.first->second.frames.begin();
		        i != insertionResult.first->second.frames.end();
		        ++i) {
			*i = va_arg(frames, unsigned int);
		}

		va_end(frames);
	} else {
		Console::Print("Failed to add the animation named : " + name);
		Console::PrintTrace();
	}
}

void RenderInfo::addAnimation(const std::string& name,
                              const AnimationParameters& newAnimation) {
	if(!(animations.insert(std::pair<std::string, AnimationParameters>(name, newAnimation)).second)) {
		Console::Print("Failed to add the animation named : " + name);
		Console::PrintTrace();
	}
}

const Color& RenderInfo::getColor() const {
	return color;
}

TextureInfo& RenderInfo::getTexInfo() {
	return *texInfo;
}

std::vector<std::vector<float> >& RenderInfo::getTexCoords() {
	return texCoords;
}

void RenderInfo::setColor(const Color& newColor) {
	color = newColor;
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
		Console::Print("Tried to get a non-existing animation: " + name);
		Console::PrintTrace();

		return NULL;
	}
}

const AnimationParameters* RenderInfo::getAnimationParameters(const std::string& name) const {
	if(animationExists(name)) {
		return &(animations.find(name)->second);
	} else {
		Console::Print("Tried to get a non-existing animation: " + name);
		Console::PrintTrace();
		return NULL;
	}
}

void RenderInfo::setCurrentFrame(unsigned int newCurrentFrame) {
	if(animationExists(currentAnimation) &&
	        newCurrentFrame <= getAnimationParameters(getCurrentAnimation())->frames.size()) {
		currentFrame = newCurrentFrame;
	} else {
		Console::Print("Tried to set the current frame that is too high: " + newCurrentFrame);
		Console::PrintTrace();
	}
}

unsigned int RenderInfo::getCurrentFrame() const {
	if(isAnimated() && animationExists(currentAnimation)) {
		return getAnimationParameters(getCurrentAnimation())->frames[currentFrame];
	} else {
		return defaultFrame;
	}
}

bool RenderInfo::isAnimated() const {
	return !(animations.empty());
}

void RenderInfo::incrementFrame() {
	AnimationParameters* anim = getAnimationParameters(getCurrentAnimation());

	if(anim) {
		++currentFrame;

		if(currentFrame >= anim->frames.size()) {
			if(anim->nbLoops == -1) {
				currentFrame = 0;
			} else if(anim->nbLoops > -1) {
				++currentNbLoops;

				if(currentNbLoops > anim->nbLoops) {
					currentNbLoops = anim->nbLoops;
					--currentFrame;
				} else {
					currentFrame = 0;
				}
			}
		}
	}
}

const std::string& RenderInfo::getCurrentAnimation() const {
	return currentAnimation;
}
void RenderInfo::setCurrentAnimation(const std::string& name) {
	currentAnimation = name;
}
void RenderInfo::resetCurrentNbLoops() {
	currentNbLoops = 0;
}

unsigned int RenderInfo::getDefaultFrame() const {
	return defaultFrame;
}

void RenderInfo::setDefaultFrame(unsigned int newDefaultFrame) {
	if(newDefaultFrame < texCoords.size()) {
		defaultFrame = newDefaultFrame;
	} else {
		Console::Print("Tried to set the default frame to a value too high: " + newDefaultFrame);
		Console::PrintTrace();
		defaultFrame = (texCoords.size()) ? (texCoords.size() - 1) : (0);
	}
}

namespace RedBox {
	std::ostream& operator<<(std::ostream& output, const RenderInfo& r) {
		output << "{color: " << r.color << ", texInfo: " << r.texInfo <<
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
