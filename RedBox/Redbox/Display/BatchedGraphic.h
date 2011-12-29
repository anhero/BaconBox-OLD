/**
 * @file
 * @ingroup Display
 */
#ifndef RB_BATCHED_GRAPHIC_H
#define RB_BATCHED_GRAPHIC_H

#include <algorithm>

#include "TextureMappable.h"
#include "StaticAssert.h"
#include "IsBaseOf.h"
#include "Maskable.h"
#include "Shapable.h"
#include "Colorable.h"
#include "BatchedVertexArray.h"
#include "TexturePointer.h"

namespace RedBox {
	/**
	 * Represents a batched graphic.
	 * @tparam T Animatable or Inanimate.
	 * @tparam U BatchedSprite or BatchedInanimateSprite.
	 */
	template <typename T, typename U>
	class BatchedGraphic : public Colorable,
		public Shapable<BatchedVertexArray<U> >, public T {
		template <typename V> friend class RenderBatchParent;
		template <typename V, bool ANIMATABLE> friend class RenderBatchMiddle;
	public:
		/**
		 * Default constructor.
		 */
		BatchedGraphic() : Colorable(), Shapable<BatchedVertexArray<U> >(),
			T() {
		}

		/**
		 * Parameterized constructor.
		 */
		explicit BatchedGraphic(TexturePointer newTexture) : Colorable(),
			Shapable<BatchedVertexArray<U> >(), T(newTexture) {
		}

		/**
		 * Copy contstructor.
		 * @param src Batched graphic to make a copy of.
		 */
		BatchedGraphic(const BatchedGraphic<T, U> &src) : Colorable(src),
			Shapable<BatchedVertexArray<U> >(src), T(src) {
			this->setColor(src.getColor());
			this->refreshTextureCoordinates();
		}

		/**
		 * Destructor.
		 */
		virtual ~BatchedGraphic() {
		}

		/**
		 * Assignation operator overload.
		 * @param src Batched graphic to make a copy of.
		 * @return Batched graphic resulting of the copy.
		 */
		BatchedGraphic &operator=(const BatchedGraphic<T, U> &src) {
			this->Colorable::operator=(src);
			this->Shapable<BatchedVertexArray<U> >::operator=(src);
			this->T::operator=(src);

			return *this;
		}

		/**
		 * Sets the body's color.
		 * @param newColor New color.
		 * @see RedBox::Colorable::color
		 */
		virtual void setColor(const Color &newColor) {
			this->Colorable::setColor(newColor);

			// We update the colors in the batch.
			if (this->getVertices().batch && !this->getVertices().vertices) {
				std::fill_n(this->getVertices().batch->colors.begin() + this->getVertices().begin, this->getVertices().getNbVertices(), newColor);
			}
		}

		/**
		 * Refreshes the graphic's texture coordinates in its parent batch.
		 */
		void refreshTextureCoordinates() {
			// We update the texture coordinates in the batch.
			if (this->getVertices().batch && !this->getVertices().vertices) {
				std::copy(this->getCurrentTextureCoordinates().begin(),
				          this->getCurrentTextureCoordinates().end(),
				          this->getVertices().batch->textureCoordinates.begin() + this->getVertices().begin);
			}
		}

		/**
		 * Clones the current batched graphic.
		 * @return Pointer to the new allocated batched graphic.
		 */
		virtual BatchedGraphic<T, U> *clone() const {
			return new BatchedGraphic<T, U>(*this);
		}
	protected:
		/**
		 * Parameterized constructor.
		 * @param newBatch Pointer to the parent batch.
		 * @param newVertices Pointer to the array of vertices to use. The
		 * graphic's vertex array will manage this pointer.
		 */
		BatchedGraphic(RenderBatch<U> *newBatch,
					   typename BatchedVertexArray<U>::ContainerType *newVertices,
					   const BatchedGraphic<T, U> &src) :
			Colorable(src), Shapable<BatchedVertexArray<U> >(), T(src) {
			this->getVertices().batch = newBatch;
			this->getVertices().vertices = newVertices;

			std::copy(src.getVertices().getBegin(), src.getVertices().getEnd(),
					  this->getVertices().getBegin());

			this->setColor(src.getColor());
			this->refreshTextureCoordinates();
		}

		/**
		 * Parameterized constructor.
		 * @param newBatch Pointer to the parent batch.
		 * @param newBegin Index at which the graphic's vertices begin in the
		 * parent batch.
		 * @param newNbVertices Number of vertices the graphic contains.
		 */
		BatchedGraphic(RenderBatch<U> *newBatch,
		               typename BatchedVertexArray<U>::SizeType newBegin,
					   typename BatchedVertexArray<U>::SizeType newNbVertices,
					   const BatchedGraphic<T, U> &src) :
			Colorable(src), Shapable<BatchedVertexArray<U> >(), T(src) {
			this->getVertices().batch = newBatch;
			this->getVertices().nbVertices = newNbVertices;
			this->getVertices().begin = newBegin;

			std::copy(src.getVertices().getBegin(), src.getVertices().getEnd(),
					  this->getVertices().getBegin());

			this->setColor(src.getColor());
			this->refreshTextureCoordinates();
		}
	private:
		/// We make sure the Graphic is derived from a texture mappable type.
		typedef typename StaticAssert<IsBaseOf<TextureMappable, T>::RESULT>::Result IsTextureMappable;

		/**
		 * Method called internally when the current frame is changed.
		 */
		void currentFrameChange() {
			refreshTextureCoordinates();
		}
	};

}

#endif // RB_BATCHED_GRAPHIC_H
