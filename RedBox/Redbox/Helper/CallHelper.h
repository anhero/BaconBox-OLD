/**
 * @file
 * @ingroup Helper
 */
#ifndef RB_CALL_HELPER_H
#define RB_CALL_HELPER_H

namespace RedBox {
	template <typename T, typename U, bool CALL>
	struct CallUpdate {
		void operator() (T *) {
		}
	};

	template <typename T, typename U>
	struct CallUpdate<T, U, true> {
		void operator() (T *ptr) {
			ptr->U::update();
		}
	};

	template <typename T, typename U, bool CALL>
	struct CallSetToBeDeleted {
		void operator() (bool, T *) {
		}
	};

	template <typename T, typename U>
	struct CallSetToBeDeleted<T, U, true> {
		void operator() (bool newToBeDeleted, T *ptr) {
			ptr->U::setToBeDeleted(newToBeDeleted);
		}
	};
}

#endif // RB_CALL_HELPER_H
