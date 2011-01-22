/**
 * @file
 * @ingroup Drawer
 */


#ifndef DRAWER
#define DRAWER

#include "PlatformFlager.h"

namespace RedBox{
    /**
     * @class Drawer
     * @ingroup Drawer
     *  Graphic abstraction layer
     */
        class Drawer {
        private:
        public:
        /**
         * Draw a colored and textured shape
         * with the given vertices, texture coordinate, rendering informations (colors array and textureID) and
         * number of vertices
         * color information will blend with the textured (and background if alpha is not at max value of 255)
         *
         * @param vertices Array of vertex to draw, must have this form (X1, Y1, X2, Y2, Xn, Yn).
         * The order must be clock wise
         * @param textCoordArray Array of texture coordinate, every value must be in the range 0 to 1.
         * @param renderingInfo object of type RenderInfo, containing colors array and textureID
         * @param nbVertices number equal to the number of vertices to draw
         */
                static void drawShapeWithTextureAndColor(float * vertices, Float * textCoordArray, RenderInfo * renderingInfo, int nbVertices);

        /**
         * Draw a textured shape
         * with the given vertices, texture coordinate, rendering informations (colors array and textureID) and
         * number of vertices
         *
         * @param vertices Array of vertex to draw, must have this form (X1, Y1, X2, Y2, Xn, Yn).
         * The order must be clock wise
         * @param textCoordArray Array of texture coordinate, every value must be in the range 0 to 1.
         * @param renderingInfo object of type RenderInfo, containing colors array and textureID
         * @param nbVertices number equal to the number of vertices to draw
         */
                static void drawShapeWithTexture(float * vertices,float * textCoordArray, RenderInfo * renderingInfo, int nbVertices);

        };

}

#endif

/** @} */
