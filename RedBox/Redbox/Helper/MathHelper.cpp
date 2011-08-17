#include "MathHelper.h"

namespace RedBox {
	template <> MathHelper::PI<float>::operator float() { return 3.14159265f; }
	template <> MathHelper::PI<double>::operator double() { return 3.14159265f; }
	template <> MathHelper::PI<long double>::operator long double() { return 3.14159265l; }

	template <> const float MathHelper::RadiansToDegrees<float>::RADIAN_TO_DEGREE = 57.2957795785523f;
	template <> const double MathHelper::RadiansToDegrees<double>::RADIAN_TO_DEGREE = 57.2957795785523;
	template <> const long double MathHelper::RadiansToDegrees<long double>::RADIAN_TO_DEGREE = 57.2957795785523l;

	template <> const float MathHelper::DegreesToRadians<float>::DEGREE_TO_RADIAN = 0.0174532925f;
	template <> const double MathHelper::DegreesToRadians<double>::DEGREE_TO_RADIAN = 0.0174532925;
	template <> const long double MathHelper::DegreesToRadians<long double>::DEGREE_TO_RADIAN = 0.0174532925l;
}
