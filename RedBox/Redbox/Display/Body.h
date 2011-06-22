/**
 * @file
 * @ingroup Display
 */
#ifndef RB_BODY_H
#define RB_BODY_H

#include "Object.h"
#include "Vec2.h"

namespace RedBox {
	/**
	 * Basic body a state can have. Has neither a position, a size nor any
	 * graphical information.
	 * @ingroup Display
	 */
	class Body : public Object {
	public:
		/**
		 * Default constructor.
		 */
		Body();

		/**
		 * Copy constructor.
		 * @param src Body to make a copy of.
		 */
		Body(const Body& src);

		/**
		 * Destructor.
		 */
		virtual ~Body();

		/**
		 * Assignation operator overload.
		 * @param src Body to make a copy of.
		 * @return Reference to the modified body.
		 */
		Body& operator=(const Body& src);

		/**
		 * Checks if the body is active. An inactive body will not be updated.
		 * @return True if the body is active, false if not.
		 * @see RedBox::Body::active
		 */
		bool isActive() const;

		/**
		 * Sets if the body is active or not. An inactive body will not be
		 * updated.
		 * @param newActive New value for the active flag.
		 * @see RedBox::Body::active
		 */
		void setActive(bool newActive);

		/**
		 * Checks if the body is visible. An invisible body is simply not
		 * rendered.
		 * @return True if the body is visible, false if not.
		 * @see RedBox::Body::visible
		 */
		bool isVisible() const;

		/**
		 * Sets if the body is visible or not. An invisible body is simply not
		 * rendered.
		 * @param newVisible New value for visible flag.
		 * @see RedBox::Body::visible
		 */
		void setVisible(bool newVisible);

		/**
		 * Checks if the body is enabled. A disabled body will neither be
		 * updated nor rendered.
		 * @return True if the body is enabled, false if not.
		 * @see RedBox::Body::enabled
		 */
		bool isEnabled() const;

		/**
		 * Sets if the body is enabled or not. A disabled body will neither be
		 * updated nor rendered.
		 * @param newEnabled New value for the enabled flag.
		 * @see RedBox::Body::enabled
		 */
		void setEnabled(bool newEnabled);

		/**
		 * Updates the body.
		 */
		virtual void update() = 0;

		/**
		 * Renders the body.
		 */
		virtual void render() = 0;
	private:
		/**
		 * If set to true, the body is updated by its container (like a state).
		 * If set to false, the body won't be updated.
		 */
		bool active;

		/**
		 * If set to true, the body is rendered by its container (like a state).
		 * If set to false, the body won't be rendered.
		 */
		bool visible;

		/**
		 * If set to true, the body is updated (only if the body is also active)
		 * and rendered (only if the body is also visible). If set to false, the
		 * body will neither be updated nor rendered, regardless if it's active
		 * or not and visible or not.
		 */
		bool enabled;
	};
}

#endif
