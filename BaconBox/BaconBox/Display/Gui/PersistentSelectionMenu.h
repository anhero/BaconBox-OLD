/**
 * @file
 * @ingroup GUI
 */

#ifndef RB_PERSISTENTSELECTIONMENU_H
#define RB_PERSISTENTSELECTIONMENU_H

#include "Menu.h"
#include "sigly.h"
namespace BaconBox {
	/**
	 * Abstract class implementing common functions of Persistent Selection Menu.
	 * PersistentSelectionMenu's elements won't act as buttons. 1 or 0 element can
	 * be selected. (Example of use: Radio box selection).
	 * @ingroup GUI
	 */
	template <typename Parent>
	class PersistentSelectionMenu : public Parent {
	public:

		sigly::Signal1<const std::string &> selectingAnElement;



		/**
		 * Default constructor
		 */
		PersistentSelectionMenu(): Parent(), selectingAnElement(),
			selectedElementIterator(this->Parent::menuElements.begin()),
			selectionIsActive(false) {
		}


		/**
		 * Returns a pointer to the currently selected menu element.
		 * @return a pointer to the currently selected menu element.
		 * or NULL if no element is selected.
		 */
		MenuElement *getSelected() {
			if (selectionIsActive) {
				return *selectedElementIterator;

			} else {
				return NULL;
			}
		}

		/**
		 * Returns the key of the currently selected element.
		 * @return Return the Key of the currently selected menu element.
		 * or an empty string if no item is selected.
		 */
		const std::string getSelectedKey() {
			if (selectionIsActive) {
				return (*selectedElementIterator)->getKey();

			} else {
				return "";
			}

		}

		virtual void addElement(MenuElement *newElement) {
			this->Parent::addElement(newElement);
			clearSelection();
		}

		void selectFirstElement() {
			selectAnElement(this->Parent::menuElements.begin());
		}


		virtual void selectAnElement(std::list<MenuElement *>::iterator elementIterator) {
			selectedElementIterator = elementIterator;
			selectionIsActive = true;
			selectingAnElement((*selectedElementIterator)->getKey());
		}

		/**
		 * Select the next menu element.
		 * If no element is selected it will select the first one.
		 * The selection won't loop, if it's the last element, the
		 * selection will stay on the last element.
		 */
		void selectNextElement() {
			if (selectionIsActive) {
				selectedElementIterator++;
				//Calling select an element this way won't change the iterator, since we
				//we change it with the ++ operator, but it give inheriting menu the oportunity
				//of overloading the selecting behavior without having to overload every selecting function
				//(only the selectAnElement function).
				selectAnElement(selectedElementIterator);

				if (selectedElementIterator == this->Parent::menuElements.end()) {
					selectedElementIterator--;
					//Calling selectAnElement this way won't change the iterator, since we
					//we change it with the -- operator, but it give inheriting menu the oportunity
					//of overloading the selecting behavior without having to overload every selecting function
					//(only the selectAnElement function).
					selectAnElement(selectedElementIterator);
				}

			} else {
				selectFirstElement();
			}
		}

		/**
		 * Select the previous menu element.
		 * If No element is selected it will select the first one.
		 * The selection won't loop, if it's the first element, the
		 * selection will stay on the first element.
		 */
		void selectPreviousElement() {
			if (selectionIsActive) {
				if (selectedElementIterator != this->Parent::menuElements.begin()) {
					selectedElementIterator--;
					//Calling selectAnElement this way won't change the iterator, since we
					//we change it with the -- operator, but it give inheriting menu the oportunity
					//of overloading the selecting behavior without having to overload every selecting function
					//(only the selectAnElement function).
					selectAnElement(selectedElementIterator);
				}

			} else {
				selectFirstElement();
			}
		}

		/**
		 * Unselect the selected element.
		 */
		virtual void clearSelection() {
			selectionIsActive = false;
			selectedElementIterator = this->Parent::menuElements.end();
		}

	protected:
		///Iterator pointing to the currently selected element.
		std::list<MenuElement *>::iterator selectedElementIterator;

		/**
		 * True if the menu have a selected menu element,
		 * false otherwise.
		 */
		bool selectionIsActive;
	};
}

#endif
