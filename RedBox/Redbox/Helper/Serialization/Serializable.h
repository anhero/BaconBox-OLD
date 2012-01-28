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
		 * @param setName Wether or not we need to set the name of the value
		 */
		virtual void serialize(Value &node, bool setName = true) const = 0;

		/**
		 * Deserializes the instance from a Value.
		 * @param node Value to read the data from.
		 * @return True on success, false on failure to read all the
		 * necessary data. Does not modify the instance when there is a failure.
		 */
		virtual bool deserialize(const Value &node) = 0;

		/**
		 * Checks whether or not the Value contains the necessary information
		 * to deserialize the instance.
		 * @param node Value to check.
		 * @return True if the value contains the necessary information, false
		 * if not.
		 */
		virtual bool isValidValue(const Value &node) const = 0;
	};
}

#endif
