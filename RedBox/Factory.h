#ifndef __FACTORY_H
#define __FACTORY_H
#include <string>
#include <memory>
#include <map>

//#define RBRegisterClass(cls) Factory<GraphicObject>::RegisterClass<cls>(#cls);

namespace RedBox {
	
	template <class ManufacturedType, typename ClassIDKey=std::string>
	class GenericFactory {
	private:
		typedef ManufacturedType* (*BaseCreateFn)();
		typedef std::map<ClassIDKey, BaseCreateFn> FnRegistry;
		FnRegistry registry;
		
		GenericFactory() {}
		//GenericFactory(const GenericFactory&); // Not implemented
		//GenericFactory &operator=(const GenericFactory&); // Not implemented
		static GenericFactory* myInstance;
	public:
		// Used for the singleton pattern, to get the Factory's instance.
		static GenericFactory* instance() {
			if(myInstance == NULL) {
				myInstance = new GenericFactory;
			}
			return myInstance;
		}
		
		// Used to register a class.
		void regCreateFn(const ClassIDKey & className, BaseCreateFn functionPtr) {
			registry[className] = functionPtr;
		}
		
		ManufacturedType* create(const ClassIDKey &className) {
			BaseCreateFn test = registry[className];
			return (*test)();
		}
	};
	
	// We initialize the static pointer for the singleton pattern.
	template <class ManufacturedType, typename ClassIDKey>
	GenericFactory<ManufacturedType, ClassIDKey>* GenericFactory<ManufacturedType, ClassIDKey>::myInstance = NULL;
	
	template <class AncestorType, class ManufacturedType, typename ClassIDKey=std::string>
	class RegisterInFactory
	{
	public:
		static AncestorType* createInstance() {
			return new ManufacturedType;
		}
		
		static void registerInFactory(const ClassIDKey& id) {
			GenericFactory<AncestorType>::instance()->regCreateFn(id, createInstance);
		}
	};
}
#endif