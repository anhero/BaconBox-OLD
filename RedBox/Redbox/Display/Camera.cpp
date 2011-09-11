#include "Camera.h"

#include <cmath>

#include "GraphicDriver.h"
#include "TimeHelper.h"
#include "Random.h"
#include "Engine.h"
#include "GraphicBody.h"
#include "MainWindow.h"
using namespace RedBox;

Camera::Camera(): Body(), position(Vector2()), angle(0), zoomFactor(1.0f),
	backgroundColor(Color::BLACK), shakeIntensity(0.0f),
	shakeStart(0.0), shakeDuration(0.0), shakeAxes(ShakeAxes::BOTH_AXES),
	offset(Vector2()) {
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

const Vector2& Camera::getPosition() const {
	return position;
}

void Camera::setPosition(float x, float y) {
	position = Vector2(x, y);
}

void Camera::setPosition(const Vector2& newPosition) {
	position = newPosition;
}

void Camera::move(float x, float y) {
	position += Vector2(x, y);
}

void Camera::move(const Vector2& moveVector) {
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

void Camera::setYPosition(float newYPosition) {
	position.setY(newYPosition);
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
	Vector2 center(getXPosition() + static_cast<float>(getWidth()) * 0.5f, getYPosition() + static_cast<float>(getHeight()) * 0.5f);
	zoomFactor = newZoomFactor;
	setXPosition(center.getX() - static_cast<float>(getWidth()) * 0.5f);
	setYPosition(center.getY() - static_cast<float>(getHeight()) * 0.5f);
}

void Camera::zoom(float factor) {
	setZoomFactor(zoomFactor * factor);
}

void Camera::resetZoom() {
	setZoomFactor(1.0f);
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

Vector2 Camera::screenToWorld(const Vector2& positionOnScreen) const {
	return positionOnScreen * (1.0f / zoomFactor) + position;
}

Vector2 Camera::screenToWorld(float x, float y) const {
	return Vector2(x, y) * (1.0f / zoomFactor) + position;
}

float Camera::screenToWorldX(float x) const {
	return x * (1.0f / zoomFactor) + position.getX();
}

float Camera::screenToWorldY(float y) const {
	return y * (1.0f / zoomFactor) + position.getY();
}

Vector2 Camera::worldToScreen(const Vector2& positionInWorld) const {
	return (positionInWorld - position) * (1.0f / zoomFactor);
}

Vector2 Camera::worldToScreen(float x, float y) const {
	return (Vector2(x, y) - position) * (1.0f / zoomFactor);
}

float Camera::worldToScreenX(float x) const {
	return (x - position.getX()) * (1.0f / zoomFactor);
}

float Camera::worldToScreenY(float y) const {
	return (y - position.getY()) * (1.0f / zoomFactor);
}

unsigned int Camera::getWidth() const {
	if(zoomFactor != 0.0f) {
		return static_cast<unsigned int>(static_cast<float>(MainWindow::getInstance().getContextWidth()) / fabsf(zoomFactor));
	} else {
		return 0;
	}
}

unsigned int Camera::getHeight() const {
	if(zoomFactor != 0.0f) {
		return static_cast<unsigned int>(static_cast<float>(MainWindow::getInstance().getContextHeight()) / fabsf(zoomFactor));
	} else {
		return 0;
	}
}

bool Camera::collideInside(GraphicBody* body) {
	bool result = false;
	if(body->getXPosition() <= getXPosition()) {
		// Body is too much to the left.
		if(body->getXVelocity() < 0.0f) {
			body->setXVelocity(-body->getXVelocity() * body->getElasticity());
		}

		body->setXPosition(getXPosition());

		result = true;
	} else if(body->getXPosition() + body->getWidth() >= getXPosition() + static_cast<float>(getWidth())) {
		// Body is too much to the right.
		if(body->getXVelocity() > 0.0f) {
			body->setXVelocity(-body->getXVelocity() * body->getElasticity());
		}

		body->setXPosition(getXPosition() + static_cast<float>(getWidth()) - body->getWidth());

		result = true;
	}

	if(body->getYPosition() <= getYPosition()) {
		// Body is too much to the top.
		if(body->getYVelocity() < 0.0f) {
			body->setYVelocity(-body->getYVelocity() * body->getElasticity());
		}

		body->setYPosition(getYPosition());

		result = true;
	} else if(body->getYPosition() + body->getHeight() >= getYPosition() + static_cast<float>(getHeight())) {
		// Body is too much to the bottom.
		if(body->getYVelocity() > 0.0f) {
			body->setYVelocity(-body->getYVelocity() * body->getElasticity());
		}

		body->setYPosition(getYPosition() + static_cast<float>(getHeight()) - body->getHeight());

		result = true;
	}

	return result;
}

void Camera::update() {
	double timeSinceStarted = TimeHelper::getInstance().getSinceStart() - shakeStart;

	if(timeSinceStarted < shakeDuration) {
		// We set random offsets to the camera.
		float tmpIntensity = (timeSinceStarted == 0.0) ? (shakeIntensity) : ((1.0f - ((TimeHelper::getInstance().getSinceStart() - shakeStart) / shakeDuration)) * shakeIntensity);

		if(shakeAxes == ShakeAxes::BOTH_AXES || shakeAxes == ShakeAxes::HORIZONTAL_AXIS) {
			offset.setX(Random::getRandomFloat(tmpIntensity * -1.0f, tmpIntensity) * static_cast<float>(MainWindow::getInstance().getContextWidth()));
		} else {
			offset.setX(0.0f);
		}

		if(shakeAxes == ShakeAxes::BOTH_AXES || shakeAxes == ShakeAxes::VERTICAL_AXIS) {
			offset.setY(Random::getRandomFloat(tmpIntensity * -1.0f, tmpIntensity) * static_cast<float>(MainWindow::getInstance().getContextHeight()));
		} else {
			offset.setY(0.0f);
		}
	} else {
		// We reset the offsets.
		offset = Vector2();
	}
}

void Camera::render() {
	GraphicDriver::prepareScene(position + offset, angle, zoomFactor, backgroundColor, Vector2(static_cast<float>(getWidth()) * 0.5f, static_cast<float>(getHeight()) * 0.5f));
}
