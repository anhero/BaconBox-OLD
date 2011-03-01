#include "BitHelper.h"

using namespace RedBox;

bool BitHelper::isBigEndian() {
	unsigned char testing[4] = {0x12, 0x34, 0x56, 0x78};
	return *((uint32_t*)(testing)) == 0x12345678;
}