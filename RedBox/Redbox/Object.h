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
		 * @param src Object to make a copy of.
		 */
		Object(const Object& src);
		/**
		 * Destructor.
		 */
		virtual ~Object();
		/**
		 * Assignation operator overload.
		 * @param src Object to make a copy of.
		 * @return Reference to the modified instance.
		 */
		Object& operator=(const Object& src);
	};
}

#endif
