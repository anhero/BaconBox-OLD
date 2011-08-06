#include "ParticlePhase.h"

using namespace RedBox;

ParticlePhase::ParticlePhase(): phaseDuration(0.0), phaseDurationVariance(0.0),
alphaPerSecond(0.0f), scalingPerSecond(Vec2()), anglePerSecond(0.0f),
alphaPerSecondVariance(0.0f), scalingPerSecondVariance(Vec2()),
anglePerSecondVariance(0.0f) {
}

ParticlePhase::ParticlePhase(double newPhaseDuration,
							 double newPhaseDurationVariance,
							 float newAlphaPerSecond,
							 const Vec2& newScalingPerSecond,
							 float newAnglePerSecond,
							 float newAlphaPerSecondVariance,
							 const Vec2& newScalingPerSecondVariance,
							 float newAnglePerSecondVariance,
							 const std::string& newAnimationName):
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
