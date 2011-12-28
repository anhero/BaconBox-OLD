/**
 * @file
 */
#ifndef RB_BATCHED_GRAPHIC_H
#define RB_BATCHED_GRAPHIC_H

#include "TextureMappable.h"
#include "StaticAssert.h"
#include "IsBaseOf.h"
#include "Maskable.h"
#include "Shapable.h"
#include "Colorable.h"
#include "BatchedVertexArray.h"
#include "TexturePointer.h"

namespace RedBox {
	template <typename T, typename U>
	class BatchedGraphic : public Colorable,
		public Shapable<BatchedVertexArray<U> >, public T {
		template <typename V> friend class RenderBatch;
	public:
		/**
		 * Parameterized constructor.
		 */
		explicit BatchedGraphic(const BatchedVertexArray &newVertices,
		                          TexturePointer newTexture = TexturePointer()) : Colorable(),
			Shapable<BatchedVertexArray>(newVertices), T(newTexture) {
		}

		BatchedGraphic(const BatchedGraphic<T> &src) : Colorable(src),
		    Shapable<BatchedVertexArray>(src), T(src) {
		}

		virtual ~BatchedGraphic() {
		}

		BatchedGraphic &operator=(const BatchedGraphic<T> &src) {
			this->Colorable::operator=(src);
			this->Shapable<BatchedVertexArray>::operator=(src);
			this->T::operator=(src);

			return *this;
		}

		/**
		 * Sets the body's color.
		 * @param newColor New color.
		 * @see RedBox::Colorable::color
		 */
		void setColor(const Color &newColor) {
			this->Colorable::setColor(newColor);
		}

	private:
		/// We make sure the Graphic is derived from a texture mappable type.
		typedef typename StaticAssert<IsBaseOf<TextureMappable, T>::RESULT>::Result IsTextureMappable;

		/**
		 * Refreshes the graphic's texture coordinates in its parent batch.
		 */
		void refreshTextureCoordinates() {
		}
	};

}

#endif // RB_BATCHED_GRAPHIC_H
