/**
 * @file
 * @ingroup Display
 */
#ifndef RB_SPRITE_DEFINITION_H
#define RB_SPRITE_DEFINITION_H

#include <iostream>

#include "StandardVertexArray.h"
#include "FrameArray.h"
#include "AnimationDefinition.h"

namespace RedBox {
	/**
	 * Contains information about the frames and animations to load for a
	 * sprite. Sprite definitions are mainly managed by texture atlases.
	 * @see RedBox::TextureAtlas
	 * @ingroup Display
	 */
	struct SpriteDefinition {
		/// Array of vertices containing the information about the shape.
		StandardVertexArray vertices;

		/// List of frames to load from a texture.
		FrameArray frames;

		/// Animations to load for the sprite.
		AnimationMap animations;

		/**
		 * Default constructor.
		 */
		SpriteDefinition();

		/**
		 * Copy constructor.
		 * @param src Sprite definition to make a copy of.
		 */
		SpriteDefinition(const SpriteDefinition &src);

		/**
		 * Assignment operator overload.
		 * @param src Sprite definition to copy.
		 * @return Reference to the modified sprite definition.
		 */
		SpriteDefinition &operator=(const SpriteDefinition &src);
	};

	std::ostream &operator<<(std::ostream &output, const SpriteDefinition &sd);
}

#endif
