#include "Vector2.h"

namespace BaconBox {
	template <> const Vector<float, 2u> Vector<float, 2u>::UP(0.0f, -1.0f);
	template <> const Vector<double, 2u> Vector<double, 2u>::UP(0.0, -1.0);
	template <> const Vector<long double, 2u> Vector<long double, 2u>::UP(0.0l, -1.0l);

	template <> const float Vector<float, 2u>::ZERO = 0.0f;
	template <> const double Vector<double, 2u>::ZERO = 0.0;
	template <> const long double Vector<long double, 2u>::ZERO = 0.0l;
}
