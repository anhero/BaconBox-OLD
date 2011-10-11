/**
 * @file
 * @ingroup Display
 */
#ifndef RB_GRAPHIC_H
#define RB_GRAPHIC_H

#include "TextureMappable.h"
#include "StaticAssert.h"
#include "IsBaseOf.h"
#include "Maskable.h"
#include "Shapable.h"
#include "Colorable.h"
#include "StandardVerticesArray.h"
#include "GraphicDriver.h"
#include "FlagSet.h"
#include "RenderMode.h"
#include "TexturePointer.h"

namespace RedBox {
	/**
	 * All graphics that are not batched are derived from this class, whether
	 * they are animated or not.
	 * @tparam T Type specification to specify if the graphic can be aninated or
	 * not.
	 * @ingroup Display
	 */
	template <typename T>
	class Graphic : virtual public Maskable, public Colorable,
		public Shapable<StandardVerticesArray>, public T {
	public:
		/**
		 * Default constructor.
		 */
		Graphic() : Maskable(), Colorable(), Shapable<StandardVerticesArray>(),
			T(), renderModes(), currentMask(NULL) {
		}

		/**
		 * Simple parameterized constructor. Only sets the texture information.
		 * Does not load any texture coordinates.
		 * @param newTexture Texture pointer to use as the texture.
		 * @see RedBox::Texturable::textureInformation
		 */
		explicit Graphic(TexturePointer newTexture) : Maskable(),
			Colorable(), Shapable<StandardVerticesArray>(), T(newTexture),
			renderModes(), currentMask(NULL) {
		}

		/**
		 * Copy constructor.
		 * @param src Graphic to make a copy of.
		 */
		Graphic(const Graphic<T> &src) : Maskable(src), Colorable(src),
		    Shapable<StandardVerticesArray>(src), T(src),
		    renderModes(src.renderModes), currentMask(src.currentMask) {
		}

		/**
		 * Destructor.
		 */
		virtual ~Graphic() {
		}

		/**
		 * Assignment operator.
		 * @param src Graphic to make a copy of.
		 * @return Reference to the modified Graphic.
		 */
		Graphic &operator=(const Graphic<T> &src) {
			this->Colorable::operator=(src);
			this->Shapable<StandardVerticesArray>::operator=(src);
			this->T::operator=(src);

			if (this != &src) {
				currentMask = src.currentMask;
				renderModes = src.renderModes;
			}

			return *this;
		}

		/**
		 * Renders the body in the context.
		 */
		void render() {
			// We make sure there are vertices to render.
			if (!this->getVertices().isEmpty()) {

				// We check which graphic driver method to use.
				if (renderModes.isSet(RenderMode::SHAPE)) {
					// We check if we have a texture to render.
					if (renderModes.isSet(RenderMode::TEXTURE)) {
						// We check if we are rendering a mask.
						if (renderModes.isSet(RenderMode::MASKED) ||
						    renderModes.isSet(RenderMode::INVERSE_MASKED)) {
							Maskable *tmpMask = this->getMask();

							// We make sure the mask is valid.
							if (tmpMask) {
								tmpMask->mask();
								// Masked with texture.
								GraphicDriver::getInstance().drawMaskedShapeWithTextureAndColor(this->getVertices(),
								                                                                this->getTextureInformation(),
								                                                                this->getCurrentTextureCoordinates(),
								                                                                this->getColor(),
								                                                                renderModes.isSet(RenderMode::INVERSE_MASKED));
								tmpMask->unmask();
							}

						} else {
							// We render with the texture.
							GraphicDriver::getInstance().drawShapeWithTextureAndColor(this->getVertices(),
							                                                          this->getTextureInformation(),
							                                                          this->getCurrentTextureCoordinates(),
							                                                          this->getColor());
						}

					} else if (renderModes.isSet(RenderMode::COLOR)) {
						// We render with the color only.
						GraphicDriver::getInstance().drawShapeWithColor(this->getVertices(), this->getColor());

					}
				}
			}
		}

		/**
		 * Similar to the render function except that it will only
		 * render to the alpha component of the color buffer. It is used to mask
		 * the next rendered renderable body (if the next renderable body is set
		 * as a masked renderable body).
		 */
		void mask() {
			if (!this->getVertices().isEmpty()) {
				GraphicDriver::getInstance().drawMaskShapeWithTextureAndColor(this->getVertices(),
				                                                              this->getTextureInformation(),
				                                                              this->getCurrentTextureCoordinates(),
				                                                              this->getColor());
			}
		}

		/**
		 * Undo what the mask function did. This function must be once after the
		 * masked renderable body has been rendered.
		 */
		void unmask() {
			if (!this->getVertices().isEmpty()) {
				GraphicDriver::getInstance().unmaskShape(this->getVertices());
			}
		}

		/**
		 * Gets the renderable body masking the current renderable body.
		 * @return Pointer to the renderable body's mask.
		 */
		Maskable *getMask() const {
			return currentMask;
		}

		/**
		 * Sets the renderable body used to mask the parent renderstep.
		 * @param newMask A mask body.
		 * @param inverted Sets this parameter to true if you want to invert
		 * the effect of the mask. False by default.
		 */
		void setMask(Maskable *newMask, bool inverted = false) {
			currentMask = newMask;

			// If the new mask is valid.
			if (currentMask) {
				// We set the flags correctly depending on the "inverted"
				// parameter.
				renderModes.set(RenderMode::INVERSE_MASKED, inverted);
				renderModes.set(RenderMode::MASKED, !inverted);

			} else {
				// If we removed the graphic's mask, we reset the flags.
				renderModes.set(RenderMode::INVERSE_MASKED, false);
				renderModes.set(RenderMode::MASKED, false);
			}
		}

		/**
		 * Gets the rendering modes.
		 * @return Current rendering modes.
		 */
		const FlagSet<RenderMode>& getRenderModes() const {
			return renderModes;
		}

		/**
		 * Sets the rendering modes. Replaces the current rendering modes with
		 * the ones given.
		 * @param newRenderModes New mode to be set.
		 */
		void setRenderModes(const FlagSet<RenderMode> &newRenderModes) {
			renderModes = newRenderModes;
		}

		/**
		 * Adds modes with the bitwise inclusive OR. More than one mode can
		 * be added at the same time.
		 * @param newRenderModes New modes to add.
		 */
		void addRenderModes(const FlagSet<RenderMode> &newRenderModes) {
			renderModes |= newRenderModes;
		}

		/**
		 * Adds a mode with the bitwise inclusive OR. More than one mode can
		 * be added at the same time using the same operator.
		 * @param newRenderMode New render mode to add.
		 */
		void addRenderMode(RenderMode newRenderMode) {
			renderModes.set(newRenderMode);
		}

		/**
		 * Flip off given mode flags.
		 * @param renderModesToRemove Render mode(s) flags to flip off.
		 */
		void removeRenderModes(const FlagSet<RenderMode>& renderModesToRemove) {
			renderModes.reset(renderModesToRemove);
		}

		/**
		 * Flip off given mode flag.
		 * @param renderModeToRemove Mode to flip off.
		 */
		void removeRenderMode(RenderMode renderModeToRemove) {
			renderModes.reset(renderModeToRemove);
		}

	private:
		/// We make sure the Graphic is derived from a texture mappable type.
		typedef typename StaticAssert<IsBaseOf<TextureMappable, T>::RESULT>::Result IsTextureMappable;

		/// Flag set of render modes.
		FlagSet<RenderMode> renderModes;

		/**
		 * Pointer to the current mask used to mask the graphic. Contains NULL
		 * no mask is selected.
		 */
		Maskable *currentMask;
	};
}

#endif
