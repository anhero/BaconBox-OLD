/**
 * @file
 * @ingroup Display
 */
#ifndef RB_TEXTURE_MAPPABLE_H
#define RB_TEXTURE_MAPPABLE_H

#include "Texturable.h"
#include "TextureCoordinates.h"

namespace RedBox {
	class VerticesArray;
	/**
	 * All bodies that have texture coordinates are derived from this class.
	 * @ingroup Display
	 */
	class TextureMappable : public Texturable {
	public:
		/**
		 * Loads texture coordinates.
		 * @param textureInformation Pointer to the new texture information
		 * to use.
		 * @param vertices Vertices to use to load the texture coordinates.
		 * @param offset Offset from the upper left corner of the texture (in
		 * pixels).
		 * @param textureCoordinates  Pointer to the container for the loaded
		 * texture coordinates. Loads as many texture coordinates as there are
		 * vertices.
		 */
		static void loadTextureCoordinates(const TextureInformation *textureInformation,
		                                   const VerticesArray &vertices,
		                                   const Vector2 &offset,
		                                   TextureCoordinates *textureCoordinates);

		/**
		 * Default constructor.
		 */
		TextureMappable();

		/**
		 * Simple parameterized constructor.
		 * @param newTextureKey Key to the texture to create a texturable from.
		 * @see RedBox::Texturable::textureInformation
		 */
		explicit TextureMappable(const std::string &newTextureKey);

		/**
		 * Simple parameterized constructor. Does the same thing as the
		 * constructor that recieves an key.
		 * @param newTextureInformation Pointer to the texture information to
		 * load the sprite with.
		 * @see RedBox::Texturable::textureInformation
		 */
		explicit TextureMappable(const TextureInformation *newTextureInformation);

		/**
		 * Copy constructor.
		 * @param src Displayable to make a copy of.
		 */
		TextureMappable(const TextureMappable &src);

		/**
		 * Destructor.
		 */
		virtual ~TextureMappable();

		/**
		 * Assignment operator.
		 * @param src Displayable to make a copy of.
		 * @return Reference to the modified Displayable.
		 */
		TextureMappable &operator=(const TextureMappable &src);

		/**
		 * Gets the texture coordinates for the body.
		 * @return Texture coordinates used to map the texture on the body's
		 * polygon.
		 */
		virtual const TextureCoordinates &getCurrentTextureCoordinates() const = 0;
	};

}

#endif
