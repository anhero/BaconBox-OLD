/**
 * @file
 * @ingroup GUI
 */

#ifndef SCROLLINGMENU_H
#define SCROLLINGMENU_H

#include "SelectingMenu.h"
namespace RedBox {
	/** 
	 * A normal implementation of a SelectingMenu which has a beginning and a end. 
     * @ingroup GUI
     */
	class ScrollingMenu : public SelectingMenu{
	public:
		/**
		 * Default constructor.
		 */
		ScrollingMenu();
		/**
		 * Parametrized constructor. Loads the menu with a specific size.
		 * @param width The width of the menu.
		 * @param height The height of the menu.
		 * @param spacing The spacing between the middle of two elements in the 
		 * menu.
		 */
		ScrollingMenu(float realWidth, float realHeight, float spacing);
		/**
		 * Cloner.
		 * @return a copy of the menu.
		 */
		ScrollingMenu* clone() const;

		/**
		 * Adds an element to the menu.
		 * @param newElement The element to be added.
		 */
		void addElement(IMenuElement* newElement);
		/**
		 * Goes to a specific element in the menu.
		 */
		void scrollTo(std::list<IMenuElement *>::iterator dest, bool force);
		
	protected:
		/**
		 * Updates the element's position and their visibility.
		 */
		void updateElementsPosition();
	};
}

#endif
