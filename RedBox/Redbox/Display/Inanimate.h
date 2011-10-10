/**
 * @file
 * @ingroup Display
 */
#ifndef RB_INANIMATE_H
#define RB_INANIMATE_H

#include "TextureMappable.h"
#include "TextureCoordinates.h"

namespace RedBox {
	class VerticesArray;
	/**
	 * All bodies that are sure to not be animated can be derived from this
	 * class for a more lightweight implementation.
	 * @ingroup Display
	 */
	class Inanimate : public TextureMappable {
	public:
		/**
		 * Default constructor. Does not load the texture coordinates.
		 */
		Inanimate();

		/**
		 * Simple parameterized constructor.
		 * @param newTextureKey Key to the texture to create a texturable from.
		 */
		explicit Inanimate(const std::string &newTextureKey);

		/**
		 * Simple parameterized constructor. Does the same thing as the
		 * constructor that recieves an key. Does not load the texture
		 * coordinates
		 * @param newTextureInformation Pointer to the texture information to
		 * load the body with.
		 * @see RedBox::Texturable::textureInformation
		 */
		explicit Inanimate(const TextureInformation *newTextureInformation);

		/**
		 * Parameterized constructor.
		 * @param newTextureKey Key to the texture to create a texturable from.
		 * @param vertices Vertices to use to load the texture coordinates.
		 * @param offset Offset in the texture to use when loading the texture
		 * coordinates.
		 * @see RedBox::Inanimate::textureCoordinates
		 */
		Inanimate(const std::string &newTextureKey,
		          const VerticesArray &vertices,
		          const Vector2 &offset);

		/**
		 * Parameterized constructor.
		 * @param newTextureInformation Pointer to the texture information to
		 * load the body with.
		 * @param vertices Vertices to use to load the texture coordinates.
		 * @param offset Offset in the texture to use when loading the texture
		 * coordinates.
		 * @see RedBox::Inanimate::textureCoordinates
		 */
		Inanimate(const TextureInformation *newTextureInformation,
		          const VerticesArray &vertices,
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
		 * @see RedBox::Inanimate::textureCoordinates
		 */
		virtual const TextureCoordinates &getCurrentTextureCoordinates() const;

		/**
		 * Gets the texture coordinates for the body.
		 * @return Texture coordinates used to map the texture on the body's
		 * polygon.
		 * @see RedBox::Inanimate::textureCoordinates
		 */
		const TextureCoordinates &getTextureCoordinates() const;

		/**
		 * Loads the texture coordinates.
		 * @param vertices Vertices to use to load the texture coordinates.
		 * @param offset Offset from the upper left corner of the texture.
		 * @see RedBox::Inanimate::textureCoordinates
		 */
		void loadTextureCoordinates(const VerticesArray &vertices,
		                            const Vector2 &offset);

		/**
		 * Loads the texture coordinates.
		 * @param newTextureKey Key to the texture to load the texture
		 * coordinates from.
		 * @param vertices Vertices to use to load the texture coordinates.
		 * @param offset Offset from the upper left corner of the texture (in
		 * pixels).
		 * @see RedBox::Inanimate::textureCoordinates
		 */
		void loadTextureCoordinates(const std::string &newTextureKey,
		                            const VerticesArray &vertices,
		                            const Vector2 &offset);

		/**
		 * Loads the texture coordinates.
		 * @param newTextureInformation Pointer to the new texture information
		 * to use to load the texture coordinates.
		 * @param vertices Vertices to use to load the texture coordinates.
		 * @param offset Offset from the upper left corner of the texture (in
		 * pixels).
		 * @see RedBox::Inanimate::textureCoordinates
		 */
		void loadTextureCoordinates(const TextureInformation *newTextureInformation,
		                            const VerticesArray &vertices,
		                            const Vector2 &offset);
	private:
		/// Contains the texture coordinates.
		TextureCoordinates textureCoordinates;
	};

}

#endif
