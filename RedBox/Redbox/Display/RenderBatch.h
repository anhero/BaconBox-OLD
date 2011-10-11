#if 0
/**
 * @file
 * @ingroup Display
 */
#ifndef RB_RENDERBATCH_H
#define RB_RENDERBATCH_H

#include <vector>

#include "Sprite.h"
#include "GraphicBody.h"
#include "TextureInformation.h"

namespace RedBox {
	/**
	 * @ingroup Display
	 */
	class RenderBatch : public GraphicBody {
	public:
		RenderBatch();
		virtual ~RenderBatch();

		/**
		 *  Reconstruct the internal batch arrays from the sprites in the batch.
		 */
		void reconstruct();

		/**
		 * Updates the sprites in the batch.
		 */
		virtual void update();
		/**
		 * Renders the batch.
		 */
		virtual void render();

		/**
		 * Similar to the render function except that it will only
		 * render to the alpha component of the color buffer. It is
		 * used to mask the next rendered sprite (if the next sprite
		 * is set as a masked sprite).
		 */
		virtual void mask();

		/**
		 * Undo what the mask function did. This function
		 * MUST be once after the masked sprite has been rendered.
		 */
		virtual void unmask();

		/**
		 * Set the sprite used to mask the parent renderstep.
		 * @param newMask A mask sprite.
		 * @param inversed Set this parameter to true if you want to inverse
		 * the effect of the mask. False by default.
		 */
		virtual void setMask(GraphicBody *newMask, bool inversed = false);


		virtual float getWidth() const;
		virtual float getHeight() const;
		/**
		 * Gets the graphic body masking the current graphic body.
		 * @return Pointer to the graphic body's mask.
		 */
		virtual GraphicBody *getMask();

		virtual GraphicBody *clone() const;


		/**
		 * Add a sprite in the batch.
		 * All the sprites must use the same texture (or no texture if they
		 * don't use textures.
		 */
		void addSprite(Sprite *aSprite);

		/**
		 * Remove the given sprite from the batch
		 */
		void removeSprite(Sprite *aSprite);
	private:

		///Batch of sprite
		std::set<Sprite *> sprites;

		///Batch array of texture coordinate
		Vector2 *textureCoord;
		///Batch array of vertices
		Vector2 *vertices;

		///Batch array of colors
		unsigned char *colors;

		std::vector<unsigned short> indices;

		///Number of vertices in the batch
		unsigned int verticesCount;

		///Number of sprites in the batch
		unsigned int spritesCount;

		FlagSet<RenderMode> renderModes;

		/**
		 * Pointer to a mask sprite. Pointer is NULL if the parent render step
		 * is not masked.
		 */
		GraphicBody *maskBody;

		///Number of color channel in the texture
		unsigned int colorChannelCount;

		TextureInformation textureInfo;
	};
}

#endif
#endif
