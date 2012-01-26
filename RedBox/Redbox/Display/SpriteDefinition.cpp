#include "SpriteDefinition.h"

#include "ShapeFactory.h"

namespace RedBox {
	bool SpriteDefinition::isValidValue(const Value &node) {
		bool result = true;

		const Object &tmpObject = node.getObject();
		Object::const_iterator itVertices = tmpObject.find("vertices");
		Object::const_iterator itFrameSize = tmpObject.find("frameSize");
		Object::const_iterator itFrames = tmpObject.find("frames");
		Object::const_iterator itAnimations = tmpObject.find("animations");

		// We make sure the vertices are valid and that we found the frame
		// and animations attributes.
		if (itFrames != tmpObject.end() && itAnimations != tmpObject.end() &&
		    ((itVertices != tmpObject.end() && StandardVertexArray::isValidValueStatic(itVertices->second)) ||
			 (itFrameSize != tmpObject.end() && Vector2::isValidValue(itFrameSize->second)))) {

			const Array &tmpArray = itFrames->second.getArray();
			Array::const_iterator i1 = tmpArray.begin();

			while (result && i1 != tmpArray.end()) {
				if (FrameDetails::isValidValue(*i1)) {
					++i1;

				} else {
					result = false;
				}
			}

			if (result) {
				const Object &tmpAnimations = itAnimations->second.getObject();
				Object::const_iterator i2 = tmpAnimations.begin();

				while (result && i2 != tmpAnimations.end()) {
					if (AnimationDefinition::isValidValue(i2->second)) {
						++i2;

					} else {
						result = false;
					}
				}
			}

		} else {
			result = false;
		}

		return result;
	}

	SpriteDefinition::SpriteDefinition() : vertices(), frames(), animations() {
	}

	SpriteDefinition::SpriteDefinition(const SpriteDefinition &src) :
		vertices(src.vertices), frames(src.frames), animations(src.animations) {
	}

	SpriteDefinition &SpriteDefinition::operator=(const SpriteDefinition &src) {
		if (this != &src) {
			vertices = src.vertices;
			frames = src.frames;
			animations = src.animations;
		}

		return *this;
	}

	void SpriteDefinition::serialize(Value &node) const {
		DefaultSerializer::serialize(vertices, node["vertices"]);
		Value &tmpFrames = node["frames"];
		tmpFrames.setArray(Array(frames.size()));

		for (FrameArray::size_type i = 0; i < frames.size(); ++i) {
			DefaultSerializer::serialize(frames[i], tmpFrames[i]);
		}

		Value &tmpAnimations = node["animations"];

		for (AnimationMap::const_iterator i = animations.begin();
		     i != animations.end(); ++i) {
			DefaultSerializer::serialize(i->second, tmpAnimations[i->first]);
		}
	}

	bool SpriteDefinition::deserialize(const Value &node) {
		bool result = true;

		const Object &tmpObject = node.getObject();
		Object::const_iterator itVertices = tmpObject.find("vertices");
		Object::const_iterator itFrameSize = tmpObject.find("frameSize");
		Object::const_iterator itFrames = tmpObject.find("frames");
		Object::const_iterator itAnimations = tmpObject.find("animations");

		if ((itVertices != tmpObject.end() || itFrameSize != tmpObject.end()) &&
		    itFrames != tmpObject.end() &&
		    itAnimations != tmpObject.end()) {

			const Array &tmpArray = itFrames->second.getArray();
			Array::const_iterator i1 = tmpArray.begin();

			while (result && i1 != tmpArray.end()) {
				if (FrameDetails::isValidValue(*i1)) {
					++i1;

				} else {
					result = false;
				}
			}

			if (result) {
				const Object &tmpAnimations = itAnimations->second.getObject();
				Object::const_iterator i2 = tmpAnimations.begin();

				while (result && i2 != tmpAnimations.end()) {
					if (AnimationDefinition::isValidValue(i2->second)) {
						++i2;

					} else {
						result = false;
					}
				}

				if (result) {

					// We check if the value contains an array of vertices or a
					// frame size.
					if (itVertices != tmpObject.end()) {
						// If it's an array of vertices, we read them.
						result = DefaultSerializer::deserialize(itVertices->second, vertices);

					} else if (itFrameSize != tmpObject.end()) {
						// If it's a frame size, we generate the vertices to
						// shape a rectangle of the specified size.
						Vector2 tmpFrameSize;

						if (DefaultSerializer::deserialize(itFrameSize->second, tmpFrameSize)) {
							vertices.resize(4, Vector2());
							ShapeFactory::createRectangle(tmpFrameSize, Vector2(), &vertices);

						} else {
							result = false;
						}

					} else {
						result = false;
					}

					// If the vertices are valid and loaded correctly.
					if (result) {
						// We load the frames.
						frames.resize(tmpArray.size());
						FrameArray::size_type i3 = 0;

						while (result && i3 < frames.size()) {
							if (DefaultSerializer::deserialize(tmpArray[i3], frames[i3])) {
								++i3;

							} else {
								result = false;
							}
						}

						if (result) {
							animations.clear();
							i2 = tmpAnimations.begin();

							while (result && i2 != tmpAnimations.end()) {
								if (DefaultSerializer::deserialize(i2->second, animations[i2->first])) {
									++i2;

								} else {
									result = false;
								}
							}
						}

					}
				}
			}

		} else {
			result = false;
		}

		return result;
	}

	std::ostream &operator<<(std::ostream &output, SpriteDefinition &sd) {

		return output;
	}
}
