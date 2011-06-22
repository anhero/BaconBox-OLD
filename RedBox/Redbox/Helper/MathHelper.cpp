#include "MathHelper.h"

#include <cmath>
#include <climits>

using namespace RedBox;

const float MathHelper::PI = 3.141592f;
const float MathHelper::DEGREE_TO_RADIAN = 0.017453f;

int MathHelper::nextPowerOf2(int number){
	if(number == 0) {
		return 1;
	}

	--number;
	for (unsigned int i = 1; i < sizeof(int) * CHAR_BIT; i <<= 1) {
		number = number | number >> i;
	}
	return number + 1;
}

float MathHelper::modFloat(float dividend, float divisor) {
	return dividend - (floor(dividend / divisor) * divisor);
}

float MathHelper::degreesToRadians(float degrees) {
	return degrees * 0.0174532925f;
}
