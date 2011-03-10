/**
 * @file
 */
#ifndef __STATE_H
#define __STATE_H

#include <map>
#include <list>
#include <string>
#include "Camera.h"
#include "Renderable.h"

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
         * Adds a renderable object to the multimap to begin rendering and updating it.
         * @param aRenderable the object to be rendered.
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
	private:
		/// Temporarily stores the renderable objects to be deleted.
        std::list<Renderable*> toDelete;
		/// Temporarily stores the renderable objects that need to change their Z value.
        std::list<Renderable*> zChange;
		/// Stores all the renderables active renderables objects.
        std::multimap<int, Renderable*> renderables;
		/// State's name, used as an identifier.
        std::string name;
		
		///The camera object which prepare the scene before rendering any object.
		Camera camera;
	};
}
#endif