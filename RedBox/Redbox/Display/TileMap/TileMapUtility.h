/**
 * @file
 * @ingroup TileMap
 */
#ifndef RB_TILE_MAP_UTILITY_H
#define RB_TILE_MAP_UTILITY_H

#include <string>

#include "PropertyMap.h"
#include "Vector2.h"
#include "FrameDetails.h"

namespace RedBox {
	class Collidable;

	/**
	 * Contains utility functions for the tile map system.
	 * @ingroup TileMap
	 */
	class TileMapUtility {
	public:
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
		 * Reads the frame details from a property map.
		 * @param properties Properties to use to read the frame details.
		 * @return Frame details.
		 */
		static const FrameDetails readFrame(const PropertyMap &properties);
	private:
		/**
		 * Private undefined default constructor.
		 */
		TileMapUtility();
	};

	template <typename T, typename U, bool CALL>
	struct CallLoadCollidable {
		void operator()(const PropertyMap &, T &) {
		}
	};

	template <typename T, typename U>
	struct CallLoadCollidable<T, U, true> {
		void operator()(const PropertyMap &properties, T &collidable) {
			TileMapUtility::loadCollidableFromProperties(properties, collidable);
		}
	};
}

#endif