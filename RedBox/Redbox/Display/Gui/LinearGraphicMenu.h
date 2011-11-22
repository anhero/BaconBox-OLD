/**
 * @file
 * @ingroup GUI
 */

#ifndef RB_LINEARGRAPHICMENU_H
#define RB_LINEARGRAPHICMENU_H

#include "Menu.h"

namespace RedBox{
	/** 
	 * A LinearGraphicMenu is a menu that render its elements as 
     * a straight angle line (vertical or horizontal) of GraphicMenuElement.
     * @ingroup GUI
     */
	class LinearGraphicMenu : public Menu{
	public:
        enum Layout{Horizontal, Vertical};
        
        LinearGraphicMenu();
        LinearGraphicMenu(Layout layout);
        
        /**
         * Set the layout (Horizontal or Vertical) 
         * of the menu.
         */
        void setLayout(Layout layout);
        
        void update();
        
        virtual void addElement(MenuElement* newElement);
        
        

        
	private:
        
        
        /**
         * Update the position of each MenuElement according to the first menu element.
         */
        void updateElementPosition();
        
        
        
        ///Layout (Horizontal or Vertical) of the menu
        Layout layout;
        
        Vector2 elementOffset;
        

	};
}

#endif
