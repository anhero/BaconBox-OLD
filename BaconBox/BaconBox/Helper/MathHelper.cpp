#include "MathHelper.h"

#include <cmath>

namespace BaconBox {
	/// Float containing the PI value.
	template <> MathHelper::PI<float>::operator float() {
		return 3.14159265f;
	}
	
	/// Double containing the PI value.
	template <> MathHelper::PI<double>::operator double() {
		return 3.14159265;
	}
	
	/// Long double containing the PI value.
	template <> MathHelper::PI<long double>::operator long double() {
		return 3.14159265l;
	}

	template <> const float MathHelper::AngleConvert<float>::RADIANS_TO_DEGREES = 180.0f / (4.0f * std::atan(1.0f));
	template <> const double MathHelper::AngleConvert<double>::RADIANS_TO_DEGREES = 180.0 / (4.0 * std::atan(1.0));
	template <> const long double MathHelper::AngleConvert<long double>::RADIANS_TO_DEGREES = 180.0l / (4.0l * std::atan(1.0l));

	template <> const float MathHelper::AngleConvert<float>::DEGREES_TO_RADIANS = (4.0f * std::atan(1.0f)) / 180.0f;
	template <> const double MathHelper::AngleConvert<double>::DEGREES_TO_RADIANS = (4.0 * std::atan(1.0)) / 180.0;
	template <> const long double MathHelper::AngleConvert<long double>::DEGREES_TO_RADIANS = (4.0l * std::atan(1.0l)) / 180.0l;

	float MathHelper::ease(float t, Ease easeType, float b, float c, float d) {

		// We apply different easing depending on the type given.
		switch (easeType.underlying()) {
		case Ease::LINEAR:
			return c * t / d + b;
			break;

		case Ease::IN_QUADRATIC:
			t /= d;
			return c * t * t + b;
			break;

		case Ease::OUT_QUADRATIC:
			t /= d;
			return -c * t * (t - 2.0f) + b;
			break;

		case Ease::IN_OUT_QUADRATIC:
			t /= d / 2.0f;

			if (t < 1.0f) {
				return c / 2.0f * t * t + b;
			}

			t -= 1.0f;
			return -c / 2.0f * (t * (t - 2.0f) - 1.0f) + b;
			break;

		case Ease::IN_CUBIC:
			t /= d;
			return c * t * t * t + b;
			break;

		case Ease::OUT_CUBIC:
			t /= d;
			t -= 1.0f;
			return c * (t * t * t + 1.0f) + b;
			break;

		case Ease::IN_OUT_CUBIC:
			t /= d / 2.0f;

			if (t < 1.0f) {
				return c / 2 * t * t * t + b;
			}

			t -= 2.0f;
			return c / 2.0f * (t * t * t + 2.0f) + b;
			break;

		case Ease::IN_QUARTIC:
			t /= d;
			return c * t * t * t * t + b;
			break;

		case Ease::OUT_QUARTIC:
			t /= d;
			t -= 1.0f;
			return -c * (t * t * t * t - 1.0f) + b;
			break;

		case Ease::IN_OUT_QUARTIC:
			t /= d / 2.0f;

			if (t < 1.0f) {
				return c / 2 * t * t * t * t + b;
			}

			t -= 2.0f;
			return -c / 2.0f * (t * t * t * t - 2.0f) + b;
			break;

		case Ease::IN_QUINTIC:
			t /= d;
			return c * t * t * t * t * t + b;
			break;

		case Ease::OUT_QUINTIC:
			t /= d;
			t -= 1.0f;
			return c * (t * t * t * t * t + 1.0f) + b;
			break;

		case Ease::IN_OUT_QUINTIC:
			t /= d / 2.0f;

			if (t < 1.0f) {
				return c / 2.0f * t * t * t * t * t + b;
			}

			t -= 2.0f;
			return c / 2.0f * (t * t * t * t * t + 2.0f) + b;
			break;

		case Ease::IN_SINE:
			return -c * std::cos(t / d * (MathHelper::PI<float>() / 2.0f)) + c + b;
			break;

		case Ease::OUT_SINE:
			return c * std::sin(t / d * (MathHelper::PI<float>() / 2.0f)) + b;
			break;

		case Ease::IN_OUT_SINE:
			return -c / 2.0f * (std::cos(MathHelper::PI<float>() * t / d) - 1.0f) + b;
			break;

		case Ease::IN_EXPO:
			return c * std::pow(2.0f, 10.0f * (t / d - 1.0f)) + b;
			break;

		case Ease::OUT_EXPO:
			return c * (-std::pow(2.0f, -10.0f * t / d) + 1.0f) + b;
			break;

		case Ease::IN_OUT_EXPO:
			t /= d / 2.0f;

			if (t < 1.0f) {
				return c / 2.0f * std::pow(2.0f, 10.0f * (t - 1.0f)) + b;
			}

			t -= 1.0f;
			return c / 2 * (-std::pow(2.0f, -10.0f * t) + 2.0f) + b;
			break;

		case Ease::IN_BOUNCE:
			return c - ease(1 - t, Ease::OUT_BOUNCE) + b;
			break;

		case Ease::IN_CIRCULAR:
			t /= d;
			return -c * (std::sqrt(1.0f - t * t) - 1.0f) + b;
			break;

		case Ease::OUT_CIRCULAR:
			t /= d;
			t -= 1.0f;
			return c * std::sqrt(1.0f - t * t) + b;
			break;

		case Ease::IN_OUT_CIRCULAR:
			t /= d / 2.0f;

			if (t < 1.0f) {
				return -c / 2.0f * (std::sqrt(1.0f - t * t) - 1) + b;
			}

			t -= 2.0f;
			return c / 2.0f * (std::sqrt(1.0f - t * t) + 1.0f) + b;
			break;

		case Ease::OUT_BOUNCE:
			t /= d;

			if ((t) < (1.0f / 2.75f)) {
				return c * (7.5625f * t * t) + b;

			} else if (t < (2 / 2.75f)) {
				t -= (1.5f / 2.75f);
				return c * (7.5625f * (t) * t + .75f) + b;

			} else if (t < (2.5f / 2.75f)) {
				t -= (2.25f / 2.75f);
				return c * (7.5625f * (t) * t + .9375f) + b;

			} else {
				t -= (2.625f / 2.75f);
				return c * (7.5625f * (t) * t + .984375f) + b;
			}

			break;

		case Ease::IN_OUT_BOUNCE:

			if (t < d * 0.5f) {
				return ease(t * 2.0f, Ease::IN_BOUNCE) * 0.5f + b;

			} else {
				return ease(t * 2.0f - d, Ease::OUT_BOUNCE) * 0.5f + c * 0.5f + b;
			}

			break;

		default:
			break;
		}

		return t;
	}

	template <>
	float MathHelper::clampAngle(float angle) {
		if (angle > 180.0f || angle <= -180.0f) {
			if (angle > 0.0f) {
				angle = angle - (static_cast<float>(static_cast<int>(angle + 180.0f) / 360) * 360.0f);

			} else {
				angle = angle + (static_cast<float>(static_cast<int>(angle - 180.0f) / -360) * 360.0f);
			}
		}

		return angle;
	}

	template <>
	double MathHelper::clampAngle(double angle) {
		if (angle > 180.0 || angle <= -180.0) {
			if (angle > 0.0) {
				angle = angle - (static_cast<double>(static_cast<int>(angle + 180.0) / 360) * 360.0);

			} else {
				angle = angle + (static_cast<double>(static_cast<int>(angle - 180.0) / -360) * 360.0);
			}
		}

		return angle;
	}
}
