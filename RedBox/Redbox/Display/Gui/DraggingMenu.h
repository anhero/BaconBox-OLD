/**
 * @file
 * @ingroup GUI
 */

#ifndef DRAGGINGMENU_H
#define DRAGGINGMENU_H

#include "IMenu.h"
#include "GraphicElement.h"
#include "Sprite.h"
#include "Tween.h"
namespace RedBox {
	/** 
	 * A implementation of a IMenu which has a middle(selected) element. 
     * @ingroup GUI
     */
	class DraggingMenu : public IMenu{
	public:
		/**
		 * Default constructor.
		 */
		DraggingMenu();
		/**
		 * Virtual destructor.
		 */
		virtual ~DraggingMenu();
		/**
		 * Copy constructor.
		 * @param src The DraggingMenu to make a copy of.
		 */
		DraggingMenu(const DraggingMenu &src);
		/**
		 * Parametrized constructor. Loads the menu with a specific size.
		 * @param width The width of the menu.
		 * @param height The height of the menu.
		 * @param spacing The spacing between the middle of two elements in the 
		 * menu.
		 */
		DraggingMenu(float width, float height, float spacing);
		/**
		 * Sets a new position for the center of the menu.
		 * @param vect The vector of the new center position
		 */
		void setCenterPosition(Vector2 vect);
		/**
		 * Sets a new position for menu.
		 * @param vect The vector of the new position
		 */
		void setPosition(float x, float y);
		/**
		 * Gets the position of the center of the menu.
		 * @return the middle's position of the menu.
		 */
		Vector2 getCenterPosition();
		/**
		 * Rotate the menu around a certain point.
		 * @param rotationAngle the angle to be added to the menu.
		 * @param rotationPoint the point around witch the rotation must be made.
		 */
		void rotateFromPoint(float rotationAngle, const Vector2& rotationPoint);
		void scaleFromPoint(float xScaling, float yScaling,
							const Vector2 &fromPoint); 
		/**
		 * Sets a new element to the elements.
		 * @param newAngle the new angle to be setted to the elements
		 */
		virtual void setElementAngle(float newAngle);
		/**
		 * Gets the angle of the elements.
		 */
		float getElementAngle();
		/**
		 * Updates the menu and its elements.
		 */
		virtual void update();
		/**
		 * Gets the menu's mask.
		 * @return the menu's mask.
		 */
		virtual Maskable* getMask() const;
		/**
		 * Sets a mask to the menu.
		 * @param newMask The new menu's mask.
		 * @param inverted The mask is going to be applied inversly or not.
		 */
		virtual void setMask(Maskable* newMask, bool inverted = false);
		/**
		 * Gets the internal mask, the one applied to the menu's elements.
		 * @return The internal mask.
		 */
		Maskable* getInternalMask();
		/**
		 * Sets the internal mask, the one applied to the menu's elements.
		 * @param The internal mask.
		 */
		virtual void setInternalMask(GraphicElement<Transformable>* internalMask, bool inverted = false);
		/**
		 * Scale the internalMask proportionnaly with the menu.
		 * @param x the ratio in X between the internalMask and the menu.
		 * @param y the ratio in Y between the internalMask and the menu.
		 */
		virtual void scaleMaskToMenu(float x, float y);
		std::string getSelectedKey() const;
		/**
		 * Is called when a menu's element is triggered.
		 */
		virtual void onHoldNMove(const Vector2, const Vector2);
		void onRelease(Vector2 ptr);
		void addElement(IMenuElement* newElement);
	protected:
		IMenuElement* selectedElement;
		Sprite* cursor;
		Tween<Vector2> theTween;
		///The angle of the elements
		int elementsAngle;
		///The spacing between the element's middle
		float spacing;
		///The mask applied to the menu
		Maskable* currentMask;
		///The mask applied to the menu
		GraphicElement<Transformable>* internalMask;
		/**
		 * Virtual method to update the element's visibility.
		 */
		void updateElementsVisibility();
		/**
		 * Virtual method to update the element's position.
		 */
		void updateElementsPosition();
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
	};
}
#endif
