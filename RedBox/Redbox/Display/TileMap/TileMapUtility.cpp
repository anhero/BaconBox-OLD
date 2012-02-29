#include "TileMapUtility.h"

#include "StringHelper.h"
#include "AlgorithmHelper.h"
#include "Collidable.h"

namespace RedBox {
	const std::string TileMapUtility::DEFAULT_ANIMATION_NAME("defaultAnimation");
	const std::string TileMapUtility::DEFAULT_FRAME_NAME("defaultFrame");

	static const PropertyMap::key_type::value_type TRUE_CHAR = '1';
	static const PropertyMap::key_type::value_type FALSE_CHAR = '0';
	static const PropertyMap::key_type FRAME_START("frame[");
	static const PropertyMap::key_type ANIMATION_START("animation[");

	struct BoolCharPredicate {
		bool operator()(const PropertyMap::key_type::value_type &a) const {
			return a == TRUE_CHAR || a == FALSE_CHAR;
		}
	};

	void TileMapUtility::loadCollidableFromProperties(const PropertyMap &properties,
	                                                  Collidable &collidable) {
		static const PropertyMap::key_type VELOCITY_X("velocity.x");
		static const float VELOCITY_X_DEFAULT_VALUE = 0.0f;

		static const PropertyMap::key_type VELOCITY_Y("velocity.y");
		static const float VELOCITY_Y_DEFAULT_VALUE = 0.0f;

		static const PropertyMap::key_type MAXIMUM_VELOCITY_X("maximumVelocity.x");
		static const float MAXIMUM_VELOCITY_X_DEFAULT_VALUE = -1.0f;

		static const PropertyMap::key_type MAXIMUM_VELOCITY_Y("maximumVelocity.y");
		static const float MAXIMUM_VELOCITY_Y_DEFAULT_VALUE = -1.0f;

		static const PropertyMap::key_type ACCELERATION_X("acceleration.x");
		static const float ACCELERATION_X_DEFAULT_VALUE = 0.0f;

		static const PropertyMap::key_type ACCELERATION_Y("acceleration.y");
		static const float ACCELERATION_Y_DEFAULT_VALUE = 0.0f;

		static const PropertyMap::key_type GLOBAL_DRAG("globalDrag");
		static const float GLOBAL_DRAG_DEFAULT_VALUE = 0.0f;

		static const PropertyMap::key_type HORIZONTAL_DRAG("horizontalDrag");
		static const float HORIZONTAL_DRAG_DEFAULT_VALUE = 0.0f;

		static const PropertyMap::key_type VERTICAL_DRAG("verticalDrag");
		static const float VERTICAL_DRAG_DEFAULT_VALUE = 0.0f;

		static const PropertyMap::key_type COLLIDABLE_SIDES("collidableSides");
		static const FlagSet<Side> COLLIDABLE_SIDES_DEFAULT_VALUE(FlagSet<Side>(Side::TOP) | FlagSet<Side>(Side::BOTTOM) | FlagSet<Side>(Side::LEFT) | FlagSet<Side>(Side::RIGHT));

		static const PropertyMap::key_type ELASTICITY("elasticity");
		static const float ELASTICITY_DEFAULT_VALUE = 0.0f;

		static const PropertyMap::key_type STATIC_BODY("elasticity");
		static const bool STATIC_BODY_DEFAULT_VALUE = false;

		static const PropertyMap::key_type OFFSET_X("offset.x");
		static const float OFFSET_X_DEFAULT_VALUE = 0.0f;

		static const PropertyMap::key_type OFFSET_Y("offset.y");
		static const float OFFSET_Y_DEFAULT_VALUE = 0.0f;

		static const PropertyMap::key_type COLLIDING_BOX_RATIO_X("collidingBoxRatio.x");
		static const float COLLIDING_BOX_RATIO_X_DEFAULT_VALUE = 1.0f;

		static const PropertyMap::key_type COLLIDING_BOX_RATIO_Y("collidingBoxRatio.y");
		static const float COLLIDING_BOX_RATIO_Y_DEFAULT_VALUE = 1.0f;

		static const PropertyMap::key_type OFFSET_RATIO("offsetRatio");
		static const bool OFFSET_RATIO_DEFAULT_VALUE = false;

		// We read the horizontal velocity.
		PropertyMap::const_iterator found = properties.find(VELOCITY_X);

		float tmpFloat = 0.0f;

		if (found != properties.end() &&
		    StringHelper::fromString(found->second, tmpFloat)) {
			collidable.setXVelocity(tmpFloat);

		} else {
			collidable.setXVelocity(VELOCITY_X_DEFAULT_VALUE);
		}

		// We read the vertical velocity.
		found = properties.find(VELOCITY_Y);

		if (found != properties.end() &&
		    StringHelper::fromString(found->second, tmpFloat)) {
			collidable.setYVelocity(tmpFloat);

		} else {
			collidable.setYVelocity(VELOCITY_Y_DEFAULT_VALUE);
		}

		// We read the maximum horizontal velocity.
		found = properties.find(MAXIMUM_VELOCITY_X);

		if (found != properties.end() &&
		    StringHelper::fromString(found->second, tmpFloat)) {
			collidable.setMaximumXVelocity(tmpFloat);

		} else {
			collidable.setMaximumXVelocity(MAXIMUM_VELOCITY_X_DEFAULT_VALUE);
		}

		// We read the maximum vertical velocity.
		found = properties.find(MAXIMUM_VELOCITY_Y);

		if (found != properties.end() &&
		    StringHelper::fromString(found->second, tmpFloat)) {
			collidable.setMaximumYVelocity(tmpFloat);

		} else {
			collidable.setMaximumYVelocity(MAXIMUM_VELOCITY_Y_DEFAULT_VALUE);
		}

		// We read the horizontal acceleration.
		found = properties.find(ACCELERATION_X);

		if (found != properties.end() &&
		    StringHelper::fromString(found->second, tmpFloat)) {
			collidable.setXAcceleration(tmpFloat);

		} else {
			collidable.setXAcceleration(ACCELERATION_X_DEFAULT_VALUE);
		}

		// We read the vertical acceleration.
		found = properties.find(ACCELERATION_Y);

		if (found != properties.end() &&
		    StringHelper::fromString(found->second, tmpFloat)) {
			collidable.setYAcceleration(tmpFloat);

		} else {
			collidable.setYAcceleration(ACCELERATION_Y_DEFAULT_VALUE);
		}

		// We read the global drag.
		found = properties.find(GLOBAL_DRAG);

		if (found != properties.end() &&
		    StringHelper::fromString(found->second, tmpFloat)) {
			collidable.setGlobalDrag(tmpFloat);

		} else {
			collidable.setGlobalDrag(GLOBAL_DRAG_DEFAULT_VALUE);
		}

		// We read the horizontal drag.
		found = properties.find(HORIZONTAL_DRAG);

		if (found != properties.end() &&
		    StringHelper::fromString(found->second, tmpFloat)) {
			collidable.setHorizontalDrag(tmpFloat);

		} else {
			collidable.setHorizontalDrag(HORIZONTAL_DRAG_DEFAULT_VALUE);
		}

		// We read the vertical drag.
		found = properties.find(VERTICAL_DRAG);

		if (found != properties.end() &&
		    StringHelper::fromString(found->second, tmpFloat)) {
			collidable.setHorizontalDrag(tmpFloat);

		} else {
			collidable.setHorizontalDrag(VERTICAL_DRAG_DEFAULT_VALUE);
		}

		// We read the collidable sides.
		found = properties.find(COLLIDABLE_SIDES);

		if (found != properties.end() &&
		    found->second.size() == 4 &&
		    AlgorithmHelper::allOf(found->second.begin(), found->second.end(), BoolCharPredicate())) {
			collidable.getCollidableSides().set(Side::TOP, found->second[0] == TRUE_CHAR);
			collidable.getCollidableSides().set(Side::BOTTOM, found->second[1] == TRUE_CHAR);
			collidable.getCollidableSides().set(Side::LEFT, found->second[2] == TRUE_CHAR);
			collidable.getCollidableSides().set(Side::RIGHT, found->second[3] == TRUE_CHAR);

		} else {
			collidable.getCollidableSides() = COLLIDABLE_SIDES_DEFAULT_VALUE;
		}

		// We read the elasticity.
		found = properties.find(ELASTICITY);

		if (found != properties.end() &&
		    StringHelper::fromString(found->second, tmpFloat)) {
			collidable.setElasticity(tmpFloat);

		} else {
			collidable.setElasticity(ELASTICITY_DEFAULT_VALUE);
		}

		// We read wether or not the body is static.
		found = properties.find(STATIC_BODY);

		if (found != properties.end() &&
		    found->second.size() == 1 &&
		    BoolCharPredicate()(found->second[0])) {
			collidable.setStaticBody(found->second[0] == TRUE_CHAR);

		} else {
			collidable.setStaticBody(STATIC_BODY_DEFAULT_VALUE);
		}

		// We read the horizontal offset.
		found = properties.find(OFFSET_X);

		if (found != properties.end() &&
		    StringHelper::fromString(found->second, tmpFloat)) {
			collidable.setXOffset(tmpFloat);

		} else {
			collidable.setXOffset(OFFSET_X_DEFAULT_VALUE);
		}

		// We read the vertical offset.
		found = properties.find(OFFSET_Y);

		if (found != properties.end() &&
		    StringHelper::fromString(found->second, tmpFloat)) {
			collidable.setYOffset(tmpFloat);

		} else {
			collidable.setYOffset(OFFSET_Y_DEFAULT_VALUE);
		}

		// We read the horizontal colliding box ratio.
		found = properties.find(COLLIDING_BOX_RATIO_X);

		if (found != properties.end() &&
		    StringHelper::fromString(found->second, tmpFloat)) {
			collidable.setXCollidingBoxRatio(tmpFloat);

		} else {
			collidable.setXCollidingBoxRatio(COLLIDING_BOX_RATIO_X_DEFAULT_VALUE);
		}

		// We read the vertical colliding box ratio.
		found = properties.find(COLLIDING_BOX_RATIO_Y);

		if (found != properties.end() &&
		    StringHelper::fromString(found->second, tmpFloat)) {
			collidable.setYCollidingBoxRatio(tmpFloat);

		} else {
			collidable.setYCollidingBoxRatio(COLLIDING_BOX_RATIO_Y_DEFAULT_VALUE);
		}

		// We read wether or not the offset is a ratio.
		found = properties.find(OFFSET_RATIO);

		if (found != properties.end() &&
		    found->second.size() == 1 &&
		    BoolCharPredicate()(found->second[0])) {
			collidable.setOffsetRatio(found->second[0] == TRUE_CHAR);

		} else {
			collidable.setOffsetRatio(OFFSET_RATIO_DEFAULT_VALUE);
		}
	}

	const Vector2 TileMapUtility::readFramePosition(const PropertyMap &properties) {
		static const PropertyMap::key_type FRAME_POSITION_X("frame.position.x");
		static const PropertyMap::key_type FRAME_POSITION_Y("frame.position.y");

		Vector2 result;

		// We read the frame's horizontal position.
		PropertyMap::const_iterator found = properties.find(FRAME_POSITION_X);

		float tmpFloat;

		if (found != properties.end() &&
		    StringHelper::fromString(found->second, tmpFloat)) {
			result.setX(tmpFloat);
		}

		// We read the frame's vertical position.
		found = properties.find(FRAME_POSITION_Y);

		if (found != properties.end() &&
		    StringHelper::fromString(found->second, tmpFloat)) {
			result.setY(tmpFloat);
		}

		return result;
	}

	const Vector2 TileMapUtility::readFramePosition(const PropertyMap &properties,
	                                                unsigned int index) {
		static const std::string FRAME_POSITION_END("].position.");
		std::stringstream ss;
		ss << FRAME_START << index << FRAME_POSITION_END;

		// We read the frame's horizontal position.
		PropertyMap::const_iterator found = properties.find(ss.str() + "x");

		Vector2 result;

		float tmpFloat;

		if (found != properties.end() &&
		    StringHelper::fromString(found->second, tmpFloat)) {
			result.setX(tmpFloat);
		}

		// We read the frame's vertical position.
		found = properties.find(ss.str() + "y");

		if (found != properties.end() &&
		    StringHelper::fromString(found->second, tmpFloat)) {
			result.setY(tmpFloat);
		}

		return result;
	}

	const std::string TileMapUtility::readTextureKey(const PropertyMap &properties) {
		static const PropertyMap::key_type TEXTURE_KEY("textureKey");

		PropertyMap::const_iterator found = properties.find(TEXTURE_KEY);

		return (found != properties.end()) ? (found->second) : (std::string());
	}

	FrameDetails::Orientation TileMapUtility::readFrameOrientation(const PropertyMap &properties) {
		static const PropertyMap::key_type FRAME_ORIENTATION("frame.orientation.");

		PropertyMap::const_iterator found = properties.find(FRAME_ORIENTATION);

		if (found != properties.end()) {
			return FrameDetails::stringToOrientation(found->second);

		} else {
			return FrameDetails::Orientation::NORTH;
		}
	}

	FrameDetails::Orientation TileMapUtility::readFrameOrientation(const PropertyMap &properties,
	                                                               unsigned int index) {
		static const PropertyMap::key_type FRAME_ORIENTATION_END("].orientation");
		std::stringstream ss;
		ss << FRAME_START << index << FRAME_ORIENTATION_END;

		PropertyMap::const_iterator found = properties.find(ss.str());

		if (found != properties.end()) {
			return FrameDetails::stringToOrientation(found->second);

		} else {
			return FrameDetails::Orientation::NORTH;
		}
	}

	const FrameDetails TileMapUtility::readFrame(const PropertyMap &properties) {
		return FrameDetails(TileMapUtility::readFramePosition(properties),
		                    TileMapUtility::readFrameOrientation(properties));
	}

	const FrameDetails TileMapUtility::readFrame(const PropertyMap &properties,
	                                             unsigned int index) {
		return FrameDetails(TileMapUtility::readFramePosition(properties, index),
		                    TileMapUtility::readFrameOrientation(properties, index));
	}

	void TileMapUtility::readFrames(const PropertyMap &properties,
	                                FrameArray &outputArray) {
		static const PropertyMap::key_type NB_FRAMES("nbFrames");
		PropertyMap::const_iterator found = properties.find(NB_FRAMES);

		unsigned int nbFrames = 1;

		if (found != properties.end()) {
			StringHelper::fromString(found->second, nbFrames);
		}

		outputArray.clear();
		outputArray.reserve(nbFrames);

		for (unsigned int i = 0; i < nbFrames; ++i) {
			outputArray.push_back(FrameDetails(TileMapUtility::readFramePosition(properties, i),
			                                   TileMapUtility::readFrameOrientation(properties, i)));
		}
	}

	int TileMapUtility::readAnimationNbLoops(const PropertyMap &properties,
	                                         const std::string &animationName) {
		static const PropertyMap::key_type ANIMATION_NB_LOOPS_END("].nbLoops");

		int result = -1;

		PropertyMap::const_iterator found = properties.find(ANIMATION_START + animationName + ANIMATION_NB_LOOPS_END);

		if (found != properties.end()) {
			StringHelper::fromString(found->second, result);
		}

		return result;
	}

	double TileMapUtility::readAnimationTimePerFrame(const PropertyMap &properties,
	                                                 const std::string &animationName) {
		static const PropertyMap::key_type ANIMATION_TIME_PER_FRAME_END("].timePerFrame");

		double result = 0.3;

		PropertyMap::const_iterator found = properties.find(ANIMATION_START + animationName + ANIMATION_TIME_PER_FRAME_END);

		if (found != properties.end()) {
			StringHelper::fromString(found->second, result);
		}

		return result;
	}

	const std::vector<unsigned int> TileMapUtility::readAnimationFrames(const PropertyMap &properties,
	                                                                    const std::string &animationName) {
		static const PropertyMap::key_type ANIMATION_FRAMES_END("].frames");

		std::vector<unsigned int> result(1, 0u);

		PropertyMap::const_iterator found = properties.find(ANIMATION_START + animationName + ANIMATION_FRAMES_END);

		if (found != properties.end()) {
			std::string tmp(found->second);
			StringHelper::trim(tmp);

			if (tmp.size() >= 2 &&
			    *tmp.begin() == '[' &&
			    *tmp.rbegin() == ']') {
				tmp.erase(tmp.begin());
				tmp.erase(tmp.end() - 1);
				std::list<std::string> indexes;
				StringHelper::tokenize(tmp, indexes, ",");

				result.resize(indexes.size(), 0u);

				std::list<std::string>::const_iterator i = indexes.begin();
				std::vector<unsigned int>::size_type i2 = 0;

				while (i != indexes.end()) {
					StringHelper::fromString(*i, result[i2]);
					++i;
					++i2;
				}
			}
		}

		return result;
	}

	const AnimationDefinition TileMapUtility::readAnimation(const PropertyMap &properties,
	                                                        const std::string &animation) {
		return AnimationDefinition(TileMapUtility::readAnimationFrames(properties, animation),
		                           TileMapUtility::readAnimationTimePerFrame(properties, animation),
		                           TileMapUtility::readAnimationNbLoops(properties, animation));
	}

	const Color TileMapUtility::readColor(const PropertyMap &properties) {
		PropertyMap::const_iterator found = properties.find("color");

		if (found != properties.end()) {
			return Color(found->second);

		} else {
			return Color::WHITE;
		}
	}
}
