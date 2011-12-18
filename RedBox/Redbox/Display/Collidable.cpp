#include "Collidable.h"

#include <cassert>

#include <algorithm>

#include "Engine.h"
#include "MathHelper.h"

namespace RedBox {
	const float Collidable::NO_MAX_VELOCITY = -1.0f;
	const float OVERLAP_BIAS = 4.0f;
	FlagSet<Side> initAllSides();

	const FlagSet<Side> Collidable::ALL_SIDES = initAllSides();

	FlagSet<Side> initAllSides() {
		FlagSet<Side> result;
		result.set(Side::LEFT);
		result.set(Side::RIGHT);
		result.set(Side::TOP);
		result.set(Side::BOTTOM);
		return result;
	}

	Collidable::Collidable() : Updateable(), Transformable(),
		oldPosition(getPosition()), velocity(),
		maximumVelocity(NO_MAX_VELOCITY, NO_MAX_VELOCITY),
		acceleration(), drag(), collidableSides(ALL_SIDES),
		elasticity(0.0f), staticBody(false), offset(),
		collidingBoxRatio(1.0f, 1.0f), offsetRatio(false) {
	}

	Collidable::Collidable(const Vector2 &newPosition) :
		Updateable(), Transformable(newPosition), oldPosition(newPosition),
		velocity(), maximumVelocity(NO_MAX_VELOCITY, NO_MAX_VELOCITY),
		acceleration(), drag(), collidableSides(ALL_SIDES),
		elasticity(0.0f), staticBody(false), offset(),
		collidingBoxRatio(1.0f, 1.0f), offsetRatio(false) {
	}

	Collidable::Collidable(const Collidable &src) : Updateable(src),
		Transformable(src), oldPosition(src.oldPosition), velocity(src.velocity),
		maximumVelocity(src.maximumVelocity), acceleration(src.acceleration),
		drag(src.drag), collidableSides(src.collidableSides),
		elasticity(src.elasticity), staticBody(src.staticBody),
		offset(src.offset), collidingBoxRatio(src.collidingBoxRatio),
		offsetRatio(src.offsetRatio) {
	}

	Collidable::~Collidable() {
	}

	Collidable &Collidable::operator=(const Collidable &src) {
		this->Transformable::operator=(src);

		if (this != &src) {
			oldPosition = src.oldPosition;
			velocity = src.velocity;
			maximumVelocity = src.maximumVelocity;
			acceleration = src.acceleration;
			drag = src.drag;
			collidableSides = src.collidableSides;
			elasticity = src.elasticity;
			staticBody = src.staticBody;
			offset = src.offset;
			collidingBoxRatio = src.collidingBoxRatio;
			offsetRatio = src.offsetRatio;
		}

		return *this;
	}

	void Collidable::update() {
		oldPosition = getPosition();

		// Update the motion.
		computeVelocity();
		Vector2 delta = velocity * static_cast<float>(Engine::getSinceLastUpdate());

		if (delta != Vector2(0.0f, 0.0f)) {
			move(delta);
		}
	}

	const Vector2 &Collidable::getOldPosition() const {
		return oldPosition;
	}

	float Collidable::getOldXPosition() const {
		return oldPosition.getX();
	}

	float Collidable::getOldYPosition() const {
		return oldPosition.getY();
	}

	const Vector2 &Collidable::getVelocity() const {
		return velocity;
	}

	void Collidable::setVelocity(const Vector2 &newVelocity) {
		velocity.setXY(checkMaximumVelocity(newVelocity.getX(), maximumVelocity.getX()),
		               checkMaximumVelocity(newVelocity.getY(), maximumVelocity.getY()));
	}

	void Collidable::setVelocity(float newXVelocity, float newYVelocity) {
		checkMaximumVelocity(&newXVelocity, maximumVelocity.getX());
		checkMaximumVelocity(&newYVelocity, maximumVelocity.getY());
		velocity.setXY(newXVelocity, newYVelocity);
	}

	float Collidable::getXVelocity() const {
		return velocity.getX();
	}

	void Collidable::setXVelocity(float newXVelocity) {
		checkMaximumVelocity(&newXVelocity, maximumVelocity.getX());
		velocity.setX(newXVelocity);
	}

	float Collidable::getYVelocity() const {
		return velocity.getY();
	}

	void Collidable::setYVelocity(float newYVelocity) {
		checkMaximumVelocity(&newYVelocity, maximumVelocity.getY());
		velocity.setY(newYVelocity);
	}

	const Vector2 &Collidable::getMaximumVelocity() const {
		return maximumVelocity;
	}

	void Collidable::setMaximumVelocity(const Vector2 &newMaximumVelocity) {
		maximumVelocity = newMaximumVelocity;
		setVelocity(velocity);
	}

	void Collidable::setMaximumVelocity(float newMaximumXVelocity, float newMaximumYVelocity) {
		maximumVelocity.setXY(newMaximumXVelocity, newMaximumYVelocity);
		setVelocity(velocity);
	}

	float Collidable::getMaximumXVelocity() const {
		return maximumVelocity.getX();
	}

	void Collidable::setMaximumXVelocity(float newMaximumXVelocity) {
		maximumVelocity.setX(newMaximumXVelocity);
		setXVelocity(velocity.getX());
	}

	float Collidable::getMaximumYVelocity() const {
		return maximumVelocity.getY();
	}

	void Collidable::setMaximumYVelocity(float newMaximumYVelocity) {
		maximumVelocity.setY(newMaximumYVelocity);
		setYVelocity(velocity.getY());
	}

	const Vector2 &Collidable::getAcceleration() const {
		return acceleration;
	}

	void Collidable::setAcceleration(const Vector2 &newAcceleration) {
		acceleration = newAcceleration;
	}

	void Collidable::setAcceleration(float newXAcceleration, float newYAcceleration) {
		acceleration.setXY(newXAcceleration, newYAcceleration);
	}

	float Collidable::getXAcceleration() const {
		return acceleration.getX();
	}

	void Collidable::setXAcceleration(float newXAcceleration) {
		acceleration.setX(newXAcceleration);
	}

	float Collidable::getYAcceleration() const {
		return acceleration.getY();
	}

	void Collidable::setYAcceleration(float newYAcceleration) {
		acceleration.setY(newYAcceleration);
	}

	const Vector2 &Collidable::getDrag() const {
		return drag;
	}

	void Collidable::setDrag(const Vector2 &newDrag) {
		drag = newDrag;
	}

	void Collidable::setDrag(float newXDrag, float newYDrag) {
		drag.setXY(newXDrag, newYDrag);
	}

	float Collidable::getXDrag() const {
		return drag.getX();
	}

	void Collidable::setXDrag(float newXDrag) {
		drag.setX(newXDrag);
	}

	float Collidable::getYDrag() const {
		return drag.getY();
	}

	void Collidable::setYDrag(float newYDrag) {
		drag.setY(newYDrag);
	}

	FlagSet<Side> &Collidable::getCollidableSides() {
		return collidableSides;
	}

	float Collidable::getElasticity() const {
		return elasticity;
	}

	void Collidable::setElasticity(float newElasticity) {
		elasticity = newElasticity;
	}

	bool Collidable::isStaticBody() const {
		return staticBody;
	}

	void Collidable::setStaticBody(bool newStaticBody) {
		staticBody = newStaticBody;
	}

	const Vector2 &Collidable::getOffset() const {
		return offset;
	}

	void Collidable::setOffset(const Vector2 &newOffset) {
		offset = newOffset;
	}

	void Collidable::setOffset(float newXOffset, float newYOffset) {
		offset.setXY(newXOffset, newYOffset);
	}

	float Collidable::getXOffset() const {
		return offset.getX();
	}

	void Collidable::setXOffset(float newXOffset) {
		offset.setX(newXOffset);
	}

	float Collidable::getYOffset() const {
		return offset.getY();
	}

	void Collidable::setYOffset(float newYOffset) {
		offset.setY(newYOffset);
	}

	const Vector2 &Collidable::getCollidingBoxRatio() const {
		return collidingBoxRatio;
	}

	void Collidable::setCollidingBoxRatio(const Vector2 &newCollidingBoxRatio) {
		collidingBoxRatio = newCollidingBoxRatio;
	}

	void Collidable::setCollidingBoxRatio(float newXCollidingBoxRatio, float newYCollidingBoxRatio) {
		collidingBoxRatio.setXY(newXCollidingBoxRatio, newYCollidingBoxRatio);
	}

	float Collidable::getXCollidingBoxRatio() const {
		return collidingBoxRatio.getX();
	}

	void Collidable::setXCollidingBoxRatio(float newXCollidingBoxRatio) {
		collidingBoxRatio.setX(newXCollidingBoxRatio);
	}

	float Collidable::getYCollidingBoxRatio() const {
		return collidingBoxRatio.getY();
	}

	void Collidable::setYCollidingBoxRatio(float newYCollidingBoxRatio) {
		collidingBoxRatio.setY(newYCollidingBoxRatio);
	}

	const Vector2 Collidable::getCollidingSize() const {
		Vector2 result(getSize());
		result.scalarMultiplication(getCollidingBoxRatio());
		return result;
	}

	float Collidable::getCollidingWidth() const {
		return getWidth() * getXCollidingBoxRatio();
	}

	float Collidable::getCollidingHeight() const {
		return getHeight() * getYCollidingBoxRatio();
	}

	bool Collidable::isOffsetRatio() const {
		return offsetRatio;
	}

	void Collidable::setOffsetRatio(bool newOffsetRatio) {
		offsetRatio = newOffsetRatio;
	}

	const AxisAlignedBoundingBox Collidable::getAxisAlignedBoundingBox() const {
		if (offsetRatio) {
			return AxisAlignedBoundingBox(getPosition() + Vector2(getOffset().getX() * getCollidingWidth(), getOffset().getY() * getCollidingHeight()),
										  getCollidingSize());
		} else {
			return AxisAlignedBoundingBox(getPosition() + getOffset(), getCollidingSize());
		}
	}

	std::pair<bool, CollisionDetails> Collidable::collide(Collidable *other) {
		std::pair<bool, CollisionDetails> result(false, CollisionDetails());
		result.second.body1 = this;
		result.second.body2 = other;

		// We make sure we aren't colliding a body with itself.
		if (this != other) {
			// The bool is set to true if there is either a horizontal or
			// vertical collision.
			result.first = solveXCollision(other, &result.second) ||
			               solveYCollision(other, &result.second);
		}

		return result;
	}

	std::pair<bool, std::list<std::pair<bool, CollisionDetails> > > Collidable::collide(const std::list<Collidable *> &others) {
		std::pair<bool, std::list<std::pair<bool, CollisionDetails> > > result(false, std::list<std::pair<bool, CollisionDetails> >());

		// We test the collisions with each collidable from the list.
		for (std::list<Collidable *>::const_iterator i = others.begin();
		     i != others.end(); ++i) {
			// We add the collision details to the resulting list.
			result.second.push_back(collide(*i));
			// We check if there was a collisions and take note of it if
			// needed.
			result.first = result.first || result.second.back().first;
		}

		return result;
	}

	bool Collidable::collideHorizonalLine(float yPosition, float lowerXBoundary,
	                                      float higherXBoundary) {
		bool result = false;

		// We make sure the body is not static.
		if (!isStaticBody()) {
			AxisAlignedBoundingBox aabb = getAxisAlignedBoundingBox();

			// We check if the body overlaps with the horizontal line.
			if (aabb.overlapsHorizontalLine(yPosition, lowerXBoundary, higherXBoundary)) {
				// If the body is going down.
				if (getYVelocity() > 0.0f) {
					// We put the body's bottom at the line's position.
					moveY(yPosition - aabb.getBottom());
					// If the body is going up.

				} else if (getYVelocity() < 0.0f) {
					// We put the body's top at the line's position.
					moveY(yPosition - aabb.getTop());
					// If the body is not moving and its upper half is over
					// the line.

				} else if (aabb.getTop() + aabb.getHeight() * 0.5f < yPosition) {
					// We put the body's bottom at the line's position.
					moveY(yPosition - aabb.getBottom());

				} else {
					// We put the body's top at the line's position.
					moveY(yPosition - aabb.getTop());
				}

				// We inverse the body's vertical velocity and we take into
				// account its elasticity.
				setYVelocity(-getYVelocity() * getElasticity());

				result = true;
			}

		}

		return result;
	}

	bool Collidable::collideHorizonalLine(float yPosition) {
		bool result = false;

		// We make sure the body is not static.
		if (!isStaticBody()) {
			AxisAlignedBoundingBox aabb = getAxisAlignedBoundingBox();

			// We check if the body overlaps with the horizontal line.
			if (aabb.overlapsHorizontalLine(yPosition)) {
				// If the body is going down.
				if (getYVelocity() > 0.0f) {
					// We put the body's bottom at the line's position.
					moveY(yPosition - aabb.getBottom());
					// If the body is going up.

				} else if (getYVelocity() < 0.0f) {
					// We put the body's top at the line's position.
					moveY(yPosition - aabb.getTop());
					// If the body is not moving and its upper half is over
					// the line.

				} else if (aabb.getTop() + aabb.getHeight() * 0.5f < yPosition) {
					// We put the body's bottom at the line's position.
					moveY(yPosition - aabb.getBottom());

				} else {
					// We put the body's top at the line's position.
					moveY(yPosition - aabb.getTop());
				}

				// We inverse the body's vertical velocity and we take into
				// account its elasticity.
				setYVelocity(-getYVelocity() * getElasticity());

				result = true;
			}

		}

		return result;
	}

	bool Collidable::collideVerticalLine(float xPosition, float lowerYBoundary, float higherYBoundary) {
		bool result = false;

		// We make sure the body is not static.
		if (!isStaticBody()) {
			AxisAlignedBoundingBox aabb = getAxisAlignedBoundingBox();

			// We check if the body overlaps with the horizontal line.
			if (aabb.overlapsVerticalLine(xPosition, lowerYBoundary, higherYBoundary)) {
				// If the body is going right.
				if (getXVelocity() > 0.0f) {
					// We put the body's right at the line's position.
					moveX(xPosition - aabb.getRight());
					// If the body is going left.

				} else if (getXVelocity() < 0.0f) {
					// We put the body's left at the line's position.
					moveX(xPosition - aabb.getLeft());
					// If the body is not moving and its left half is to the
					// left of the line.

				} else if (aabb.getLeft() + aabb.getWidth() * 0.5f < xPosition) {
					// We put the body's bottom at the line's position.
					moveX(xPosition - aabb.getRight());

				} else {
					// We put the body's top at the line's position.
					moveX(xPosition - aabb.getLeft());
				}

				// We inverse the body's vertical velocity and we take into
				// account its elasticity.
				setXVelocity(-getXVelocity() * getElasticity());

				result = true;
			}

		}

		return result;
	}

	bool Collidable::collideVerticalLine(float xPosition) {
		bool result = false;

		// We make sure the body is not static.
		if (!isStaticBody()) {
			AxisAlignedBoundingBox aabb = getAxisAlignedBoundingBox();

			// We check if the body overlaps with the horizontal line.
			if (aabb.overlapsVerticalLine(xPosition)) {
				// If the body is going right.
				if (getXVelocity() > 0.0f) {
					// We put the body's right at the line's position.
					moveX(xPosition - aabb.getRight());
					// If the body is going left.

				} else if (getXVelocity() < 0.0f) {
					// We put the body's left at the line's position.
					moveX(xPosition - aabb.getLeft());
					// If the body is not moving and its left half is to the
					// left of the line.

				} else if (aabb.getLeft() + aabb.getWidth() * 0.5f < xPosition) {
					// We put the body's bottom at the line's position.
					moveX(xPosition - aabb.getRight());

				} else {
					// We put the body's top at the line's position.
					moveX(xPosition - aabb.getLeft());
				}

				// We inverse the body's vertical velocity and we take into
				// account its elasticity.
				setXVelocity(-getXVelocity() * getElasticity());

				result = true;
			}

		}

		return result;
	}

	std::pair<bool, std::list<std::pair<bool, CollisionDetails> > > Collidable::collide(const std::list<Collidable *> &collidables1,
	        const std::list<Collidable *> &collidables2) {
		std::pair<bool, std::list<std::pair<bool, CollisionDetails> > > result(false, std::list<std::pair<bool, CollisionDetails> >());

		// We test the collisions with each collidable from the lists.
		for (std::list<Collidable *>::const_iterator i = collidables1.begin();
		     i != collidables1.end(); ++i) {
			// We make sure the body isn't NULL.
			if (*i) {
				for (std::list<Collidable *>::const_iterator j = collidables2.begin();
				     j != collidables2.end(); ++j) {
					// We add the collision details to the resulting list.
					result.second.push_back((*i)->collide(*j));
					// We check if there was a collisions and take note of it if
					// needed.
					result.first = result.first || result.second.back().first;
				}
			}
		}

		return result;
	}

	float Collidable::computeVelocity(float velocity, float acceleration, float drag, float maximumVelocity) {
		if (acceleration != 0.0f) {
			velocity += acceleration * static_cast<float>(Engine::getSinceLastUpdate());

		} else if (drag != 0.0f) {
			float tmpDrag = drag * static_cast<float>(Engine::getSinceLastUpdate());

			if (velocity - tmpDrag > 0.0f) {
				velocity -= tmpDrag;

			} else if (velocity + tmpDrag < 0.0f) {
				velocity += tmpDrag;

			} else {
				velocity = 0.0f;
			}
		}

		checkMaximumVelocity(&velocity, maximumVelocity);

		return velocity;
	}

	float Collidable::checkMaximumVelocity(float *velocity, float maximumVelocity) {
		if (velocity) {
			if (*velocity != 0.0f && maximumVelocity >= 0.0f) {
				*velocity = MathHelper::clamp(*velocity, -maximumVelocity, maximumVelocity);
			}

			return *velocity;

		} else {
			Console::println("Checking maximum velocity, but received a null pointer.");
			return 0.0f;
		}
	}

	float Collidable::checkMaximumVelocity(float velocity, float maximumVelocity) {
		return checkMaximumVelocity(&velocity, maximumVelocity);
	}

	void Collidable::computeVelocity() {
		velocity.setXY(computeVelocity(velocity.getX(), acceleration.getX(), drag.getX(), maximumVelocity.getX()),
		               computeVelocity(velocity.getY(), acceleration.getY(), drag.getY(), maximumVelocity.getY()));
	}

	void Collidable::checkMaximumVelocity() {
		velocity.setXY(checkMaximumVelocity(velocity.getX(), maximumVelocity.getX()),
		               checkMaximumVelocity(velocity.getY(), maximumVelocity.getY()));
	}

	bool Collidable::solveXCollision(Collidable *other,
	                                 CollisionDetails *collisionDetails) {
		assert(collisionDetails);

		if (other) {
			// We check if both instances are static
			if (isStaticBody() && other->isStaticBody()) {
				return false;
			}

			// We calculate object delta
			float overlap = 0.0f;
			float obj1Delta = getXPosition() - getOldXPosition();
			float obj2Delta = other->getXPosition() - other->getOldXPosition();

			// If they have the same speed, it means they are following each
			// other.
			if (obj1Delta != obj2Delta) {
				float obj1DeltaAbs = fabsf(obj1Delta);
				float obj2DeltaAbs = fabsf(obj2Delta);
				// We create AABBs of the old position with the updated horizontal
				//position.
				AxisAlignedBoundingBox box1(Vector2(getXPosition() - ((obj1Delta > 0.0f) ? (obj1Delta) : (0.0f)), getOldYPosition()),
				                            Vector2(getWidth() + obj1DeltaAbs, getHeight()));
				AxisAlignedBoundingBox box2(Vector2(other->getXPosition() - ((obj2Delta > 0.0f) ? (obj2Delta) : (0.0f)), other->getOldYPosition()),
				                            Vector2(other->getWidth() + obj2DeltaAbs, other->getHeight()));

				if (box1.overlaps(box2)) {
					float maxOverlap = obj1DeltaAbs + obj2DeltaAbs + OVERLAP_BIAS;

					if (obj1Delta > obj2Delta) {
						overlap = box1.getRight() - box2.getLeft();

						if (overlap > maxOverlap || !collidableSides.isSet(Side::RIGHT) || !other->collidableSides.isSet(Side::LEFT)) {
							overlap = 0.0f;

						} else {
							collisionDetails->sidesBody1.set(Side::RIGHT);
							collisionDetails->sidesBody2.set(Side::LEFT);
						}

					} else if (obj1Delta < obj2Delta) {
						overlap = box1.getLeft() - box2.getWidth() - box2.getLeft();

						if ((-overlap > maxOverlap) || !collidableSides.isSet(Side::LEFT) || !other->collidableSides.isSet(Side::RIGHT)) {
							overlap = 0.0f;

						} else {
							collisionDetails->sidesBody1.set(Side::LEFT);
							collisionDetails->sidesBody2.set(Side::RIGHT);
						}
					}
				}
			}

			if (overlap != 0.0f) {

				if (isStaticBody()) {
					other->moveX(overlap);
					other->setXVelocity(getXVelocity() - other->getXVelocity() * other->getElasticity());

				} else if (other->isStaticBody()) {
					moveX(-overlap);
					setXVelocity(other->getXVelocity() - getXVelocity() * getElasticity());

				} else {
					overlap *= 0.5f;

					moveX(-overlap);
					other->moveX(overlap);

					float average = (getXVelocity() + other->getXVelocity()) * 0.5f;

					setXVelocity(average + (other->getXVelocity() - average) * getElasticity());
					other->setXVelocity(average + (getXVelocity() - average) * other->getElasticity());
				}

				return true;

			} else {
				return false;
			}

		} else {
			return false;
		}
	}

	bool Collidable::solveYCollision(Collidable *other, CollisionDetails *collisionDetails) {
		assert(collisionDetails);

		if (other) {
			// We check if both instances are static
			if (isStaticBody() && other->isStaticBody()) {
				return false;
			}

			// We calculate object delta
			float overlap = 0.0f;
			float obj1Delta = getYPosition() - getOldYPosition();
			float obj2Delta = other->getYPosition() - other->getOldYPosition();

			// If they have the same speed, it means they are following each
			// other.
			if (obj1Delta != obj2Delta) {
				float obj1DeltaAbs = fabsf(obj1Delta);
				float obj2DeltaAbs = fabsf(obj2Delta);
				// We create AABBs of the old position with the updated horizontal
				//position.
				AxisAlignedBoundingBox box1(Vector2(getXPosition(), getYPosition() - ((obj1Delta > 0.0f) ? (obj1Delta) : (0.0f))),
				                            Vector2(getWidth(), getHeight() + obj1DeltaAbs));
				AxisAlignedBoundingBox box2(Vector2(other->getXPosition(), other->getYPosition() - ((obj2Delta > 0.0f) ? (obj2Delta) : (0.0f))),
				                            Vector2(other->getWidth(), other->getHeight() + obj1DeltaAbs));

				if (box1.overlaps(box2)) {
					float maxOverlap = obj1DeltaAbs + obj2DeltaAbs + OVERLAP_BIAS;

					if (obj1Delta > obj2Delta) {
						overlap = box1.getBottom() - box2.getTop();

						if (overlap > maxOverlap || !collidableSides.isSet(Side::BOTTOM) || !other->collidableSides.isSet(Side::TOP)) {
							overlap = 0.0f;

						} else {
							collisionDetails->sidesBody1.set(Side::BOTTOM);
							collisionDetails->sidesBody2.set(Side::TOP);
						}

					} else if (obj1Delta < obj2Delta) {
						overlap = box1.getTop() - box2.getHeight() - box2.getTop();

						if ((-overlap > maxOverlap) || !collidableSides.isSet(Side::TOP) || !other->collidableSides.isSet(Side::BOTTOM)) {
							overlap = 0.0f;

						} else {
							collisionDetails->sidesBody1.set(Side::TOP);
							collisionDetails->sidesBody2.set(Side::BOTTOM);
						}
					}
				}
			}

			if (overlap != 0.0f) {

				if (isStaticBody()) {
					other->moveY(overlap);
					other->setYVelocity(getYVelocity() - other->getYVelocity() * other->getElasticity());

					// Special case code that handles cases like horizontally
					// moving platforms that a collidable can ride.
					if (getVelocity() != Vector2(0.0f, 0.0f) &&
					    obj1Delta < obj2Delta) {
						other->moveX(getXPosition() - getOldXPosition());
					}

				} else if (other->isStaticBody()) {
					moveY(-overlap);
					setYVelocity(other->getYVelocity() - getYVelocity() * getElasticity());

					// Special case code that handles cases like horizontally
					// moving platforms that a collidable can ride.
					if (other->getVelocity() != Vector2(0.0f, 0.0f) &&
					    obj1Delta > obj2Delta) {
						moveX(other->getXPosition() - other->getOldXPosition());
					}

				} else {
					overlap *= 0.5f;

					moveY(-overlap);
					other->moveY(overlap);

					float average = (getYVelocity() + other->getYVelocity()) * 0.5f;

					setYVelocity(average + (other->getYVelocity() - average) * getElasticity());
					other->setYVelocity(average + (getYVelocity() - average) * other->getElasticity());
				}

				return true;

			} else {
				return false;
			}

		} else {
			return false;
		}
	}
}
