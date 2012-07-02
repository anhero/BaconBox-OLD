/**
 * @file
 * @ingroup Display
 */
#ifndef RB_MASKABLE_H
#define RB_MASKABLE_H

#include "BaconBox/Display/Renderable.h"

namespace BaconBox {
	class Maskable : public Renderable {
	public:
		/**
		 * Destructor.
		 */
		virtual ~Maskable();

		/**
		 * Similar to the render function except that it will only
		 * render to the alpha component of the color buffer. It is used to mask
		 * the next rendered renderable body (if the next renderable body is set
		 * as a masked renderable body).
		 */
		virtual void mask() = 0;

		/**
		 * Undo what the mask function did. This function must be once after the
		 * masked renderable body has been rendered.
		 */
		virtual void unmask() = 0;

		/**
		 * Gets the renderable body masking the current renderable body.
		 * @return Pointer to the renderable body's mask.
		 */
		virtual Maskable *getMask() const = 0;

		/**
		 * Sets the renderable body used to mask the parent renderstep.
		 * @param newMask A mask sprite.
		 * @param inverted Sets this parameter to true if you want to invert
		 * the effect of the mask. False by default.
		 */
		virtual void setMask(Maskable *newMask, bool inverted = false) = 0;
	};

}

#endif
