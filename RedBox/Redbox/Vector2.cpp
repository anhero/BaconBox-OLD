#include "Vector2.h"

namespace RedBox {
	template<> const Vector2T<float> Vector2T<float>::UP = Vector2T<float>(0.0f, -1.0f);
	template<> const Vector2T<double> Vector2T<double>::UP = Vector2T<double>(0.0, -1.0);
	template<> const Vector2T<long double> Vector2T<long double>::UP = Vector2T<long double>(0.0l, -1.0l);
}
