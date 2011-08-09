#include "Tween.h"

#include <cmath>
#include <cassert>

#include <algorithm>

#include "MathHelper.h"
#include "DeleteHelper.h"

using namespace RedBox;

Tween& Tween::getInstance() {
	static Tween instance;
	return instance;
}

float Tween::ease(float t, Ease easeType, float b, float c, float d) {

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
		return -c * cosf(t / d * (MathHelper::PI / 2.0f)) + c + b;
		break;
	case Ease::OUT_SINE:
		return c * sinf(t / d * (MathHelper::PI / 2.0f)) + b;
		break;
	case Ease::IN_OUT_SINE:
		return -c / 2.0f * (cosf(MathHelper::PI * t / d) - 1.0f) + b;
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

Tween::Tween() {
}

Tween::~Tween() {
	// We delete the tweeners that are not done.
	std::for_each(tweeners.begin(), tweeners.end(), DeletePointerDirect());
}

void Tween::update() {
	// We update all the active tweeners.
	for(std::list<Tweener*>::iterator i = tweeners.begin(); i != tweeners.end();
	    ++i) {
		(*i)->update();
	}

	// We remove the tweeners that need to be removed.
	for(std::list<Tweener*>::iterator i = tweenersToRemove.begin();
	    i != tweenersToRemove.end(); ++i) {
		assert(*i);
		tweeners.remove(*i);
		delete *i;
	}

	tweenersToRemove.clear();
}

void Tween::remove(Tweener* tweener) {
	tweenersToRemove.push_back(tweener);
}
