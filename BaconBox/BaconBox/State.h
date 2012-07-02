/**
 * @file
 */
#ifndef RB_STATE_H
#define RB_STATE_H

#include <string>

#include <sigly.h>

#include "BaconBox/Display/Camera.h"
#include "BaconBox/Display/Color.h"
#include "BaconBox/BodyManager.h"
#include "BaconBox/Display/Layerable.h"

namespace BaconBox {
	/**
	 * A state represents the game's different states, it contains and
	 * manages the Layerable objects. Ex: the PlayState, the MenuState.
	 */
	class State : public Updateable, public Renderable,
		public BodyManager<Layerable, Layerable::LessCompare>,
        public sigly::HasSlots<> {
		friend class Engine;
	public:
		/**
		 * Default name given to states initialized with the default
		 * constructor.
		 */
		static const std::string DEFAULT_NAME;

		/**
		 * Simple parameterized constructor and default constructor.
		 * @param newName Initial name to give to the state.
		 */
		State(const std::string &newName = DEFAULT_NAME);

		/**
		 * Destructor.
		 */
		virtual ~State();

		/**
		 * Deletes, Updates and moves all concerns objects. You have to
		 * overload this method if you want to add custom code to it. You don't
		 * have to call the parent update function inside your implementation.
		 * The internal update code happens in internalUpdate, which then calls
		 * this update method.
		 * @see BaconBox::State::internalUpdate()
		 */
		virtual void update();

		/**
		 * Renders all the objects that need to be rendered. You have to
		 * overload this method if you want to add custom code to it. You don't
		 * have to call the parent render function inside your implementation.
		 * The internal render code happens in internalRender, which then calls
		 * this render method.
		 * @see BaconBox::State::internalRender()
		 */
		virtual void render();

		/**
		 * Gets the state's name.
		 * @return State's name.
		 * @see BaconBox::State::name
		 */
		const std::string &getName() const;

		/**
		 * Sets the state's name.
		 * @param newName State's new name.
		 * @see BaconBox::State::name
		 */
		void setName(const std::string &newName);

		/**
		 * Gets the state's background color.
		 * @return State's background color.
		 * @see BaconBox::State::camera
		 * @see BaconBox::Camera::backgroundColor
		 */
		const Color &getBackgroundColor() const;

		/**
		 * Sets the state's background color.
		 * @param newBackgroundColor State's new background color.
		 * @see BaconBox::State::camera
		 * @see BaconBox::Camera::backgroundColor
		 */
		void setBackgroundColor(const Color &newBackgroundColor);

		/**
		 * Gets the state's camera.
		 * @return The state's camera.
		 * @see BaconBox::State::camera
		 */
		const Camera &getCamera() const;
	protected:
		/// The camera object which prepare the scene before rendering any object.
		Camera camera;

		/**
		 * Method called by the engine when the state gets called to be played.
		 * @see BaconBox::State::internalOnGetFocus()
		 */
		virtual void onGetFocus();

		/**
		 * Method called by the engine when the state is not the current state
		 * anymore.
		 * @see BaconBox::State::internalOnLoseFocus()
		 */
		virtual void onLoseFocus();
	private:

		/// State's name, used as an identifier.
		std::string name;

		/**
		 * Private update method called by the Engine class.
		 * @see BaconBox::Engine
		 */
		void internalUpdate();

		/**
		 * Private render method called by the Engine class.
		 * @see BaconBox::Engine
		 */
		void internalRender();

		/**
		 * Private onGetFocus method called by the Engine class.
		 * @see BaconBox::Engine
		 */
		void internalOnGetFocus();

		/**
		 * Private onLoseFocus method called by the Engine class.
		 * @see BaconBox::Engine
		 */
		void internalOnLoseFocus();
	};
}
#endif
