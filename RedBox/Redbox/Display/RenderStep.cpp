#include "RenderStep.h"

#include "TextureInfo.h"
#include "RenderInfo.h"
#include "GraphicDriver.h"
#include "ResourceManager.h"
#include "TimeHelper.h"
#include "AnimationParameters.h"
#include "Debug.h"
#include "Vertex.h"
#include "VerticesGroup.h"

using namespace RedBox;

RenderStep::RenderStep(): vertices(0), useSinceEpoch(false),
	deleteVerticesGroup(false), lastFrameChange(0.0), isPaused(false),
pauseFrameRemain(0.0) {
}

RenderStep::RenderStep(TextureInfo* newTexInfo,
					   VerticesGroup* newVertices,
					   unsigned int frameWidth,
					   unsigned int frameHeight,
					   unsigned int nbFrames,
					   const Color& newColor,
					   bool newDeleteVerticesGroup): 
info(RenderInfo(newTexInfo, newVertices, frameWidth, frameHeight, nbFrames,
				newColor)),
mode(RenderStepMode::SHAPE | RenderStepMode::TEXTURE),
vertices(newVertices),
useSinceEpoch(false),
deleteVerticesGroup(newDeleteVerticesGroup),
lastFrameChange(0.0),
isPaused(false),
pauseFrameRemain(0.0) {
	if(vertices) {
		vertices->updateDataFromVertices(verticesData);
	}
	if(newColor != Color::WHITE) {
		mode |= RenderStepMode::COLOR;
	}
}

RenderStep::RenderStep(const std::string& key,
					   VerticesGroup* newVertices,
					   unsigned int frameWidth,
					   unsigned int frameHeight,
					   unsigned int nbFrames,
					   bool newDeleteVerticesGroup):
info(RenderInfo(ResourceManager::getTexture(key), newVertices, frameWidth, frameHeight, nbFrames)),
mode(RenderStepMode::SHAPE | RenderStepMode::TEXTURE), vertices(newVertices),
useSinceEpoch(false), deleteVerticesGroup(newDeleteVerticesGroup),
lastFrameChange(0.0), isPaused(false),
pauseFrameRemain(0.0) {
	if(vertices) {
		vertices->updateDataFromVertices(verticesData);
	}
}

RenderStep::RenderStep(const RenderStep& src): vertices(0),
useSinceEpoch(false), deleteVerticesGroup(false), lastFrameChange(0.0),
isPaused(false), pauseFrameRemain(0.0) {
	copyFrom(src);
}

RenderStep& RenderStep::operator=(const RenderStep &src) {
 
    copyFrom(src);
    return *this;
}

RenderStep::~RenderStep() {
    clean();
}

void RenderStep::render() {
	updateVerticesData();
	if(verticesData.size()) {
		// We use the bitwise inclusive OR to combine different modes.
		if(mode == (RenderStepMode::SHAPE | RenderStepMode::TEXTURE | RenderStepMode::COLOR)) {
			GraphicDriver::drawShapeWithTextureAndColor(verticesData, info,
												 vertices->getVertices().size());
		} else if(mode == (RenderStepMode::SHAPE | RenderStepMode::TEXTURE)) {
			GraphicDriver::drawShapeWithTexture(verticesData, info,
										 vertices->getVertices().size());
		} else if(mode == (RenderStepMode::SHAPE | RenderStepMode::COLOR)) {
			GraphicDriver::drawShapeWithColor(verticesData, info, vertices->getVertices().size());
		}
	}
}

void RenderStep::update() {
	if(!isPaused) {
		if(info.isAnimated()) {
			AnimationParameters* anim = info.getAnimationParameters(info.getCurrentAnimation());
			if(anim) {
				if(((useSinceEpoch)?(TimeHelper::getInstance().getSinceStartComplete()):(TimeHelper::getInstance().getSinceStart())) >= lastFrameChange + anim->timePerFrame) {
					info.incrementFrame();
					lastFrameChange = ((useSinceEpoch)?(TimeHelper::getInstance().getSinceStartComplete()):(TimeHelper::getInstance().getSinceStart()));
				}
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

void RenderStep::removeMode(RenderStepMode::Enum mode) {
	//Magic line fliping to 0 every flag passed with the mode parameter. 
    mode = ~(~(mode) | (mode));
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
		info.setCurrentAnimation(name);
		info.setCurrentFrame(0);
		info.resetCurrentNbLoops();
		if(useSinceEpoch) {
			lastFrameChange = TimeHelper::getInstance().getSinceStartComplete();
		} else {
			lastFrameChange = TimeHelper::getInstance().getSinceStart();
		}
	} else {
		RB_ECHO("Tried play an animation which does not exist for the concerned RenderStep: " << name);
	}
}

void RenderStep::pauseAnimation() {
	isPaused = true;
	if(useSinceEpoch) {
		pauseFrameRemain = TimeHelper::getInstance().getSinceStartComplete() - lastFrameChange;
	} else {
		pauseFrameRemain = TimeHelper::getInstance().getSinceStart() - lastFrameChange;
	}
}

void RenderStep::resumeAnimation() {
	isPaused = false;
	if(useSinceEpoch) {
		lastFrameChange = TimeHelper::getInstance().getSinceStartComplete() - pauseFrameRemain;
	} else {
		lastFrameChange = TimeHelper::getInstance().getSinceStart() - pauseFrameRemain;
	}
	pauseFrameRemain = 0.0;
}

const std::string& RenderStep::getCurrentAnimation() const {
	return info.getCurrentAnimation();
}

void RenderStep::clean() {
    if(deleteVerticesGroup && vertices) {
        delete vertices;
    }
}

void RenderStep::updateVerticesData() {
	if(vertices) {
		vertices->updateDataFromVertices(verticesData);
	} else {
		// We make sure that verticesData has the correct size.
		if(verticesData.size() != verticesPtr.size() * 2) {
			verticesData.resize(verticesPtr.size() * 2);
		}
		// We set all the verticesData's correct values.
		std::vector<float>::iterator data = verticesData.begin();
		for (std::list<Vertex*>::iterator i = verticesPtr.begin();
			 i != verticesPtr.end(); i++) {
			*data = (*i)->getXPosition();
			++data;
			*data = (*i)->getYPosition();
		}
	}
}

void RenderStep::addVertexPtr(Vertex* vertexPtr) {
	verticesPtr.push_back(vertexPtr);
}

void RenderStep::addVerticesPtr(std::list<Vertex*>::iterator first,
								std::list<Vertex*>::iterator last) {
	verticesPtr.insert(verticesPtr.end(), first, last);
}

void RenderStep::addVerticesPtr(unsigned int nbVerticesPtr, ...) {
	if(nbVerticesPtr) {
		va_list lstPtr;
		va_start(lstPtr, nbVerticesPtr);
		for(unsigned int i = 0; i < nbVerticesPtr; i++) {
			addVertexPtr(va_arg(lstPtr, Vertex*));
		}
		va_end(lstPtr);
	}
}

void RenderStep::removeVertexPtr(Vertex* vertexPtr) {
	verticesPtr.remove(vertexPtr);
}

void RenderStep::copyFrom(const RenderStep &src) {
    if(this != &src && &src) {
        clean();
		info = src.info;
		mode = src.mode;
		vertices = 0;
		verticesData.clear();
		verticesPtr.clear();
		useSinceEpoch = src.useSinceEpoch;
        deleteVerticesGroup = src.deleteVerticesGroup;
		lastFrameChange = 0.0;
		isPaused = false;
		pauseFrameRemain = 0.0;
    }
}

void RenderStep::setColor(const Color& newColor){
	info.setColor(newColor);
}

namespace RedBox {
	std::ostream& operator<<(std::ostream& output, const RenderStep& r) {
		output << "{info: " << r.info << ", mode: ";
		bool needsPipe = false;
		if(r.mode & RenderStepMode::SHAPE) {
			needsPipe = true;
			output << "RenderStepMode::SHAPE";
		}
		if(r.mode & RenderStepMode::TEXTURE) {
			if(needsPipe) {
				output << "|";
			} else {
				needsPipe = true;
			}
			output << "RenderStepMode::TEXTURE";
		}
		if(r.mode & RenderStepMode::COLOR) {
			if(needsPipe) {
				output << "|";
			}
			output << "RenderStepMode::COLOR";
		}
		output << ", vertices: " << r.vertices << ", useSinceEpoch: " <<
		((r.useSinceEpoch)?("true"):("false")) << ", deleteVerticesGroup: " <<
		((r.deleteVerticesGroup)?("true"):("false")) << ", lastFrameChange: " <<
		r.lastFrameChange << ", isPaused: " <<
		((r.isPaused)?("true"):("false")) <<
		", pauseFrameRemain: " << r.pauseFrameRemain << "}";
		return output;
	}
}


