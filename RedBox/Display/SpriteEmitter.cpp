#include "SpriteEmitter.h"

#include "RedBoxEngine.h"

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
	// We check that the sprite emitter is active.
	if(isActive) {
		for(std::vector<Particle>::iterator i = particles.begin();
			i != particles.end(); i++) {
			if(i->lifeSpan > 0.0) {
				i->sprite->render();
			}
		}
	}
}

void SpriteEmitter::update() {
	// We make sure that the sprite emitter is active and has a valid emitRate.
	if(isActive && emitRate > 0.0) {
		float rate = 1.0 / emitRate;
		emitCounter += RedBoxEngine::getUpdateDelta();
		// We try to shoot particles as long as the emission rate lets us.
		while(emitCounter > rate && shootParticle()) {
			emitCounter -= rate;
		}
		// We check if we have to count the sprite emitter's life span.
		if(lifeSpan != -1.0) {
			// We update the elapsed time for the sprite emitter.
			elapsedTime += RedBoxEngine::getUpdateDelta();
			if(lifeSpan < elapsedTime) {
				deactivate();
			}
		}
	}
	// We update the particles that still have a lifespan remaining.
	for(std::vector<Particle>::iterator i = particles.begin();
		i != particles.end(); i++) {
		// We check if it is still alive.
		if (i->lifeSpan > 0.0) {
			// We update the sprite.
			i->sprite->update();
			// We update the lifespan.
			i->lifeSpan -= RedBoxEngine::getUpdateDelta();
		}
	}
}

bool SpriteEmitter::getIsActive() const {
	return isActive;
}

bool SpriteEmitter::shootParticle() {
	if(nbParticles < particles.size()) {
		if(!particles[nbParticles].sprite) {
			// TODO: Initialize the sprite correctly.
			particles[nbParticles].sprite = new Sprite();
		}
		// We initialize its lifespan.
		particles[nbParticles].lifeSpan = particlesLifeSpan +
			Random::getRandomDouble(0.0, particlesLifeSpanVariance);
		return true;
	} else {
		return false;
	}
}

void SpriteEmitter::clean() {
}

void SpriteEmitter::copyFrom(const SpriteEmitter& src) {
	if(this != &src && &src) {
	}
}