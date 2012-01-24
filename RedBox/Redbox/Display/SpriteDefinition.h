/**
 * @file
 * @ingroup Display
 */
#ifndef RB_SPRITE_DEFINITION_H
#define RB_SPRITE_DEFINITION_H

#include "FrameList.h"
#include "AnimationDefinition.h"

namespace RedBox {
	/**
	 * Contains information about the frames and animations to load for a
	 * sprite. Sprite definitions are mainly managed by texture atlases.
	 * @see RedBox::TextureAtlas
	 * @ingroup Display
	 */
	struct SpriteDefinition {
		/// List of frames to load from a texture.
		FrameList frames;

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
}

#endif
