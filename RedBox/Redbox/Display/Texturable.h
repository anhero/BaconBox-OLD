/**
 * @file
 * @ingroup Display
 */
#ifndef RB_TEXTURABLE_H
#define RB_TEXTURABLE_H

#include <string>

namespace RedBox {
	struct TextureInformation;
	/**
	 * All texturable bodies are derived from this.
	 * @ingroup Display
	 */
	class Texturable {
	public:
		/**
		 * Default constructor.
		 */
		Texturable();

		/**
		 * Simple parameterized constructor.
		 * @param newTextureKey Key to the texture to create a texturable from.
		 * @see RedBox::Texturable::textureInformation
		 */
		explicit Texturable(const std::string &newTextureKey);

		/**
		 * Simple parameterized constructor. Does the same thing as the
		 * constructor that recieves an key.
		 * @param newTextureInformation Pointer to the texture information to
		 * load the body with.
		 * @see RedBox::Texturable::textureInformation
		 */
		explicit Texturable(const TextureInformation *newTextureInformation);

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
		 * @see RedBox::Texturable::textureInformation
		 */
		const TextureInformation *getTextureInformation() const;

		/**
		 * Sets the texturable body's texture.
		 * @param newTextureKey Key of the new texture information.
		 * @see RedBox::Texturable::textureInformation
		 * @see RedBox::ResourceManager::getTexture(const std::string &key)
		 */
		void setTextureInformation(const std::string &newTextureKey);

		/**
		 * Sets the texturable body's texture.
		 * @param newTextureInformation Pointer to the body's new texture
		 * information.
		 * @see RedBox::Texturable::textureInformation
		 */
		void setTextureInformation(const TextureInformation *newTextureInformation);
	private:
		/// Pointer to the texture information.
		const TextureInformation *textureInformation;
	};

}

#endif
