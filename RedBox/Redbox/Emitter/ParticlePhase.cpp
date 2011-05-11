#include "ParticlePhase.h"

using namespace RedBox;

ParticlePhase::ParticlePhase(): phaseDuration(0.0), phaseDurationVariance(0.0),
alphaPerSecond(0.0f), scalingPerSecond(Vec2(0.0f, 0.0f)), anglePerSecond(0.0f) {
}

ParticlePhase::ParticlePhase(double newPhaseDuration,
							 double newPhaseDurationVariance,
							 float newAlphaPerSecond,
							 const Vec2& newScalingPerSecond,
							 float newAnglePerSecond):
phaseDuration(newPhaseDuration),
phaseDurationVariance(newPhaseDurationVariance),
alphaPerSecond(newAlphaPerSecond),
scalingPerSecond(newScalingPerSecond),
anglePerSecond(newAnglePerSecond) {
}
