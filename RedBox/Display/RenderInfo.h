/**
 * @file
 * @ingroup Display
 */
#ifndef RB_RENDER_INFO_H
#define RB_RENDER_INFO_H

#include <vector>

namespace RedBox {
    /**
     * Struct contaning rendering information.
     * @ingroup Display
     */
    struct RenderInfo {
        /**
         * Default constructor.
         */
        RenderInfo();
        /**
         * Parametrized constructor.
         * @param newTextureID RenderInfo's texture ID to set.
         * @param newColor Array to use to set the RenderInfo's color.
         */
        RenderInfo(int newTextureID, int* newColor);
        /**
         * Color, first int is red, second is green, third is blue and last one
         * is alpha.
         */
        int color[4];
        /// Texture ID used for OpenGL
        int textureID;
		/// Vector containing the texture's coordinates.
		std::vector<float> texCoords;
    };
}

#endif