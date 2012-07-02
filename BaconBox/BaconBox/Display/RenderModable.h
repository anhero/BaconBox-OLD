/**
 * @file
 * @ingroup Display
 */
#ifndef RB_RENDER_MODABLE_H
#define RB_RENDER_MODABLE_H

#include "BaconBox/Display/RenderMode.h"
#include "BaconBox/Helper/FlagSet.h"

namespace BaconBox {
	class RenderModable {
	public:
		/**
		 * Default constructor.
		 */
		RenderModable();

		/**
		 * Parameterized constructor.
		 * @param newRenderModes Initial render modes.
		 * @see BaconBox::RenderModable::renderModes
		 */
		explicit RenderModable(const FlagSet<RenderMode> &newRenderModes);

		/**
		 * Copy constructor.
		 * @param src RenderModable to make a copy of.
		 */
		RenderModable(const RenderModable &src);

		/**
		 * Destructor.
		 */
		virtual ~RenderModable();

		/**
		 * Assignment operator.
		 * @param src RenderModable to make a copy of.
		 * @return Reference to the modified RenderModable.
		 */
		RenderModable &operator=(const RenderModable &src);

		/**
		 * Gets the rendering modes.
		 * @return Current rendering modes.
		 */
		const FlagSet<RenderMode>& getRenderModes() const;

		/**
		 * Sets the rendering modes. Replaces the current rendering modes with
		 * the ones given.
		 * @param newRenderModes New mode to be set.
		 */
		void setRenderModes(const FlagSet<RenderMode> &newRenderModes);

		/**
		 * Adds modes with the bitwise inclusive OR. More than one mode can
		 * be added at the same time.
		 * @param newRenderModes New modes to add.
		 */
		void addRenderModes(const FlagSet<RenderMode> &newRenderModes);

		/**
		 * Adds a mode with the bitwise inclusive OR. More than one mode can
		 * be added at the same time using the same operator.
		 * @param newRenderMode New render mode to add.
		 */
		void addRenderMode(RenderMode newRenderMode);

		/**
		 * Flip off given mode flags.
		 * @param renderModesToRemove Render mode(s) flags to flip off.
		 */
		void removeRenderModes(const FlagSet<RenderMode>& renderModesToRemove);

		/**
		 * Flip off given mode flag.
		 * @param renderModeToRemove Mode to flip off.
		 */
		void removeRenderMode(RenderMode renderModeToRemove);
	protected:
		/// Flag set of render modes.
		FlagSet<RenderMode> renderModes;
	};

}

#endif // RB_RENDER_MODABLE_H
