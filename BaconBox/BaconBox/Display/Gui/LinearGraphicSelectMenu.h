/**
 * @file
 * @ingroup GUI
 */
#ifndef RB_DRAGGABLE_MENU_H
#define RB_DRAGGABLE_MENU_H

#include "BaconBox/Display/Gui/PersistentSelectionMenu.h"
#include "BaconBox/Display/Gui/LinearGraphicMenu.h"
#include "BaconBox/Display/Gui/GraphicMenuElement.h"

namespace BaconBox {
	/**
	 * @ingroup GUI
	 */
	class LinearGraphicSelectMenu : public PersistentSelectionMenu<LinearGraphicMenu> {
	public:

		LinearGraphicSelectMenu(GraphicMenuElement *newSelector,
		                        LinearGraphicMenu::Layout layout = Horizontal,
		                        float selectingTolerance = 0.5f);

		void render();

		void setSelectingTolerance(float selectingTolerance);

		void move(float xDelta, float yDelta);

		using PersistentSelectionMenu<LinearGraphicMenu>::selectAnElement;
		
		void selectAnElement(std::list<MenuElement *>::iterator elementIterator);
	protected:
		void onPress(const Vector2 &position);

		void onRelease(const Vector2 &position, bool onMenu);

		void onHover(const Vector2 &position);

		void onHeld(const Vector2 &position, bool onMenu);
	private:
		GraphicMenuElement *selector;

		Vector2 lastClickPosition;

		float selectingTolerance;
	};
}


#endif
