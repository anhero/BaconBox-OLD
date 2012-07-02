/**
 * @file
 * @ingroup Display
 */
#ifndef RB_INANIMATE_H
#define RB_INANIMATE_H

#include "BaconBox/Display/TextureMappable.h"
#include "BaconBox/Display/TextureCoordinates.h"
#include "BaconBox/Display/TexturePointer.h"

namespace BaconBox {
	class VertexArray;
	/**
	 * All bodies that are sure to not be animated can be derived from this
	 * class for a more lightweight implementation.
	 * @ingroup Display
	 */
	class Inanimate : public TextureMappable {
	public:
		/**
		 * Simple parameterized constructor.
		 * @param newTexture Texture pointer to use as the texture.
		 */
		explicit Inanimate(TexturePointer newTexture = TexturePointer());

		/**
		 * Parameterized constructor.
		 * @param newTexture Texture pointer to use as the texture.
		 * @param vertices Vertices to use to load the texture coordinates.
		 * @param offset Offset in the texture to use when loading the texture
		 * coordinates.
		 * @see BaconBox::Inanimate::textureCoordinates
		 */
		Inanimate(TexturePointer newTexture,
		          const VertexArray &vertices,
		          const Vector2 &offset);

		/**
		 * Copy constructor.
		 * @param src Inanimate to make a copy of.
		 */
		Inanimate(const Inanimate &src);

		/**
		 * Destructor.
		 */
		virtual ~Inanimate();

		/**
		 * Assignment operator.
		 * @param src Inanimate to make a copy of.
		 * @return Reference to the modified Inanimate.
		 */
		Inanimate &operator=(const Inanimate &src);

		/**
		 * Gets the texture coordinates for the body.
		 * @return Texture coordinates used to map the texture on the body's
		 * polygon.
		 * @see BaconBox::Inanimate::textureCoordinates
		 */
		virtual const TextureCoordinates &getCurrentTextureCoordinates() const;

		/**
		 * Gets the texture coordinates for the body.
		 * @return Texture coordinates used to map the texture on the body's
		 * polygon.
		 * @see BaconBox::Inanimate::textureCoordinates
		 */
		const TextureCoordinates &getTextureCoordinates() const;

		/**
		 * Gets the texture coordinates for the body.
		 * @return Texture coordinates used to map the texture on the body's
		 * polygon.
		 * @see BaconBox::Inanimate::textureCoordinates
		 */
		TextureCoordinates &getTextureCoordinates();

		/**
		 * Loads the texture coordinates.
		 * @param vertices Vertices to use to load the texture coordinates.
		 * @param offset Offset from the upper left corner of the texture.
		 * @see BaconBox::Inanimate::textureCoordinates
		 */
		void loadTextureCoordinates(const VertexArray &vertices,
		                            const Vector2 &offset);
		
		/**
		 * Loads the texture coordinates.
		 * @param vertices Vertices to use to load the texture coordinates.
		 * @param details Details about the frame's offset and orientation.
		 */
		void loadTextureCoordinates(const VertexArray &vertices,
									const FrameDetails &details);

		/**
		 * Loads the texture coordinates.
		 * @param newTexture Texture pointer to use as the texture.
		 * @param vertices Vertices to use to load the texture coordinates.
		 * @param offset Offset from the upper left corner of the texture (in
		 * pixels).
		 * @see BaconBox::Inanimate::textureCoordinates
		 */
		void loadTextureCoordinates(TexturePointer newTexture,
		                            const VertexArray &vertices,
		                            const Vector2 &offset);
	private:
		/// Contains the texture coordinates.
		TextureCoordinates textureCoordinates;
	};

}

#endif
