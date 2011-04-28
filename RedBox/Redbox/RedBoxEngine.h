/**
 * @file
 * @ingroup StateMachine
 */

#ifndef RB_RED_BOX_ENGINE_H
#define RB_RED_BOX_ENGINE_H

#include <map>
#include <string>
#include "sigly.h"

#include "State.h"
namespace RedBox {
	/**
	 * Class managing the states.
	 * @ingroup StateMachine
	 */
	class RedBoxEngine {
		friend class ResourcePathHandler;

	public:
		///This function must be called by the main function. The main function arguments must be passed this function 
		static void application(int argc, char *argv[]);
		
		/// Signal sent when the RedBox engine is initialized.
		static sigly::Signal2<int, int> onInitialize;
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
		static int getFpsMin();
		/**
		 * Gets the number of updates per second.
		 * @return Number of updates per second.
		 */
		static int getUpdatesPerSecond();
		/**
		 * Gets the ratio of time to catch up to time things correctly in the
		 * updates.
		 */
		static double getDeltaRatio();
		/**
		 * Sets the minimum number of frames per second to be rendered. Cannot
		 * have a higher number than the number of updates per second.
		 * @param fpsMin Minimum number of frames per second.
		 */
		static void setFpsMin(int fpsMin);
		/**
		 * Sets the updates per second. Updates per second called on the current
		 * state. Cannot have a lower number than the number of frames per
		 * second.
		 * @param updatesPerSecond Number of updates per second.
		 */
		static void setUpdatesPerSecond(int updatesPerSecond);
		/**
		 * Called by the context to call the update and the render correctly
		 * on the current state.
		 */
		static void pulse();
		/**
		 * Initialize the different parts of the engine (drawer, audio engine, etc.)
		 */
		static void initializeEngine(int screenWidth, int screenHeight);
		/**
		 * Gets the time elapsed since the last update called on a state.
		 * @return Time in seconds since the last update called on a state.
		 */
		static double getUpdateDelta();

		/**
		 * Gets the screen's width.
		 */
		static int getScreenWidth();
		/**
		 * Gets the screen's height.
		 */
		static int getScreenHeight();
	private:
		/// Map of states in the engine.
		static std::map<std::string, State*> states;
		/// Pointer to the current state being played.
		static State* currentState;
		/// Maximum delay between each render called on the current state.
		static double maxRenderDelay;
		/// Delay between each update called on the current state.
		static double updateDelay;
		/// Time at which the last update was called on the current state.
		static double lastUpdate;
		/// Time at which the last render was called on the current state.
		static double lastRender;
		/// Ratio of time that the updates need to watch for to catch up.
		static double deltaRatio;
		///The path to the current application binary.
		static std::string applicationPath;
		/// Screen's width.
		static int screenWidth;
		/// Screen's height.
		static int screenHeight;
	};
}

#endif
