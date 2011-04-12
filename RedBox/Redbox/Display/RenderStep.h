/**
 * @file
 * @ingroup Display
 */

#ifndef RB_RENDER_STEP_H
#define RB_RENDER_STEP_H

#include <vector>
#include <list>
#include <string>
#include <cstdarg>

#include "TextureInfo.h"
#include "RenderInfo.h"
#include "Renderable.h"
#include "RenderStepMode.h"

namespace RedBox {
	class VerticesGroup;
	class Vertex;
    /**
     * Definition of a specific render step.
     * @ingroup Display
     */
    class RenderStep : public Renderable {
        /**
         * Outputs the RenderStep's content.
         * @param output The ostream in which RenderStep is output.
         * @param r RenderStep to output in the ostream.
         * @return Resulting ostream.
         */
		friend std::ostream& operator<<(std::ostream& output,
										const RenderStep& r);
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
		 * @param frameWidth Width of the frames to read from the image (in 
		 * pixels).
		 * @param frameHeight Height of the frames to read from the image (in
		 * pixels).
		 * @param nbFrames Number of frames of texture coordinates to generate.
		 * will start loading.
         * @param newColor Array to use to set the RenderInfo's color.
		 * @param newDeleteVerticesGroup True if the RenderStep needs to delete
		 * the vertices when destroyed. False if not. Sprites loading their
		 * render steps will put this parameter to false.
		 */
		RenderStep(TextureInfo* newTexInfo,
				   VerticesGroup* newVertices,
				   unsigned int frameWidth,
				   unsigned int frameHeight,
				   unsigned int nbFrames = 1,
				   int* newColor = NULL,
				   bool newDeleteVerticesGroup = false);
		/**
		 * Parameterized constructor.
		 * @param key Name of the image to get from the resource loader.
		 * @param newVertices Pointer to the vertices of the shape to take from
		 * the image.
		 * @param frameWidth Width of the frames to read from the image (in 
		 * pixels).
		 * @param frameHeight Height of the frames to read from the image (in
		 * pixels).
		 * @param nbFrames Number of frames of texture coordinates to generate.
		 * will start loading.
         * @param newColor Array to use to set the RenderInfo's color.
		 * @param newDeleteVerticesGroup True if the RenderStep needs to delete
		 * the vertices when destroyed. False if not. Sprites loading their
		 * render steps will put this parameter to false.
		 */
		RenderStep(const std::string& key,
				   VerticesGroup* newVertices,
				   unsigned int frameWidth,
				   unsigned int frameHeight,
				   unsigned int nbFrames = 1,
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
		
		///Flip off the given flags. (You can pass more than one flag like this: (Flag1 | flag2))
		void removeMode(RenderStepMode::Enum newMode);
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
		
		/**
		 * Synchronizes the vertices data with their respective vertices. To be
		 * called at each sprite update or each time a sprite is moved.
		 */
		void updateVerticesData();
		
		/**
		 * Adds a vertex pointer to the render step. Only useful if the instance
		 * is a secondary render step.
		 * @param vertexPtr Pointer to add to the list.
		 */
		void addVertexPtr(Vertex* vertexPtr);
		/**
		 * Adds vertices to the list that the render step needs to keep
		 * synchronized with.
		 * @param first Iterator to the first vertex to add.
		 * @param last Iterator to the last vertex to add.
		 */
		void addVerticesPtr(std::list<Vertex*>::iterator first,
							std::list<Vertex*>::iterator last);
		/**
		 * Adds vertices to the list that the render step needs to keep
		 * synchronized with. Takes a variable number of arguments.
		 * @param nbVerticesPtr Number of vertices pointers to add.
		 */
		void addVerticesPtr(unsigned int nbVerticesPtr, ...);
		/**
		 * Removes a vertex pointer from the render step's list.
		 * @param vertexPtr Pointer to remove from the list.
		 */
		void removeVertexPtr(Vertex* vertexPtr);
		/**
		 * Set the color of in the renderInfo with the
		 * given color components Range are from 0 to 255.
		 * Componentes are RGBA.
		 */
		void setColor(int red, int green, int blue, int alpha);
    private:
        /// Information on the render. Includes the color and the texture ID.
        RenderInfo info;
        /**
         * Render mode to be used for this rendering step. Modes can be
         * combined with the bitwise inclusive OR.
         */
		RenderStepMode::Enum mode;
        /**
		 * Pointer to the vertices group that contains the vertices this render
		 * step has to keep its vertices data synchronized with. Is set to NULL
		 * if the render step is instead synchronized with a few specific
		 * vertices. In this case, verticesPtr is used.
		 */
        VerticesGroup* vertices;
		/**
		 * Data about the vertices' coordinates.
		 */
		std::vector<float> verticesData;
		/**
		 * Contains a list of pointers to the vertices this render step has to
		 * keep its vertices data synchronized with.
		 */
		std::list<Vertex*> verticesPtr;
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

#endif