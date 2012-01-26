/**
 * @file
 */
#ifndef RB_RESOURCE_DEFINITION_H
#define RB_RESOURCE_DEFINITION_H

#include <iostream>
#include <string>

namespace RedBox {
	class Value;
	/**
	 * String values used to define a resource.
	 */
	struct ResourceDefinition {
		/**
		 * Checks whether or not the Value contains the necessary information
		 * to deserialize the type.
		 * @param node Value to check.
		 * @return True if the value contains the necessary information, false
		 * if not.
		 */
		static bool isValidValue(const Value &node);

		/**
		 * Default constructor.
		 */
		ResourceDefinition();

		/**
		 * Parameterized constructor.
		 * @param newKey Initial resource key to use.
		 * @param newFilePath Initial file path to use.
		 */
		ResourceDefinition(const std::string &newKey,
		                   const std::string &newFilePath);

		/**
		 * Copy constructor.
		 * @param src Resource definition to make a copy of.
		 */
		ResourceDefinition(const ResourceDefinition &src);

		/**
		 * Assignment operator overload.
		 * @param src Resource definition to copy.
		 * @return Reference to the modified resource definition.
		 */
		ResourceDefinition &operator=(const ResourceDefinition &src);

		/**
		 * Serializes the instance to a Value.
		 * @param node Node to serialize the instance into.
		 */
		void serialize(Value &node) const;

		/**
		 * Deserializes the instance from a Value.
		 * @param node Value to read the data from.
		 * @return True on success, false on failure to read all the
		 * necessary data. Does not modify the instance when there is a failure.
		 */
		bool deserialize(const Value &node);

		/// Key of the texture in the resource manager.
		std::string key;

		/// Relative path (from the resources folder) to the resource file.
		std::string filePath;
	};

	std::ostream &operator<<(std::ostream &output,
	                         const ResourceDefinition &rd);
}

#endif
