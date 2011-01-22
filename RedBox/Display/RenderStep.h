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

namespace RedBox {
    /**
     * Definition of a specific render step.
     * @ingroup Display
     */
    class RenderStep {
    private:
        /// Information on the render.
        RenderInfo info;
        /// Render mode to be used for this rendering step.
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
    };
}

#endif