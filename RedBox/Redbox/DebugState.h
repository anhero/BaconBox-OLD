#if 0
/**
 * @file
 * @ingroup Debug
 */
#ifndef RB_DEBUG_STATE_H
#define RB_DEBUG_STATE_H

#include "State.h"
#include "PointerButtonSignalData.h"
#include "KeySignalData.h"
#include "Key.h"
#include "Vector2.h"

namespace RedBox {
	/**
	 * Used to help in debugging. Can be used to move graphic bodies and get
	 * their position.
	 * @ingroup Debug
	 */
	class DebugState : public State {
	public:
		/**
		 * Simple parameterized constructor and default constructor.
		 * @param newName Initial name to give to the state.
		 */
		DebugState(const std::string& newName = State::DEFAULT_NAME,
		           Key::Enum newDebugKey = Key::D0);

		/**
		 * Destructor.
		 */
		virtual ~DebugState();

	private:
		/// Pointer to the currently selected graphic body.
		GraphicBody* selectedBody;

		/// Cursor offset when the body was selected.
		Vector2 cursorOffset;

		/// Debug key used for printing the cursor's position.
		Key::Enum debugKey;

		/**
		 * Called when the state detects a pointer button press. It
		 * selects the graphic body that's the most on top that's under the
		 * cursor.
		 * @param data Pointer data.
		 */
		void onPointerButtonPress(PointerButtonSignalData data);
		void onPointerButtonHold(PointerButtonSignalData data);
		void onPointerButtonRelease(PointerButtonSignalData data);
		void onKeyRelease(KeySignalData data);
	};
}

#endif
#endif
