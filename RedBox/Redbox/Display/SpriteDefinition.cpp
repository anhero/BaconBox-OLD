#include "SpriteDefinition.h"

namespace RedBox {
	SpriteDefinition::SpriteDefinition() : frames(), animations() {
	}

	SpriteDefinition::SpriteDefinition(const SpriteDefinition &src) :
		frames(src.frames), animations(src.animations) {
	}

	SpriteDefinition &SpriteDefinition::operator=(const SpriteDefinition &src) {
		if (this != &src) {
			frames = src.frames;
			animations = src.animations;
		}

		return *this;
	}
}
