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
		 * @param newTexInfo Pointer to the texture information needed to
		 * initialize the render step.
		 * @param newVertices Pointer to the vertices of the shape to take from
		 * the image.
		 * @param nbFrames Number of frames of texture coordinates to generate.
		 * @param factor Size factor between the shape and hte size of the
		 * texxture coordinates to take.
		 * @param offsetX Horizontal offset from where the texture coordinates
		 * will start loading.
		 * @param offsetY Vertical offset from where the texture coordinates
		 * will start loading.
         * @param newColor Array to use to set the RenderInfo's color.
		 * @param newDeleteVerticesGroup True if the RenderStep needs to delete
		 * the vertices when destroyed. False if not. Sprites loading their
		 * render steps will put this parameter to false.
		 */
		RenderStep(TextureInfo* newTexInfo,
				   VerticesGroup* newVertices,
				   unsigned int nbFrames = 1,
				   float factor = 1.0f,
				   float offsetX = 0.0f,
				   float offsetY = 0.0f,
				   int* newColor = NULL,
				   bool newDeleteVerticesGroup = false);
		/**
		 * Parameterized constructor.
		 * @param key Name of the image to get from the resource loader.
		 * @param newVertices Pointer to the vertices of the shape to take from
		 * the image.
		 * @param nbFrames Number of frames of texture coordinates to generate.
		 * @param factor Size factor between the shape and hte size of the
		 * texxture coordinates to take.
		 * @param offsetX Horizontal offset from where the texture coordinates
		 * will start loading.
		 * @param offsetY Vertical offset from where the texture coordinates
		 * will start loading.
         * @param newColor Array to use to set the RenderInfo's color.
		 * @param newDeleteVerticesGroup True if the RenderStep needs to delete
		 * the vertices when destroyed. False if not. Sprites loading their
		 * render steps will put this parameter to false.
		 */
		RenderStep(const std::string& key,
				   VerticesGroup* newVertices,
				   unsigned int nbFrames = 1,
				   float factor = 1.0f,
				   float offsetX = 0.0f,
				   float offsetY = 0.0f,
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
		/**
		 * Gets if the RenderStep is using the epoch time or not for animations.
		 * @return True if the RenderStep uses epoch time, false if not.
		 */
		bool isUseSinceEpoch() const;
		/**
		 * Sets if the RenderStep uses the epoch time or not for animations.
		 * @param newUseSinceEpoch True if the RenderStep needs to use the
		 * epoch time, false if not.
		 */
		void setUseSinceEpoch(bool newUseSinceEpoch);
		/**
		 * Plays an animation.
		 * @param name Name of the animation to play.
		 */
		void playAnimation(const std::string& name);
		/**
		 * Pauses the animation.
		 */
		void pauseAnimation();
		/**
		 * Resumes the animation.
		 */
		void resumeAnimation();
		/**
		 * Gets the name of the current animation.
		 * @return Name of the current animation being played.
		 */
		const std::string& getCurrentAnimation() const;
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
		 * Wether to use the epoch time or not for animations. If it doesn't, it 
		 * uses the time since the game was started. Useful for RenderSteps with
		 * animations used for the pause menu. By default this member is set to
		 * false.
		 */
		bool useSinceEpoch;
        /**
         * Determines if the RenderStep needs to delete its vertices in its
         * destructor.
         */
        bool deleteVerticesGroup;
		/**
		 * Gets the time at which the last frame was changed for the animation.
		 */
		double lastFrameChange;
		/**
		 * Name of the animation currently playing.
		 */
		std::string currentAnimation;
		/**
		 * If the animation is paused or 
		 */
		bool isPaused;
		/// Time since the last frame when it was paused.
		double pauseFrameRemain;
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