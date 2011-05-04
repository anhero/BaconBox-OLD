/**
 * @file
 */
#ifndef RB_STATE_H
#define RB_STATE_H

#include <map>
#include <list>
#include <string>
#include <sigly.h>
#include "Camera.h"
#include "GraphicBody.h"
#include "Color.h"

namespace RedBox {
	/**
     * A state represents the THE GAME's different states, it contains and
	 * manages the GraphicBody objects. Ex: the playState, the MenuState.
     */
	class State : public sigly::HasSlots<> {
		friend class Engine;
	public:
		/**
		 * Default constructor.
		 */
		State();

		/**
		 * Destructor.
		 */
		virtual ~State();
		/**
         * Adds a GraphicBody object to the multimap to begin rendering and
		 * updating it. Once a GraphicBody is added with this function, it is
		 * added in a temporary list of GraphicBodys that will be added on the
		 * next update. The GraphicBody's destruction is managed by the state.
         * @param aGraphicBody Pointer to the GraphicBody to add to the state's
		 * GraphicBodys.
         */
		void addGraphicBody(GraphicBody* aGraphicBody);
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
		/**
		 * Method called by the engine when the state gets called to be played.
		 */
		virtual void onGetFocus();
		/**
		 * Method called by the engine when the state is not the current state
		 * anymore.
		 */
		virtual void onLoseFocus();
	private:
		/// Temporarily stores the GraphicBody objects to be deleted.
        std::list<GraphicBody*> toDelete;
		/// Temporarily stores the GraphicBody objects to be added.
		std::list<GraphicBody*> toAdd;
		/// Temporarily stores the GraphicBody objects that need to change their Z value.
        std::list<GraphicBody*> zChange;
		/// Stores all the GraphicBodys active GraphicBodys objects.
        std::multimap<int, GraphicBody*> GraphicBodys;
		/// State's name, used as an identifier.
        std::string name;
		
		/**
		 * Adds a GraphicBody in the multimap of GraphicBodys. It will then be
		 * able to be updated and rendered correctly.
		 * @param aGraphicBody Pointer to the GraphicBody to add.
		 */
		void addGraphicBodyDirect(GraphicBody* aGraphicBody);
	};
}
#endif
