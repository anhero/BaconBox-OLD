#include "BaconBox/Emitter/SpriteEmitter.h"

namespace BaconBox {
	SpriteEmitter::SpriteEmitter(const GraphicElement<Collidable> *newDefaultGraphic) :
		ParticleEmitter<Collidable, GraphicElement<Collidable> >(newDefaultGraphic),
		Layerable() {
	}

	SpriteEmitter::SpriteEmitter(const SpriteEmitter &src) :
		ParticleEmitter<Collidable, GraphicElement<Collidable> >(src),
		Layerable(src) {
	}

	SpriteEmitter::~SpriteEmitter() {
	}

	SpriteEmitter &SpriteEmitter::operator=(const SpriteEmitter &src) {
		this->ParticleEmitter<Collidable, GraphicElement<Collidable> >::operator=(src);
		this->Layerable::operator=(src);
		return *this;
	}

	void SpriteEmitter::finished() {
		this->BaseType::finished();
		this->setToBeDeleted(true);
	}
}
