/**
 * @file
 * @ingroup GUI
 */

#ifndef RB_GRAPHICEMENUELEMENT_H
#define RB_GRAPHICEMENUELEMENT_H

#include "MenuElement.h"
#include "GraphicElement.h"
#include "Transformable.h"
#include "Colorable.h"

namespace BaconBox{
	/** 
	 * This implementation of MenuElement represent its elements as GraphicElement
     * which are similar to simple Sprite.
     * @ingroup GUI
     */
	class GraphicMenuElement : public MenuElement, public Colorable{
	public:
        /**
         * Parametrized constructor.
         * This constructor will use the given textureKey for both, 
         * the texture key and the menu element key.
         */
        GraphicMenuElement(const std::string & textureKey);
        
        /**
         * Parametrized constructor 
         * This constructor let you set a menu element key different from
         * the texture key.
         */
        GraphicMenuElement(const std::string & textureKey, const std::string & menuElementKey);
        
        ~GraphicMenuElement();
        
        void render();
        
        void update();
        
        void mask();
        
        void unmask();
        
        Maskable *getMask() const;
        
        void setMask(Maskable *newMask, bool inverted = false);
        
        float getWidth() const;

        float getHeight() const;
        
        void move(float xDelta, float yDelta);

        const Vector2 & getOffset();
        
        void setColor(const Color &newColor);
	private:
        GraphicElement<Transformable> * graphicElement;
        
        Vector2 offset;
	};
}

#endif
