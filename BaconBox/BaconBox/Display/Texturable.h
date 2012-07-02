/**
 * @file
 * @ingroup Display
 */
#ifndef RB_TEXTURABLE_H
#define RB_TEXTURABLE_H

#include <string>

#include "BaconBox/Display/TexturePointer.h"

namespace BaconBox {
	struct TextureInformation;
	/**
	 * All texturable bodies are derived from this.
	 * @ingroup Display
	 */
	class Texturable {
	public:
		/**
		 * Simple parameterized constructor.
		 * @param newTexture Texture pointer to use as the texture.
		 * @see BaconBox::Texturable::textureInformation
		 */
		explicit Texturable(TexturePointer newTexture = TexturePointer());

		/**
		 * Copy constructor.
		 * @param src Texturable to make a copy of.
		 */
		Texturable(const Texturable &src);

		/**
		 * Destructor.
		 */
		virtual ~Texturable();

		/**
		 * Assignment operator.
		 * @param src Texturable to make a copy of.
		 * @return Reference to the modified Texturable.
		 */
		Texturable &operator=(const Texturable &src);

		/**
		 * Gets the texturable body's texture.
		 * @return Pointer to the body's texture.
		 * @see BaconBox::Texturable::textureInformation
		 */
		TextureInformation *getTextureInformation() const;

		/**
		 * Sets the texturable body's texture.
		 * @param newTexture Texture pointer to use as the new texture.
		 * @see BaconBox::Texturable::textureInformation
		 * @see BaconBox::ResourceManager::getTexture(const std::string &key)
		 */
		virtual void setTextureInformation(TexturePointer newTexture);
	private:
		/// Pointer to the texture information.
		TextureInformation *textureInformation;
	};

}

#endif
