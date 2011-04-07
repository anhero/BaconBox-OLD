#include "MathHelper.h"

#include <cmath>
#include <climits>

using namespace RedBox;

int MathHelper::nextPowerOf2(int number){
	if (number == 0)
		return 1;
	--number;
	for (int i=1; i < sizeof(int)*CHAR_BIT; i <<= 1)
		number = number | number >> i;
	return number+1;
}

float MathHelper::modFloat(float dividend, float divisor) {
	return dividend - (floor(dividend / divisor) * divisor);
}