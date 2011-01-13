#include "SpriteEmitter.h"
#include <cmath>
#include "ResourceHelper.h"
#include <cassert>
#include "TimeHelper.h"

using namespace RedBox;

void SpriteEmitter::clean() {
}

void SpriteEmitter::copyFrom(const SpriteEmitter& src) {
	if (this != &src) {
		clean();
		assert(&src);
		if (&src) {
			force = src.force;
			forceRange = src.forceRange;
			coneAngle = src.coneAngle;
			directionAngle = src.directionAngle;
			x = src.x;
			y = src.y;
			xFriction = src.xFriction;
			yFriction = src.yFriction;
			emitObjects = src.emitObjects;
			spriteLifespan = src.spriteLifespan;
			spriteLifespanVariation = src.spriteLifespanVariation;
			isDead = src.isDead;
			deltaXCorrection = src.deltaXCorrection;
			deltaYCorrection = src.deltaYCorrection;
		} else {
			force = 0.0f;
			forceRange = 0.0f;
			coneAngle = 0.0f;
			directionAngle = 0.0f;
			x = 0.0;
			y = 0.0;
			xFriction = 0.0f;
			yFriction = 0.0f;
			emitObjects.clear();
			spriteLifespan = 0.0f;
			spriteLifespanVariation = 0.0f;
			isDead = true;
		}
	}
}

SpriteEmitter::SpriteEmitter(): GraphicObject(), force(0.0), forceRange(0.0), directionAngle(0.0), coneAngle(0.0),
x(0), y(0), spriteLifespan(0.0), spriteLifespanVariation(0.0),
isDead(true), xFriction(0.0), yFriction(0.0), deltaXCorrection(0.0), deltaYCorrection(0.0) {
}

SpriteEmitter::SpriteEmitter(double newX, double newY, 
							 double newForce, double newForceRange, 
							 double newDirectionAngle, double newConeAngle,
							 unsigned int nbSprites,
							 double newSpriteLifespan,
							 double newSpriteLifespanVariation,
							 int newNbBlasts, bool now): GraphicObject(), 
force(newForce), forceRange(newForceRange), directionAngle(newDirectionAngle), coneAngle(newConeAngle),
x(newX), y(newY), spriteLifespan(newSpriteLifespan), 
spriteLifespanVariation(newSpriteLifespanVariation), xFriction(0.0), yFriction(0.0), deltaXCorrection(0.0), deltaYCorrection(0.0) {
	if(newNbBlasts == 0 ) {
		isDead = true;
		die();
	}
	else isDead = false;
	
	// We make sure the angles are between 0 and 360.
	if(directionAngle < 0.0) directionAngle *= -1.0;
	if(directionAngle >= 360.0) directionAngle = fmod(directionAngle, 360.0);
	if(coneAngle < 0.0) coneAngle *= -1.0;
	if(coneAngle >= 360.0) coneAngle = fmod(coneAngle, 360.0);
	
	emitObjects.resize(nbSprites, EmitObject());
	for(std::vector<EmitObject>::iterator i = emitObjects.begin(); i != emitObjects.end(); i++) {
		i->birthdate = TimeHelper::TimeHelper::getSinceEpoch();
		i->lifespan = (now)?(0):(this->generateLifespan());
		i->nbBlasts = newNbBlasts;
	}
}

SpriteEmitter::SpriteEmitter(const SpriteEmitter& src): GraphicObject(src) {
	copyFrom(src);
}

SpriteEmitter::~SpriteEmitter() {
	clean();
}

SpriteEmitter& SpriteEmitter::operator=(const SpriteEmitter& src) {
	GraphicObject::operator=(src);
	copyFrom(src);
	return *this;
}

void SpriteEmitter::update() {
	bool areAllDead = true;
	// We update each sprite.
	for(std::vector<EmitObject>::iterator i = emitObjects.begin(); i != emitObjects.end(); i++) {
		if(updateEmitObject(i)) {
			areAllDead = false;
		}
	}
	if (areAllDead) {
		isDead = true;
		die();
	}
}

void SpriteEmitter::render() {
	for(std::vector<EmitObject>::iterator i = emitObjects.begin(); i != emitObjects.end(); i++) {
		if(i->nbBlasts != 0 && i->isActive) {
			i->mySprite->render();
		}
	}
}

void SpriteEmitter::die() {
	GraphicObject::die();
	for(std::vector<EmitObject>::iterator i = emitObjects.begin(); i!= emitObjects.end(); i++) {
		i->mySprite->die();
		i->isActive = false;
		i->nbBlasts = 0;
	}
	isDead = true;
}

bool SpriteEmitter::updateEmitObject(std::vector<EmitObject>::iterator currentEmitObject) {
	if (currentEmitObject->nbBlasts != 0) {
		if (currentEmitObject->isActive) {
			// Apply friction.
			currentEmitObject->deltaX += xFriction;
			currentEmitObject->deltaY += yFriction;
			currentEmitObject->mySprite->setPosition(currentEmitObject->mySprite->getXPosition() + currentEmitObject->deltaX, currentEmitObject->mySprite->getYPosition() + currentEmitObject->deltaY);
			currentEmitObject->mySprite->update();
		}
		// Do we change its status?
		if (currentEmitObject->birthdate + currentEmitObject->lifespan < TimeHelper::TimeHelper::getSinceEpoch()) {
			// Change the status.
			currentEmitObject->isActive = !(currentEmitObject->isActive);
			// If the sprite is now active.
			if (currentEmitObject->isActive) {
				// We get the sprite's time of activation.
				currentEmitObject->birthdate = TimeHelper::TimeHelper::getSinceEpoch();
				// We generate the sprite's lifespan.
				currentEmitObject->lifespan = generateLifespan();
				// We set the graphicObject's position.
				currentEmitObject->mySprite->setPosition(x, y);
				//currentEmitObject->mySprite->setVerticesPosition(x,y);
				// We generate the random vector for the velocity.
				// First, the random angle.
				double currentAngle = directionAngle + ((coneAngle == 0.0)?(0.0):((fmod(static_cast<double> (rand()), coneAngle) - coneAngle / 2)));
				// Second, the random force.
				double currentForce = force + ((forceRange == 0.0)?(0.0):((fmod(static_cast<double> (rand()), forceRange) - forceRange / 2)));
				// We find the horizontal and vertical forces.
				float xForce, yForce;
				//bool isXNegative = false;
				//bool isYNegative = false;
				xForce = sin(currentAngle*M_PI/180.0) * currentForce ;//* ((isXNegative)?(-1.0f):(1.0f));
				yForce = cos(currentAngle*M_PI/180.0) * currentForce ;//* ((isYNegative)?(-1.0f):(1.0f));
				//10 = cos(225*M_PI/180) * currentForce * ((isYNegative)?(-1.0f):(1.0f))
				currentEmitObject->deltaX = xForce + deltaXCorrection;
				currentEmitObject->deltaY = yForce + deltaYCorrection;
				//currentEmitObject->mySprite->SetVelocity(Vec2(xForce, yForce));
				/*if(!currentEmitObject->renderedOnce) {
					currentEmitObject->renderedOnce = true;
					currentEmitObject->mySprite->render();
				}*/
				currentEmitObject->mySprite->update();
			} else {
				if(currentEmitObject->nbBlasts != -1) {
					--currentEmitObject->nbBlasts;
				}
				// We generate a deathspan.
				currentEmitObject->lifespan = generateVariation();
				// We get the sprite's time of deactivation.
				currentEmitObject->birthdate = TimeHelper::TimeHelper::getSinceEpoch();
			}
		}
	}
	return (currentEmitObject->nbBlasts != 0);
}
void SpriteEmitter::constructDrawer(double x, double y, double width, double height, double angle, const std::string& imageName, int frameWidth, int frameHeight) {
	// We construct the drawer for each EmitObject.
	for(std::vector<EmitObject>::iterator i = emitObjects.begin(); i != emitObjects.end(); i++) {
		if(i->mySprite == NULL) {
			i->mySprite = new GraphicObject();
		}
		i->mySprite->constructDrawer(x, y, width, height, angle, imageName, frameWidth, frameHeight);
	}
}

void SpriteEmitter::addAnimation(const std::string& nameOfAnimation, int frames[],  int numberOfFrames, int FPS) {
	for(std::vector<EmitObject>::iterator i = emitObjects.begin(); i != emitObjects.end(); i++) {
		assert(i->mySprite);
		i->mySprite->addAnimation(nameOfAnimation, frames, numberOfFrames, FPS);
	}
}
void SpriteEmitter::playAnimation(char name[]) {
	for(std::vector<EmitObject>::iterator i = emitObjects.begin(); i != emitObjects.end(); i++) {
		assert(i->mySprite);
		i->mySprite->playAnimation(name);
	}
}
void SpriteEmitter::playFirstAnimation() {
	for(std::vector<EmitObject>::iterator i = emitObjects.begin(); i != emitObjects.end(); i++) {
		assert(i->mySprite);
		i->mySprite->playFirstAnimation();
	}
}
double SpriteEmitter::getForce() const { return force; }
double SpriteEmitter::getDirectionAngle() const { return directionAngle; }
double SpriteEmitter::getConeAngle() const { return coneAngle; }
double SpriteEmitter::getX() const { return x; }
double SpriteEmitter::getY() const { return y; }
unsigned int SpriteEmitter::getNbEmitObjects() const { return emitObjects.size(); }

void SpriteEmitter::setForce(float newForce) { force = force; }
void SpriteEmitter::setDirectionAngle(float newDirectionAngle) { directionAngle = newDirectionAngle; }
void SpriteEmitter::setConeAngle(float newConeAngle) { coneAngle = newConeAngle; }

void SpriteEmitter::setAngle(double angle) {}
void SpriteEmitter::setWidth(double width) {
	for(std::vector<EmitObject>::iterator i = emitObjects.begin(); i != emitObjects.end(); i++) {
		if(i->mySprite == NULL) {
			i->mySprite = new GraphicObject();
			i->mySprite->constructDrawer();
		}
		i->mySprite->setWidth(width);
	}
}
void SpriteEmitter::setHeight(double height) {
	for(std::vector<EmitObject>::iterator i = emitObjects.begin(); i != emitObjects.end(); i++) {
		if(i->mySprite == NULL) {
			i->mySprite = new GraphicObject();
			i->mySprite->constructDrawer();
		}
		i->mySprite->setHeight(height);
	}
}
void SpriteEmitter::setPosition(double x, double y) { this->x = x; this->y = y; };
void SpriteEmitter::setXPosition(double x) { this->x = x; }
void SpriteEmitter::setYPosition(double y) { this->y = y; }
void SpriteEmitter::setFrameWidth(int frameWidth) {
	for(std::vector<EmitObject>::iterator i = emitObjects.begin(); i != emitObjects.end(); i++) {
		if(i->mySprite == NULL) {
			i->mySprite = new GraphicObject();
			i->mySprite->constructDrawer();
		}
		i->mySprite->setFrameWidth(frameWidth);
	}
}
void SpriteEmitter::setFrameHeight(int frameHeight) {
	for(std::vector<EmitObject>::iterator i = emitObjects.begin(); i != emitObjects.end(); i++) {
		if(i->mySprite == NULL) {
			i->mySprite = new GraphicObject();
			i->mySprite->constructDrawer();
		}
		i->mySprite->setFrameHeight(frameHeight);
	}
}
void SpriteEmitter::setFilename(const char* filename) {
	for(std::vector<EmitObject>::iterator i = emitObjects.begin(); i != emitObjects.end(); i++) {
		if(i->mySprite == NULL) {
			i->mySprite = new GraphicObject();
			i->mySprite->constructDrawer();
		}
		i->mySprite->setFilename(filename);
	}
}
void SpriteEmitter::setXFriction(double newXFriction) { xFriction = newXFriction; }
void SpriteEmitter::setYFriction(double newYFriction) { yFriction = newYFriction; }

double SpriteEmitter::getWidth() const { return 1.0; }
double SpriteEmitter::getHeight() const { return 1.0; }
double SpriteEmitter::getXPosition() const { return this->x; }
double SpriteEmitter::getYPosition() const { return this->y; }
double SpriteEmitter::getAngle() { return 0.0; }
int SpriteEmitter::getFrameWidth() { return 1; }
int SpriteEmitter::getFrameHeight() { return 1; }
std::string SpriteEmitter::getFilename() { return ""; }
double SpriteEmitter::getXFriction() const { return xFriction; }
double SpriteEmitter::getYFriction() const { return yFriction; }

void SpriteEmitter::setDeltaXCorrection(double newXCorr) {
	deltaXCorrection = newXCorr;
}
void SpriteEmitter::setDeltaYCorrection(double newYCorr) {
	deltaYCorrection = newYCorr;
}

void SpriteEmitter::initDrawer() {
	for(std::vector<EmitObject>::iterator i = emitObjects.begin(); i != emitObjects.end(); i++) {
		i->mySprite->initDrawer();
	}
}
