/**
 * @file
 * @ingroup Display
 */
#ifndef RB_ANIMATION_PARAMETERS_H
#define RB_ANIMATION_PARAMETERS_H

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
		 * @param newFrames Suit of frames to use for the animation.
		 * @param newTimePerFrame Time per frame to use.
		 * @param newNbLoops Number of loops before the animation finishes to
		 * use.
		 */
		AnimationParameters(const std::vector<unsigned int>& newFrames,
		                    double newTimePerFrame,
		                    int newNbLoops = -1);

		/**
		 * Copy constructor.
		 * @param src Animation parameters to make a copy of.
		 */
		AnimationParameters(const AnimationParameters &src);

		/**
		 * Assignment operator overload.
		 * @param src Animation parameters to make a copy of.
		 * @return Reference to the modified animation parameters.
		 */
		AnimationParameters &operator=(const AnimationParameters &src);

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
	std::ostream &operator<<(std::ostream &output, const AnimationParameters &a);
}
#endif
