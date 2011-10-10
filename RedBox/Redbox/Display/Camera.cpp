#include "Camera.h"

#include <cmath>

#include "GraphicDriver.h"
#include "TimeHelper.h"
#include "Random.h"
#include "Engine.h"
#include "MainWindow.h"

namespace RedBox {
	Camera::Camera() : Collidable(), Disableable(),
		Shapable<StandardVerticesArray>(), backgroundColor(Color::BLACK),
		shakeIntensity(0.0f), shakeStart(0.0), shakeDuration(0.0), shakeAxes(ShakeAxes::BOTH_AXES), offset() {
		this->getVertices().resize(4);
		StandardVerticesArray::Iterator i = this->getVertices().getBegin();
		++i;
		i->setXY(MainWindow::getInstance().getContextWidth(), 0.0f);
		++i;
		i->setXY(MainWindow::getInstance().getContextWidth(),
		         MainWindow::getInstance().getContextHeight());
		++i;
		i->setXY(0.0f, MainWindow::getInstance().getContextHeight());
	}

	Camera::Camera(const Camera &src) : Collidable(src), Disableable(src),
		Shapable<StandardVerticesArray>(src),
		backgroundColor(src.backgroundColor),
		shakeIntensity(src.shakeIntensity), shakeStart(src.shakeStart),
		shakeDuration(src.shakeDuration), shakeAxes(src.shakeAxes),
		offset(src.offset) {
	}

	Camera &Camera::operator=(const Camera &src) {
		this->Collidable::operator=(src);
		this->Disableable::operator=(src);
		this->Shapable<StandardVerticesArray>::operator=(src);

		if (this != &src) {
			backgroundColor = src.backgroundColor;
			shakeIntensity = src.shakeIntensity;
			shakeStart = src.shakeStart;
			shakeDuration = src.shakeDuration;
			shakeAxes = src.shakeAxes;
			offset = src.offset;
		}

		return *this;
	}

	const Vector2 Camera::getSize() const {
		return getVertices().getSize();
	}

	float Camera::getWidth() const {
		return this->getVertices().getWidth();
	}

	float Camera::getHeight() const {
		return this->getVertices().getHeight();
	}

	void Camera::move(float xDelta, float yDelta) {
		this->Collidable::move(xDelta, yDelta);
		this->getVertices().move(xDelta, yDelta);
	}

	void Camera::scaleFromPoint(float xScaling, float yScaling,
	                            const Vector2 &fromPoint) {
		this->Collidable::scaleFromPoint(xScaling, yScaling, fromPoint);
		this->getVertices().scaleFromPoint(1.0f / xScaling, 1.0f / yScaling, fromPoint);
		Vector2 tmpPosition = this->getVertices().getMinimumXY();
		this->Collidable::move(tmpPosition.getX() - getXPosition(),
		                       tmpPosition.getY() - getYPosition());
	}

	void Camera::rotateFromPoint(float rotationAngle,
	                             const Vector2 &rotationPoint) {
		this->Collidable::rotateFromPoint(rotationAngle, rotationPoint);
		getVertices().rotateFromPoint(rotationAngle, rotationPoint);
		Vector2 tmpPosition = this->getVertices().getMinimumXY();
		this->Collidable::move(tmpPosition.getX() - getXPosition(),
		                       tmpPosition.getY() - getYPosition());
	}

	const Color &Camera::getBackgroundColor() const {
		return backgroundColor;
	}

	void Camera::setBackgroundColor(const Color &newBackgroundColor) {
		backgroundColor = newBackgroundColor;
	}

	void Camera::shake(float intensity, double duration, bool forceReset,
	                   ShakeAxes axes) {
		if (forceReset || intensity > shakeIntensity) {
			shakeIntensity = fabsf(intensity);
			shakeStart = TimeHelper::getInstance().getSinceStart();
			shakeDuration = ((duration > 0.0) ? (duration) : (0.0));
			shakeAxes = axes;
		}
	}

	const Vector2 Camera::screenToWorld(const Vector2 &positionOnScreen) const {
		// We apply the camera's scaling and rotation to the position on screen.
		Vector2 result(positionOnScreen);
		result.scalarDivision(this->getScaling());
		result.rotate(this->getAngle());
		// We add this new vector to the camera's first vertices, which
		// corresponds to the screen's upper left corner.
		return *this->getVertices().getBegin() + result;
	}

	const Vector2 Camera::screenToWorld(float x, float y) const {
		return screenToWorld(Vector2(x, y));
	}

	float Camera::screenToWorldX(float x) const {
		return screenToWorld(x, 0.0f).getX();
	}

	float Camera::screenToWorldY(float y) const {
		return screenToWorld(0.0f, y).getY();
	}

	const Vector2 Camera::worldToScreen(const Vector2 &positionInWorld) const {
		// We subtract the screen's upper left corner's world position from
		// the position in world received.
		Vector2 result(positionInWorld);
		result.subtractFromXY(*this->getVertices().getBegin());
		// We then unapply the rotation and the scaling.
		result.rotate(-this->getAngle());
		result.scalarMultiplication(this->getScaling());
		return result;
	}

	const Vector2 Camera::worldToScreen(float x, float y) const {
		return worldToScreen(Vector2(x, y));
	}

	float Camera::worldToScreenX(float x) const {
		return worldToScreen(x, 0.0f).getX();
	}

	float Camera::worldToScreenY(float y) const {
		return worldToScreen(0.0f, y).getY();
	}

	bool Camera::collideInside(Collidable *collidable) {
		bool result = false;

		if (collidable) {
			AxisAlignedBoundingBox bodyAabb = collidable->getAxisAlignedBoundingBox();
			AxisAlignedBoundingBox cameraAabb = this->getAxisAlignedBoundingBox();

			if (bodyAabb.getLeft() <= cameraAabb.getLeft()) {
				// The collidable is too much to the left.
				if (collidable->getXVelocity() < 0.0f) {
					collidable->setXVelocity(-collidable->getXVelocity() * collidable->getElasticity());
				}

				// We correct the position.
				collidable->moveX(cameraAabb.getLeft() - bodyAabb.getLeft());

				result = true;

			} else if (bodyAabb.getRight() >= cameraAabb.getRight()) {
				// The collidable is too much to the right.
				if (collidable->getXVelocity() > 0.0f) {
					collidable->setXVelocity(-collidable->getXVelocity() * collidable->getElasticity());
				}

				// We correct the position.
				collidable->moveX(cameraAabb.getLeft() - bodyAabb.getLeft());

				result = true;
			}

			if (bodyAabb.getTop() <= cameraAabb.getTop()) {
				// The collidable is too much to the top.
				if (collidable->getYVelocity() < 0.0f) {
					collidable->setYVelocity(-collidable->getYVelocity() * collidable->getElasticity());
				}

				// We correct the position.
				collidable->moveY(cameraAabb.getTop() - bodyAabb.getTop());

				result = true;

			} else if (bodyAabb.getBottom() >= cameraAabb.getBottom()) {
				// The collidable is too much to the right.
				if (collidable->getYVelocity() > 0.0f) {
					collidable->setYVelocity(-collidable->getYVelocity() * collidable->getElasticity());
				}

				// We correct the position.
				collidable->moveY(cameraAabb.getBottom() - bodyAabb.getBottom());

				result = true;
			}
		}

		return result;
	}

	void Camera::update() {
		double timeSinceStarted = TimeHelper::getInstance().getSinceStart() - shakeStart;

		if (timeSinceStarted < shakeDuration) {
			// We set random offsets to the camera.
			float tmpIntensity = (timeSinceStarted == 0.0) ? (shakeIntensity) : ((1.0f - ((TimeHelper::getInstance().getSinceStart() - shakeStart) / shakeDuration)) * shakeIntensity);

			if (shakeAxes == ShakeAxes::BOTH_AXES || shakeAxes == ShakeAxes::HORIZONTAL_AXIS) {
				offset.setX(Random::getRandomFloat(tmpIntensity * -1.0f, tmpIntensity) * static_cast<float>(MainWindow::getInstance().getContextWidth()));

			} else {
				offset.setX(0.0f);
			}

			if (shakeAxes == ShakeAxes::BOTH_AXES || shakeAxes == ShakeAxes::VERTICAL_AXIS) {
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
		GraphicDriver::getInstance().prepareScene(*this->getVertices().getBegin() + offset, getAngle(), getScaling(), backgroundColor);
	}

	void Camera::mask() {
	}

	void Camera::unmask() {
	}

	Maskable *Camera::getMask() const {
		return NULL;
	}

	void Camera::setMask(Maskable *, bool) {
	}
}
