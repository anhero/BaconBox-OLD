/**
 * @file
 * @ingroup Display
 */
#ifndef RB_LAYERED_BATCH_H
#define RB_LAYERED_BATCH_H

#include "Layerable.h"
#include "RenderBatch.h"

namespace BaconBox {
	/**
	 * Contains a batch of sprites to be rendered efficiently.
	 */
	template <typename ValueType>
	class LayeredBatch : public Layerable, public RenderBatch<ValueType> {
	public:
		/**
		 * Default constructor.
		 */
		LayeredBatch() : Layerable(), RenderBatch<ValueType>() {
		}

		/**
		 * Parameterized constructor. Constructs the sprite batch and sets its
		 * texture.
		 * @param newTexture Texture pointer to use as the batch's texture. All
		 * sprites in the batch will use this texture.
		 */
		explicit LayeredBatch(TexturePointer newTexture) : Layerable(),
			RenderBatch<ValueType>(newTexture) {
		}


		/**
		 * Copy constructor.
		 * @param src Sprite batch to make a copy of.
		 */
		LayeredBatch(const LayeredBatch<ValueType> &src) : Layerable(src),
			RenderBatch<ValueType>(src) {
		}

		/**
		 * Destructor.
		 */
		virtual ~LayeredBatch() {
		}

		/**
		 * Assignation operator overload.
		 * @param src Sprite batch to make a copy of.
		 * @return Reference to the modified sprite batch.
		 */
		LayeredBatch<ValueType> &operator=(const LayeredBatch<ValueType> &src)  {
			this->Layerable::operator=(src);
			this->RenderBatch<ValueType>::operator=(src);
			return *this;
		}
	};
}

#endif // RB_LAYERED_BATCH_H
