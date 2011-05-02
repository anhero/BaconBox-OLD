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
		static const double DEFAULT_UPDATES_PER_SECOND = 60.0;
		static const unsigned int DEFAULT_MIN_FRAMES_PER_SECOND = 5;
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
		static unsigned int getMinFps();
		/**
		 * Gets the number of updates per second.
		 * @return Number of updates per second.
		 */
		static double getUpdatesPerSecond();
		/**
		 * Return the normal delay between each update (1/Update per second)
		 */
		static double getUpdateDelay();
		/**
		 * Sets the minimum number of frames per second to be rendered. Cannot
		 * have a higher number than the number of updates per second.
		 * @param fpsMin Minimum number of frames per second.
		 */
		static void setMinFps(unsigned int newMinFps);
		/**
		 * Sets the updates per second. Updates per second called on the current
		 * state. Cannot have a lower number than the number of frames per
		 * second.
		 * @param updatesPerSecond Number of updates per second.
		 */
		static void setUpdatesPerSecond(double updatesPerSecond);
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
		static double getSinceLastUpdate();

		/**
		 * Gets the screen's width.
		 */
		static int getScreenWidth();
		/**
		 * Gets the screen's height.
		 */
		static int getScreenHeight();

		static bool isBufferSwapped();

		static void setBufferSwapped();
	private:
		/// Map of states in the engine.
		static std::map<std::string, State*> states;
		/// Pointer to the current state being played.
		static State* currentState;
		/// Time at which the last update was called on the current state.
		static double lastUpdate;
		/// Internal update count between each render.
		static unsigned int loops;
		/// Time at which the next update can be called.
		static double nextUpdate;
		/// Delay between each update called on the current state.
		static double updateDelay;
		/// Minimum renders that can be skipped between updates.
		static unsigned int minFps;
		/// Flag to set when the buffer needs to be swapped.
		static bool bufferSwapped;
		/**
		 * Flag used to limit rendering so it doesn't render more times than
		 * it updates.
		 */
		static bool renderedSinceLastUpdate;
		///The path to the current application binary.
		static std::string applicationPath;
		/// Screen's width.
		static int screenWidth;
		/// Screen's height.
		static int screenHeight;
	};
}

#endif
