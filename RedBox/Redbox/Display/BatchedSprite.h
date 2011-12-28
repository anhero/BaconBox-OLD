/**
 * @file
 */
#ifndef RB_BATCHED_SPRITE_H
#define RB_BATCHED_SPRITE_H

#include "BatchedGraphic.h"
#include "Animatable.h"
#include "Collidable.h"
#include "BatchedBody.h"

namespace RedBox {
	class BatchedSprite : public BatchedGraphic<Animatable, BatchedSprite>,
		public Collidable, public BatchedBody {
	public:
	private:
		/**
		 * Default constructor.
		 */
		BatchedSprite();

		/**
		 * Destructor.
		 */
		virtual ~BatchedSprite();
	};

}

#endif // RB_BATCHED_SPRITE_H
