/**
 * @file
 * @ingroup Group
 */

#ifndef SPRITEMENUELEMENT_H
#define SPRITEMENUELEMENT_H

#include "IMenuElement.h"
#include "Sprite.h"
namespace RedBox {
	/** 
	 * A Sprite's implementation for IMenuElement. 
     * @ingroup GUI
     */
	class SpriteMenuElement : public IMenuElement{
	public:
		/**
		 * Parametrized constructor.
		 * @param imageKey the textureId to create the SpriteMenuElement
		 */
		SpriteMenuElement(const std::string& imageKey);
		/**
		 * Parametrized constructor.
		 * @param imageKey the textureId to create the SpriteMenuElement.
		 * @param idKey the key to be returned to the menu.
		 */
		SpriteMenuElement(const std::string& imageKey, const std::string& idKey);
		/**
		 * Copy constructor.
		 * @param imageKey the textureId to create the SpriteMenuElement
		 */
		SpriteMenuElement(const SpriteMenuElement &src);
		/**
		 * Cloner.
		 * @return a copy of the menu.
		 */
		SpriteMenuElement* clone() const;
		/**
		 * Destructor.
		 */
		~SpriteMenuElement();
		/**
		 * Updates its Sprite.
		 */
		void update();
		/**
		 * Render its Sprite.
		 */
		void render();
		/**
		 * Gets the width of its Sprite.
		 * @return The width of the Sprite.
		 */
		float getWidth() const;
		/**
		 * Gets the height of its Sprite.
		 * @return The height of the Sprite.
		 */
		float getHeight() const;
		/**
		 * Sets a new position for the Sprite.
		 * @param vect The vector of the new position
		 */
		void setPosition(float x, float y);
		/**
		 * Rotate the element around a certain point.
		 * @param rotationAngle the angle to be added to the element.
		 * @param rotationPoint the point around witch the rotation must be made.
		 */
		void rotateFromPoint(float rotationAngle, const Vector2&);
		/**
		 * Sets a mask to the element.
		 * @param newMask The new element's mask.
		 * @param inverted The mask is going to be applied inversly or not.
		 */
		void setMask(GraphicBody* newMask, bool inverted = false);
		/**
		 * Similar to the render function except that it will only
		 * render to the alpha component of the color buffer. It is
		 * used to mask the next rendered sprite (if the next sprite
		 * is set as a masked sprite).
		 */
		void mask();
		/**
		 * Undo what the mask function did. This function
		 * MUST be once after the masked sprite has been rendered.
		 */
		void unmask();
		/**
		 * Gets a pointer to the mask of the element.
		 * @return A pointer to the current mask.
		 */
		GraphicBody* getMask();
	protected:
		///The visible part of the element.
		Sprite* image;
		///The masked part of the element.
		GraphicBody* currentMask;
	};
}
#endif
