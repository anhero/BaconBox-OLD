/**
 * @file
 * @ingroup Serialization
 */
#ifndef RB_DEFAULT_SERIALIZER_H
#define RB_DEFAULT_SERIALIZER_H

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
