/**
 * @file
 * @ingroup Input
 */
#ifndef RB_IOS_POINTER_H
#define RB_IOS_POINTER_H

#include "PlatformFlagger.h"

#ifdef RB_IPHONE_PLATFORM

#include <Foundation/Foundation.h>
#include <UIKit/UITouch.h>
#include <UIKit/UIEvent.h>

#include "Pointer.h"
#include "sigly.h"

namespace RedBox {
	/**
	 * Implementation for the touch input for iOS.
	 * @ingroup Input
	 */
	class IOSPointer : public Pointer, public sigly::HasSlots<> {
		friend class InputManager;
		friend class sigly::Signal2<NSSet*, UIEvent*>;
	public:
		/// Signal sent by EAGLView when a touch begins.
		static sigly::Signal2<NSSet*, UIEvent*> touchBegin;
		/// Signal sent by EAGLView when a touch ends.
		static sigly::Signal2<NSSet*, UIEvent*> touchEnd;
		/// Signal sent by EAGLView when a touch moves.
		static sigly::Signal2<NSSet*, UIEvent*> touchMove;
	protected:
		/**
		 * Default constructor.
		 */
		IOSPointer();
		/**
		 * Destructor.
		 */
		~IOSPointer();
		/**
		 * Updates the input device information.
		 */
		void updateDevice();
	private:
		/// Temporary position for ios' event handling.
		Vec2 iosPosition;
		/// Temporary button state for ios' event handling.
		bool isTouchDown;
		/**
		 * Called when EAGLView gets a touchesBegan event.
		 */
		void onTouchBegin(NSSet* touches, UIEvent* event);
		/**
		 * Called when EAGLView gets a touchesEnded event.
		 */
		void onTouchEnd(NSSet* touches, UIEvent* event);
		/**
		 * Called when EAGLView gets a touchesMoved event.
		 */
		void onTouchMove(NSSet* touches, UIEvent* event);
	};
}

#endif

#endif
