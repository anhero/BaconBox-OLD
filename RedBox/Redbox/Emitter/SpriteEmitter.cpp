#include "SpriteEmitter.h"

#include <cassert>

#include "Debug.h"

#include "Random.h"

using namespace RedBox;

SpriteEmitter::SpriteEmitter(): Emitter<Sprite>(), defaultSprite(0) {
}

SpriteEmitter::SpriteEmitter(const std::string& keyName): Emitter<Sprite>(),
defaultSprite(0) {
	defaultSprite = new Sprite(keyName);
}

SpriteEmitter::SpriteEmitter(Sprite* newDefaultSprite): Emitter<Sprite>(),
defaultSprite(newDefaultSprite) {
}

SpriteEmitter::SpriteEmitter(const SpriteEmitter& src): Emitter<Sprite>(src),
defaultSprite(0) {
	copyFrom(src);
}

SpriteEmitter::~SpriteEmitter() {
	if(defaultSprite) {
		delete defaultSprite;
	}
}

SpriteEmitter& SpriteEmitter::operator=(const SpriteEmitter& src) {
	Emitter<Sprite>::operator=(src);
	copyFrom(src);
	return *this;
}

void SpriteEmitter::setDefaultSprite(Sprite* newDefaultSprite) {
	if(defaultSprite) {
		delete defaultSprite;
	}
	defaultSprite = newDefaultSprite;
}

Sprite* SpriteEmitter::getDefaultSprite() {
	return defaultSprite;
}

void SpriteEmitter::updateAlpha(float deltaAlpha, Sprite* renderable) {
}

void SpriteEmitter::updateScaling(float deltaScaling, Sprite* renderable) {
}

Sprite* SpriteEmitter::initParticle() {
	if(defaultSprite) {
		return new Sprite(*defaultSprite);
	} else {
		RB_ECHO("Initializing a particle without a default sprite.");
		return NULL;
	}
}

void SpriteEmitter::startParticle(Sprite*& renderable) {
	if (!renderable) {
		renderable = initParticle();
	}
	if (renderable) {
		renderable->setPosition(getXPosition(), getYPosition());
		Vec2 shootVec(Vec2::UP);
		shootVec.setLength(force + Random::getRandomFloat(0.0f, forceVariance));
		shootVec.rotate(angle + Random::getRandomFloat(-angleVariance, angleVariance));
		renderable->setVelocity(shootVec);
	}
}

void SpriteEmitter::clean() {
	if(defaultSprite) {
		delete defaultSprite;
		defaultSprite = NULL;
	}
}

void SpriteEmitter::copyFrom(const SpriteEmitter& src) {
	if(this != &src && &src) {
		clean();
		if(src.defaultSprite) {
			defaultSprite = new Sprite(*src.defaultSprite);
		}
	}
}

void SpriteEmitter::updateParticle(Sprite* renderable) {
	assert(renderable);
	renderable->update();
}

void SpriteEmitter::renderParticle(Sprite* renderable) {
	assert(renderable);
	renderable->render();
}
