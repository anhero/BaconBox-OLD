#include "SpriteBatch.h"

namespace RedBox {
	SpriteBatch::SpriteBatch() : Layerable(), RenderBatch<BatchedSprite>() {
	}

	SpriteBatch::SpriteBatch(TexturePointer newTexture) : Layerable(),
		RenderBatch<BatchedSprite>(newTexture) {
	}

	SpriteBatch::SpriteBatch(const SpriteBatch &src) : Layerable(src),
		RenderBatch<BatchedSprite>(src) {
	}

	SpriteBatch::~SpriteBatch() {
	}

	SpriteBatch &SpriteBatch::operator=(const SpriteBatch &src) {
		this->Layerable::operator=(src);
		this->RenderBatch<BatchedSprite>::operator=(src);
		return *this;
	}
}
