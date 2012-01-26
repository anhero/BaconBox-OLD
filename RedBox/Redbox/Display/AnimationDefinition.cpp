#include "AnimationDefinition.h"

#include "Value.h"
#include "DefaultSerializer.h"
#include "Serializer.h"

namespace RedBox {
	bool AnimationDefinition::isValidValue(const Value &node) {
		const Object &tmpObject = node.getObject();
		Object::const_iterator itFrames = tmpObject.find("frames");
		Object::const_iterator itTimePerFrame = tmpObject.find("timePerFrame");
		Object::const_iterator itNbLoops = tmpObject.find("nbLoops");

		bool result = true;

		if (itFrames != tmpObject.end() &&
		    itTimePerFrame != tmpObject.end() &&
		    itNbLoops != tmpObject.end() &&
		    itTimePerFrame->second.isNumeric() &&
		    itNbLoops->second.isNumeric()) {

			const Array &tmpFrames = itFrames->second.getArray();
			Array::const_iterator i = tmpFrames.begin();

			while (result && i != tmpFrames.end()) {
				if (i->isNumeric()) {
					++i;

				} else {
					result = false;
				}
			}
		}

		return result;
	}

	AnimationDefinition::AnimationDefinition(): frames(), timePerFrame(0.0),
		nbLoops(-1) {
	}

	AnimationDefinition::AnimationDefinition(const std::vector<unsigned int>& newFrames,
	                                         double newTimePerFrame,
	                                         int newNbLoops): frames(newFrames),
		timePerFrame(newTimePerFrame), nbLoops(newNbLoops) {
	}

	AnimationDefinition::AnimationDefinition(const AnimationDefinition &src) :
		frames(src.frames), timePerFrame(src.timePerFrame), nbLoops(src.nbLoops) {
	}

	AnimationDefinition &AnimationDefinition::operator=(const AnimationDefinition &src) {
		if (this != &src) {
			frames = src.frames;
			timePerFrame = src.timePerFrame;
			nbLoops = src.nbLoops;
		}

		return *this;
	}

	void AnimationDefinition::serialize(Value &node) const {
		node["nbLoops"].setInt(nbLoops);
		node["timePerFrame"].setDouble(timePerFrame);
		Value &tmpValue = node["frames"];
		tmpValue.setArray(Array(frames.size()));

		for (std::vector<unsigned int>::size_type i = 0; i < frames.size(); ++i) {
			tmpValue[i].setInt(static_cast<int>(frames[i]));
		}
	}

	bool AnimationDefinition::deserialize(const Value &node) {
		bool result = true;
		const Object &tmpObject = node.getObject();
		Object::const_iterator itNbLoops = tmpObject.find("nbLoops");
		Object::const_iterator itTimePerFrame = tmpObject.find("timePerFrame");
		Object::const_iterator itFrames = tmpObject.find("frames");

		if (itNbLoops != tmpObject.end() &&
		    itTimePerFrame != tmpObject.end() &&
		    itFrames != tmpObject.end()) {

			// We make sure the frames value is an Array.
			if (itFrames->second.isArray()) {
				// We make sure the array contains only numbers.
				const Array &tmpArray = itFrames->second.getArray();
				Array::const_iterator i = tmpArray.begin();

				while (result && i != tmpArray.end()) {
					if (i->isNumeric()) {
						++i;

					} else {
						result = false;
					}
				}

				if (result) {
					// We make sure the nbLoops ans timePerFrame attributes are
					// of correct type.
					if (itNbLoops->second.isNumeric() && itTimePerFrame->second.isNumeric()) {

						nbLoops = itNbLoops->second.getInt();
						timePerFrame = itTimePerFrame->second.getDouble();

						frames.resize(tmpArray.size());

						for (Array::size_type i2 = 0; i2 < tmpArray.size(); ++i2) {
							frames[i2] = static_cast<unsigned int>(tmpArray[i2].getInt());
						}

					} else {
						result = false;
					}
				}

			} else {
				result = false;
			}

		} else {
			result = false;
		}

		return result;
	}

	std::ostream &operator<<(std::ostream &output,
	                         const AnimationDefinition &a) {
		Value tmpValue;
		DefaultSerializer::serialize(a, tmpValue);
		DefaultSerializer::getDefaultSerializer().writeToStream(output, tmpValue);
		return output;
	}
}
