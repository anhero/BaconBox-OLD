#include "RenderStep.h"

#include <iostream>

#include "TextureInfo.h"
#include "RenderInfo.h"
#include "GraphicDriver.h"
#include "ResourceManager.h"
#include "TimeHelper.h"
#include "AnimationParameters.h"
#include "Console.h"
#include "VerticesGroup.h"
#include "Engine.h"
#include "Sprite.h"

using namespace RedBox;

RenderStep::RenderStep(): Object(), info(), mode(), vertices(NULL),
	deleteVerticesGroup(false), isPaused(false), animCounter(0.0) {
}

RenderStep::RenderStep(TextureInfo* newTexInfo,
                       VerticesGroup* newVertices,
                       unsigned int frameWidth,
                       unsigned int frameHeight,
                       unsigned int nbFrames,
                       const Color& newColor,
                       bool newDeleteVerticesGroup): Object(),
	info(newTexInfo, newVertices, frameWidth, frameHeight, nbFrames, newColor),
	mode(FlagSet<RenderStepMode>(RenderStepMode::SHAPE) |
	     FlagSet<RenderStepMode>(RenderStepMode::TEXTURE)),
	vertices(newVertices), deleteVerticesGroup(newDeleteVerticesGroup),
	isPaused(false), animCounter(0.0) {

	if(newColor != Color::WHITE) {
		mode |= RenderStepMode::COLOR;
	}
}

RenderStep::RenderStep(const std::string& key,
                       VerticesGroup* newVertices,
                       unsigned int frameWidth,
                       unsigned int frameHeight,
                       unsigned int nbFrames,
                       bool newDeleteVerticesGroup): Object(),
	info(ResourceManager::getTexture(key), newVertices, frameWidth, frameHeight,
	     nbFrames),
	mode(FlagSet<RenderStepMode>(RenderStepMode::SHAPE) |
	     FlagSet<RenderStepMode>(RenderStepMode::TEXTURE)),
	vertices(newVertices), deleteVerticesGroup(newDeleteVerticesGroup),
	isPaused(false), animCounter(0.0) {
}

RenderStep::RenderStep(const RenderStep& src): Object(src), info(src.info),
	mode(src.mode), vertices(NULL), deleteVerticesGroup(false), isPaused(false),
	animCounter(0.0) {
}

RenderStep::~RenderStep() {
	clearVertices();
}

RenderStep& RenderStep::operator=(const RenderStep& src) {
	Object::operator=(src);

	if(this != &src) {
		info = src.info;
		mode = src.mode;
		clearVertices();
		vertices = NULL;
		deleteVerticesGroup = src.deleteVerticesGroup;
		isPaused = false;
		animCounter = 0.0;
	}

	return *this;
}

void RenderStep::update() {
	if(!isPaused) {
		if(info.isAnimated() && info.getCurrentAnimation() != "") {
			AnimationParameters* anim = info.getAnimationParameters(info.getCurrentAnimation());

			if(anim) {
				animCounter += Engine::getSinceLastUpdate();

				if(animCounter >= anim->timePerFrame) {
					info.incrementFrame();
					animCounter -= anim->timePerFrame;
				}
			}
		}
	}
}

void RenderStep::render() {
	if(vertices && !vertices->getVertices().empty()) {
		// We check which graphic driver method to use.
		if(mode.isSet(RenderStepMode::SHAPE)) {
			if(mode.isSet(RenderStepMode::TEXTURE)) {
				if(mode.isSet(RenderStepMode::MASKED) || mode.isSet(RenderStepMode::INVERSE_MASKED)) {
					GraphicBody* mask = getMask();
					mask->mask();
					//MASKED+TEXTURE
					bool inversed = mode.isSet(RenderStepMode::INVERSE_MASKED);
					GraphicDriver::drawMaskedShapeWithTextureAndColor(vertices->getVertices(),
					        info, inversed);
					mask->unmask();
				} else {
					//TEXTURE
					GraphicDriver::drawShapeWithTextureAndColor(vertices->getVertices(),
					        info);
				}
			} else if(mode.isSet(RenderStepMode::COLOR)) {
				//COLOR ONLY
				GraphicDriver::drawShapeWithColor(vertices->getVertices(),
				                                  info);
			}
		}
	}
}

void RenderStep::mask() {
	if(vertices && !vertices->getVertices().empty()) {
		GraphicDriver::drawMaskShapeWithTextureAndColor(vertices->getVertices(),
		        info);
	}
}

void RenderStep::unmask() {
	if(vertices && !vertices->getVertices().empty()) {
		GraphicDriver::unmask(vertices->getVertices(), info);
	}
}
RenderInfo& RenderStep::getRenderInfo() {
	return info;
}

void RenderStep::setRenderInfo(const RenderInfo& newRenderInfo) {
	info = newRenderInfo;
}

const FlagSet<RenderStepMode>& RenderStep::getMode() const {
	return mode;
}

void RenderStep::setMode(const FlagSet<RenderStepMode>& newMode) {
	mode = newMode;
}

void RenderStep::setMode(const RenderStepMode& newMode) {
	mode = FlagSet<RenderStepMode>(newMode);
}

void RenderStep::addMode(const FlagSet<RenderStepMode>& newMode) {
	mode |= newMode;
}

void RenderStep::addMode(const RenderStepMode& newMode) {
	mode.set(newMode);
}

void RenderStep::removeMode(const FlagSet<RenderStepMode>& modeToRemove) {
	mode.reset(modeToRemove);
}

void RenderStep::removeMode(const RenderStepMode& modeToRemove) {
	mode.reset(modeToRemove);
}

bool RenderStep::isDeleteVerticesGroup() const {
	return deleteVerticesGroup;
}

void RenderStep::setDeleteVerticesGroup(bool newDeleteVerticesGroup) {
	deleteVerticesGroup = newDeleteVerticesGroup;
}

VerticesGroup* RenderStep::getVerticesGroup() {
	return vertices;
}

void RenderStep::setVerticesGroup(VerticesGroup* newVertices) {
	vertices = newVertices;
}

void RenderStep::playAnimation(const std::string& name) {
	// We check if the animation really exists.
	if(info.animationExists(name)) {
		if(info.getCurrentAnimation() != name) {
			// We set the new current animation and start the animation at the first
			// frame.
			info.setCurrentAnimation(name);
			info.setCurrentFrame(0);
			info.resetCurrentNbLoops();
			animCounter = 0.0;
			isPaused = false;
		}
	} else {
		Console::print("Tried to play an animation which does not exist for the concerned RenderStep: " + name);
		Console::printTrace();
	}
}

void RenderStep::pauseAnimation() {
	isPaused = true;
}

void RenderStep::resumeAnimation() {
	isPaused = false;
}

const std::string& RenderStep::getCurrentAnimation() const {
	return info.getCurrentAnimation();
}

GraphicBody* RenderStep::getMask() {
	return info.getMask();
}

void RenderStep::setMask(GraphicBody* aMask) {
	info.setMask(aMask);
}

void RenderStep::setColor(const Color& newColor) {
	info.setColor(newColor);
}

void RenderStep::clearVertices() {
	if(deleteVerticesGroup && vertices) {
		delete vertices;
	}
}

namespace RedBox {
	std::ostream& operator<<(std::ostream& output, const RenderStep& r) {
		output << "{info: " << r.info << ", vertices: " << r.vertices <<
				  ", deleteVerticesGroup: " << r.deleteVerticesGroup <<
				  ", isPaused: " << r.isPaused << ", animCounter: " <<
				  r.animCounter << "}";
		return output;
	}
}


