#ifndef RB_DELETE_HELPER_H
#define RB_DELETE_HELPER_H

#include <cassert>

#include <utility>

namespace BaconBox {

	struct DeletePointer {
		template <typename T>
		void operator() (T pointer) {
			if(pointer) {
				delete pointer;
			}
		}
	};

	struct DeletePointerDirect {
		template <typename T>
		void operator() (T pointer) {
			delete pointer;
		}
	};

	struct DeletePointerFromPair {
		template <typename T, typename U>
		void operator() (const std::pair<T, U>& myPair) {
			if(myPair.second) {
				delete myPair.second;
			}
		}
	};
	
	struct DeletePointerFromPairDirect {
		template <typename T, typename U>
		void operator() (const std::pair<T, U>& myPair) {
			delete myPair.second;
		}
	};
}

#endif
