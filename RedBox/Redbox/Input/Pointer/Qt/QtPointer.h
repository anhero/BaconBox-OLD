/**
 * @file
 * @ingroup Input
 */
#ifndef RB_QT_POINTER_H
#define RB_QT_POINTER_H

#include "PlatformFlagger.h"

#ifdef RB_QT

#include <QWidget>
#include <Qt>

#include <map>
#include <vector>

#include "Pointer.h"
#include "Vec2.h"

namespace RedBox {
	/**
	 * Mouse input implementation for Qt.
	 * @ingroup Input
	 */
	class QtPointer : public QWidget, public Pointer {
		Q_OBJECT
		friend class InputManager;
	public:
		/**
		 * Used to make the mouse recieve input events.
		 * @param Pointer to the mouse's parent widget.
		 */
		static void setParentWidget(QWidget* parent);
	protected:
		/**
		 * Constructor.
		 * @param Pointer to the parent widget.
		 */
		QtPointer(QWidget* parent = 0);
		/**
		 * Destructor.
		 */
		~QtPointer();

		/**
		 * Updates the pointer. Updates the pointer's buttons' state from
		 * the qtButtons member.
		 */
		void updateDevice();

	private:

		/**
		 * Singleton instance for the pointer. Qt cannot have more than one
		 * mouse input simultaneously.
		 */
		static QtPointer* instance;
	};
}

#endif // RB_QT
#endif
