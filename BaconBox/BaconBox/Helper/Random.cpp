#include "BaconBox/Helper/Random.h"

#include "BaconBox/PlatformFlagger.h"

#include <ctime>

using namespace BaconBox;

double Random::D_RAND_MAX = static_cast<double>(RAND_MAX);
bool Random::initialized = false;

int Random::getRandomInteger(int min, int max) {
	if(!initialized) {
		init();
	}
#ifdef RB_IPHONE_PLATFORM
	return (arc4random() % ((max + 1) - min)) + min;
#else
	return (rand() % ((max + 1) - min)) + min;
#endif
	//return min + (int) ((double) rand () * (max - min + 1)
	//					/ ((unsigned) RAND_MAX + 1));
}

bool Random::getRandomBool(){
	if(!initialized) {
		init();
	}
#ifdef RB_IPHONE_PLATFORM
	return arc4random()%2;
#else
	return rand()%2;
#endif
}

double Random::getRandomDouble(double min, double max) {
	if(!initialized) {
		init();
	}
	return (static_cast<double>(rand()) / Random::D_RAND_MAX) * (max - min) + min;
}

double Random::getRandomFloat(float min, float max) {
	if(!initialized) {
		init();
	}
	return (static_cast<float>(rand()) / Random::D_RAND_MAX) * (max - min) + min;
}

void Random::init() {
	srand(time(NULL));
	initialized = true;
}
