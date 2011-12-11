/**
 * @file
 * @ingroup GUI
 */

#ifndef RB_MENU_H
#define RB_MENU_H

#include "MenuElement.h"
#include "Positionable.h"
#include "Transformable.h"
#include "Collidable.h"
#include "Layerable.h"
#include <vector>



namespace RedBox{
	/** 
     * Abstract menu interface defining functions that every menu should implements and implement 
     * and implement function that are common to every type of menu.
	 * @ingroup GUI
	 */
	class Menu : public Collidable, public Layerable {
	public:
        
        /**
         * Default constructor
         */
        Menu();
        
        /**
         * Parametrized constructor 
         * @param spacing Distance between each menu element.
         */
        Menu(float spacing);
        
        /**
         * Add the given menu element to the menu.
         */
        virtual void addElement(MenuElement* newElement);
        
        /**
         * Remove the given menu element from the menu.
         */
        virtual void removeElements(MenuElement* menuElement);
        
        /**
         * Set the distance between each menu element.
         */
        virtual void setSpacing(float spacing);
        
        /**
         * Return the distance between each menu element.
         */
        virtual float getSpacing();
    
        /**
         * Call the render function on it's MenuElement.
         */
        virtual void render();
        
        /**
         * Call the update function on it's MenuElement.
         */
        virtual void update();
        
        
        virtual void move(float xDelta, float yDelta);
        
        float getWidth() const;
        
        float getHeight() const;
        
        Maskable *getMask() const;
        
        void unmask();
        
        void mask();
        
        void setMask(Maskable *newMask, bool inverted = false);
        
	protected:
        ///Contain all the menu element for the current menu.
        std::list<MenuElement*> menuElements;
        
        ///Distance between each element.
        float elementSpacing;
        
        Maskable * renderMask;
        
        virtual void onPress(const Vector2 & position);
        
        virtual void onRelease(const Vector2 & position, bool onMenu);
        
        virtual void onHover(const Vector2 & position);
        
        virtual void onHeld(const Vector2 & position, bool onMenu);

        
        
    private:
        
		bool tmpHold;
        
	};
}

#endif
