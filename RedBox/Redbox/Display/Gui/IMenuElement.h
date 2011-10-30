/**
 * @file
 * @ingroup Group
 */

#ifndef IMENUELEMENT_H
#define IMENUELEMENT_H

#include <sigly.h>

#include "Collidable.h"
#include "Layerable.h"
#include "Graphic.h"
#include "Animatable.h"

namespace RedBox{
	/**
	 * Interface class for all MenuElement implementations. This class is abstract.
	 * @ingroup GUI
	 */
	class IMenuElement : public Graphic<Animatable>, public Collidable,
	public Layerable, public sigly::HasSlots<> {
	public:
		/**
		 * Default constructor.
		 */
		IMenuElement(const std::string& key);	
		
		/**
		 * Copy constructor.
		 * @param src the MenuElement to make a copy of.
		 */
		IMenuElement(const IMenuElement& src);
		/**
		 * Virtual Clone fonction.
		 * @return a clone of the MenuElement
		 */
		virtual IMenuElement* clone() const = 0;
		/**
		 * Destructor.
		 */
		virtual ~IMenuElement();
		
		/// Signal sent when the element is selected.
		sigly::Signal0<> select;
		/// Signal sent when the element is not selected anymore.
		sigly::Signal0<> deselect;
		/// Signal sent when the element is triggered.
		sigly::Signal0<> trigger;
		/**
		 * Updates the MenuElement.
		 */
		virtual void update()=0;
		
		/**
		 * Renders the MenuElement.
		 */
		virtual void render()=0;
		/**
		 * Change the visibility
		 * @param newVisible the new visible value
		 */
		void setVisible(bool newVisible);
		/**
		 * Gets the MenuElement's Key
		 * @return the string Key
		 */
		virtual std::string getKey();
		/// The selection value.
		bool isSelected;
		
	protected:
		/// The key to identify the MenuElement.
		std::string key;
	};
}

#endif
