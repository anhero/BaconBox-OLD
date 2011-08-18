/**
 * @file
 * @ingroup Helper
 */
#ifndef RB_STATIC_ASSERT_H
#define RB_STATIC_ASSERT_H

namespace RedBox {
	template<bool Condition, typename Dummy = void>
	struct StaticAssert {
		typedef bool Result;
	};
	
	template<typename IntentionalError>
	struct StaticAssert<false, IntentionalError> {
		typedef typename IntentionalError::DoesNotExist Result;
	};
}

#endif
