#include "MathHelper.h"

#include <cmath>
#include <climits>

using namespace RedBox;

const float MathHelper::PI = 3.141592f;
const float MathHelper::DEGREE_TO_RADIAN = 0.0174532925f;
const float MathHelper::RADIAN_TO_DEGREE = 57.2957795785523f;

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
	return degrees * DEGREE_TO_RADIAN;
}

float MathHelper::radiansToDegrees(float radians) {
	return radians * RADIAN_TO_DEGREE;
}

unsigned int MathHelper::roundUpDivision(unsigned int dividend,
										 unsigned int divisor) {
	return ((dividend % divisor) ? (dividend / divisor + 1) : (dividend / divisor));
}
