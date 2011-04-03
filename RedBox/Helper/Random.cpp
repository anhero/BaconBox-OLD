#include "Random.h"

#include "PlatformFlagger.h"

#include <ctime>

using namespace RedBox;

double Random::D_RAND_MAX = static_cast<double>(RAND_MAX);
bool Random::initialized = false;

int Random::getRandomInteger(int min, int max) {
	if(!initialized) {
		init();
	}
#ifdef RB_WIN32
	return (rand() % ((max + 1) - min)) + min;
#else
	return (arc4random() % ((max + 1) - min)) + min;
#endif
	//return min + (int) ((double) rand () * (max - min + 1)
	//					/ ((unsigned) RAND_MAX + 1));
}

bool Random::getRandomBool(){
	if(!initialized) {
		init();
	}
#ifdef RB_WIN32
	return rand()%2;
#else
	return arc4random()%2;
#endif
}

double Random::getRandomDouble(double min, double max) {
	if(!initialized) {
		init();
	}
	return (static_cast<double>(rand()) / Random::D_RAND_MAX) * (max - min) + min;
}

void Random::init() {
	srand(time(NULL));
	initialized = true;
}
