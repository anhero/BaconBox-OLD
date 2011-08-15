#include "Tweener.h"

#include "Engine.h"
#include "Tween.h"

using namespace RedBox;

Tweener::Tweener(double newTime, Ease newEase) : timer(0.0), time(newTime),
	ease(newEase) {
}

void Tweener::update() {
	timer += Engine::getSinceLastUpdate();
	if(timer > time) {
		timer = time;
	}
	setValue(Tween::ease(timer / time, ease));

	if(timer >= time) {
		Tween::getInstance().remove(this);
	}
}
