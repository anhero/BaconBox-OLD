/**
 * @file
 * @ingroup Display
 */
#ifndef RB_FRAME_DETAILS_H
#define RB_FRAME_DETAILS_H

#include <iostream>
#include <string>

#include "Vector2.h"
#include "SafeEnum.h"
#include "Value.h"

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

		/**
		 * Checks whether or not the Value contains the necessary information
		 * to deserialize the type.
		 * @param node Value to check.
		 * @return True if the value contains the necessary information, false
		 * if not.
		 */
		static bool isValidValue(const Value &node);

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
		 * Reads the orientation from a string. "NORTH" corresponds to
		 * Orientation::NORTH, "SOUTH" corresponds to Orientation::SOUTH, etc.
		 * @param orientationString String containing the orientation.
		 */
		static Orientation stringToOrientation(const std::string &orientationString);
		
		/**
		 * Assignment operator overload.
		 * @param src FrameDetails to copy.
		 * @return Reference to the modified FrameDetails.
		 */
		FrameDetails &operator=(const FrameDetails &src);

		/**
		 * Serializes the frame details to a Value.
		 * @param node Value to serialize the frame details to.
		 * @param setName Wether or not we need to set the name.
		 */
		void serialize(Value &node, bool setName = true) const;

		/**
		 * Deserializes the frame details from a Value.
		 * @param node Node to read the frame details from. If it doesn't have
		 * an orientation attribute, it assumes it has a NORTH orientation.
		 * @return True if the deserialization was successful, false if not. If
		 * the deserialization failed, the output frame details are not
		 * modified.
		 */
		bool deserialize(const Value &node);
		
		/// Position in the image (in pixels).
		Vector2 position;
		
		/**
		 * Orientation the image, used when the frame is rotated to save space
		 * when maximizing space in the texture. NORTH by default.
		 */
		Orientation orientation;
	};

	std::ostream &operator<<(std::ostream &output, const FrameDetails &fd);
}

#endif
