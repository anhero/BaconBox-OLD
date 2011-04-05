#include "IEmitter.h"

using namespace RedBox;

IEmitter::IEmitter(): Renderable(), nbParticles(0), nbParticlesToShoot(-1),
lifeSpan(-1.0), elapsedTime(0.0), isActive(true), angle(0.0f),
angleVariance(0.0f), force(0.0f), forceVariance(0.0f), emitRate(0.0),
emitCounter(0.0), birthPhase(ParticlePhase()), lifePhase(ParticlePhase()),
dyingPhase(ParticlePhase()) {
}
IEmitter::IEmitter(const IEmitter& src): Renderable(src),
nbParticles(src.nbParticles), nbParticlesToShoot(src.nbParticlesToShoot),
lifeSpan(src.lifeSpan), elapsedTime(src.elapsedTime), isActive(src.isActive),
angle(src.angle), angleVariance(src.angleVariance), force(src.force),
forceVariance(src.forceVariance), emitRate(src.emitRate),
emitCounter(src.emitCounter), birthPhase(src.birthPhase),
lifePhase(src.lifePhase), dyingPhase(src.dyingPhase) {
}

IEmitter::~IEmitter() {
}

IEmitter& IEmitter::operator=(const IEmitter& src) {
	Renderable::operator=(src);
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

bool IEmitter::getIsActive() const {
	return isActive;
}

float IEmitter::getAngle() const {
	return angle;
}

float IEmitter::getAngleVariance() const {
	return angleVariance;
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

void IEmitter::activate() {
	isActive = true;
}

void IEmitter::deactivate() {
	isActive = false;
}

void IEmitter::setAngle(float newAngle) {
	angle = newAngle;
}

void IEmitter::setAngleVariance(float newAngleVariance) {
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

void IEmitter::clean() {
	nbParticles = 0;
	nbParticlesToShoot = -1;
	lifeSpan = 0.0;
	elapsedTime = 0.0;
	isActive = true;
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
			isActive = src.isActive;
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