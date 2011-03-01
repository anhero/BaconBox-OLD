#include "BitHelper.h"

using namespace RedBox;

bool BitHelper::isBigEndian() {
	unsigned char testing[4] = {0x12, 0x34, 0x56, 0x78};
	return *((uint32_t*)(testing)) == 0x12345678;
}

void BitHelper::endianSwap(uint16_t& x) {
    x = (x>>8) | 
	(x<<8);
}

void BitHelper::endianSwap(uint32_t& x) {
    x = (x>>24) | 
	((x<<8) & 0x00FF0000) |
	((x>>8) & 0x0000FF00) |
	(x<<24);
}

void BitHelper::endianSwap(uint64_t& x) {
    x = (x>>56) | 
	((x<<40) & 0x00FF000000000000) |
	((x<<24) & 0x0000FF0000000000) |
	((x<<8)  & 0x000000FF00000000) |
	((x>>8)  & 0x00000000FF000000) |
	((x>>24) & 0x0000000000FF0000) |
	((x>>40) & 0x000000000000FF00) |
	(x<<56);
}