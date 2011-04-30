#include "Camera.h"
#include "GraphicDriver.h"
#include "TimeHelper.h"
#include "Random.h"
#include "RedBoxEngine.h"
#include <cmath>

using namespace RedBox;

Camera::Camera(): x(0), y(0), angle(0), zoomFactor(1.0f),
backgroundColor(Color::BLACK), shakeIntensity(0.0f), shakeStart(0.0),
shakeDuration(0.0), shakeAxes(BOTH_AXES), offsetX(0), offsetY(0) {
}

void Camera::move(int x, int y) {
	this->x += x;
	this->y += y;
}

void Camera::setPosition(int x, int y) {
	this->x = x;
	this->y = y;
}

int Camera::getX() {
	return x;
}

int Camera::getY() {
	return y;
}

void Camera::resetAngle() {
	angle = 0;
}
void Camera::setAngle(int angle) {
	this->angle = angle;
}
float Camera::getAngle() {
	return angle;
}
void Camera::rotateLeft(int angle) {
	this->angle -= angle;
}
void Camera::rotateRight(int angle) {
	this->angle += angle;
}

void Camera::setBackgroundColor(const Color& newBackgroundColor) {
	backgroundColor = newBackgroundColor;
}

const Color& Camera::getBackgroundColor() const {
	return backgroundColor;
}

void Camera::zoom(float factor) {
	zoomFactor *= factor;
}
void Camera::setZoom(float factor) {
	zoomFactor = factor;
}
void Camera::resetZoom() {
	zoomFactor = 1.0f;
}

void Camera::shake(float intensity, double duration, bool forceReset,
				   ShakeAxes axes) {
	if(forceReset || intensity > shakeIntensity) {
		shakeIntensity = fabs(intensity);
		shakeStart = TimeHelper::getInstance().getSinceStart();
		shakeDuration = ((duration > 0.0) ? (duration) : (0.0));
		shakeAxes = axes;
	}
}

void Camera::update() {
	double timeSinceStarted = TimeHelper::getInstance().getSinceStart() - shakeStart;
	if(timeSinceStarted < shakeDuration) {
		// We set random offsets to the camera.
		float tmpIntensity = (timeSinceStarted == 0.0) ? (shakeIntensity) : ((1.0f - ((TimeHelper::getInstance().getSinceStart() - shakeStart) / shakeDuration)) * shakeIntensity);
		if(shakeAxes == BOTH_AXES || shakeAxes == HORIZONTAL_AXIS) {
			offsetX = static_cast<int>(Random::getRandomFloat(tmpIntensity * -1.0f, tmpIntensity) * static_cast<float>(RedBoxEngine::getScreenWidth()));
		} else {
			offsetX = 0;
		}
		if(shakeAxes == BOTH_AXES || shakeAxes == VERTICAL_AXIS) {
			offsetY = static_cast<int>(Random::getRandomFloat(tmpIntensity * -1.0f, tmpIntensity) * static_cast<float>(RedBoxEngine::getScreenHeight()));
		} else {
			offsetY = 0;
		}
	} else {
		// We reset the offsets.
		offsetX = 0;
		offsetY = 0;
	}
}

void Camera::render() {
	GraphicDriver::prepareScene(-x + offsetX, -y + offsetY, angle, zoomFactor, backgroundColor);
}
