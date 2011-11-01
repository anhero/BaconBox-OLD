/**
 * @file
 * @ingroup GUI
 */

#ifndef LOOPINGMENU_H
#define LOOPINGMENU_H

#include "SelectingMenu.h"
namespace RedBox {
	/** 
	 * An implementation of a SelectingMenu which is looping. 
     * @ingroup GUI
     */
	class LoopingMenu : public SelectingMenu{
	public:
		/**
		 * Default constructor.
		 */
		LoopingMenu();
		/**
		 * Destructor.
		 */
		~LoopingMenu();
		/**
		 * Parametrized constructor. Loads the menu with a specific size.
		 * @param width The width of the menu.
		 * @param height The height of the menu.
		 * @param spacing The spacing between the middle of two elements in the 
		 * menu.
		 */
		LoopingMenu(float width, float height, float spacing);
		/**
		 * Cloner.
		 * @return a copy of the menu.
		 */
		SelectingMenu* clone() const;
		/**
		 * Renders the MenuElement.
		 */
		void render();
		/**
		 * Adds an element to the menu.
		 * @param newElement The element to be added.
		 */
		void addElement(IMenuElement*);
		
		void scrollTo(std::list<IMenuElement *>::iterator dest, bool force);
		
		void setElementAngle(float newAngle);
		/**
		 * Sets the internal mask, the one applied to the menu's elements.
		 * @param The internal mask.
		 */
		virtual void setInternalMask(GraphicElement<Transformable>* internalMask, bool inverted = false);
	protected:
		/*The list of the doubles in case the menu don't have enough elements
		 * to loop properly.
		 */
		std::list<IMenuElement*> fillingElements;
		/**
		 * Creates element's clones for the filling list.
		 */
		void generateFillingList();
		/**
		 * Updates the element's position and their visibility.
		 */
		void updateElementsPosition();
		/**
		 * Is called when a menu's element is triggered.
		 */
		virtual void onClick(RedBox::Vector2 ptr);
	};
}

#endif
