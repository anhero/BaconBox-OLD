/**
 * @file
 * @ingroup Input
 */
#ifndef RB_IOS_POINTER_H
#define RB_IOS_POINTER_H

#include <Foundation/Foundation.h>
#include <UIKit/UITouch.h>
#include <UIKit/UIEvent.h>

#include <vector>
#include "BaconBox/Input/Pointer/Pointer.h"
#include <sigly.h>

namespace BaconBox {
	/**
	 * Implementation for the touch input for iOS.
	 * @ingroup Input
	 */
	class IOSPointer : public Pointer, public sigly::HasSlots<> {
		friend class InputManager;
		friend class sigly::Signal2<NSSet *, UIEvent *>;
	public:
		/// Signal sent by EAGLView when a touch begins.
		static sigly::Signal2<NSSet *, UIEvent *> touchBegin;
		
		/// Signal sent by EAGLView when a touch ends.
		static sigly::Signal2<NSSet *, UIEvent *> touchEnd;
		
		/// Signal sent by EAGLView when a touch moves.
		static sigly::Signal2<NSSet *, UIEvent *> touchMove;
		
		/// Signal sent by EAGLView when a touch is cancelled.
		static sigly::Signal2<NSSet *, UIEvent *> touchCancelled;
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
		/**
		 * Converts the position we receive to BaconBox's format.
		 * @param newIosPosition Pointer to the vector to set the BaconBox
		 * screen position.
		 */
		static void convertToBaconBoxScreenPosition(Vector2 *newIosPosition);

		/**
		 * Called when EAGLView gets a touchesBegan event.
		 */
		void onTouchBegin(NSSet *touches, UIEvent *event);

		/**
		 * Called when EAGLView gets a touchesEnded event.
		 */
		void onTouchEnd(NSSet *touches, UIEvent *event);

		/**
		 * Called when EAGLView gets a touchesMoved event.
		 */
		void onTouchMove(NSSet *touches, UIEvent *event);

		/**
		 * Called when EAGLView gets a touchesCancelled event.
		 */
		void onTouchCancelled(NSSet *touches, UIEvent *event);


		struct IOSTouch {
			IOSTouch(): touch(NULL), inContact(false), position(0.0f, 0.0f) {}
			///Pointer to the IOS touch object
			UITouch *touch;

			///Last known position for this touch event.
			Vector2 position;
			///True if the touch is currently happening, false if the touch is ended.
			bool inContact;
		};

		/**
		 * Add the given touch object and match it to a cursor.
		 * @return Return the matching cursor ID and -1 if it can't add the given touch object.
		 */
		int AddNewTouch(UITouch *touch);

		/**
		 * Return the matching cursor ID for the given touch object.
		 * @return The matching cursor ID or -1 if there is no matching cursor.
		 */
		int getTouchID(UITouch *touch);

		/**
		 * Used for multi touch tracking; it matches the touch object with their cursor ID.
		 * (The key of each object in the vector is the matching cursor ID.)
		 */
		std::vector<IOSTouch> touches;
	};
}

#endif

