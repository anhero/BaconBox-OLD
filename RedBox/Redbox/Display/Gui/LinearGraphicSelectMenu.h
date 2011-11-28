/**
 * @file
 * @ingroup GUI
 */
#ifndef RB_DRAGGABLE_MENU_H
#define RB_DRAGGABLE_MENU_H

#include "PersistentSelectionMenu.h"
#include "LinearGraphicMenu.h"
#include "GraphicMenuElement.h"

namespace RedBox {
	/**
	 * @ingroup GUI
	 */
	class LinearGraphicSelectMenu : public PersistentSelectionMenu<LinearGraphicMenu> {
	public:
        
        LinearGraphicSelectMenu(GraphicMenuElement * selector, LinearGraphicMenu::Layout layout = Horizontal, float selectingTolerance = 0.5f);
        
        void render();
        
        void clearSelection();
        
        void setSelectingTolerance(float selectingTolerance);
        
        void move(float xDelta, float yDelta);
        
        void selectAnElement(std::list<MenuElement*>::iterator elementIterator);
        
    protected:
        
        
        void onPress(const Vector2 & position);
        
        void onRelease(const Vector2 & position, bool onMenu);
        
        void onHover(const Vector2 & position);
        
        void onHeld(const Vector2 & position, bool onMenu);
        
        
        
    private:
        GraphicMenuElement * selector;
        
        Vector2 lastClickPosition;


        float selectingTolerance;
    };
}


#endif
