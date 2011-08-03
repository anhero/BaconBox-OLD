/**
 * @file
 * @ingroup GUI
 */
#ifndef RB_IBUTTON_H
#define RB_IBUTTON_H

#include <sigly.h>

#include "GraphicBody.h"
#include "ButtonState.h"

namespace RedBox {
	/**
	 * Interface class for all button implementations. This class is abstract.
	 * When writing a
	 * @ingroup GUI
	 */
	class IButton : public GraphicBody {
	public:
		/// Signal sent when the button is clicked.
		sigly::Signal0<> click;

		/// Signal sent when the cursor starts hovering the button.
		sigly::Signal0<> hover;

		/**
		 * Default constructor.
		 */
		IButton();

		/**
		 * Copy constructor.
		 * @param src IButton to make a copy of.
		 */
		IButton(const IButton& src);

		/**
		 * Destructor.
		 */
		virtual ~IButton();

		/**
		 * Assignment operator overload.
		 * @param src IButton to make a copy of.
		 * @return Reference to the modified IButton.
		 */
		IButton& operator=(const IButton& src);

		/**
		 * Updates the button. Detects the clicks on the control.
		 */
		virtual void update();

		/**
		 * Gets the button's state.
		 * @return Button's current state.
		 * @see RedBox::IButton::state
		 */
		ButtonState getState() const;

	protected:
		/**
		 * Called when a pointer button press is detected while the cursor is
		 * over the button.
		 */
		virtual void onPress() = 0;

		/**
		 * Called when a pointer button hold is detected while the cursor is
		 * over the button.
		 */
		virtual void onHold() = 0;

		/**
		 * Called when a pointer button release is detected while the cursor is
		 * over the button and that the button press was also on the same
		 * button.
		 */
		virtual void onRelease() = 0;

		/**
		 * Called when the button is up and the cursor hovers the button.
		 */
		virtual void onEnter() = 0;

		/**
		 * Called when the button is up and the cursor leaves the button.
		 */
		virtual void onLeave() = 0;

	private:
		/// Button's current state.
		ButtonState state;

		/**
		 * Boolean value used when the button is pressed and the cursor leaves
		 * the button.
		 */
		bool tmpHold;
	};
}

#endif
