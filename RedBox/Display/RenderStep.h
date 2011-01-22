/**
 * @file
 * @ingroup Display
 */

#ifndef __RENDER_STEP_H
#define __RENDER_STEP_H

#include <vector>

#include "Renderable.h"
#include "VerticesGroup.h"
#include "RenderInfo.h"
#include "RenderStepMode.h"
#include "OpenGLDrawer.h"

namespace RedBox {
    /**
     * Definition of a specific render step.
     * @ingroup Display
     */
    class RenderStep : public Renderable {
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
        virtual ~RenderStep();
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
        /**
         * Checks if the RenderStep needs to delete its vertices in its
         * destructor.
         * @return True if it needs to delete, false if not.
         */
        bool isDeleteVerticesGroup() const;
        /**
         * Sets if the RenderStep needs to delete its vertices in its
         * destructor.
         * @param newDeleteVerticesGroup New boolean value.
         */
        void setDeleteVerticesGroup(bool newDeleteVerticesGroup);
        /**
         * Gets a pointer to the instance's vertices group.
         * @return Pointer to the vertices group.
         */
        VerticesGroup* getVerticesGroup();
        /**
         * Sets the pointer to the instance's vertices group.
         * @param newVertices Pointer to the new vertices group.
         */
        void setVerticesGroup(VerticesGroup* newVertices);
    private:
        /// Information on the render. Includes the color and the texture ID.
        RenderInfo info;
        /**
         * Render mode to be used for this rendering step. Modes can be
         * combined with the bitwise inclusive OR.
         */
        RenderStepMode mode;
        /// Vertices to be rendered in this step.
        VerticesGroup* vertices;
        /**
         * Determines if the RenderStep needs to delete its vertices in its
         * destructor.
         */
        bool deleteVerticesGroup;
        /**
         * Resets the RenderStep. Also frees up all allocated memory.
         */
        void clean();
        /**
         * Makes the instance a copy of the recieved RenderStep.
         * @param src RenderStep to make a copy of.
         */
        void copyFrom(const RenderStep& src);
    };
}

#endif