/**
 * @file
 * @ingroup Serialization
 */
#ifndef RB_SERIALIZABLE_H
#define RB_SERIALIZABLE_H

namespace RedBox {
	class Value;

	/**
	 * Base class for all serializable classes.
	 * @ingroup Serialization
	 */
	class Serializable {
	public:
		/**
		 * Destructor.
		 */
		virtual ~Serializable();

		/**
		 * Serializes the instance to a Value.
		 * @param node Node to serialize the instance into.
		 */
		virtual void serialize(Value &node) const = 0;

		/**
		 * Deserializes the instance from a Value.
		 * @param node Value to read the data from.
		 * @return True on success, false on failure to read all the
		 * necessary data. Does not modify the instance when there is a failure.
		 */
		virtual bool deserialize(const Value &node) = 0;
	};
}

#endif
