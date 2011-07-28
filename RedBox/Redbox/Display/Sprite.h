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
#include "GraphicBody.h"
#include "VerticesGroup.h"
#include "Color.h"


namespace RedBox {
	class RenderStep;
	class RenderInfo;
    /** 
	 * Represents a sprite. A is used to display animated or non-animated
	 * images or display colored shapes. To use a sprite, initialize it and
	 * pass it to a State. A sprite can only be in one state at a time. Once
	 * you have given the pointer to the state, you don't have to worry about
	 * deleting it, the state takes care of that for you. To remove a sprite
	 * from a state, simply call setToBeDeleted(true), which is inherited from
	 * GraphicBody.
     * @ingroup Display
	 * @see RedBox::GraphicBody
	 * @see RedBox::State
     */
	class Sprite : public GraphicBody {
    public:
		/**
		 * Default constructor.
		 */
        Sprite();

		/**
		 * Simple parameterized constructor.
		 * @param imageKey Key to the texture to create a sprite from.
		 */
		Sprite(const std::string& imageKey);

		/**
		 * Simple parameterized constructor. Does the same thing as the
		 * constructor that recieves an key.
		 * @param texInfo Pointer to the texture information to load the sprite
		 * with.
		 * @see RedBox::RenderInfo::texInfo
		 */
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
			   unsigned int nbFrames = 1);

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
			   unsigned int nbFrames = 1);

        /**
         * Copy constructor.
         * @param src Sprite to make a copy of.
         */
        Sprite(const Sprite& src);

        /**
         * Assignation operator overload.
         * @param src Sprite to make a copy of.
		 * @return Reference to the modified sprite.
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
         */
        void createVertex(float x, float y);
		
		/**
		 * Gets the sprite's center's position.
		 * @return 2D vector containing the sprite's center's position.
		 */
		Vec2 getPositionCenter() const;

		/**
		 * Gets the sprite's center's horizontal position.
		 * @return Sprite's center's horizontal position.
		 */
		float getXPositionCenter() const;

		/**
		 * Gets the sprite's center's vertical position.
		 * @return Sprite's center vertical position.
		 */
		float getYPositionCenter() const;

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

		using GraphicBody::setPosition;

		/**
		 * Sets the sprite's horizontal and vertical position.
		 * @param x New horizontal position (in pixels). Lower value means more
		 * to the left.
		 * @param y New vertical position (in pixels). Lower value means more at
		 * the top.
		 */
		void setPosition(float x, float y);

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
		const Vec2 getWidthHeight() const;
		
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
		 * @return Reference to the list of RenderSteps used by the sprite.
		 */
		std::list<RenderStep*>& getRenderSteps();
		
		/**
		 * Set the color of the main renderStep with the
		 * given color components Range are from 0 to 255.
		 * Componentes are RGBA.
		 */
		void setMainColor(const Color& color);
		
		/**
		 * Set the alpha component on the main renderstep.
         * Range is from 0 to 255.
		 */
		void setMainAlpha(int alpha);
		
		/**
		 * Return a Color object containing the color component of the main RenderStep.
		 */
		Color getMainColor();
		
		/**
		 * Gets the vertices group.
		 * @return Reference to the sprite's group of vertices.
		 */
		VerticesGroup& getVertices();

		/**
		 * Gets the sprite's left side's position.
		 * @return Sprite's left side's position.
		 */
		float getMinX() const;

		/**
		 * Gets the sprite's right side's position.
		 * @return Sprite's right side's position.
		 */
		float getMaxX() const;

		/**
		 * Gets the sprite's top side's position.
		 * @return Sprite's top side's position.
		 */
		float getMinY() const;

		/**
		 * Gets the sprite's bottom side's position.
		 * @return Sprite's bottom side's position.
		 */
		float getMaxY() const;

		/**
		 * Gets a pointer to the main render step's render information.
		 * @return Pointer to the main RenderStep's render information. Returns
		 * NULL if there aren't any RenderSteps for the sprite.
		 */
		RenderInfo* getMainRenderInfo();
		
		/**
		 * Sets the current animation.
		 * @param name Name of the animation to play.
		 */
		void playAnimation(const std::string& name);
		
		/**
		 * Adds an animation. Accepts a variable number of parameters for each
		 * animation frame. For example, an animation of 7 frames could be added
		 * as such:
		 * addAnimation("myAnimationName", 0.2, -1, 7, 0, 1, 2, 4, 3, 5, 6);
		 * @param name Animation's name used for identification when playing it.
		 * @param timePerFrame Time in seconds that each frame lasts during the
		 * animation.
		 * @param nbLoops Number of times the animation will play before
		 * stopping. -1 means it will loop infinitely.
		 * @param nbFrames Number of frames the animation has.
		 */
		void addAnimation(const std::string& name,
						  double timePerFrame,
						  int nbLoops,
						  unsigned int nbFrames, ... );

		using GraphicBody::setScaling;

		/**
		 * Change the sprite's scaling.
		 * @param xScaling New horizontal scaling to apply.
		 * @param yScaling New vertical scaling to apply.
		 */
		void setScaling(float xScaling, float yScaling);

		/**
		 * Sets the sprite's rotation angle.
		 * @param newAngle Sprite's new rotation angle. As the angle increments,
		 * it makes the sprite rotate counter-clockwise.
		 */
		void setAngle(float newAngle);
        
        /** 
        * Similar to the render function except that it will only
        * render to the alpha component of the color buffer. It is
        * used to mask the next rendered sprite (if the next sprite
        * is set as a masked sprite).
        */
        void mask();
        
        /**
         * Undo what the mask function did. This function
         * MUST be once after the masked sprite has been rendered.
         */
        void unmask();
        
        
        /**
         * Set the sprite used to mask the parent renderstep.
         * @param aMask A mask sprite.
         * @param inversed Set this parameter to true if you want to inverse the effect of the mask.
         * false by default.
         */
        void setMask(Sprite * aMask, bool inversed =false);
		
//		void setTexture(TextureInfo * aTextureInfo);
//		void setTexture(std::string key);
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
					   unsigned int nbFrames = 1);
        
        
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
