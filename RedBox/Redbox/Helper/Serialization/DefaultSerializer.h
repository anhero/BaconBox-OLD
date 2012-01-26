/**
 * @file
 * @ingroup Serialization
 */
#ifndef RB_DEFAULT_SERIALIZER_H
#define RB_DEFAULT_SERIALIZER_H

#include "Value.h"
#include "IsBaseOf.h"
#include "Serializable.h"

namespace RedBox {
	class Serializer;

	/**
	 * Wrapper class used to get the default format of serializer. By default,
	 * it's a JSON serializer.
	 * @ingroup Serialization
	 */
	class DefaultSerializer {
	public:
		/**
		 * Gets the default serializer.
		 * @return Reference to the default serializer.
		 */
		static Serializer &getDefaultSerializer();

		/**
		 * Sets the default serializer.
		 * @param newDefaultSerializer Pointer to the new serializer. This class
		 * becomes the owner of the instance being pointed. It will be
		 * automatically deleted when the application exits. In other words, you
		 * should use this function like so:
		 * DefaultSerializer::setDefaultSerializer(new JsonSerializer());
		 */
		static void setDefaultSerializer(Serializer *newDefaultSerializer);

		/**
		 * Serializes a custom type to a Value. By default, it assumes the
		 * class is derived from Serializable. If the class to be serialized
		 * cannot be derived from Serializable, you can write static functions
		 * that will take care of the serialization, see RedBox::Vector2T for
		 * an example.
		 * @param input Instance of custom type to serialize.
		 * @param node Value to serialize to.
		 * @tparam T Type of the instance to be serialized.
		 * @see RedBox::Serializable
		 * @see RedBox::Vector2T<T>
		 */
		template <typename T>
		static void serialize(const T &input, Value &node) {
			input.serialize(node);
		}

		/**
		 * Deserializes a custom type from a Value. By default, it assumes the
		 * class is derived from Serializable. If the class to be deserialized
		 * cannot be derived from Serializable, you can write static functions
		 * that will take care of the serialization, see RedBox::Vector2T for an
		 * example.
		 * @param node Value to deserialize from.
		 * @param output Instance of the type to serialize to.
		 * @return True if the deserialization was successful, false if not.
		 * the output parameter is not modified if the deserialization failed.
		 * @tparam T Type of the instance to be deserialized.
		 */
		template <typename T>
		static bool deserialize(const Value &node, T &output) {
			return output.deserialize(node);
		}
	private:
		/**
		 * Gets the singleton instance.
		 * @return Reference to the singleton instance.
		 */
		static DefaultSerializer &getInstance();

		/**
		 * Default constructor. Initializes with a JSON serializer.
		 */
		DefaultSerializer();

		/**
		 * Destructor. Deletes the default serializer.
		 */
		~DefaultSerializer();

		/// Pointer to the default serializer.
		Serializer *defaultSerializer;
	};
}

#endif
