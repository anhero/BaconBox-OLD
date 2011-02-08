/**
 * @file
 * @ingroup Display
 */

#ifndef RB_RENDER_STEP_H
#define RB_RENDER_STEP_H

#include <vector>
#include <string>

#include "Renderable.h"
#include "VerticesGroup.h"
#include "RenderInfo.h"
#include "RenderStepMode.h"
#include "Drawer.h"
#include "TextureInfo.h"

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
         * Parameterized constructor.
         * @param newTexInfo Pointer to the information about the texture.
         * @param newColor Array to use to set the RenderInfo's color.
         */
        RenderStep(TextureInfo* newTexInfo, int* newColor = NULL);
		/**
		 * Parameterized constructor.
		 * @param newTexInfo Pointer to the texture information needed to
		 * initialize the render step.
		 * @param newVertices Pointer to the vertices of the shape to take from
		 * the image.
		 * @param newDeleteVerticesGroup True if the RenderStep needs to delete
		 * the vertices when destroyed. False if not. Sprites loading their
		 * render steps will put this parameter to false.
		 */
		RenderStep(TextureInfo* newTexInfo,
				   VerticesGroup* newVertices,
				   bool newDeleteVerticesGroup = false);
		/**
		 * Parameterized constructor.
		 * @param key Name of the image to get from the resource loader.
		 * @param newVertices Pointer to the vertices of the shape to take from
		 * the image.
		 * @param newDeleteVerticesGroup True if the RenderStep needs to delete
		 * the vertices when destroyed. False if not. Sprites loading their
		 * render steps will put this parameter to false.
		 */
		RenderStep(std::string key,
				   VerticesGroup* newVertices,
				   bool newDeleteVerticesGroup = false);
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
        virtual void render();
		/**
		 * Updates the the RenderStep.
		 */
		virtual void update();
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
        RenderStepMode::Enum getMode() const;
        /**
         * Sets the rendering mode.
         * @param newMode New mode to be set.
         */
        void setMode(RenderStepMode::Enum newMode);
        /**
         * Adds a mode with the bitwise inclusive OR. More than one mode can
         * be added at the same time using the same operator.
         * @param New mode to add.
         */
        void addMode(RenderStepMode::Enum newMode);
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
		RenderStepMode::Enum mode;
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

#include "Sprite.h"

#endif