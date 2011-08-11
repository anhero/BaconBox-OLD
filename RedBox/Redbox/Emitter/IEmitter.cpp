#include "IEmitter.h"

using namespace RedBox;

IEmitter::IEmitter(): GraphicBody(), nbParticles(0), nbParticlesToShoot(-1),
lifeSpan(-1.0), elapsedTime(0.0), started(false), angle(0.0f),
angleVariance(360.0f), force(200.0f), forceVariance(25.0f), emitRate(5.0),
emitCounter(0.0), birthPhase(ParticlePhase(0.25, 0.0, 1000.0f)),
lifePhase(ParticlePhase(0.25, 0.1)),
dyingPhase(ParticlePhase(0.5, 0.0, -1000.0f)),
dieOnDeactivate(false) {
}
IEmitter::IEmitter(const IEmitter& src): GraphicBody(src),
nbParticles(src.nbParticles), nbParticlesToShoot(src.nbParticlesToShoot),
lifeSpan(src.lifeSpan), elapsedTime(src.elapsedTime), started(src.started),
angle(src.angle), angleVariance(src.angleVariance), force(src.force),
forceVariance(src.forceVariance), emitRate(src.emitRate),
emitCounter(src.emitCounter), birthPhase(src.birthPhase),
lifePhase(src.lifePhase), dyingPhase(src.dyingPhase),
dieOnDeactivate(src.dieOnDeactivate) {
}

IEmitter::~IEmitter() {
}

IEmitter& IEmitter::operator=(const IEmitter& src) {
	GraphicBody::operator=(src);
	copyFrom(src);
	return *this;
}

unsigned int IEmitter::getNbParticles() const {
	return nbParticles;
}

int IEmitter::getNbParticlesToShoot() const {
	return nbParticlesToShoot;
}

double IEmitter::getLifeSpan() const {
	return lifeSpan;
}

double IEmitter::getElapsedTime() const {
	return elapsedTime;
}

bool IEmitter::isStarted() const {
	return started;
}

float IEmitter::getForce() const {
	return force;
}

float IEmitter::getForceVariance() const {
	return forceVariance;
}

double IEmitter::getEmitRate() const {
	return emitRate;
}

const ParticlePhase& IEmitter::getBirthPhase() const {
	return birthPhase;
}

const ParticlePhase& IEmitter::getLifePhase() const {
	return lifePhase;
}

const ParticlePhase& IEmitter::getDyingPhase() const {
	return dyingPhase;
}

void IEmitter::setNbParticlesToShoot(int newNbParticlesToShoot) {
	nbParticlesToShoot = newNbParticlesToShoot;
}

void IEmitter::setLifeSpan(double newLifeSpan) {
	elapsedTime = 0.0;
	lifeSpan = newLifeSpan;
}

void IEmitter::start() {
	started = true;
}

void IEmitter::stop() {
	started = false;
}

void IEmitter::rotateFromPoint(float rotationAngle, const Vec2& rotationPoint) {
	this->GraphicBody::rotateFromPoint(rotationAngle, rotationPoint);
	Vec2 tmp = getPosition() - rotationPoint;
	tmp.rotate(rotationAngle);
	tmp += rotationPoint;
	this->GraphicBody::setPosition(tmp.getX(), tmp.getY());
}

float IEmitter::getShootingAngle() const {
	return angle;
}

float IEmitter::getShootingAngleVariance() const {
	return angleVariance;
}

void IEmitter::setShootingAngle(float newAngle) {
	angle = newAngle;
}

void IEmitter::setShootingAngleVariance(float newAngleVariance) {
	angleVariance = newAngleVariance;
}

void IEmitter::setForce(float newForce) {
	force = newForce;
}

void IEmitter::setForceVariance(float newForceVariance) {
	forceVariance = newForceVariance;
}

void IEmitter::setEmitRate(double newEmitRate) {
	emitRate = newEmitRate;
}

void IEmitter::setBirthPhase(const ParticlePhase& newBirthPhase) {
	birthPhase = newBirthPhase;
}

void IEmitter::setLifePhase(const ParticlePhase& newLifePhase) {
	lifePhase = newLifePhase;
}

void IEmitter::setDyingPhase(const ParticlePhase& newDyingPhase) {
	dyingPhase = newDyingPhase;
}

void IEmitter::deleteOnDeactivate() {
	dieOnDeactivate = true;
}
void IEmitter::dontDeleteOnDeactivate() {
	dieOnDeactivate = false;
}

void IEmitter::clean() {
	nbParticles = 0;
	nbParticlesToShoot = -1;
	lifeSpan = 0.0;
	elapsedTime = 0.0;
	started = false;
	angle = 0.0f;
	angleVariance = 0.0f;
	force = 0.0f;
	forceVariance = 0.0f;
	emitRate = 0.0;
	emitCounter = 0.0;
	birthPhase = ParticlePhase();
	lifePhase = ParticlePhase();
	dyingPhase = ParticlePhase();
}

void IEmitter::copyFrom(const IEmitter& src) {
	if(this != &src) {
		if(&src) {
			nbParticles = src.nbParticles;
			nbParticlesToShoot = src.nbParticlesToShoot;
			lifeSpan = src.lifeSpan;
			elapsedTime = src.elapsedTime;
			started = src.started;
			angle = src.angle;
			angleVariance = src.angleVariance;
			force = src.force;
			forceVariance = src.forceVariance;
			emitRate = src.emitRate;
			emitCounter = src.emitCounter;
			birthPhase = src.birthPhase;
			lifePhase = src.lifePhase;
			dyingPhase = src.dyingPhase;
		} else {
			clean();
		}
	}
}

float IEmitter::getWidth() const {
	return 1.0f;
}
float IEmitter::getHeight() const{
	return 1.0f;
}
