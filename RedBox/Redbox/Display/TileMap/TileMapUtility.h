/**
 * @file
 * @ingroup TileMap
 */
#ifndef RB_TILE_MAP_UTILITY_H
#define RB_TILE_MAP_UTILITY_H

#include <string>
#include <vector>

#include "PropertyMap.h"
#include "Vector2.h"
#include "FrameDetails.h"
#include "AnimationDefinition.h"
#include "Color.h"
#include "FrameArray.h"

namespace RedBox {
	class Collidable;

	/**
	 * Contains utility functions for the tile map system.
	 * @ingroup TileMap
	 */
	class TileMapUtility {
	public:
		/**
		 * Name of the property that contains the name about the default
		 * animation.
		 */
		static const std::string DEFAULT_ANIMATION_NAME;

		/**
		 * Name of the property that contains the index of the default frame.
		 */
		static const std::string DEFAULT_FRAME_NAME;

		/// Value to use by default if the default frame is not specified.
		static const unsigned int DEFAULT_FRAME = 0u;

		/**
		 * Loads a collidable's attributes from properties. See the
		 * tiled_properties.pdf for more information about the properties read.
		 * @param properties Properties to use to load the collidable.
		 * @param collidable Reference to the collidable in which to load the
		 * attributes.
		 */
		static void loadCollidableFromProperties(const PropertyMap &properties,
		                                         Collidable &collidable);

		/**
		 * Reads the frame's position in a texture from the property map.
		 * @param properties Properties to use to read the frame position.
		 * @return Position of the frame in the texture. Properties not found
		 * default to 0.0f.
		 */
		static const Vector2 readFramePosition(const PropertyMap &properties);

		/**
		 * Reads the frame's position in a texture from the property map.
		 * @param properties Properties to use to read the frame position.
		 * @param index Index of the frame to read.
		 * @return Position of the frame in the texture. Properties not found
		 * default to 0.0f.
		 */
		static const Vector2 readFramePosition(const PropertyMap &properties,
		                                       unsigned int index);

		/**
		 * Reads the texture key from the property map.
		 * @param properties Properties to use to read the texture key.
		 * @return String containing the key of the texture.
		 */
		static const std::string readTextureKey(const PropertyMap &properties);

		/**
		 * Reads the frame orientation from a property map.
		 * @param properties Properties to use to read the frame orientation.
		 * @return Orientation of the frame.
		 */
		static FrameDetails::Orientation readFrameOrientation(const PropertyMap &properties);

		/**
		 * Reads the frame orientation from a property map.
		 * @param properties Properties to use to read the frame orientation.
		 * @param index Index of the frame to read.
		 * @return Orientation of the frame.
		 */
		static FrameDetails::Orientation readFrameOrientation(const PropertyMap &properties,
		                                                      unsigned int index);

		/**
		 * Reads the frame details from a property map.
		 * @param properties Properties to use to read the frame details.
		 * @return Frame details.
		 */
		static const FrameDetails readFrame(const PropertyMap &properties);

		/**
		 * Reads the frame details from a property map.
		 * @param properties Properties to use to read the frame details.
		 * @param index Index of the frame to read.
		 * @return Frame details.
		 */
		static const FrameDetails readFrame(const PropertyMap &properties,
		                                    unsigned int index);
		
		/**
		 * Reads the frames from a property map.
		 * @param properties Properties to use to read the frame details.
		 * @param outputArray Array of frame details to output to.
		 */
		static void readFrames(const PropertyMap &properties,
							   FrameArray &outputArray);

		/**
		 * Reads the number of times an animation should loop from a property
		 * map.
		 * @param properties Properties to use to read the animation details.
		 * @param animationName Name of the animation to read.
		 * @return Number of times the animation should loop.
		 */
		static int readAnimationNbLoops(const PropertyMap &properties,
		                                const std::string &animationName);

		/**
		 * Reads the time per frame for an animation from a property map.
		 * @param properties Properties to use to read the animation details.
		 * @param animationName Name of the animation to read.
		 * @return Number of the animation should loop.
		 */
		static double readAnimationTimePerFrame(const PropertyMap &properties,
		                                        const std::string &animationName);

		/**
		 * Reads the frame indexes for an animation from a property map.
		 * @param properties Properties to use to read the animation details.
		 * @param animationName Name of the animation to read.
		 * @return Vector containing the animation's frame indexes.
		 */
		static const std::vector<unsigned int> readAnimationFrames(const PropertyMap &properties,
		                                                           const std::string &animationName);

		/**
		 * Reads the animation from a property map.
		 * @param properties Properties to use to read the animation details.
		 * @param animationName Name of the animation to read.
		 * @return Animation definition.
		 */
		static const AnimationDefinition readAnimation(const PropertyMap &properties,
		                                               const std::string &animation);
		
		/**
		 * Reads the animations from a property map.
		 * @param properties Properties to use to read the animations.
		 * @param animations Animation map to contain the details about the
		 * animations found.
		 */
		void readAnimations(const PropertyMap &properties,
							AnimationMap &animations);

		/**
		 * Reads the color from a tile map object's properties.
		 * @param properties Properties to read the color from.
		 * @return Color found in the properties. White if no color property is
		 * found or if the color string is invalid.
		 */
		static const Color readColor(const PropertyMap &properties);
	private:
		/**
		 * Private undefined default constructor.
		 */
		TileMapUtility();
	};

	template <typename T, bool CALL>
	struct CallLoadCollidable {
		void operator()(const PropertyMap &, T &) const {
		}
	};

	template <typename T>
	struct CallLoadCollidable<T, true> {
		void operator()(const PropertyMap &properties, T &collidable) const {
			TileMapUtility::loadCollidableFromProperties(properties, collidable);
		}
	};
}

#endif