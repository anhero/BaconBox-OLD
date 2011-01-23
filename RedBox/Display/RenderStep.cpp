#include "RenderStep.h"

using namespace RedBox;

RenderStep::RenderStep(): Renderable(), vertices(NULL), deleteVerticesGroup(false) {
}

RenderStep::RenderStep(const RenderStep& src): mode(src.mode), info(src.info), 
vertices(src.vertices), deleteVerticesGroup(src.deleteVerticesGroup) {
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
    // We use the bitwise inclusive OR to combine different modes.
    if(mode == (SHAPE | TEXTURE | COLOR)) {
        // drawShapeWithTextureAndColor
    } else if(mode == (SHAPE | TEXTURE)) {
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
        deleteVerticesGroup = src.deleteVerticesGroup;
    }
}
