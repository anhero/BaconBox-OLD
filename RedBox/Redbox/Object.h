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
	public:
		/**
		 * Default constructor.
		 */
		Object();
		/**
		 * Copy constructor.
		 */
		Object(const Object& src);
		/**
		 * Assignation operator overload.
		 */
		Object& operator=(const Object& src);
		/**
		 * Destructor.
		 */
		virtual ~Object();
	};
}

#endif
