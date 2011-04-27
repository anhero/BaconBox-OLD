#include "Camera.h"
#include "GraphicDriver.h"

using namespace RedBox;


Camera::Camera(): x(0), y(0), angle(0), zoomFactor(1.0f) {
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

void Camera::zoom(float factor) {
	zoomFactor *= factor;
}
void Camera::setZoom(float factor) {
	zoomFactor = factor;
}
void Camera::resetZoom() {
	zoomFactor = 1.0f;
}

void Camera::render() {
	GraphicDriver::prepareScene(-x, -y, angle, zoomFactor);
}
