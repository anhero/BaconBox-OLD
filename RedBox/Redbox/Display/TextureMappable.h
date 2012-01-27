/**
 * @file
 * @ingroup Display
 */
#ifndef RB_TEXTURE_MAPPABLE_H
#define RB_TEXTURE_MAPPABLE_H

#include "Texturable.h"
#include "TextureCoordinates.h"
#include "TexturePointer.h"

namespace RedBox {
	struct FrameDetails;
	class VertexArray;
	/**
	 * All bodies that have texture coordinates are derived from this class.
	 * @ingroup Display
	 */
	class TextureMappable : public Texturable {
	public:
		/**
		 * Loads texture coordinates.
		 * @param texture Texture pointer to use as the texture.
		 * @param vertices Vertices to use to load the texture coordinates.
		 * @param offset Offset from the upper left corner of the texture (in
		 * pixels).
		 * @param textureCoordinates Pointer to the container for the loaded
		 * texture coordinates. Loads as many texture coordinates as there are
		 * vertices.
		 */
		static void loadTextureCoordinates(TexturePointer texture,
		                                   const VertexArray &vertices,
		                                   const Vector2 &offset,
		                                   TextureCoordinates *textureCoordinates);

		/**
		 * Loads texture coordinates.
		 * @param texture Texture pointer to use as the texture.
		 * @param vertices Vertices to use to load the texture coordinates.
		 * @param details Details about the frame's offset and orientation.
		 * @param textureCoordinates Pointer to the container for the loaded
		 * texture coordinates. Loads as many texture coordinates as there are
		 * vertices.
		 */
		static void loadTextureCoordinates(TexturePointer texture,
										   const VertexArray &vertices,
										   const FrameDetails &details,
										   TextureCoordinates *textureCoordinates);

		/**
		 * Default constructor.
		 */
		TextureMappable();

		/**
		 * Simple parameterized constructor.
		 * @param newTexture Texture pointer to use as the texture.
		 * @see RedBox::Texturable::textureInformation
		 */
		explicit TextureMappable(TexturePointer newTexture);

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
