#include "Body.h"

using namespace RedBox;

Body::Body() : Object(), active(true), visible(true), enabled(true) {
}

Body::Body(const Body& src) : Object(src), active(src.active),
visible(src.visible), enabled(src.enabled) {
}

Body::~Body() {
}

Body& Body::operator=(const Body& src) {
	Object::operator=(src);
	if(this != &src) {
		active = src.active;
		visible = src.visible;
		enabled = src.enabled;
	}
	return *this;
}

bool Body::isActive() const {
	return active;
}

void Body::setActive(bool newActive) {
	active = newActive;
}

bool Body::isVisible() const {
	return visible;
}

void Body::setVisible(bool newVisible) {
	visible = newVisible;
}

bool Body::isEnabled() const {
	return enabled;
}

void Body::setEnabled(bool newEnabled) {
	enabled = newEnabled;
}
