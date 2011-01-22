/**
 * @file
 * @ingroup Display
 */

#ifndef __RENDER_STEP_H
#define __RENDER_STEP_H

#include <vector>

#include "Vertex.h"
#include "RenderInfo.h"
#include "RenderStepMode.h"
#include "OpenGLDrawer.h"

namespace RedBox {
    /**
     * Definition of a specific render step.
     * @ingroup Display
     */
    class RenderStep {
    private:
        /// Information on the render. Includes the color and the texture ID.
        RenderInfo info;
        /**
         * Render mode to be used for this rendering step. Modes can be
         * combined with the bitwise inclusive OR.
         */
        RenderStepMode mode;
        /// Vertices to be rendered in this step.
        std::vector<Vertex*> vertices;
        /**
         * Makes the instance a copy of the recieved RenderStep.
         * @param src RenderStep to make a copy of.
         */
        void copyFrom(const RenderStep& src);
    public:
        /**
         * Default constructor. Constructs an empty RenderStep.
         */
        RenderStep();
        /**
         * Copy constructor. Constructs a copy of the recieved RenderStep.
         * @param src RenderStep to make a copy of.
         */
        RenderStep(const RenderStep& src);
        /**
         * Empty destructor.
         */
        ~RenderStep();
        /**
         * Assignation operator overload. Makes the instance a copy of the
         * recieved RenderStep.
         * @param src RenderStep to make a copy of.
         * @return Current instance for assignation chaining.
         */
        RenderStep& operator=(const RenderStep& src);
        /**
         * Renders the vertices using the info and the mode known.
         */
        void render();
        /**
         * Accessor for the rendering information.
         * @return Information about the rendering.
         */
        RenderInfo& getRenderInfo();
        /**
         * Changes the rendering information.
         * @param newRenderInfo New rendering information to overwrite the
         * current one.
         */
        void setRenderInfo(const RenderInfo& newRenderInfo);
        /**
         * Gets the rendering mode.
         * @return Current rendering mode.
         */
        RenderStepMode getMode() const;
        /**
         * Sets the rendering mode.
         * @param newMode New mode to be set.
         */
        void setMode(RenderStepMode newMode);
        /**
         * Adds a mode with the bitwise inclusive OR. More than one mode can
         * be added at the same time using the same operator.
         * @param New mode to add.
         */
        void addMode(RenerStepMode newMode);
    };
}

#endif