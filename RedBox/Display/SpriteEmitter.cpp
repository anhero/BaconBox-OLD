#include "SpriteEmitter.h"

using namespace RedBox;

SpriteEmitter::SpriteEmitter(): Renderable() {
}

SpriteEmitter::SpriteEmitter(const SpriteEmitter& src): Renderable(src) {
}

SpriteEmitter::~SpriteEmitter() {
}

SpriteEmitter& SpriteEmitter::operator=(const SpriteEmitter& src) {
	copyFrom(src);
	return *this;
}

void SpriteEmitter::render() {
}

void SpriteEmitter::update() {
}

bool SpriteEmitter::getIsActive() const {
	return isActive;
}

void SpriteEmitter::clean() {
}

void SpriteEmitter::copyFrom(const SpriteEmitter& src) {
	if(this != &src && &src) {
	}
}