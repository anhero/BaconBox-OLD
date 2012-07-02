/**
 * @file
 * @ingroup Input
 */
#ifndef RB_QT_POINTER_H
#define RB_QT_POINTER_H

#include <QWidget>
#include <Qt>

#include <map>
#include <vector>

#include "BaconBox/Input/Pointer/Pointer.h"
#include "BaconBox/Vector2.h"

namespace BaconBox {
	/**
	 * Mouse input implementation for Qt.
	 * @ingroup Input
	 */
	class QtPointer : public QWidget, public Pointer {
		Q_OBJECT
		friend class InputManager;
	public:
		/**
		 * Used to make the mouse receive input events.
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
		 * Qt's mouse state.
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

#endif
