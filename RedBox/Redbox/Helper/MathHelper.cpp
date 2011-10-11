#include "MathHelper.h"

#include <cmath>

namespace RedBox {
	template <> MathHelper::PI<float>::operator float() { return 3.14159265f; }
	template <> MathHelper::PI<double>::operator double() { return 3.14159265; }
	template <> MathHelper::PI<long double>::operator long double() { return 3.14159265l; }

	template <> const float MathHelper::RadiansToDegrees<float>::RADIAN_TO_DEGREE = 57.2957795785523f;
	template <> const double MathHelper::RadiansToDegrees<double>::RADIAN_TO_DEGREE = 57.2957795785523;
	template <> const long double MathHelper::RadiansToDegrees<long double>::RADIAN_TO_DEGREE = 57.2957795785523l;

	template <> const float MathHelper::DegreesToRadians<float>::DEGREE_TO_RADIAN = 0.0174532925f;
	template <> const double MathHelper::DegreesToRadians<double>::DEGREE_TO_RADIAN = 0.0174532925;
	template <> const long double MathHelper::DegreesToRadians<long double>::DEGREE_TO_RADIAN = 0.0174532925l;

	float MathHelper::ease(float t, Ease easeType, float b, float c, float d) {

		// We apply different easing depending on the type given.
		switch(easeType.underlying()) {
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

			if(t < 1.0f) {
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

			if(t < 1.0f) {
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

			if(t < 1.0f) {
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

			if(t < 1.0f) {
				return c / 2.0f * t * t * t * t * t + b;
			}

			t -= 2.0f;
			return c / 2.0f * (t * t * t * t * t + 2.0f) + b;
			break;
		case Ease::IN_SINE:
			return -c * cosf(t / d * (MathHelper::PI<float>() / 2.0f)) + c + b;
			break;
		case Ease::OUT_SINE:
			return c * sinf(t / d * (MathHelper::PI<float>() / 2.0f)) + b;
			break;
		case Ease::IN_OUT_SINE:
			return -c / 2.0f * (cosf(MathHelper::PI<float>() * t / d) - 1.0f) + b;
			break;
		case Ease::IN_EXPO:
			return c * powf(2.0f, 10.0f * (t / d - 1.0f)) + b;
			break;
		case Ease::OUT_EXPO:
			return c * (-powf(2.0f, -10.0f * t / d) + 1.0f) + b;
			break;
		case Ease::IN_OUT_EXPO:
			t /= d / 2.0f;

			if(t < 1.0f) {
				return c / 2.0f * powf(2.0f, 10.0f * (t - 1.0f)) + b;
			}

			t -= 1.0f;
			return c / 2 * (-powf(2.0f, -10.0f * t) + 2.0f) + b;
			break;
		case Ease::IN_BOUNCE:
			return c - ease(1 - t, Ease::OUT_BOUNCE) + b;
			break;
		case Ease::IN_CIRCULAR:
			t /= d;
			return -c * (sqrtf(1.0f - t * t) - 1.0f) + b;
			break;
		case Ease::OUT_CIRCULAR:
			t /= d;
			t -= 1.0f;
			return c * sqrtf(1.0f - t * t) + b;
			break;
		case Ease::IN_OUT_CIRCULAR:
			t /= d / 2.0f;

			if(t < 1.0f) {
				return -c / 2.0f * (sqrtf(1.0f - t * t) - 1) + b;
			}

			t -= 2.0f;
			return c / 2.0f * (sqrtf(1.0f - t * t) + 1.0f) + b;
			break;
		case Ease::OUT_BOUNCE:
			t /= d;

			if((t) < (1.0f / 2.75f)) {
				return c * (7.5625f * t * t) + b;
			} else if(t < (2 / 2.75f)) {
				t -= (1.5f / 2.75f);
				return c * (7.5625f * (t) * t + .75f) + b;
			} else if(t < (2.5f / 2.75f)) {
				t -= (2.25f / 2.75f);
				return c * (7.5625f * (t) * t + .9375f) + b;
			} else {
				t -= (2.625f / 2.75f);
				return c * (7.5625f * (t) * t + .984375f) + b;
			}

			break;
		case Ease::IN_OUT_BOUNCE:

			if(t < d * 0.5f) {
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
			float tmp = angle / 180.0f;
			float tmp2;
			modff(tmp, &tmp2);

			if (angle > 180.0f) {
				tmp2 += 1.0f;

			} else {
				tmp2 -= 1.0f;
			}

			angle -= tmp2 * 180.0f;
		}

		return angle;
	}

	template <>
	double MathHelper::clampAngle(double angle) {
		if (angle > 180.0 || angle <= -180.0) {
			double tmp = angle / 180.0;
			double tmp2;
			modf(tmp, &tmp2);

			if (angle > 180.0) {
				tmp2 += 1.0;

			} else {
				tmp2 -= 1.0;
			}

			angle -= tmp2 * 180.0;
		}

		return angle;
	}
}
