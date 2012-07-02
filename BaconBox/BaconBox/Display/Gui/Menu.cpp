#include "BaconBox/Display/Gui/Menu.h"

#include "BaconBox/Engine.h"
#include "BaconBox/Input/Pointer/Pointer.h"


using namespace BaconBox;

Menu::Menu(): elementSpacing(0) {}

Menu::Menu(float spacing): elementSpacing(spacing) {}


void Menu::addElement(MenuElement *newElement) {
	menuElements.push_back(newElement);
}

void Menu::removeElements(MenuElement *menuElement) {
	menuElements.remove(menuElement);
}


void Menu::setSpacing(float spacing) {
	elementSpacing = spacing;
}


float Menu::getSpacing() {
	return elementSpacing;
}

void Menu::render() {
	for (std::list<MenuElement *>::iterator i = menuElements.begin(); i != menuElements.end(); i++) {
		(*i)->render();
	}
}

void Menu::update() {
	this->Collidable::update();
	
	for (std::list<MenuElement *>::iterator i = menuElements.begin(); i != menuElements.end(); i++) {
		(*i)->update();
	}

	Pointer *ptr = Pointer::getDefault();

	// We make sure the pointer is initialized.
	if (ptr) {
		if (this->getAxisAlignedBoundingBox().overlaps((isHud()) ? (ptr->getPosition()) : (Engine::getCurrentState()->getCamera().screenToWorld(ptr->getPosition())))) {
			if (ptr->isButtonPressed(CursorButton::LEFT)) {
				tmpHold = true;
				onPress(ptr->getPosition());

			} else if (tmpHold && ptr->isButtonHeld(CursorButton::LEFT)) {
				onHeld(ptr->getPosition(), true);

			} else if (tmpHold && ptr->isButtonReleased(CursorButton::LEFT)) {
				tmpHold = false;
				onRelease(ptr->getPosition(), true);

			} else {
				onHover(ptr->getPosition());
			}

		} else if (tmpHold) {
			if (ptr->isButtonReleased(CursorButton::LEFT)) {
				tmpHold = false;
				onRelease(ptr->getPosition(), false);

			} else if (ptr->isButtonHeld(CursorButton::LEFT)) {
				onHeld(ptr->getPosition(), false);
			}
		}


	}

}


void Menu::move(float xDelta, float yDelta) {
	this->Collidable::move(xDelta, yDelta);

	for (std::list<MenuElement *>::iterator i = menuElements.begin(); i != menuElements.end(); i++) {
		(*i)->move(xDelta, yDelta);
	}
}

float Menu::getWidth() const {
	std::list<MenuElement *>::const_iterator i = menuElements.begin();
	float temp = 0.0f;
	float min = (*i)->getXPosition();
	float max = (*i)->getXPosition() + (*i)->getWidth();
	i++;

	for (; i != menuElements.end(); i++) {
		temp = (*i)->getXPosition() + (*i)->getWidth();

		if (min > (*i)->getXPosition()) {
			min = (*i)->getXPosition();
		}

		if (max < temp) {
			max = temp;
		}
	}

	return max - min;
}

float Menu::getHeight() const {
	std::list<MenuElement *>::const_iterator i = menuElements.begin();
	float temp = 0.0f;
	float min = (*i)->getYPosition();
	float max = (*i)->getYPosition() + (*i)->getHeight();
	i++;

	for (; i != menuElements.end(); i++) {
		temp = (*i)->getYPosition() + (*i)->getHeight();

		if (min > (*i)->getYPosition()) {
			min = (*i)->getYPosition();
		}

		if (max < temp) {
			max = temp;
		}
	}

	return max - min;
}

Maskable *Menu::getMask() const {
	return renderMask;
}




void Menu::unmask() {
	for (std::list<MenuElement *>::iterator i = menuElements.begin(); i != menuElements.end(); i++) {
		(*i)->unmask();
	}
}

void Menu::mask() {
	for (std::list<MenuElement *>::iterator i = menuElements.begin(); i != menuElements.end(); i++) {
		(*i)->mask();
	}
}

void Menu::setMask(Maskable *newMask, bool inverted) {
	renderMask = newMask;

	for (std::list<MenuElement *>::iterator i = menuElements.begin(); i != menuElements.end(); i++) {
		(*i)->setMask(newMask, inverted);
	}
}

void Menu::onPress(const Vector2 &) {
}

void Menu::onRelease(const Vector2 &, bool) {
}

void Menu::onHover(const Vector2 &) {
}

void Menu::onHeld(const Vector2 &, bool) {
}
