/**
 * @file
 */
#ifndef __STATE_H
#define __STATE_H

#include <map>
#include <list>
#include <string>

#include "Renderable.h"

namespace RedBox {
	/**
     * A state represents the THE GAME's different states, it contains and
	 * manages the renderable objects. Ex: the playState, the MenuState.
     */
	class State {
	public:
		/**
         * Adds a renderable object to the multimap to begin rendering and updating it.
         * @param aRenderable the object to be rendered.
         */
		void addRenderable(Renderable* aRenderable);
		/**
         * Renders all the objects that need to be rendered.
         */
        void render();
		/**
         * Deletes, Updates and moves all concerns objects.
         */
        void update();
	private:
		/// Temporarily stores the renderable objects to be deleted.
        std::list<Renderable*> toDelete;
		/// Temporarily stores the renderable objects that need to change their Z value.
        std::list<Renderable*> zChange;
		/// Stores all the renderables active renderables objects.
        std::multimap<int, Renderable*> renderables;
		/// The name of the state.
        std::string name;
	};
}
#endif