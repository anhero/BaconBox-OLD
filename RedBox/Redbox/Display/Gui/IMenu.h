/**
 * @file
 * @ingroup GUI
 */
#ifndef IMENU_H
#define IMENU_H


#include "IMenuElement.h"
#include "Layerable.h"
#include "Collidable.h"
namespace RedBox {
	/**
	 * Interface class for all Menu implementations.
	 * @ingroup GUI
	 */
	class IMenu : public Collidable, public Layerable{
public:
	/**
	 * Default constructor.
	 */
	IMenu();
	/**
	 * Virtual destructor.
	 */
	virtual ~IMenu();
	/**
	 * Copy constructor.
	 * @param src the Menu to make a copy of.
	 */
	IMenu(const IMenu &src);
	/**
	 * Adds an element to the menu.
	 * @param newElement The element to be added.
	 */
	virtual void addElement(IMenuElement* newElement);
	/**
	 * Removes an MenuElement from the Menu.
	 * @param toBeRemoved the element to be removed
	 */
	virtual void removeElement(IMenuElement* toBeRemoved);
	/**
	 * Gets the width of the menu.
	 */
	virtual float getWidth() const;
	/**
	 * Gets the height of the menu.
	 */
	virtual float getHeight() const;

	/**
	 * Renders the menu and its components.
	 */
	void render();
	/**
	 * Updates the menu and its components.
	 */
	void update();
protected:
	/**
	 * The screen width of the menu.
	 */
	float width;
	/**
	 * The height of the menu.
	 */
	float height;
	/**
	 * A list that contains all the menu's elements.
	 */
	std::list<IMenuElement*> elements;

};
}
#endif