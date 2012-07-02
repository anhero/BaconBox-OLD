/**
 * @file
 * @ingroup Input
 */
#ifndef RB_QT_KEYBOARD_H
#define RB_QT_KEYBOARD_H

#include "BaconBox/PlatformFlagger.h"

#ifdef RB_QT

#include "BaconBox/Input/Keyboard/Keyboard.h"
#include <QWidget>
#include <map>
#include <vector>
#include "BaconBox/Input/Keyboard/Key.h"

namespace BaconBox {
	/**
	 * Keyboard input implementation for Qt.
	 * @ingroup Input
	 */
	class QtKeyboard : public QWidget, public Keyboard {
		Q_OBJECT
		friend class InputManager;
	public:
		/**
		 * Used to make the keyboard receive input events.
		 * @param Pointer to the keyboard's parent widget.
		 */
		static void setParentWidget(QWidget* parent);
	protected:
		/**
		 * Constructor.
		 * @param Pointer to the parent widget.
		 */
		QtKeyboard(QWidget* parent = 0);
		/**
		 * Destructor.
		 */
		~QtKeyboard();
		/**
		 * Updates the keyboard. Updates the keyboard's keys' state from
		 * the qtKeys member.
		 */
		void updateDevice();
		/**
		 * Called by Qt when a key is pressed (includes key holding).
		 * @param e Pointer to the event information for the key press.
		 */
		void keyPressEvent(QKeyEvent* e);
		/**
		 * Called by Qt when a key is released.
		 * @param e Pointer to the event information for the key release.
		 */
		void keyReleaseEvent(QKeyEvent* e);
	private:
		/**
		 * Singleton instance for the keyboard. Qt cannot have more than one
		 * keyboard input simultaneously.
		 */
		static QtKeyboard* instance;
		/// Temporary keyboard's keys' state for Qt events.
		std::vector<bool> qtKeys;
		/// Mappings for Qt's key codes with BaconBox's key codes.
		std::map<int, Key::Enum> mappings;
		/**
		 * Fills the key code mappings.
		 */
		void fillMappings();
		/**
		 * Gets BaconBox's equivalent key code for a Qt key code.
		 * @param qtKey Qt key code to get its equivalent.
		 * @return BaconBox key code for the corresponding Qt key code. Returns
		 * Key::INVALID for non-existent mappings.
		 */
		Key::Enum getMapping(int qtKey) const;
	};
}

#endif

#endif
