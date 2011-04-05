#ifndef RB_QT_KEYBOARD_H
#define RB_QT_KEYBOARD_H

#include "PlatformFlagger.h"

#ifdef RB_QT

#include "Keyboard.h"
#include <QWidget>
#include <map>
#include <vector>
#include "Key.h"

namespace RedBox {
	class QtKeyboard : public QWidget, public Keyboard {
		Q_OBJECT
		friend class InputManager;
	public:
		static void setParentWidget(QWidget* parent);
	protected:
		QtKeyboard(QWidget* parent = 0);
		~QtKeyboard();
		void updateDevice();
		void keyPressEvent(QKeyEvent* e);
		void keyReleaseEvent(QKeyEvent* e);
	private:
		static QtKeyboard* instance;
		std::vector<bool> qtKeys;
		std::map<int, Key::Enum> mappings;
		void fillMappings();
		Key::Enum getMapping(int qtKey) const;
	};
}

#endif

#endif
