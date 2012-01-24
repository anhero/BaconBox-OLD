/**
 * @file
 * @ingroup Display
 */
#ifndef RB_FRAME_DETAILS_H
#define RB_FRAME_DETAILS_H

#include "Vector2.h"
#include "SafeEnum.h"


namespace RedBox {
	/**
	 * Contains the details about a frame in a texture atlas.
	 * @see RedBox::FrameList
	 * @see RedBox::TextureAtlas
	 * @ingroup Display
	 */
	struct FrameDetails {
		struct OrientationDef {
			enum type {
			    NORTH,
			    SOUTH,
			    EAST,
			    WEST
			};
		};

		/// Used to specify the frame's orientation in the image.
		typedef SafeEnum<OrientationDef> Orientation;

		/// Position in the image (in pixels).
		Vector2 position;

		/**
		 * Orientation the image, used when the frame is rotated to save space
		 * when maximizing space in the texture. NORTH by default.
		 */
		Orientation orientation;

		/**
		 * Default constructor.
		 */
		FrameDetails();

		/**
		 * Parameterized constructor.
		 * @param newPosition Frame's position in the image (in pixels).
		 * @param newOrientation Frame's orientation in the image, NORTH by
		 * default.
		 * @see RedBox::FrameDetails::position
		 * @see RedBox::FrameDetails::orientation
		 */
		explicit FrameDetails(const Vector2 &newPosition,
		                      Orientation newOrientation = Orientation::NORTH);

		/**
		 * Copy constructor.
		 * @param src FrameDetails to make a copy of.
		 */
		FrameDetails(const FrameDetails &src);

		/**
		 * Assignment operator overload.
		 * @param src FrameDetails to copy.
		 * @return Reference to the modified FrameDetails.
		 */
		FrameDetails &operator=(const FrameDetails &src);
	};
}

#endif
