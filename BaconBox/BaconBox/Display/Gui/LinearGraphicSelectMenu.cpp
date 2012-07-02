#include "LinearGraphicSelectMenu.h"

namespace BaconBox {
	LinearGraphicSelectMenu::LinearGraphicSelectMenu(GraphicMenuElement *newSelector,
													 LinearGraphicMenu::Layout layout,
													 float selectingTolerance) :
		PersistentSelectionMenu<LinearGraphicMenu>(), selector(newSelector),
		selectingTolerance(selectingTolerance) {
		this->selector = selector;
		this->setLayout(layout);
	}

	void LinearGraphicSelectMenu::setSelectingTolerance(float selectingTolerance) {
		this->selectingTolerance = selectingTolerance;
	}


	void LinearGraphicSelectMenu::onPress(const Vector2 &position) {
		lastClickPosition = position;
	}

	void LinearGraphicSelectMenu::onRelease(const Vector2 &position, bool onMenu) {
		if (onMenu) {
			for (std::list<MenuElement *>::iterator i = menuElements.begin(); i != menuElements.end(); i++) {
				Vector2 temp = lastClickPosition - position;

				if (temp.getLength() < selectingTolerance) {
					if ((*i)->getAxisAlignedBoundingBox().overlaps(position)) {
						selectAnElement(i);
					}
				}
			}
		}

	}

	void LinearGraphicSelectMenu::selectAnElement(std::list<MenuElement *>::iterator elementIterator) {
		this->PersistentSelectionMenu<LinearGraphicMenu>::selectAnElement(elementIterator);
		if (getSelected()) {
			this->selector->setPosition(getSelected()->getPosition() - getSelected()->getOffset() + this->selector->getOffset());
		}
	}


	void LinearGraphicSelectMenu::move(float xDelta, float yDelta) {
		selector->move(xDelta, yDelta);
		Menu::move(xDelta, yDelta);
	}

	void LinearGraphicSelectMenu::onHover(const Vector2 &) {
	}

	void LinearGraphicSelectMenu::onHeld(const Vector2 &, bool) {
	}



	void LinearGraphicSelectMenu::render() {
		PersistentSelectionMenu<LinearGraphicMenu>::render();
		if (getSelected()) {
			this->selector->render();
		}

	}
}
