/**
 * @file
 * @ingroup Display
 */
#ifndef RB_RENDERABLE_INTERFACE_H
#define RB_RENDERABLE_INTERFACE_H

namespace BaconBox {
	/**
	 * Interface for all renderable bodies.
	 * @ingroup Display
	 */
	class Renderable {
	public:
		/**
		 * Destructor.
		 */
		virtual ~Renderable();

		/**
		 * Renders the body in the context.
		 */
		virtual void render() = 0;
	};
}

#endif
