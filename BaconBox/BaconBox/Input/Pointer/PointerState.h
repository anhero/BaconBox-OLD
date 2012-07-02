/**
 * @file
 * @ingroup Input
 */
#ifndef RB_POINTER_STATE_H
#define RB_POINTER_STATE_H

#include <vector>

#include "BaconBox/Input/InputState.h"
#include "BaconBox/Input/Pointer/CursorState.h"

namespace BaconBox {
	/**
	 * Represents the current state of a pointing device.
	 * @ingroup Input
	 */
	class PointerState : public InputState {
		friend class Pointer;
	public:
		/// Default number of cursors a pointer's state has.
		static const unsigned int DEFAULT_NB_CURSORS = 1;

		/**
		 * Parameterizable default constructor.
		 * @param nbCursors Number of cursors the pointing device(s) can
		 * support.
		 */
		PointerState(unsigned int nbCursors = DEFAULT_NB_CURSORS);

		/**
		 * Destructor.
		 */
		~PointerState();

		/**
		 * Gets the state of a cursor.
		 * @param index Index of the cursor's state to get.
		 */
		const CursorState& getCursorState(unsigned int index = 0) const;
	private:
		/// Cursors' states.
		std::vector<CursorState> cursors;

		/**
		 * Gets a cursor's position.
		 * @param index Index of the cursor to get.
		 * @return Reference to the cursor's position.
		 */
		Vector2& getCursorPosition(unsigned int index);

		/**
		 * Gets a cursor's previous position.
		 * @param index Index of the cursor to get.
		 * @return Reference to the cursor's previous position.
		 */
		Vector2& getCursorPreviousPosition(unsigned int index);

		/**
		 * Gets a cursor's buttons.
		 * @param index Index of the cursor to get.
		 * @return Reference to the cursor's buttons.
		 */
		std::vector<bool>& getCursorButtons(unsigned int index);

		/**
		 * Gets a cursor's previous buttons.
		 * @param index Index of the cursor to get.
		 * @return Reference to the cursor's previous buttons.
		 */
		std::vector<bool>& getCursorPreviousButtons(unsigned int index);
	};
}

#endif
