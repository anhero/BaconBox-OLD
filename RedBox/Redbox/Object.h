/**
 * @file
 */
#ifndef RB_OBJECT_H
#define RB_OBJECT_H

namespace RedBox {
	/**
	 * Base class that all RedBox instantiable classes extend.
	 */
	class Object {
		/**
		 * Default constructor.
		 */
		Object();
		/**
		 * Destructor.
		 */
		virtual ~Object();
	};
}

#endif
