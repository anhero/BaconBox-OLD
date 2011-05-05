/**
 * @file
 * @ingroup Display
 */
#ifndef RB_ANIMATIONPARAMETERS_H
#define RB_ANIMATIONPARAMETERS_H

#include <vector>
#include <string>
#include <iostream>

namespace RedBox {
	/**
	 * Represents the details of an animation in a RenderStep.
	 * @see RedBox::RenderStep
	 * @ingroup Display
	 */
	struct AnimationParameters {
		/**
		 * Default constructor. By default, an animation will loop indefinetely.
		 */
		AnimationParameters();
		/**
		 * Parametrized constroctor. By default, an animation will loop
		 * indefinitely.
		 */
		AnimationParameters(const std::vector<unsigned int>& newFrames,
							double timePerFrame,
							int nbLoops = -1);
		/// The suit of frames composing the animation
		std::vector<unsigned int> frames;
		/// The time per frame (in seconds).
		double timePerFrame;
		/**
		 * Number of loops before the animation finishes. -1 for infinite
		 * looping.
		 */
		int nbLoops;
	};
	/**
	 * Outputs the AnimationParameters' content.
	 * @param output The ostream in which AnimationParameters is output.
	 * @param a AnimationParameters to output in the ostream.
	 * @return Resulting ostream.
	 */
	std::ostream& operator<<(std::ostream& output, const AnimationParameters& a);
}
#endif
