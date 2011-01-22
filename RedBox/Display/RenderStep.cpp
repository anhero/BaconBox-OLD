#include "RenderStep.h"

using namespace RedBox;

RenderStep::RenderStep() {
}

RenderStep::RenderStep(const RenderStep& src): mode(src.mode), info(src.info), 
vertices(src.vertices) {
}

RenderStep::~RenderStep() {
}

void RenderStep::copyFrom(const RenderStep &src) {
    if(this != &src && &src) {
        mode = src.mode;
        info = src.info;
        vertices = src.vertices;
    }
}

RenderStep& RenderStep::operator=(const RenderStep &src) {
    copyFrom(src);
    return *this;
}

void RenderStep::render() {
    // We use the bitwise inclusive OR to combine different modes.
    if(mode == SHAPE | TEXTURE | COLOR) {
        // drawShapeWithTextureAndColor
    } else if(mode == SHAPE | TEXTURE) {
        // drawShapeWithTexture
    }
}

RenderInfo& RenderStep::getRenderInfo() {
    return info;
}

void RenderStep::setRenderInfo(const RenderInfo& newRenderInfo) {
    info = newRenderInfo;
}

RenderStepMode RenderStep::getMode() const {
    return mode;
}

void RenderStep::setMode(RenderStepMode newMode) {
    mode = newMode;
}

void RenderStep::addMode(RenderStepMode newMode) {
    mode |= newMode;
}