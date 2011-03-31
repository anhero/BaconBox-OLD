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

#ifdef RB_PHYSICS_ENABLED
#include "Edge.h"
#endif

namespace RedBox {
	class RenderStep;
#ifdef RB_PHYSICS_ENABLED
	class GraphicBody;
#endif
    /** 
     * Represents a sprite.
     * @ingroup Display
     */
	class Sprite : public Renderable {
    public:
#ifdef RB_PHYSICS_ENABLED
        /**
         * Default constructor.
         */
        Sprite(GraphicBody* = NULL);
#else
        Sprite();
#endif
#ifdef RB_PHYSICS_ENABLED
		/**
		 * Parameterized constructor. Loads a sprite using the image in the
		 * ResourceManager with the corresponding key.
		 * @param imageKey Image's key in the ResourceManager to use for the
		 * constructed sprite.
		 * @param parentBody Parent graphic body, if there is one. Only exists
		 * if the Physics engine is enabled.
		 */
		Sprite(const std::string& imageKey, GraphicBody* parentBody = NULL);
#else
		Sprite(const std::string& imageKey);
#endif
#ifdef RB_PHYSICS_ENABLED
		/**
		 * Parameterized constructor. Loads a sprite using the image in the
		 * ResourceManager with the corresponding key.
		 * @param texInfo TextureInfo to load the sprite from.
		 * @param parentBody Parent graphic body, if there is one. Only exists
		 * if the Physics engine is enabled.
		 */
		Sprite(TextureInfo* texInfo, GraphicBody* parentBody = NULL);
#else
		Sprite(TextureInfo* texInfo);
#endif
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
		 * @param parentBody Parent graphic body, if there is one. Only exists
		 * if the Physics engine is enabled.
		 */
		Sprite(const std::string& imageKey,
			   unsigned int frameWidth,
			   unsigned int frameHeight,
			   unsigned int nbFrames = 1
#ifdef RB_PHYSICS_ENABLED
			   , GraphicBody* parentBody = NULL);
#else
			   );
#endif
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
		 * @param parentBody Parent graphic body, if there is one. Only exists
		 * if the Physics engine is enabled.
		 */
		Sprite(TextureInfo* texInfo,
			   unsigned int frameWidth,
			   unsigned int frameHeight,
			   unsigned int nbFrames = 1
#ifdef RB_PHYSICS_ENABLED
			   , GraphicBody* parentBody = NULL);
#else
		);
#endif
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
		 * Gets the sprite's horizontal position.
		 * @return Horizontal position (in pixels). Lower value means more to
		 * the left.
		 */
		float getXPosition() const;
		/**
		 * Gets the sprite's vertical position.
		 * @return Vertical position (in pixels). Lower value means more at the
		 * top.
		 */
		float getYPosition() const;
		/**
		 * Gets the sprite's horizontal and vertical position.
		 * @return Horizontal and vertical position (in pixels).
		 */
		std::pair<float, float> getPosition() const;
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
         * Warns the vertices not to delete their links on their destruction.
         */
        void warnVerticesOfDeletion();
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
#ifdef RB_PHYSICS_ENABLED
        /**
         * Creates an edge on the sprite. Creates an edge linking two vertices.
         * The vertices given must be part of the same sprite.
         * @param firstVertex Pointer to the first vertex that the edge will 
         * link.
         * @param secondVertex Pointer to the second vertex that the edge will
         * link.
         */
        void createEdge(Vertex* firstVertex, Vertex* secondVertex);
		/**
		 * Sets the parent graphic body to the vertices.
		 * @param body Pointer to the parent graphic body to set.
		 */
        void setParentGraphicBody(GraphicBody* body);
		/**
         * Removes the given edge from the sprite's edges.
         * @param edge Pointer to the edge to remove.
         */
        void removeEdge(Edge* edge);
		VerticesGroup& getVertices() {
			return vertices;
		}
#endif //RB_PHYSICS_ENABLED
    private:
        /**
		 * List containing the rendering steps. The first RenderStep in the list
		 * is considered as the main one.
		 */
        std::list<RenderStep*> renderSteps;
        /// Vertices making up the sprite.
        VerticesGroup vertices;
#ifdef RB_PHYSICS_ENABLED
        /// Edges making up the sprite.
        std::list<Edge> edges;
#endif //RB_PHYSICS_ENABLED
		
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
#ifdef RB_PHYSICS_ENABLED
					   , GraphicBody* parentBody = NULL);
#else
		);
#endif
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
