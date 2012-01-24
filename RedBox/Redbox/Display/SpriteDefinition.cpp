#include "SpriteDefinition.h"

namespace RedBox {
	SpriteDefinition::SpriteDefinition() : vertices(), frames(), animations() {
	}

	SpriteDefinition::SpriteDefinition(const SpriteDefinition &src) :
		vertices(src.vertices), frames(src.frames), animations(src.animations) {
	}

	SpriteDefinition &SpriteDefinition::operator=(const SpriteDefinition &src) {
		if (this != &src) {
			vertices = src.vertices;
			frames = src.frames;
			animations = src.animations;
		}

		return *this;
	}

	std::ostream &operator<<(std::ostream &output, SpriteDefinition &sd8) {
		/*output << "{ \"frames\": " << sd.frames << ", \"animations\": {";

		for (AnimationMap::const_iterator i = sd.animations.begin(); i != sd.animations.end(); ++i) {
			if (i != sd.animations.begin()) {
				output << ", ";
			}

			output << "\"" << i->first << "\": " << i->second;
		}

		output << "}}";*/

		return output;
	}
}
