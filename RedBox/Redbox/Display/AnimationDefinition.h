/**
 * @file
 * @ingroup Display
 */
#ifndef RB_ANIMATION_DEFINITION_H
#define RB_ANIMATION_DEFINITION_H

#include <vector>
#include <map>
#include <string>
#include <iostream>

#include "Value.h"

namespace RedBox {
	/**
	 * Represents the details of an animation in a RenderStep.
	 * @ingroup Display
	 */
	struct AnimationDefinition {
		/**
		 * Serializes the animation definition to a Value.
		 * @param input Animation definition to serialize.
		 * @param node Value to serialize the animation definition to.
		 */
		static void serialize(const AnimationDefinition &input, Value &node);

		/**
		 * Deserializes the animation definition from a Value.
		 * @param node Node to read the animation definition from.
		 * @param output Animation definition instance to write the Value to.
		 * @return True if the deserialization was successful, false if not. If
		 * the deserialization failed, the output animation definition is not
		 * modified.
		 */
		static bool deserialize(const Value &node, AnimationDefinition &output);

		/**
		 * Default constructor. By default, an animation will loop indefinetely.
		 */
		AnimationDefinition();

		/**
		 * Parametrized constroctor. By default, an animation will loop
		 * indefinitely.
		 * @param newFrames Suit of frames to use for the animation.
		 * @param newTimePerFrame Time per frame to use.
		 * @param newNbLoops Number of loops before the animation finishes to
		 * use.
		 */
		AnimationDefinition(const std::vector<unsigned int>& newFrames,
		                    double newTimePerFrame,
		                    int newNbLoops = -1);

		/**
		 * Copy constructor.
		 * @param src Animation definition to make a copy of.
		 */
		AnimationDefinition(const AnimationDefinition &src);

		/**
		 * Assignment operator overload.
		 * @param src Animation definition to make a copy of.
		 * @return Reference to the modified animation definition.
		 */
		AnimationDefinition &operator=(const AnimationDefinition &src);

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

	// Type of the map containing the animation definitions.
	typedef std::map<std::string, AnimationDefinition> AnimationMap;

	/**
	 * Outputs the AnimationDefinition' content.
	 * @param output The ostream in which AnimationDefinition is output.
	 * @param a AnimationDefinition to output in the ostream.
	 * @return Resulting ostream.
	 */
	std::ostream &operator<<(std::ostream &output, const AnimationDefinition &a);
}

#endif
