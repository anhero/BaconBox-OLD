/**
 * @file
 * @ingroup Display
 */
#ifndef RB_FRAME_LIST_H
#define RB_FRAME_LIST_H

#include <iostream>
#include <vector>

#include "Vector2.h"
#include "FrameDetails.h"

namespace RedBox {
	/**
	 * Contains information about the frames of a sprite in a texture atlas.
	 * Each frames must have the same size.
	 * @see RedBox::FrameDetails
	 * @see RedBox::TextureAtlas
	 * @ingroup Display
	 */
	struct FrameList {
		typedef std::vector<FrameDetails> FrameArray;

		/// Size of the frames (in pixels).
		Vector2 frameSize;

		/// Details of each frame (where to find them in the texture atlas).
		FrameArray frames;

		/**
		 * Default constructor.
		 */
		FrameList();

		/**
		 * Parameterized constructor.
		 * @param newFrameSize Size of the frames (in pixels).
		 * @param newFrames Array of frame details to use.
		 * @see RedBox::FrameList::frames
		 * @see RedBox::FrameList::frameSize
		 */
		explicit FrameList(const Vector2 &newFrameSize,
		                   const FrameArray &newFrames = FrameArray());

		/**
		 * Copy constructor.
		 * @param src FrameList to make a copy of.
		 */
		FrameList(const FrameList &src);

		/**
		 * Assignment operator overload.
		 * @param src FrameList to copy.
		 * @return Reference to the modified FrameList.
		 */
		FrameList &operator=(const FrameList &src);
	};

	std::ostream &operator<<(std::ostream &output, const FrameList &fl);
}

#endif
