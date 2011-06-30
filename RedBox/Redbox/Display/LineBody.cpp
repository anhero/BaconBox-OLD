#include "LineBody.h"

using namespace RedBox;

LineBody::LineBody() : GraphicBody(), length(0.0f), orientation(HORIZONTAL) {
}

LineBody::LineBody(float newLength, Orientation newOrientation) : GraphicBody(),
length(newLength), orientation(newOrientation) {
}

LineBody::LineBody(const LineBody &src) : GraphicBody(src), length(src.length),
orientation(src.orientation) {
}

LineBody::~LineBody() {
}

LineBody& LineBody::operator=(const LineBody& src) {
	this->GraphicBody::operator=(src);
	if(this != &src) {
		length = src.length;
		orientation = src.orientation;
	}
	return *this;
}

void LineBody::update() {
	this->GraphicBody::update();
}

void LineBody::render() {
}

float LineBody::getWidth() const {
	return (orientation == HORIZONTAL) ? (length) : (0.0f);
}

float LineBody::getHeight() const {
	return (orientation == VERTICAL) ? (length) : (0.0f);
}

void LineBody::setScaling(float xScaling, float yScaling) {
	if(xScaling && yScaling) {
		float tmpLength = length;
		switch(orientation) {
		case HORIZONTAL:
			length *= xScaling / getXScaling();
			setXPosition(getXPosition() + (tmpLength - length) * 0.5f);
			break;
		case VERTICAL:
			length *= yScaling / getYScaling();
			setYPosition(getYPosition() + (tmpLength - length) * 0.5f);
			break;
		default:
			break;
		}
		this->GraphicBody::setScaling(xScaling, yScaling);
	}
}
