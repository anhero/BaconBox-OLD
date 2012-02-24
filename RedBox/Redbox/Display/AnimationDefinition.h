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

namespace RedBox {
	class Value;
	/**
	 * Represents the details of an animation in a RenderStep.
	 * @ingroup Display
	 */
	struct AnimationDefinition {
		/**
		 * Checks whether or not the Value contains the necessary information
		 * to deserialize the type.
		 * @param node Value to check.
		 * @return True if the value contains the necessary information, false
		 * if not.
		 */
		static bool isValidValue(const Value &node);

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

		/**
		 * Serializes the animation definition to a Value.
		 * @param node Value to serialize the animation definition to.
		 * @param setName Wether or not we need to set the name.
		 */
		void serialize(Value &node, bool setName = true) const;

		/**
		 * Deserializes the animation definition from a Value.
		 * @param node Node to read the animation definition from.
		 * @return True if the deserialization was successful, false if not. If
		 * the deserialization failed, the output animation definition is not
		 * modified.
		 */
		bool deserialize(const Value &node);

		/// The suit of frames composing the animation
		std::vector<unsigned int> frames;

		/// The time per frame (in seconds).
		double timePerFrame;

		/**
		 * Number of loops before the animation stops/finishes. -1 for infinite
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
