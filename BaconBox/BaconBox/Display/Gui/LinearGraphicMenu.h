/**
 * @file
 * @ingroup GUI
 */
#ifndef RB_LINEARGRAPHICMENU_H
#define RB_LINEARGRAPHICMENU_H

#include "BaconBox/Display/Gui/Menu.h"

namespace BaconBox {
	/**
	 * A LinearGraphicMenu is a menu that render its elements as
	 * a straight angle line (vertical or horizontal) of GraphicMenuElement.
	 * @ingroup GUI
	 */
	class LinearGraphicMenu : public Menu {
	public:
		enum Layout {
		    Horizontal,
		    Vertical
		};

		LinearGraphicMenu();

		LinearGraphicMenu(Layout layout);


		Layout getLayout() const;

		/**
		 * Set the layout (Horizontal or Vertical)
		 * of the menu.
		 */
		void setLayout(Layout layout);

		virtual void addElement(MenuElement *newElement);

		virtual void render();
	private:
		/**
		 * Update the position of each MenuElement according to the first menu element.
		 */
		void updateElementPosition();


		bool needPositionUpdate;
		///Layout (Horizontal or Vertical) of the menu

		Layout layout;

		Vector2 elementOffset;
	};
}

#endif
