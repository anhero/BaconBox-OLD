#include "BaconBox/Emitter/ParticlePhase.h"

namespace BaconBox {

	ParticlePhase::ParticlePhase(): phaseDuration(0.0), phaseDurationVariance(0.0),
		alphaPerSecond(0.0f), scalingPerSecond(Vector2()), anglePerSecond(0.0f),
		alphaPerSecondVariance(0.0f), scalingPerSecondVariance(Vector2()),
		anglePerSecondVariance(0.0f) {
	}

	ParticlePhase::ParticlePhase(double newPhaseDuration,
	                             double newPhaseDurationVariance,
	                             float newAlphaPerSecond,
	                             const Vector2 &newScalingPerSecond,
	                             float newAnglePerSecond,
	                             float newAlphaPerSecondVariance,
	                             const Vector2 &newScalingPerSecondVariance,
	                             float newAnglePerSecondVariance,
	                             const std::string &newAnimationName):
		phaseDuration(newPhaseDuration),
		phaseDurationVariance(newPhaseDurationVariance),
		alphaPerSecond(newAlphaPerSecond),
		scalingPerSecond(newScalingPerSecond),
		anglePerSecond(newAnglePerSecond),
		alphaPerSecondVariance(newAlphaPerSecondVariance),
		scalingPerSecondVariance(newScalingPerSecondVariance),
		anglePerSecondVariance(newAnglePerSecondVariance),
		animationName(newAnimationName) {
	}

	ParticlePhase::ParticlePhase(const ParticlePhase &src) :
		phaseDuration(src.phaseDuration),
		phaseDurationVariance(src.phaseDurationVariance),
		alphaPerSecond(src.alphaPerSecond),
		scalingPerSecond(src.scalingPerSecond),
		anglePerSecond(src.anglePerSecond),
		alphaPerSecondVariance(src.alphaPerSecondVariance),
		scalingPerSecondVariance(src.scalingPerSecondVariance),
		anglePerSecondVariance(src.anglePerSecondVariance),
		animationName(src.animationName) {
	}

	ParticlePhase &ParticlePhase::operator=(const ParticlePhase &src) {
		if (this != &src) {
			phaseDuration = src.phaseDuration;
			phaseDurationVariance = src.phaseDurationVariance;
			alphaPerSecond = src.alphaPerSecond;
			scalingPerSecond = src.scalingPerSecond;
			anglePerSecond = src.anglePerSecond;
			alphaPerSecondVariance = src.alphaPerSecondVariance;
			scalingPerSecondVariance = src.scalingPerSecondVariance;
			anglePerSecondVariance = src.anglePerSecondVariance;
			animationName = src.animationName;
		}

		return *this;
	}
}
