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
		 * class is derived from Serializable. It can be specialized if the
		 * custom type is not derived from Serializable.
		 * @param input Instance of custom type to serialize.
		 * @param node Value to serialize to.
		 * @tparam T Type of the instance to be serialized.
		 * @see RedBox::Serializable
		 */
		template <typename T>
		static void serialize(const T &input, Value &node) {
			// Will call serialize on the input item if it is derived from
			// Serializable or call the static function serialize on the
			// templated type.
			SerializeTemplate<T, IsBaseOf<Serializable, T>::RESULT> st;
			st(input, node);
		}

		/**
		 * Deserializes a custom type from a Value. By default, it assumes the
		 * class is derived from Serializable. It can be specialized if the
		 * custom type is not derived from Serializable.
		 * @param node Value to deserialize from.
		 * @param output Instance of the type to serialize to.
		 * @return True if the deserialization was successful, false if not.
		 * the output parameter is not modified if the deserialization failed.
		 * @tparam T Type of the instance to be deserialized.
		 */
		template <typename T>
		static bool deserialize(const Value &node, T &output) {
			DeserializeTemplate<T, IsBaseOf<Serializable, T>::RESULT> dt;
			return dt(node, output);
		}
	private:

		template <typename T, bool INHERITS>
		class SerializeTemplate {
		public:
			void operator()(const T &input, Value &node) {
				input.serialize(node);
			}
		};

		template <typename T>
		class SerializeTemplate<T, false> {
		public:
			void operator()(const T &input, Value &node) {
				T::serialize(input, node);
			}
		};

		template <typename T, bool INHERITS>
		class DeserializeTemplate {
		public:
			bool operator()(const Value &node, T &output) {
				return output.deserialize(node);
			}
		};

		template <typename T>
		class DeserializeTemplate<T, false> {
		public:
			bool operator()(const Value &node, T &output) {
				return T::deserialize(node, output);
			}
		};

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
