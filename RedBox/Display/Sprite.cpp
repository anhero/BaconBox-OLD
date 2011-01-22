#include "Sprite.h"

using namespace RedBox;

void Sprite::clean() {
}

void Sprite::copyFrom(const Sprite& src) {
    if(this != &src && &src) {
        clean();
    } else {
    }
}

Sprite::Sprite(): Renderable() {
}

Sprite::Sprite(const Sprite& src):Renderable(src) {
    copyFrom(src);
}

Sprite::~Sprite() {
    clean();
}

Sprite& Sprite::operator=(const Sprite& src) {
    Renderable::operator=(src);
    copyFrom(src);
    return *this;
}

void Sprite::render() {
}