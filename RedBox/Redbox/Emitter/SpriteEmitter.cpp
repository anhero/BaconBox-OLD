#if 0
#include "SpriteEmitter.h"

#include <cassert>
#include <cmath>

#include "Console.h"

#include "Random.h"

#include "RenderInfo.h"

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

GraphicBody* SpriteEmitter::clone() const {
	return new SpriteEmitter(*this);
}

void SpriteEmitter::updateAlpha(int16_t deltaAlpha, Sprite* graphicBody) {
	if(graphicBody) {
		int16_t tmpAlpha = static_cast<int16_t>(graphicBody->getMainAlpha());
		tmpAlpha += deltaAlpha;

		if(tmpAlpha > static_cast<int16_t>(Color::MAX_COMPONENT_VALUE)) {
			tmpAlpha = static_cast<int16_t>(Color::MAX_COMPONENT_VALUE);
		} else if(tmpAlpha < 0) {
			tmpAlpha = 0;
		}

		graphicBody->setMainAlpha(tmpAlpha);
	}
}

void SpriteEmitter::updateScaling(const Vector2& deltaScaling,
                                  Sprite* graphicBody) {
	if(graphicBody) {
		graphicBody->addToScaling(deltaScaling);
	}
}

void SpriteEmitter::updateRotation(float deltaAngle, Sprite* graphicBody) {
	if(graphicBody) {
		graphicBody->rotate(deltaAngle);
	}
}

void SpriteEmitter::startAnimation(const std::string& animationName,
                                   Sprite* graphicBody) {
	if(graphicBody) {
		graphicBody->playAnimation(animationName);
	}
}

Sprite* SpriteEmitter::initParticle() {
	if(defaultSprite) {
		return new Sprite(*defaultSprite);
	} else {
		Console::println("Initializing a particle without a default sprite.");
		return NULL;
	}
}

void SpriteEmitter::startParticle(Sprite*& graphicBody) {
	if(!graphicBody) {
		graphicBody = initParticle();
	}

	if(graphicBody) {
		graphicBody->setPosition(getXPosition(), getYPosition());
		Vector2 shootVec(Vector2::UP);
		shootVec.setLength(force + Random::getRandomFloat(0.0f, forceVariance));
		shootVec.rotate(angle + Random::getRandomFloat(-angleVariance, angleVariance));
		graphicBody->setVelocity(shootVec);
		graphicBody->setMainColor(defaultSprite->getMainColor());
		graphicBody->setAngle(defaultSprite->getAngle());
		graphicBody->setScaling(graphicBody->getScaling());
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

void SpriteEmitter::updateParticle(Sprite* graphicBody) {
	assert(graphicBody);
	graphicBody->update();
}

void SpriteEmitter::renderParticle(Sprite* graphicBody) {
	assert(graphicBody);
	graphicBody->render();
}

void SpriteEmitter::maskParticle(Sprite* graphicBody) {
	assert(graphicBody);
	graphicBody->mask();
}

void SpriteEmitter::unmaskParticle(Sprite* graphicBody) {
	assert(graphicBody);
	graphicBody->unmask();
}

void SpriteEmitter::setMaskParticle(GraphicBody* newMask, bool inversed,
                                    Sprite* graphicBody) {
	assert(graphicBody);
	graphicBody->setMask(newMask, inversed);
}

#endif
