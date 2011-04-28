/**
 * @file
 */
#ifndef RB_STATE_H
#define RB_STATE_H

#include <map>
#include <list>
#include <string>
#include "Camera.h"
#include "Renderable.h"
#include "Color.h"

namespace RedBox {
	/**
     * A state represents the THE GAME's different states, it contains and
	 * manages the renderable objects. Ex: the playState, the MenuState.
     */
	class State {
	public:
		/**
		 * Default constructor.
		 */
		State();
		/**
         * Adds a renderable object to the multimap to begin rendering and
		 * updating it. Once a renderable is added with this function, it is
		 * added in a temporary list of renderables that will be added on the
		 * next update. The renderable's destruction is managed by the state.
         * @param aRenderable Pointer to the renderable to add to the state's
		 * renderables.
         */
		void addRenderable(Renderable* aRenderable);
		/**
         * Renders all the objects that need to be rendered.
         */
        virtual void render();
		/**
         * Deletes, Updates and moves all concerns objects.
         */
        virtual void update();
		/**
		 * Gets the state's name.
		 * @return State's name.
		 */
		const std::string& getName() const;
		/**
		 * Sets the state's name.
		 * @param newName State's new name.
		 */
		void setName(const std::string& newName);

		/**
		 * Sets the state's background color.
		 * @param newBackgroundColor State's new background color.
		 */
		void setBackgroundColor(const Color& newBackgroundColor);

		/**
		 * Gets the state's background color.
		 * @return State's background color.
		 */
		const Color& getBackgroundColor() const;
	protected:
		///The camera object which prepare the scene before rendering any object.
		Camera camera;
	private:
		/// Temporarily stores the renderable objects to be deleted.
        std::list<Renderable*> toDelete;
		/// Temporarily stores the renderable objects to be added.
		std::list<Renderable*> toAdd;
		/// Temporarily stores the renderable objects that need to change their Z value.
        std::list<Renderable*> zChange;
		/// Stores all the renderables active renderables objects.
        std::multimap<int, Renderable*> renderables;
		/// State's name, used as an identifier.
        std::string name;
		
		/**
		 * Adds a renderable in the multimap of renderables. It will then be
		 * able to be updated and rendered correctly.
		 * @param aRenderable Pointer to the renderable to add.
		 */
		void addRenderableDirect(Renderable* aRenderable);
	};
}
#endif
