#include "RenderStep.h"

#include "ResourceLoader.h"
#include "TimeHelper.h"
#include "AnimationParameters.h"
#include "Debug.h"

using namespace RedBox;

RenderStep::RenderStep(): Renderable(), vertices(new VerticesGroup()),
deleteVerticesGroup(true), useSinceEpoch(false) {
}

RenderStep::RenderStep(TextureInfo* newTexInfo,
					   VerticesGroup* newVertices,
					   unsigned int nbFrames,
					   float factor,
					   float offsetX,
					   float offsetY,
					   int* newColor,
					   bool newDeleteVerticesGroup): Renderable(),
vertices(newVertices), deleteVerticesGroup(newDeleteVerticesGroup),
info(RenderInfo(newTexInfo, newVertices, nbFrames, factor, offsetX, offsetY, newColor)),
mode(RenderStepMode::SHAPE | RenderStepMode::TEXTURE), useSinceEpoch(false),
lastFrameChange(0.0), currentAnimation(""), isPaused(false),
pauseFrameRemain(0.0) {
	if(newColor) {
		mode |= RenderStepMode::COLOR;
	}
}

RenderStep::RenderStep(const std::string& key,
					   VerticesGroup* newVertices,
					   unsigned int nbFrames,
					   float factor,
					   float offsetX,
					   float offsetY,
					   bool newDeleteVerticesGroup): Renderable(),
vertices(newVertices), deleteVerticesGroup(newDeleteVerticesGroup),
info(RenderInfo(ResourceLoader::getTexture(key), newVertices, nbFrames, factor, offsetX, offsetY)),
mode(RenderStepMode::SHAPE | RenderStepMode::TEXTURE), useSinceEpoch(false),
lastFrameChange(0.0), currentAnimation(""), isPaused(false),
pauseFrameRemain(0.0) {
}

RenderStep::RenderStep(const RenderStep& src):Renderable(src), mode(src.mode), 
info(src.info), vertices(src.vertices),
deleteVerticesGroup(src.deleteVerticesGroup), useSinceEpoch(src.useSinceEpoch),
lastFrameChange(0.0), currentAnimation(src.currentAnimation), isPaused(false),
pauseFrameRemain(0.0) {
}

RenderStep& RenderStep::operator=(const RenderStep &src) {
    Renderable::operator=(src);
    copyFrom(src);
    return *this;
}

RenderStep::~RenderStep() {
    clean();
}

void RenderStep::render() {
	if(vertices) {
		// We use the bitwise inclusive OR to combine different modes.
		if(mode == (RenderStepMode::SHAPE | RenderStepMode::TEXTURE | RenderStepMode::COLOR)) {
			Drawer::drawShapeWithTextureAndColor(vertices, info, vertices->getVertices().size());
		} else if(mode == (RenderStepMode::SHAPE | RenderStepMode::TEXTURE)) {
			Drawer::drawShapeWithTexture(vertices, info, vertices->getVertices().size());
		}
	}
}

void RenderStep::update() {
	if(info.isAnimated() && !isPaused) {
		AnimationParameters* anim = info.getAnimationParameters(currentAnimation);
		if(anim) {
			if(((useSinceEpoch)?(TimeHelper::getSinceEpoch()):(TimeHelper::getSinceStart())) >= lastFrameChange + anim->timePerFrame) {
				info.incrementFrame();
			}
		}
	}
}

RenderInfo& RenderStep::getRenderInfo() {
    return info;
}

void RenderStep::setRenderInfo(const RenderInfo& newRenderInfo) {
    info = newRenderInfo;
}

RenderStepMode::Enum RenderStep::getMode() const {
    return mode;
}

void RenderStep::setMode(RenderStepMode::Enum newMode) {
    mode = newMode;
}

void RenderStep::addMode(RenderStepMode::Enum newMode) {
    mode |= newMode;
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

bool RenderStep::isUseSinceEpoch() const {
	return useSinceEpoch;
}
void RenderStep::setUseSinceEpoch(bool newUseSinceEpoch) {
	useSinceEpoch = newUseSinceEpoch;
}

void RenderStep::playAnimation(const std::string& name) {
	// We check if the animation really exists.
	if(info.animationExists(name)) {
		// We set the new current animation and start the animation at the first
		// frame.
		currentAnimation = name;
		info.setCurrentFrame(0);
		if(useSinceEpoch) {
			lastFrameChange = TimeHelper::getSinceEpoch();
		} else {
			lastFrameChange = TimeHelper::getSinceStart();
		}
	} else {
		$ECHO("Tried play an animation which does not exist for the concerned RenderStep: " << name);
	}
}

void RenderStep::pauseAnimation() {
	isPaused = true;
	if(useSinceEpoch) {
		pauseFrameRemain = TimeHelper::getSinceEpoch() - lastFrameChange;
	} else {
		pauseFrameRemain = TimeHelper::getSinceStart() - lastFrameChange;
	}
}

void RenderStep::resumeAnimation() {
	isPaused = false;
	if(useSinceEpoch) {
		lastFrameChange = TimeHelper::getSinceEpoch() - pauseFrameRemain;
	} else {
		lastFrameChange = TimeHelper::getSinceStart() - pauseFrameRemain;
	}
	pauseFrameRemain = 0.0;
}

const std::string& RenderStep::getCurrentAnimation() const {
	return currentAnimation;
}

void RenderStep::clean() {
    if(deleteVerticesGroup && vertices) {
        delete vertices;
    }
}

void RenderStep::copyFrom(const RenderStep &src) {
    if(this != &src && &src) {
        clean();
        mode = src.mode;
        info = src.info;
        vertices = src.vertices;
		useSinceEpoch = src.useSinceEpoch;
        deleteVerticesGroup = src.deleteVerticesGroup;
		lastFrameChange = 0.0;
		currentAnimation = src.currentAnimation;
		isPaused = false;
		pauseFrameRemain = 0.0;
    }
}
