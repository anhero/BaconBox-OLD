#include "RenderStep.h"

#include "ResourceLoader.h"

using namespace RedBox;

RenderStep::RenderStep(): Renderable(), vertices(new VerticesGroup()), deleteVerticesGroup(true) {
}

RenderStep::RenderStep(TextureInfo* newTexInfo, int* newColor): Renderable(),
vertices(NULL), deleteVerticesGroup(false),
info(RenderInfo(newTexInfo, NULL, newColor)),
mode(RenderStepMode::SHAPE | RenderStepMode::TEXTURE) {
	if(newColor) {
		mode |= RenderStepMode::COLOR;
	}
}

RenderStep::RenderStep(TextureInfo* newTexInfo,
					   VerticesGroup* newVertices,
					   bool newDeleteVerticesGroup): Renderable(),
vertices(newVertices), deleteVerticesGroup(newDeleteVerticesGroup),
info(RenderInfo(newTexInfo, newVertices)),
mode(RenderStepMode::SHAPE | RenderStepMode::TEXTURE) {
}

RenderStep::RenderStep(std::string key,
					   VerticesGroup* newVertices,
					   bool newDeleteVerticesGroup): Renderable(),
vertices(newVertices), deleteVerticesGroup(newDeleteVerticesGroup),
info(RenderInfo(ResourceLoader::getTexture(key), newVertices)),
mode(RenderStepMode::SHAPE | RenderStepMode::TEXTURE) {
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
