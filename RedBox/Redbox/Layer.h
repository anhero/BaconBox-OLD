/**
 * @file
 */
#ifndef RB_LAYER_H
#define RB_LAYER_H

#include "Object.h"
#include "Vec2.h"

namespace RedBox {
	/**
	 * Represents a layer in a State. A layer has a z coordinate and a scroll
	 * factor that is used for parallax scrolling.
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
		 */
		Layer(int newZ, const Vec2& newScrollFactor);

		/**
		 * Copy constructor.
		 * @param src Layer to make a copy of.
		 */
		Layer(const Layer& src);

		/**
		 * Assignation operator overload.
		 * @param src Layer to make a copy of.
		 */
		Layer& operator=(const Layer& src);

		bool operator==(const Layer& other);
		bool operator!=(const Layer& other);

		/**
		 * Gets the layer's z coordinate.
		 */
		int getZ() const;

		/**
		 * Gets the layer's scroll factor.
		 */
		const Vec2& getScrollFactor() const;

		/**
		 * Sets the layer's z coordinate.
		 */
		void setZ(int newZ);

		/**
		 * Sets the layer's scroll factor.
		 */
		void setScrollFactor(const Vec2& newScrollFactor);
	private:
		/// Z coordinate. Lower value means more to the front of the camera.
		int z;
		/**
		 * Scroll factor. Factor applied to the bodies' coordinates to have
		 * parallax scrolling. Lower values means "farther" from the camera.
		 */
		Vec2 scrollFactor;
	};
}

#endif
