#include "RenderInfo.h"

#include <cmath>
#include <iostream>

#include "TextureInfo.h"
#include "VerticesGroup.h"
#include "Console.h"
#include "MathHelper.h"
#include "Sprite.h"
#include "CArray.h"
using namespace RedBox;

RenderInfo::RenderInfo(): Object(), color(Color::WHITE), mask(NULL),
	texInfo(NULL), texCoords(), currentTexCoord(NULL), currentTexCoordCount(0u),
	inBatch(false), currentFrame(0), currentNbLoops(0), defaultFrame(0) {
}

RenderInfo::RenderInfo(const RenderInfo& src) : Object(), color(src.color),
	mask(src.mask),	texInfo(src.texInfo), texCoords(src.texCoords),
	currentTexCoord(src.currentTexCoord),
	currentTexCoordCount(src.currentTexCoordCount), inBatch(src.inBatch),
	currentFrame(src.currentFrame),	currentNbLoops(src.currentNbLoops),
	defaultFrame(src.defaultFrame),	animations(src.animations),
	currentAnimation(src.currentAnimation) {
}

RenderInfo::RenderInfo(TextureInfo* newTexInfo,
                       VerticesGroup& vertices,
                       unsigned int frameWidth,
                       unsigned int frameHeight,
                       unsigned int nbFrames,
                       const Color& newColor) : Object(), color(newColor),
	mask(NULL), texInfo(newTexInfo), texCoords(nbFrames), currentTexCoord(NULL),
	currentTexCoordCount(0u), inBatch(false),
	currentFrame(0), currentNbLoops(0), defaultFrame(0) {
	loadTexCoords(vertices, frameWidth, frameHeight, nbFrames);
}

void RenderInfo::loadTexCoords(VerticesGroup& vertices,
                               unsigned int frameWidth,
                               unsigned int frameHeight,
                               unsigned int nbFrames,
                               TextureInfo* newTexInfo) {
	// We check if we also reassign the texInfo.
	if(newTexInfo) {
		texInfo = newTexInfo;
	}

	// We check if the texInfo, the vertices and the number of frames are valid.
	if(texInfo && nbFrames > 0) {
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
				Vector2 position = vertices.getPosition();
				// We get the width and the height of the of the vertices group.
				Vector2 size = vertices.getSize();
				unsigned int verticesCount = vertices.getVertices().elementCount;
				Vector2* verticesArray = vertices.getVertices().array;
				size_t tmpSize = static_cast<size_t>(verticesCount);

				// For each frame to load.
				for(std::vector<std::vector<Vector2> >::iterator i = texCoords.begin();
				    i != texCoords.end(); ++i) {
					// We set the number of coordinates.
					i->resize(tmpSize);
					unsigned int j2 = 0;

					for(std::vector<Vector2>::iterator j1 = i->begin();
					    j1 != i->end() && j2 < verticesCount; ++j1) {
						j1->setXY(offsetX + (verticesArray[j2].getX() - position.getX() / size.getX()) / static_cast<float>(texInfo->poweredWidth),
						          offsetY + (verticesArray[j2].getY() - position.getY() / size.getY()) / static_cast<float>(texInfo->poweredHeight));
						++j2;
					}

					offsetX += realFrameWidth;

					if(offsetX >= realWidth) {
						offsetX = 0.0f;
						offsetY += realFrameHeight;
					}
				}

			} else {
				Console::print("Attempted to construct a RenderInfo with a number of frames too high: " + nbFrames);
				Console::printTrace();
			}
		}

	} else {
		// We print the errors.
		Console::print("Attempted to load texture coordinates with incorrect parameters: ");
		Console::printTrace();

		if(!newTexInfo) {
			Console::print("    - Texture information pointer is invalid: " + Console::toString(texInfo));
			Console::printTrace();
		}

		if(nbFrames == 0) {
			Console::print("    - Number of frames must be of at least 1.");
			Console::printTrace();
		}
	}
}

void RenderInfo::addAnimation(const std::string& name,
                              const std::vector<unsigned int>& frames,
                              double timePerFrame,
                              int nbLoops) {
	// We check if the frames are within bounds, if not, we don't add the
	// animation and we print an error message.
	bool okay = true;
	std::vector<unsigned int>::const_iterator i = frames.begin();

	while(okay && i != frames.end()) {
		if(*i >= texCoords.size()) {
			okay = false;

		} else {
			++i;
		}
	}

	if(okay) {
		// We add the animation to the map and we check if it was successfully
		// added.
		if(!(animations.insert(std::pair<std::string, AnimationParameters>(name, AnimationParameters(frames, timePerFrame, nbLoops))).second)) {
			Console::print("Failed to add the animation named : " + name);
			Console::printTrace();
		}

	} else {
		Console::print("Failed to add the animation named \"" + name + "\" because it contains at least one frame index that is too high.");
		Console::printTrace();
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
		Console::print("Failed to add the animation named : " + name);
		Console::printTrace();
	}
}

void RenderInfo::addAnimation(const std::string& name,
                              const AnimationParameters& newAnimation) {
	if(!(animations.insert(std::pair<std::string, AnimationParameters>(name, newAnimation)).second)) {
		Console::print("Failed to add the animation named : " + name);
		Console::printTrace();
	}
}

GraphicBody* RenderInfo::getMask() {
	return mask;
}

void RenderInfo::setMask(GraphicBody* newMask) {
	mask = newMask;
}

const Color& RenderInfo::getColor() const {
	return color;
}

TextureInfo* RenderInfo::getTexInfo() {
	return texInfo;
}

std::vector<std::vector<Vector2> >& RenderInfo::getTexCoords() {
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
		Console::print("Tried to get a non-existing animation: " + name);
		Console::printTrace();
		return NULL;
	}
}

const AnimationParameters* RenderInfo::getAnimationParameters(const std::string& name) const {
	if(animationExists(name)) {
		return &(animations.find(name)->second);

	} else {
		Console::print("Tried to get a non-existing animation: " + name);
		Console::printTrace();
		return NULL;
	}
}

void RenderInfo::setCurrentFrame(unsigned int newCurrentFrame) {
	if(animationExists(currentAnimation) &&
	   newCurrentFrame <= getAnimationParameters(getCurrentAnimation())->frames.size()) {
		currentFrame = newCurrentFrame;

	} else {
		Console::print("Tried to set the current frame that is too high: " + newCurrentFrame);
		Console::printTrace();
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
		Console::print("Tried to set the default frame to a value too high: " + newDefaultFrame);
		Console::printTrace();
		defaultFrame = (texCoords.size()) ? (texCoords.size() - 1) : (0);
	}
}

namespace RedBox {
	std::ostream& operator<<(std::ostream& output, const RenderInfo& r) {
		output << "{color: " << r.color << ", texInfo: " << r.texInfo <<
		       ", texCoords: [";

		for(std::vector<std::vector<Vector2> >::const_iterator i = r.texCoords.begin();
		    i != r.texCoords.end(); ++i) {
			if(i != r.texCoords.begin()) {
				output << ", ";
			}

			output << "[";

			for(std::vector<Vector2>::const_iterator j = i->begin();
			    j != i->end(); ++j) {
				if(j != i->begin()) {
					output << ", ";
				}

				output << *j;
			}

			output << "]";
		}

		output << "], currentFrame: " << r.currentFrame << ", animations: [";

		for(std::map<std::string, AnimationParameters>::const_iterator i = r.animations.begin();
		    i != r.animations.end(); ++i) {
			if(i != r.animations.begin()) {
				output << ", ";
			}

			output << "{first: " << i->first << ", second: " << i->second << "}";
		}

		output << "]}";
		return output;
	}
}
