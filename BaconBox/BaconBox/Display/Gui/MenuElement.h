/**
 * @file
 * @ingroup GUI
 */

#ifndef RB_MENUELEMENT_H
#define RB_MENUELEMENT_H

#include <string>

#include "BaconBox/Display/Maskable.h"
#include "BaconBox/Display/Collidable.h"

namespace BaconBox{
	/** 
     * Represent a selectable/clickable option/element in a menu.
     * Ex. A menu that let you select a gender contain two MenuElement (Male or Female).
	 * @ingroup GUI
	 */
	class MenuElement : public Maskable, public Collidable{
	public:
        
        /**
         * Parametrized constructor.
         * @param key Set the key of the menu element.
         */
        MenuElement(const std::string & key);
        
        /**
         * Return the key of the menu element.
         */
        const std::string & getKey();
        
        void setOffset(Vector2 offset);
        
        const Vector2 & getOffset();
        
        
        
	protected:
        std::string elementKey;
        
        Vector2 offset;
	};
}

#endif
