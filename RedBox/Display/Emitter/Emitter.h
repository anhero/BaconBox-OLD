/**
 * @file
 * @ingroup Display
 */
#ifndef RB_EMITTER_H
#define RB_EMITTER_H

#include <vector>

#include "Renderable.h"

namespace RedBox {
	namespace ParticleState {
		enum Enum {
			BIRTH,
			LIFE,
			DYING,
			DEAD
		};
	}
	/**
	 * @ingroup Display
	 */
	class Emitter: public Renderable {
	public:
		struct ParticlePhase {
			ParticlePhase();
			ParticlePhase(double newPhaseDuration,
						  double newPhaseDurationVariance,
						  float newAlphaPerSecond,
						  float newScalingPerSecond);
			double phaseDuration;
			double phaseDurationVariance;
			float alphaPerSecond;
			float scalingPerSecond;
		};
		Emitter();
		Emitter(const Emitter& src);
		~Emitter();
		Emitter& operator=(const Emitter& src);
		void update();
		void render();
		
		
		unsigned int getNbMaxParticles() const;
		unsigned int getNbParticles() const;
		int getNbParticlesToShoot() const;
		double getLifeSpan() const;
		double getElapsedTime() const;
		
		float getAngle() const;
		float getAngleVariance() const;
		float getForce() const;
		float getForceVariance() const;
		double getEmitRate() const;
		double getEmitCounter() const;
		const ParticlePhase& getBirthPhase() const;
		const ParticlePhase& getLifePhase() const;
		const ParticlePhase& getDyingPhase() const;
		
		
		void setNbMaxParticles(unsigned int newNbMaxParticles);
		void setNbParticlesToShoot(int newNbParticlesToShoot);
		void setLifeSpan(double newLifeSpan);
		
		void setAngle(float newAngle);
		void setAngleVariance(float newAngleVariance);
		void setForce(float newForce);
		void setForceVariance(float newForceVariance);
		void setEmitRate(double newEmitRate);
		void setBirthPhase(const ParticlePhase& newBirthPhase);
		void setLifePhase(const ParticlePhase& newLifePhase);
		void setDyingPhase(const ParticlePhase& newDyingPhase);
	protected:
		virtual Renderable* initParticle()=0;
	private:
		struct Particle {
			Particle();
			Particle(double newTimeLeft, ParticleState::Enum newState,
					 Renderable* newRenderable = NULL);
			double timeLeft;
			ParticleState::Enum state;
			Renderable* renderable;
		};
		
		std::vector<Particle> particles;
		unsigned int nbParticles;
		int nbParticlesToShoot;
		double lifeSpan;
		double elapsedTime;

		float angle;
		float angleVariance;
		float force;
		float forceVariance;
		double emitRate;
		double emitCounter;
		ParticlePhase birthPhase;
		ParticlePhase lifePhase;
		ParticlePhase dyingPhase;
		
		bool shootParticle();
		void clean();
		void copyFrom(const Emitter& src);
	};
}
#endif