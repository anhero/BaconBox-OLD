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