/**
 * @file
 * @ingroup Helper
 */
#ifndef RB_FACTORY_H
#define RB_FACTORY_H

#include <string>
#include <map>

#define RBRegisterClass(ancestor, child) RedBox::RegisterInFactory<ancestor, child>::registerInFactory(#child)

namespace RedBox {
	/**
	 * Generic abstract factory. Generates instances of a child class unknown
	 * at compile time that is identified by a string (or any other type). For
	 * example, let's say you have a class A. Then you write a class B that
	 * inherits from A. You can register (with the RegisterInFactory class) the
	 * B class with "B" as its identifier. Then, you use this factory to
	 * instantiate an instance of B without knowing where B comes from, all you
	 * need is its "B" identifier. Will mainly used to read custom data written
	 * by game developers using the RedBox engine.
	 * @ingroup Helper
	 */
	template <typename ManufacturedType, typename ClassIDKey = std::string>
	class GenericFactory {
		template <typename T, typename U, typename C> friend class RegisterInFactory;
	private:
		/// Pointer to a function that allocates an instance of the child.
		typedef ManufacturedType *(*BaseCreateFn)();
		/// Type that will contain the information the factory needs.
		typedef std::map<ClassIDKey, BaseCreateFn> FnRegistry;
	public:
		/**
		 * Gets the factory's instance.
		 * @return Reference to the factory's instance.
		 */
		static GenericFactory &getInstance() {
			static GenericFactory instance;
			return instance;
		}

		/**
		 * Creates an instance of the child class asked for.
		 * @param className Name of the class to instantiate.
		 */
		ManufacturedType *create(const ClassIDKey &className) {
			typename FnRegistry::iterator found = registry.find(className);

			if (found != registry.end()) {
				return (*found->second)();

			} else {
				return NULL;
			}
		}
	private:
		/**
		 * Private default constructor.
		 */
		GenericFactory() : registry() {
		}

		/**
		 * Registers a class.
		 * @param className Class's identifier that will be used to find and
		 * call the function that will create an instance of it.
		 * @param functionPtr Pointer to a function that returns a pointer to
		 * the generic factory's base type. Though that function should create
		 * instance of a class that inherits the base type for it to be useful.
		 */
		void regCreateFn(const ClassIDKey &className, BaseCreateFn functionPtr) {
			registry[className] = functionPtr;
		}

		/// Associates an identifier to a function that allocates a child.
		FnRegistry registry;
	};

	/**
	 * Used to register a class. If you want to register a class so it can be
	 * used in its parent's factory, you call the registerInFactory(...). For
	 * the registering to make sense and to compile, the ManufacturedType must
	 * inherit from AncestorType.
	 * @ingroup Helper
	 */
	template <typename AncestorType, typename ManufacturedType, typename ClassIDKey = std::string>
	class RegisterInFactory {
		friend class GenericFactory<AncestorType, ClassIDKey>;
	public:
		/**
		 * Registers a class using the specified identifier.
		 * @param id Identifier to associate the manufactured type with.
		 */
		static void registerInFactory(const ClassIDKey &id) {
			GenericFactory<AncestorType, ClassIDKey>::getInstance().regCreateFn(id, createInstance);
		}
	private:
		/**
		 * Creates an instance of the manufactured type.
		 * @return New instance of the manufactured type as a pointer to its
		 * ancestor.
		 */
		static AncestorType *createInstance() {
			return new ManufacturedType;
		}
	};
}

#endif
