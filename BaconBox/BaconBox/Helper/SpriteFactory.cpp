#include "BaconBox/Helper/SpriteFactory.h"

namespace BaconBox {
	Sprite *SpriteFactory::makePolygon(unsigned int nbSides, float sideLength,
	                                   const Color &color) {
		return makeSpecificPolygon<Sprite>(nbSides, sideLength, color);
	}

	InanimateSprite *SpriteFactory::makeInanimatePolygon(unsigned int nbSides,
	                                                     float sideLength,
	                                                     const Color &color) {
		return makeSpecificPolygon<InanimateSprite>(nbSides, sideLength, color);
	}
	
	SpriteEmitter *SpriteFactory::makeExplosion(const SpriteEmitter::ParticleType *defaultGraphic,
												int nbParticlesToShoot,
												float force, const Vector2 &startingPosition) {
		SpriteEmitter *result = NULL;
		if (nbParticlesToShoot > 0) {
			result = new SpriteEmitter(defaultGraphic);
			result->getPhases().push_back(ParticlePhase(0.5, 0.2, 0.0f, Vector2(), -50.0f, 0.0f, Vector2(), 100.0f));
			result->setPosition(startingPosition);
			result->setMaximumNbParticles(static_cast<unsigned int>(nbParticlesToShoot));
			result->setLifeSpan(1.0);
			result->setNbParticlesToShoot(0);
			result->setShootingAngle(0.0f);
			result->setShootingAngleVariance(180.0f);
			result->setShootingForce(force);
			result->setShootingForceVariance(force * 0.15f);
			result->setExplosion(true);
		}
		return result;
	}
}
