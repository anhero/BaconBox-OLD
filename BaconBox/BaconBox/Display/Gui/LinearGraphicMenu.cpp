#include "BaconBox/Display/Gui/LinearGraphicMenu.h"

namespace BaconBox {
	LinearGraphicMenu::LinearGraphicMenu() : Menu(), needPositionUpdate(false), layout(Horizontal) {
	}

	LinearGraphicMenu::LinearGraphicMenu(Layout newLayout) : Menu(),
		needPositionUpdate(true), layout(newLayout) {
	}

	void LinearGraphicMenu::setLayout(Layout layout) {
		this->layout = layout;
	}

	void LinearGraphicMenu::render() {
		if (needPositionUpdate) {
			needPositionUpdate = false;
			updateElementPosition();
		}

		this->Menu::render();
	}

	LinearGraphicMenu::Layout LinearGraphicMenu::getLayout() const {
		return layout;
	}

	void LinearGraphicMenu::updateElementPosition() {
		std::list<MenuElement *>::iterator i = menuElements.begin();
		std::list<MenuElement *>::iterator previousElement = i;
		(*i)->setPosition(this->getPosition() + elementOffset + (*i)->getOffset());
		++i;

		while (i != menuElements.end()) {
			(*i)->setPosition((*previousElement)->getPosition() - (*previousElement)->getOffset() + (*i)->getOffset());

			if (layout == Horizontal) {
				(*i)->moveX((*previousElement)->getWidth() + elementSpacing);

			} else {
				(*i)->moveY((*previousElement)->getHeight() + elementSpacing);
			}

			previousElement = i;

			++i;
		}
	}

	void LinearGraphicMenu::addElement(MenuElement *newElement) {
		this->Menu::addElement(newElement);
		needPositionUpdate = true;
	}

}
