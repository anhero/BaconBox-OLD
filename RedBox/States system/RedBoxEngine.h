/**
 * @file
 * @ingroup StateMachine
 */

#ifndef __RED_BOX_ENGINE_H
#define __RED_BOX_ENGINE_H

#include <map>
#include <string>

#include "State.h"

namespace RedBox {
	/**
	 * Class managing the states.
	 * @ingroup StateMachine
	 */
	class RedBoxEngine {
	public:
		/**
		 * Adds a state to the engine's list.
		 * @param newState Pointer to the state to add to the engine.
		 * @return Pointer to the added state. The same as the one recieved.
		 */
		static State* addState(State* newState);
		/**
		 * Removes a state from the engine.
		 * @param name Name of the state to remove from the engine.
		 */
		static void removeState(const std::string& name);
		/**
		 * Changes the current state to the one asked for.
		 * @param name Name of the state to become the current one.
		 * @return Pointer to the state starting to be played.
		 */
		static State* playState(const std::string& name);
		/**
		 * Gets the current state being played.
		 * @return Pointer to the state being played.
		 */
		static State* getCurrentState();
		/**
		 * Gets the minimum fps.
		 * @return Minimum fps.
		 */
		static unsigned int getFpsMin();
	private:
		/// Map of states in the engine.
		static std::map<std::string, State*> states;
		/// Pointer to the current state being played.
		static State* currentState;
		/// Miminum frame per second before warnings start being given.
		static unsigned int fpsMin;
		/**
		 * Number of updates per second required. Will lower the fps according
		 * to the time update takes to do.
		 */
		static unsigned int updatePerSecond;
	};
}

#endif