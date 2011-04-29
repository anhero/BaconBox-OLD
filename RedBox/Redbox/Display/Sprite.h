/**
 * @file
 * @ingroup Display
 */


#ifndef RB_SPRITE_H
#define RB_SPRITE_H

#include <list>
#include <string>
#include <utility>

#include "PlatformFlagger.h"

#include "TextureInfo.h"
#include "Renderable.h"
#include "VerticesGroup.h"


namespace RedBox {
	class RenderStep;

    /** 
     * Represents a sprite.
     * @ingroup Display
     */
	class Sprite : public Renderable {
    public:

        Sprite();
		Sprite(const std::string& imageKey);
		Sprite(TextureInfo* texInfo);
		/**
		 * Parameterized constructor. Loads a sprite using the image in the 
		 * ResourceManager with the corresponding key. Only takes the asked
		 * part of the image with the given width and height. Using the offsets,
		 * can also take a part of the image that is not at the upper left
		 * corner.
		 * @param imageKey Image's key in the ResourceManager to use for the
		 * constructed sprite.
		 * @param frameWidth Width of the frames to read from the image (in 
		 * pixels).
		 * @param frameHeight Height of the frames to read from the image (in
		 * pixels).
		 * @param nbFrames Number of frames the sprite will load (for
		 * animations)
		 */
		Sprite(const std::string& imageKey,
			   unsigned int frameWidth,
			   unsigned int frameHeight,
			   unsigned int nbFrames = 1
			   );
		/**
		 * Parameterized constructor. Loads a sprite using a TextureInfo. Only
		 * takes the asked part of the image with the given width and height.
		 * Using the offsets, can also take a part of the image that is not at
		 * the upper left corner.
		 * @param texInfo TextureInfo to load the sprite from.
		 * @param frameWidth Width of the frames to read from the image (in 
		 * pixels).
		 * @param frameHeight Height of the frames to read from the image (in
		 * pixels).
		 * @param nbFrames Number of frames the sprite will load (for
		 * animations).

		 */
		Sprite(TextureInfo* texInfo,
			   unsigned int frameWidth,
			   unsigned int frameHeight,
			   unsigned int nbFrames = 1
		);
        /**
         * Copy constructor.
         * @param src Sprite to make a copy of.
         */
        Sprite(const Sprite& src);
        /**
         * Assignation operator overload.
         * @param src Sprite to make a copy of.
         */
        Sprite& operator=(const Sprite& src);
        /**
         * Destructor. Frees up all allocated memory.
         */
        virtual ~Sprite();
        /**
         * Renders the sprite.
         */
        virtual void render();
		/**
		 * Updates the sprite.
		 */
		virtual void update();
        /**
         * Creates a vertex in the vertices group.
         * @param x Horizontal position.
         * @param y Vertical position.
		 * @param parentBody
         */
        void createVertex(float x, float y);
		
		/**
		 * Sets the sprite's horizontal position.
		 * @param x New horizontal position (in pixels). Lower value means more
		 * to the left.
		 */
		void setXPosition(float x);
		/**
		 * Sets the sprite's horizontal position.
		 * @param y New vertical position (in pixels). Lower value means more at
		 * the top.
		 */
		void setYPosition(float y);
		/**
		 * Sets the sprite's horizontal and vertical position.
		 * @param x New horizontal position (in pixels). Lower value means more
		 * to the left.
		 * @param y New vertical position (in pixels). Lower value means more at
		 * the top.
		 */
		void setPosition(float x, float y);
		/**
		 * Moves the sprite horizontally.
		 * @param deltaX Value to add to the sprite's horizontal position (in
		 * pixels). Positive value moves the sprite to the right and a negative
		 * value moves the sprite to the left.
		 */
		void moveX(float deltaX);
		/**
		 * Moves the sprite vertically.
		 * @param deltaY Value to add to the sprite's vertical position (in
		 * pixels). Positive value moves the sprite down and a negative value
		 * moves the sprite up.
		 */
		void moveY(float deltaY);
		/**
		 * Moves the sprite horizontally and vertically.
		 * @param deltaX Value to add to the sprite's horizontal position (in
		 * pixels). Positive value moves the sprite to the right and a negative
		 * value moves the sprite to the left.
		 * @param deltaY Value to add to the sprite's vertical position (in
		 * pixels). Positive value moves the sprite down and a negative value
		 * moves the sprite up.
		 */
		void move(float deltaX, float deltaY);
		
		/**
		 * Gets the sprite's width.
		 * @return Sprite's width.
		 */
		float getWidth() const;
		/**
		 * Gets the sprite's height.
		 * @return Sprite's height.
		 */
		float getHeight() const;
		/**
		 * Gets the sprite's width and height.
		 * @return Pair containing the sprite's width and height. The first
		 * member is the width and the second is the height.
		 */
		const std::pair<float, float>& getWidthHeight() const;

		/**
		 * Adds a rendering step. Does nothing if the recieved pointer is NULL.
		 * @param newRenderStep Pointer to the rendering step to add.
		 * @return Pointer to the rendering step added. NULL if it failed.
		 */
		RenderStep* addRenderStep(RenderStep* newRenderStep);
		/**
		 * Removes a rendering step. Does nothing if the recieved is either NULL
		 * or isn't in the list. Does not free up any memory used by the pointed
		 * RenderStep.
		 * @param renderStep Rendering step to remove from the set.
		 */
		void removeRenderStep(RenderStep* renderStep);
		/**
		 * Gets the main RenderStep. The main RenderStep is the one at the front
		 * of the list.
		 * @return Pointer to the RenderStep at the front of the list. Returns
		 * NULL if the list is empty.
		 */
		RenderStep* getMainRenderStep();
		/**
		 * Gets a RenderStep. Has to loop through the list to get it, so it is
		 * quite slower than a direct access.
		 * @param position Position of the RenderStep to get from the list. 0 is
		 * the first RenderStep (also known as the main RenderStep).
		 * @return Pointer to the RenderStep at the position given.
		 */
		RenderStep* getRenderStep(unsigned int position);
		/**
		 * Gets the list of RenderStep's.
		 * @return List of RenderStep used by the sprite.
		 */
		std::list<RenderStep*>& getRenderSteps();
		
		/**
		 * Set the color of the main renderStep with the
		 * given color components Range are from 0 to 255.
		 * Componentes are RGBA.
		 */
		void setMainColor(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);
		
		/**
		 * Gets the vertices group.
		 * @return The sprite's group of vertices.
		 */
		VerticesGroup& getVertices();
		int getMinX();
		int getMaxX();
		int getMinY();
		int getMaxY();

    private:
        /**
		 * List containing the rendering steps. The first RenderStep in the list
		 * is considered as the main one.
		 */
        std::list<RenderStep*> renderSteps;
        /// Vertices making up the sprite.
        VerticesGroup vertices;
		
		/**
		 * Constructs the sprite using the given info.
		 * @param texInfo Pointer to the texture's information.
		 * @param frameWidth Width of the frames to read from the image (in 
		 * pixels).
		 * @param frameHeight Height of the frames to read from the image (in
		 * pixels).
		 * @param nbFrames Number of frames the sprite will load (for
		 * animations).
		 */
		void construct(TextureInfo* texInfo,
					   unsigned int frameWidth,
					   unsigned int frameHeight,
					   unsigned int nbFrames = 1
		);
        /**
         * Resets the sprite. Also frees up all allocated memory.
         */
        void clean();
        /**
         * Makes the instance a copy of the recieved one.
         * @param src Sprite to make a copy of.
         */
        void copyFrom(const Sprite& src);
		/**
		 * Frees up all memory used by the render steps.
		 */
		void clearRenderSteps();
    };
}

#endif // RB_SPRITE_H
