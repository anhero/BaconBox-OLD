/**
 * @file
 * @ingroup Display
 */

#ifndef __RENDER_INFO_H
#define __RENDER_INFO_H

namespace RedBox {
    /**
     * Struct contaning rendering information.
     * @ingroup Display
     */
    struct RenderInfo {
        /**
         * Color, first int is red, second is green, third is blue and last one
         * is alpha.
         */
        int color[4];
        /// Texture ID used for OpenGL
        int textureID;
        /**
         * Default constructor.
         */
        RenderInfo(): textureID(0) {
            color[0] = 0;
            color[1] = 0;
            color[2] = 0;
            color[3] = 0;
        }
        /**
         * Parametrized constructor.
         * @param newTextureID RenderInfo's texture ID to set.
         * @param newColor Array to use to set the RenderInfo's color.
         */
        RenderInfo(int newTextureID, int* newColor) {
            textureID = newTextureID;
            if(newColor) {
                color[0] = newColor[0];
                color[1] = newColor[1];
                color[2] = newColor[2];
                color[3] = newColor[3];
            }
        }
    };
}

#endif