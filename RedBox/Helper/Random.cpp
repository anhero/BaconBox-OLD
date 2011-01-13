#include "Random.h"

using namespace RedBox;

double Random::D_RAND_MAX = static_cast<double>(RAND_MAX);

int Random::getRandomInteger(int min, int max) {
	return (arc4random() % ((max + 1) - min)) + min;
	//return min + (int) ((double) rand () * (max - min + 1)
	//					/ ((unsigned) RAND_MAX + 1));
}

bool Random::getRandomBool(){
	return arc4random()%2;
}

double Random::getRandomDouble(double min, double max) {
	return (static_cast<double>(rand()) / Random::D_RAND_MAX) * (max - min) + min;
}