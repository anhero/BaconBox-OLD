#include "Camera.h"
#include "GraphicDriver.h"
#include "TimeHelper.h"
#include "Random.h"
#include "Engine.h"
#include <cmath>

using namespace RedBox;

Camera::Camera(): Body(), position(Vec2()), angle(0), zoomFactor(1.0f),
	backgroundColor(Color::BLACK), shakeIntensity(0.0f),
	shakeStart(0.0), shakeDuration(0.0), shakeAxes(BOTH_AXES), offset(Vec2()) {
}

Camera::Camera(const Camera& src) : Body(), position(src.position),
	angle(src.angle), zoomFactor(src.zoomFactor),
	backgroundColor(src.backgroundColor), shakeIntensity(src.shakeIntensity),
	shakeStart(src.shakeStart), shakeAxes(src.shakeAxes), offset(src.offset) {
}

Camera& Camera::operator=(const Camera& src) {
	Body::operator=(src);

	if(this != &src) {
		position = src.position;
		angle = src.angle;
		zoomFactor = src.zoomFactor;
		backgroundColor = src.backgroundColor;
		shakeIntensity = src.shakeIntensity;
		shakeStart = src.shakeStart;
		shakeAxes = src.shakeAxes;
		offset = src.offset;
	}

	return *this;
}

const Vec2& Camera::getPosition() const {
	return position;
}

void Camera::setPosition(float x, float y) {
	position = Vec2(x, y);
}

void Camera::setPosition(const Vec2& newPosition) {
	position = newPosition;
}

void Camera::move(float x, float y) {
	position += Vec2(x, y);
}

void Camera::move(const Vec2& moveVector) {
	position += moveVector;
}

float Camera::getXPosition() const {
	return position.getX();
}

void Camera::setXPosition(float newXPosition) {
	position.setX(newXPosition);
}

void Camera::moveX(float x) {
	position.addToX(x);
}

float Camera::getYPosition() const {
	return position.getY();
}

void Camera::moveY(float y) {
	position.addToY(y);
}

float Camera::getAngle() const {
	return angle;
}

void Camera::setAngle(float newAngle) {
	angle = newAngle;
}

void Camera::rotateLeft(float rotationAngle) {
	angle -= rotationAngle;
}
void Camera::rotateRight(float rotationAngle) {
	angle += rotationAngle;
}

void Camera::resetAngle() {
	angle = 0.0f;
}

void Camera::setBackgroundColor(const Color& newBackgroundColor) {
	backgroundColor = newBackgroundColor;
}

const Color& Camera::getBackgroundColor() const {
	return backgroundColor;
}

float Camera::getZoomFactor() const {
	return zoomFactor;
}

void Camera::setZoomFactor(float newZoomFactor) {
	zoomFactor = newZoomFactor;
}

void Camera::zoom(float factor) {
	zoomFactor *= factor;
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

Vec2 Camera::screenToWorld(const Vec2& positionOnScreen) {
	return positionOnScreen * (1.0f / zoomFactor) + position;
}

Vec2 Camera::worldToScreen(const Vec2& positionInWorld) {
	return (positionInWorld - position) * (1.0f / zoomFactor);
}

int Camera::getWidth() const {
	return Engine::getScreenWidth();
}

int Camera::getHeight() const {
	return Engine::getScreenHeight();
}

void Camera::update() {
	double timeSinceStarted = TimeHelper::getInstance().getSinceStart() - shakeStart;

	if(timeSinceStarted < shakeDuration) {
		// We set random offsets to the camera.
		float tmpIntensity = (timeSinceStarted == 0.0) ? (shakeIntensity) : ((1.0f - ((TimeHelper::getInstance().getSinceStart() - shakeStart) / shakeDuration)) * shakeIntensity);

		if(shakeAxes == BOTH_AXES || shakeAxes == HORIZONTAL_AXIS) {
			offset.setX(Random::getRandomFloat(tmpIntensity * -1.0f, tmpIntensity) * static_cast<float>(Engine::getScreenWidth()));
		} else {
			offset.setX(0.0f);
		}

		if(shakeAxes == BOTH_AXES || shakeAxes == VERTICAL_AXIS) {
			offset.setY(Random::getRandomFloat(tmpIntensity * -1.0f, tmpIntensity) * static_cast<float>(Engine::getScreenHeight()));
		} else {
			offset.setY(0.0f);
		}
	} else {
		// We reset the offsets.
		offset = Vec2();
	}
}

void Camera::render() {
	GraphicDriver::prepareScene(position + offset, angle, zoomFactor, backgroundColor);
}
