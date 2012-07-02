#include "BaconBox/Emitter/Emitter.h"

#include "BaconBox/Helper/MathHelper.h"

namespace BaconBox {
	Emitter::Emitter() : elapsedTime(0.0), nbParticles(0),
		nbParticlesToShoot(-1), lifeSpan(-1.0), started(false),
		explosion(false), shootingAngle(0.0f), shootingAngleVariance(0.0f),
		shootingForce(0.0f), shootingForceVariance(0.0f), timePerSpawn(-1.0),
		phases(), toDeleteWhenDone(false) {
	}

	Emitter::Emitter(const Emitter &src) :
		elapsedTime(src.elapsedTime), nbParticles(src.nbParticles),
		nbParticlesToShoot(src.nbParticlesToShoot), lifeSpan(src.lifeSpan),
		started(src.started), explosion(src.explosion),
		shootingAngle(src.shootingAngle),
		shootingAngleVariance(src.shootingAngleVariance),
		shootingForce(src.shootingForce),
		shootingForceVariance(src.shootingForceVariance),
		timePerSpawn(src.timePerSpawn), phases(src.phases),
		toDeleteWhenDone(src.toDeleteWhenDone) {
	}

	Emitter::~Emitter() {
	}

	Emitter &Emitter::operator=(const Emitter &src) {
		if (this != &src) {
			elapsedTime = src.elapsedTime;
			nbParticles = src.nbParticles;
			nbParticlesToShoot = src.nbParticlesToShoot;
			lifeSpan = src.lifeSpan;
			started = src.started;
			explosion = src.explosion;
			shootingAngle = src.shootingAngle;
			shootingAngleVariance = src.shootingAngleVariance;
			shootingForce = src.shootingForce;
			shootingForceVariance = src.shootingForceVariance;
			timePerSpawn = src.timePerSpawn;
			phases = src.phases;
			toDeleteWhenDone = src.toDeleteWhenDone;
		}

		return *this;
	}

	unsigned int Emitter::getNbParticles() const {
		return nbParticles;
	}

	int Emitter::getNbParticlesToShoot() const {
		return nbParticlesToShoot;
	}

	void Emitter::setNbParticlesToShoot(int newNbParticlesToShoot) {
		// If we received a negative number, we simply set it to -1.
		if (newNbParticlesToShoot < 0) {
			nbParticlesToShoot = -1;

		} else {
			nbParticlesToShoot = newNbParticlesToShoot;
		}
	}

	double Emitter::getLifeSpan() const {
		return lifeSpan;
	}

	void Emitter::setLifeSpan(double newLifeSpan) {
		if (newLifeSpan < 0.0) {
			lifeSpan = -1.0;

		} else {
			lifeSpan = newLifeSpan;
		}
	}

	double Emitter::getElapsedTime() const {
		return elapsedTime;
	}

	bool Emitter::isStarted() const {
		return started;
	}

	void Emitter::start() {
		started = true;
	}

	void Emitter::stop() {
		started = false;
	}
	
	bool Emitter::isExplosion() const {
		return explosion;
	}
	
	void Emitter::setExplosion(bool newExplosion) {
		explosion = newExplosion;
	}

	float Emitter::getShootingAngle() const {
		return shootingAngle;
	}

	void Emitter::setShootingAngle(float newShootingAngle) {
		shootingAngle = MathHelper::clampAngle(newShootingAngle);
	}

	float Emitter::getShootingAngleVariance() const {
		return shootingAngleVariance;
	}

	void Emitter::setShootingAngleVariance(float newShootingAngleVariance) {
		shootingAngleVariance = MathHelper::clamp(newShootingAngleVariance, 0.0f, 180.0f);
	}

	float Emitter::getShootingForce() const {
		return shootingForce;
	}

	void Emitter::setShootingForce(float newShootingForce) {
		shootingForce = newShootingForce;
	}

	float Emitter::getShootingForceVariance() const {
		return shootingForceVariance;
	}

	void Emitter::setShootingForceVariance(float newShootingForceVariance) {
		shootingForceVariance = newShootingForceVariance;
	}

	double Emitter::getTimeBetweenSpawns() const {
		return timePerSpawn;
	}

	double Emitter::getSpawningRate() const {
		if (timePerSpawn == -1.0) {
			return 0.0;

		} else {
			return 1.0 / timePerSpawn;
		}
	}

	void Emitter::setSpawningRate(double newSpawningRate) {
		if (newSpawningRate == 0.0) {
			timePerSpawn = -1.0;
		}

		timePerSpawn = 1.0 / newSpawningRate;
	}

	void Emitter::setTimeBetweenSpawns(double newTimePerSpawn) {
		if (newTimePerSpawn == -1.0 || newTimePerSpawn > 0.0) {
			timePerSpawn = newTimePerSpawn;
		}
	}

	Emitter::PhaseList &Emitter::getPhases() {
		return phases;
	}

	const Emitter::PhaseList &Emitter::getPhases() const {
		return phases;
	}

	bool Emitter::isToDeleteWhenDone() const {
		return toDeleteWhenDone;
	}

	void Emitter::setToDeleteWhenDone(bool newToDeleteWhenDone) {
		toDeleteWhenDone = newToDeleteWhenDone;
	}
}
