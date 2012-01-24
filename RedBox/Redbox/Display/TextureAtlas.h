/**
 * @file
 * @ingroup Display
 */
#ifndef RB_TEXTURE_ATLAS_H
#define RB_TEXTURE_ATLAS_H

#include <string>
#include <map>

#include "TexturePointer.h"
#include "SpriteDefinition.h"

namespace RedBox {
	struct TextureInformation;
	/**
	 * Contains texture atlas information. It contains details about a large
	 * texture containing sub-textures that can be related or not. It can be
	 * used to load a sprite that uses one or more of thoses sub-textures.
	 * @see RedBox::FrameList
	 * @see RedBox::FrameDetails
	 * @ingroup Display
	 */
	class TextureAtlas {
	public:
		/// Type used to map frame lists to a name.
		typedef std::map<std::string, SpriteDefinition> SpriteMap;

		/**
		 * Default constructor.
		 */
		TextureAtlas();

		/**
		 * Parameterized constructor.
		 * @param newTexture Texture pointer to use.
		 * @see RedBox::TextureAtlas::texture
		 */
		explicit TextureAtlas(TexturePointer newTexture);

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
		 * Gets the frame lists.
		 * @return Reference to the frame lists mapped to their name.
		 * @see RedBox::TextureAtlas::frameLists
		 */
		SpriteMap &getSpriteDefinitions();

		/**
		 * Gets the frame lists.
		 * @return Reference to the frame lists mapped to their name.
		 * @see RedBox::TextureAtlas::frameLists
		 */
		const SpriteMap &getSpriteDefinitions() const;

		/**
		 * Gets the atlas's texture information.
		 * @return Pointer to the texture information concerned by the texture
		 * atlas.
		 * @see RedBox::TextureAtlas::textureInformation
		 */
		TextureInformation *getTextureInformation() const;

		/**
		 * Sets the atlas's texture.
		 * @param newTexture Pointer to the new texture to use.
		 * @see RedBox::TextureAtlas::textureInformation
		 */
		void setTextureInformation(TexturePointer newTexture);
	private:
		/// Pointer to the texture.
		TextureInformation *textureInformation;

		/// Sprite definitions and their associated unique key.
		SpriteMap spriteDefinitions;
	};
}

#endif
