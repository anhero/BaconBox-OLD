#include "SpriteEmitter.h"

using namespace RedBox;

SpriteEmitter::SpriteEmitter(): Emitter<Sprite>() {
}

SpriteEmitter::SpriteEmitter(const SpriteEmitter& src): Emitter<Sprite>(src) {
}

SpriteEmitter::~SpriteEmitter() {
}

SpriteEmitter& SpriteEmitter::operator=(const SpriteEmitter& src) {
	Emitter<Sprite>::operator=(src);
	copyFrom(src);
	return *this;
}

void SpriteEmitter::updateAlpha(float deltaAlpha, Sprite* renderable) {
}

void SpriteEmitter::updateScaling(float deltaScaling, Sprite* renderable) {
}

Sprite* SpriteEmitter::initParticle() {
	return NULL;
}

void SpriteEmitter::startParticle(Sprite*& renderable) {
	if (!renderable) {
		renderable = initParticle();
	}
	if (renderable) {
	}
}

void SpriteEmitter::clean() {
}

void SpriteEmitter::copyFrom(const SpriteEmitter& src) {
	if(this != &src && &src) {
	}
}