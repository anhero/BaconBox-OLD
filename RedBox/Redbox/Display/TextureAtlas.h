/**
 * @file
 * @ingroup Display
 */
#ifndef RB_TEXTURE_ATLAS_H
#define RB_TEXTURE_ATLAS_H

#include <iostream>
#include <string>
#include <map>

#include "SpriteDefinition.h"
#include "TextureDefinition.h"

namespace RedBox {
	struct TextureInformation;
	class Value;
	/**
	 * Contains texture atlas information. It contains details about a large
	 * texture containing sub-textures that can be related or not. It can be
	 * used to load a sprite that uses one or more of thoses sub-textures.
	 * @see RedBox::FrameList
	 * @see RedBox::FrameDetails
	 * @ingroup Display
	 */
	struct TextureAtlas {
		/// Type used to map frame lists to a name.
		typedef std::map<std::string, SpriteDefinition> SpriteMap;

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
		TextureAtlas();

		/**
		 * Parameterized constructor.
		 * @param newTextureDefinition Texture pointer to use.
		 * @see RedBox::TextureAtlas::textureDefinition
		 */
		explicit TextureAtlas(const TextureDefinition &newTextureDefinition);

		/**
		 * Copy constructor.
		 * @param src Texture atlas to make a copy of.
		 */
		TextureAtlas(const TextureAtlas &src);

		/**
		 * Assignment operator overload.
		 * @param src Texture atlas to copy.
		 * @return Reference to the modified texture atlas.
		 */
		TextureAtlas &operator=(const TextureAtlas &src);

		/**
		 * Operator [] overload. Used to access or create the frame lists.
		 * @param name Name of the frame list to access or create.
		 * @return Reference to the frame list.
		 * @see RedBox::TextureAtlas::frameLists
		 */
		SpriteMap::mapped_type &operator[](const SpriteMap::key_type &name);

		/**
		 * Gets the texture information associated with the texture definition.
		 * If the texture isn't loaded, it loads it.
		 * @return Pointer to the texture information, NULL if the texture
		 * cannot be loaded correctly.
		 */
		TextureInformation *getTextureInformation() const;

		/**
		 * Serializes the instance to a Value.
		 * @param node Node to serialize the instance into.
		 * @param setName Wether or not we need to set the name.
		 */
		void serialize(Value &node, bool setName = true) const;

		/**
		 * Deserializes the instance from a Value.
		 * @param node Value to read the data from.
		 * @return True on success, false on failure to read all the
		 * necessary data. Does not modify the instance when there is a failure.
		 */
		bool deserialize(const Value &node);

		/// Pointer to the texture.
		TextureDefinition textureDefinition;

		/// Sprite definitions and their associated unique key.
		SpriteMap spriteDefinitions;
	};

	std::ostream &operator<<(std::ostream &output, const TextureAtlas &ta);
}

#endif
