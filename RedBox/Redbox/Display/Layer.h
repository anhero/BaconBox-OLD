/**
 * @file
 * @ingroup Display
 */
#ifndef RB_LAYER_H
#define RB_LAYER_H

#include "Object.h"
#include "Vector2.h"

namespace RedBox {
	/**
	 * Represents a layer in a State. A layer has a z coordinate and a scroll
	 * factor that is used for parallax scrolling.
	 * @ingroup Display
	 */
	class Layer : public Object {
	public:
		/**
		 * Custom compare class for the graphic body multimap in the state.
		 */
		class LessCompare {
		public:
			/**
			 * Compares which layer is closer to the camera. It first compares
			 * the z coordinate. If they are the same, it compares their
			 * scrolling factor. A lower z means its closer to the camera and
			 * a higher scrolling factor means it's closer to the camera on
			 * that specific z coordinate.
			 * @param l1 First layer to compare.
			 * @param l2 Second layer to compare.
			 * @return True if the first layer is closer to the camera than the
			 * second.
			 */
			bool operator() (const Layer& l1, const Layer& l2);
		};

		/**
		 * Default constructor. The z coordinate is set at 0 and the scroll
		 * factor is set at 1.0f.
		 */
		Layer();

		/**
		 * Parameterized constructor.
		 * @param newZ Starting z value for the layer.
		 * @param newScrollFactor Starting scroll factor for the layer.
		 * @see RedBox::Layer::z
		 * @see RedBox::Layer::scrollFactor
		 */
		Layer(int newZ, const Vector2& newScrollFactor);

		/**
		 * Copy constructor.
		 * @param src Layer to make a copy of.
		 */
		Layer(const Layer& src);

		/**
		 * Assignation operator overload.
		 * @param src Layer to make a copy of.
		 * @return Reference to the modified Layer.
		 */
		Layer& operator=(const Layer& src);

		/**
		 * Comparison operator definition.
		 * @param other Layer to compare with.
		 * @return True if the layers have the same z and scroll factor, false
		 * if not.
		 */
		bool operator==(const Layer& other);

		/**
		 * Comparison operator definition. Opposite result than operator==()
		 * @param other Layer to compare with.
		 * @return True if the layers have a different z or scroll factor, false
		 * if not.
		 * @see RedBox::Layer::operator==(const Layer& other)
		 */
		bool operator!=(const Layer& other);

		/**
		 * Gets the layer's z coordinate.
		 * @return Z coordinate. The higher the value the closer the layer will
		 * be.
		 * @see RedBox::Layer::z
		 */
		int getZ() const;

		/**
		 * Sets the graphic body's coordinate.
		 * @param newZ New z coordinate. The higher the value closer the graphic
		 * body will be.
		 * @see RedBox::Layer::z
		 */
		void setZ(int newZ);

		/**
		 * Gets the layer's scroll factor.
		 * @return Horizontal and vertical scroll factor. A value higher than 1
		 * means the layer will move faster as if it were closer to the camera,
		 * between 1 and 0 means it will move as if it were far from the camera.
		 */
		const Vector2& getScrollFactor() const;

		/**
		 * Sets the layer's scroll factor.
		 * @param newScrollFactor New horizontal and vertical scroll factor. A
		 * value higher than 1 means the layer will move faster as if it were
		 * closer to the camera and between 1 and 0 means it will move as
		 * if it were far from the camera.
		 * @see RedBox::Layer::scrollFactor
		 */
		void setScrollFactor(const Vector2& newScrollFactor);

		/**
		 * Sets the layer's scroll factor.
		 * @param newXScrollFactor New horizontal scroll factor. A value higher
		 * than 1 means the layer will move faster as if it were closer to the
		 * camera and between 1 and 0 means it will move as if it were far from
		 * the camera.
		 * @param newYScrollFactor New vertical scroll factor. A value higher
		 * than 1 means the layer will move faster as if it were closer to the
		 * camera and between 1 and 0 means it will move as if it were far from
		 * the camera.
		 * @see RedBox::Layer::scrollFactor
		 */
		void setScrollFactor(float newXScrollFactor, float newYScrollFactor);

		/**
		 * Gets the layer's horizontal scroll factor.
		 * @return Horizontal scroll factor. A value higher than 1 means the
		 * layer will move faster as if it were closer to the camera, between 1
		 * and 0 means it will move as if it were far from the camera.
		 * @see RedBox::Layer::scrollFactor
		 */
		float getXScrollFactor() const;

		/**
		 * Sets the layer's horizontal scroll factor.
		 * @param newXScrollFactor New horizontal scroll factor. A value higher
		 * than 1 means the layer will move faster as if it were closer to the
		 * camera and between 1 and 0 means it will move as if it were far from
		 * the camera.
		 * @see RedBox::Layer::scrollFactor
		 */
		void setXScrollFactor(float newXScrollFactor);

		/**
		 * Gets the layer's vertical scroll factor.
		 * @return Vertical scroll factor. A value higher than 1 means the
		 * layer will move faster as if it were closer to the camera, between 1
		 * and 0 means it will move as if it were far from the camera.
		 * @see RedBox::Layer::scrollFactor
		 */
		float getYScrollFactor() const;

		/**
		 * Sets the layer's vertical scroll factor.
		 * @param newYScrollFactor New vertical scroll factor. A value higher
		 * than 1 means the layer will move faster as if it were closer to the
		 * camera and between 1 and 0 means it will move as if it were far from
		 * the camera.
		 * @see RedBox::Layer::scrollFactor
		 */
		void setYScrollFactor(float newYScrollFactor);

	private:
		/// Z coordinate. Lower value means more to the front of the camera.
		int z;

		/**
		 * Scroll factor. Factor applied to the bodies' coordinates to have
		 * parallax scrolling. Lower values means "farther" from the camera. An
		 * horizontal scroll factor of 0 would mean the body would not move
		 * horizontally whatever the camera does. A value higher than 1 means
		 * the layer will move faster as if it were closer to the camera and
		 * between 1 and 0 means it will move as if it were far from the camera.
		 * By default, all bodies have a scroll factor of 1 both horizontally
		 * and vertically.
		 */
		Vector2 scrollFactor;
	};
}

#endif
