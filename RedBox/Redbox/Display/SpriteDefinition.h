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
	class Value;
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
		 * Checks whether or not the Value contains the necessary information
		 * to deserialize the type.
		 * @param node Value to check.
		 * @return True if the value contains the necessary information, false
		 * if not.
		 */
		static bool isValidValue(const Value &node);

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

		/**
		 * Serializes the instance to a Value.
		 * @param node Node to serialize the instance into.
		 */
		void serialize(Value &node) const;

		/**
		 * Deserializes the instance from a Value.
		 * @param node Value to read the data from.
		 * @return True on success, false on failure to read all the
		 * necessary data. Does not modify the instance when there is a failure.
		 */
		bool deserialize(const Value &node);
	};

	std::ostream &operator<<(std::ostream &output, const SpriteDefinition &sd);
}

#endif
