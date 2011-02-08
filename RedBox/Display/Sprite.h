/**
 * @file
 * @ingroup Display
 */


#ifndef RB_SPRITE_H
#define RB_SPRITE_H

#include <list>
#include <string>

#include "Renderable.h"
#include "RenderStep.h"

#ifdef RB_PHYSICS_ENABLED
#include "GraphicBody.h"
#endif
namespace RedBox {
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
		 * ResourceLoader with the corresponding key.
		 * @param imageKey Image's key in the ResourceLoader to use for the
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
		 * ResourceLoader with the corresponding key.
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
		 * ResourceLoader with the corresponding key. Only takes the asked
		 * part of the image with the given width and height. Using the offsets,
		 * can also take a part of the image that is not at the upper left
		 * corner.
		 * @param imageKey Image's key in the ResourceLoader to use for the
		 * constructed sprite.
		 * @param frameWidth Width (in pixels) of the image to use.
		 * @param frameHeight Height (in pixels) of the image to use.
		 * @param offsetX X position of the upper left corner of the frame to
		 * take from the image.
		 * @param offsetY Y position of the upper left corner of the frame to
		 * take from the image.
		 * @param parentBody Parent graphic body, if there is one. Only exists
		 * if the Physics engine is enabled.
		 */
		Sprite(const std::string& imageKey,
			   float frameWidth,
			   float frameHeight,
			   float offsetX = 0.0f,
#ifdef RB_PHYSICS_ENABLED
			   float offsetY = 0.0f,
			   GraphicBody* parentBody = NULL);
#else
			   float offsetY = 0.0f);
#endif
		/**
		 * Parameterized constructor. Loads a sprite using a TextureInfo. Only
		 * takes the asked part of the image with the given width and height.
		 * Using the offsets, can also take a part of the image that is not at
		 * the upper left corner.
		 * @param texInfo TextureInfo to load the sprite from.
		 * @param frameWidth Width (in pixels) of the image to use.
		 * @param frameHeight Height (in pixels) of the image to use.
		 * @param offsetX X position of the upper left corner of the frame to
		 * take from the image.
		 * @param offsetY Y position of the upper left corner of the frame to
		 * take from the image.
		 * @param parentBody Parent graphic body, if there is one. Only exists
		 * if the Physics engine is enabled.
		 */
		Sprite(TextureInfo* texInfo,
			   float frameWidth,
			   float frameHeight,
			   float offsetX = 0.0f,
#ifdef RB_PHYSICS_ENABLED
			   float offsetY = 0.0f,
			   GraphicBody* parentBody = NULL);
#else
		float offsetY = 0.0f);
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
		void construct(TextureInfo* texInfo,
					   float frameWidth,
					   float frameHeight,
					   float offsetX = 0.0f,
#ifdef RB_PHYSICS_ENABLED
					   float offsetY = 0.0f,
					   GraphicBody* parentBody = NULL);
#else
		float offsetY = 0.0f);
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

#include "GraphicBody.h"

#endif // RB_SPRITE_H