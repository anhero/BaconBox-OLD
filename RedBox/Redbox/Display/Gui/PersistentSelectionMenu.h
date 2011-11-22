/**
 * @file
 * @ingroup GUI
 */

#ifndef RB_PERSISTENTSELECTIONMENU_H
#define RB_PERSISTENTSELECTIONMENU_H

#include "Menu.h"

namespace RedBox{
	/** 
	 * Abstract class implementing common functions of Persistent Selection Menu. 
     * PersistentSelectionMenu's elements won't act as buttons. 1 or 0 element can
     * be selected. (Example of use: Radio box selection).
     * @ingroup GUI
     */
	template <typename Parent>
    class PersistentSelectionMenu : public Parent {
	public:
        
        /**
         * Default constructor
         */
        PersistentSelectionMenu(): selectedElementIterator(menuElements.begin()), 
        selectionIsActive(false){}
    
        /** 
         * Returns a pointer to the currently selected menu element.
         * @return a pointer to the currently selected menu element.
         * or NULL if no element is selected.
         */
        MenuElement * getSelected(){
            if (selectionIsActive) {
                return *selectedElementIterator;
            }
            else{
                return NULL;
            }
        }
        
        /** 
         * Returns the key of the currently selected element.
         * @return Return the Key of the currently selected menu element.
         * or an empty string if no item is selected.
         */
        const std::string getSelectedKey(){
            if (selectionIsActive) {
                return (*selectedElementIterator)->getKey();
            }
            else{
                return "";
            }
            
        }
        
        /**
         * Select the next menu element.
         * If no element is selected it will select the first one.
         * The selection won't loop, if it's the last element, the 
         * selection will stay on the last element.
         */
        void selectNextElement(){
            if(selectionIsActive){
                selectedElementIterator++;
                if (selectedElementIterator == menuElements.end()) {
                    selectedElementIterator--;
                }
            }
            else{
                selectedElementIterator = menuElements.begin();
                selectionIsActive = true;
            }
        }
        
        /**
         * Select the previous menu element.
         * If No element is selected it will select the first one.
         * The selection won't loop, if it's the first element, the 
         * selection will stay on the first element.
         */
        void selectPreviousElement(){
            if(selectionIsActive){
                if (selectedElementIterator != menuElements.begin()) {
                    selectedElementIterator--;
                }
            }
            else{
                selectedElementIterator = menuElements.begin();
                selectionIsActive = true;
            }
        }
        
        /**
         * Unselect the selected element.
         */
        void clearSelection(){
            selectionIsActive = false;
        }

	protected:
        ///Iterator pointing to the currently selected element.
        std::list<MenuElement*>::iterator selectedElementIterator;
        
        /**
         * True if the menu have a selected menu element, 
         * false otherwise.
         */
        bool selectionIsActive;
	};
}

#endif
