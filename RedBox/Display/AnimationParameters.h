#ifndef __ANIMATIONPARAMETERS_H
#define __ANIMATIONPARAMETERS_H
#include <vector>
#include <string>

#include "Debug.h"
#include "TimeHelper.h"


namespace RedBox {
	/**
	 * @class AnimationParameters
	 *
	 * Represents the details of an animated graphical object.
	 * @see RedBox::GraphicObject
	 */
	class AnimationParameters{
	private:
		// The animation's name.
		std::string name;
		//The suit of frames composing the animation
		std::vector<int>  frames;
		// The time per frame.
		double timePerFrame;
		
		//The current frame
		int activeFrameIndex;//TODO: Is it necessary?
		//The tick of the last time it updated
		double lastUpdateTime;//TODO: Is it really needed?
		
	public:
		/**
		 * Creates an animation parameters definition
		 *
		 * @param newName The friendly name for the animation
		 * @param setOfFrames An array that contains the frame numbers to show
		 * in the animation.
		 * @param numberOfFrames The number of frames set in setOfFrames.
		 * @param newFps The number of frames to show in a second.
		 */
		AnimationParameters(const std::string& newName, int frames[], 
							int numberOfFrames, double newFps);
		/**
		 * The destructor.
		 */
		~AnimationParameters();
		/**
		 * Gets the friendly name of the animation.
		 *
		 * @return The animation's name.
		 */
		const std::string& getName() const;
		/**
		 * Updates and gets the animation's active frame.
		 */
		int getActiveFrame();
		/**
		 * Resets the animation at the first frame.
		 */
		void reset();
	};
}
#endif
