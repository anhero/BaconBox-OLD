/**
 * @file
 * @ingroup Helper
 */
#ifndef RB_IS_BASE_OF_H
#define RB_IS_BASE_OF_H

namespace RedBox {
	typedef char(&yes)[1];
	typedef char(&no)[2];

	template <typename B, typename D>
	struct Host {
		operator B *() const;
		operator D *();
	};

	template <typename B, typename D>
	struct IsBaseOf {
		template <typename T>
		static yes check(D *, T);
		static no check(B *, int);

		static const bool RESULT = sizeof(check(Host<B, D>(), int())) == sizeof(yes);
	};
}


#endif
