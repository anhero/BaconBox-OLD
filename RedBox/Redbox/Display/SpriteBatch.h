/**
 * @file
 * @ingroup Display
 */
#ifndef RB_SPRITE_BATCH_H
#define RB_SPRITE_BATCH_H

#include "Layerable.h"
#include "RenderBatch.h"
#include "BatchedSprite.h"

namespace RedBox {
	/**
	 * Contains a batch of sprites to be rendered efficiently.
	 */
	class SpriteBatch : public Layerable, public RenderBatch<BatchedSprite> {
	public:
		/**
		 * Default constructor.
		 */
		SpriteBatch();

		/**
		 * Parameterized constructor. Constructs the sprite batch and sets its
		 * texture.
		 * @param newTexture Texture pointer to use as the batch's texture. All
		 * sprites in the batch will use this texture.
		 */
		explicit SpriteBatch(TexturePointer newTexture);

		/**
		 * Copy constructor.
		 * @param src Sprite batch to make a copy of.
		 */
		SpriteBatch(const SpriteBatch &src);

		/**
		 * Destructor.
		 */
		virtual ~SpriteBatch();

		/**
		 * Assignation operator overload.
		 * @param src Sprite batch to make a copy of.
		 * @return Reference to the modified sprite batch.
		 */
		SpriteBatch &operator=(const SpriteBatch &src);
	};
}

#endif // RB_SPRITE_BATCH_H
