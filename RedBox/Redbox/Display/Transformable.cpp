#include "Transformable.h"

#include <cfloat>

#include "MathHelper.h"

namespace RedBox {
	Transformable::Transformable() : Positionable(), scaling(1.0f, 1.0f),
	    angle(0.0f) {
	}

	Transformable::Transformable(const Vector2 &newPosition,
	                             const Vector2 &newScaling,
	                             float newAngle) : Positionable(newPosition),
		scaling(newScaling), angle(newAngle) {
	}

	Transformable::Transformable(const Transformable &src) : Positionable(src),
		scaling(src.scaling), angle(src.angle) {
	}

	Transformable::~Transformable() {
	}

	Transformable &Transformable::operator=(const Transformable &src) {
		this->Positionable::operator=(src);

		if (this != &src) {
			scaling = src.scaling;
			angle = src.angle;
		}

		return *this;
	}

	const Vector2 &Transformable::getScaling() const {
		return scaling;
	}

	void Transformable::setScaling(const Vector2 &newScaling) {
		setScaling(newScaling.getX(), newScaling.getY());
	}

	void Transformable::setScaling(float newXScaling, float newYScaling) {
		scale(newXScaling / scaling.getX(), newYScaling / scaling.getY());
	}

	void Transformable::scale(const Vector2 &scalingToApply) {
		scaleFromPoint(scalingToApply.getX(), scalingToApply.getY(), getCentroid());
	}

	void Transformable::scale(float xScaling, float yScaling) {
		scaleFromPoint(xScaling, yScaling, getCentroid());
	}

	void Transformable::addToScaling(const Vector2 &scalingToAdd) {
		addToScaling(scalingToAdd.getX(), scalingToAdd.getY());
	}

	void Transformable::addToScaling(float xScaling, float yScaling) {
		if (xScaling || yScaling) {
			if (xScaling + scaling.getX() == 0.0f) {
				if (xScaling > 0.0f) {
					xScaling += FLT_MIN;

				} else if (xScaling < 0.0f) {
					xScaling -= FLT_MIN;
				}
			}

			if (yScaling + scaling.getY() == 0.0f) {
				if (yScaling > 0.0f) {
					yScaling += FLT_MIN;

				} else if (yScaling < 0.0f) {
					yScaling -= FLT_MIN;
				}
			}

			setScaling(scaling.getX() + xScaling, scaling.getY() + yScaling);
		}
	}

	void Transformable::scaleFromPoint(const Vector2 &scalingToApply,
	                                   const Vector2 &fromPoint) {
		scaleFromPoint(scalingToApply.getX(), scalingToApply.getY(), fromPoint);
	}

	void Transformable::scaleFromPoint(float xScaling, float yScaling,
	                                   const Vector2 &) {
		scaling.scalarMultiplication(xScaling, yScaling);
	}

	float Transformable::getXScaling() const {
		return scaling.getX();
	}

	void Transformable::setXScaling(float newXScaling) {
		setScaling(newXScaling, scaling.getY());
	}

	void Transformable::scaleX(float xScaling) {
		scale(xScaling, 1.0f);
	}

	void Transformable::scaleXFromPoint(float xScaling,
	                                    const Vector2 &fromPoint) {
		scaleFromPoint(xScaling, 1.0f, fromPoint);
	}

	float Transformable::getYScaling() const {
		return scaling.getY();
	}

	void Transformable::setYScaling(float newYScaling) {
		setScaling(scaling.getX(), newYScaling);
	}

	void Transformable::scaleY(float yScaling) {
		scale(1.0f, yScaling);
	}

	void Transformable::scaleYFromPoint(float yScaling,
	                                    const Vector2 &fromPoint) {
		scaleFromPoint(1.0f, yScaling, fromPoint);
	}

	float Transformable::getAngle() const {
		return angle;
	}

	void Transformable::setAngle(float newAngle) {
		rotate(newAngle - angle);
	}

	void Transformable::rotate(float angleToAdd) {
		rotateFromPoint(angleToAdd, getCentroid());
	}

	void Transformable::rotateFromPoint(float rotationAngle,
	                                    const Vector2 &) {
		angle += rotationAngle;

		angle = MathHelper::clampAngle(angle);
	}
}
