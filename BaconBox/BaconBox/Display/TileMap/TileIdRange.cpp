#include "TileIdRange.h"

namespace BaconBox {
	const unsigned int FLIPPED_HORIZONTALLY_FLAG = 0x80000000;
	const unsigned int FLIPPED_VERTICALLY_FLAG = 0x40000000;
	const unsigned int FLIPPED_DIAGONALLY_FLAG = 0x20000000;
	const unsigned int FLIPPED_FLAGS = ~(FLIPPED_HORIZONTALLY_FLAG | FLIPPED_VERTICALLY_FLAG | FLIPPED_DIAGONALLY_FLAG);

	bool TileIdRange::Comparator::operator()(const TileIdRange &first,
	                                         const TileIdRange &second) const {
		return withoutFlipFlags(first.min) < withoutFlipFlags(second.min) &&
		       withoutFlipFlags(first.max) <= withoutFlipFlags(second.max);
	}

	unsigned int TileIdRange::withoutFlipFlags(unsigned int value) {
		return value & FLIPPED_FLAGS;
	}

	bool TileIdRange::isFlippedHorizontally(unsigned int value) {
		return static_cast<bool>(value & FLIPPED_HORIZONTALLY_FLAG);
	}

	bool TileIdRange::isFlippedVertically(unsigned int value) {
		return static_cast<bool>(value & FLIPPED_VERTICALLY_FLAG);
	}

	bool TileIdRange::isFlippedDiagonally(unsigned int value) {
		return static_cast<bool>(value & FLIPPED_DIAGONALLY_FLAG);
	}

	unsigned int TileIdRange::flipHorizontally(unsigned int value) {
		return value ^ FLIPPED_HORIZONTALLY_FLAG;
	}

	unsigned int TileIdRange::flipVertically(unsigned int value) {
		return value ^ FLIPPED_VERTICALLY_FLAG;
	}

	unsigned int TileIdRange::flipDiagonally(unsigned int value) {
		return value ^ FLIPPED_DIAGONALLY_FLAG;
	}

	TileIdRange::TileIdRange() : min(0u), max(0u) {
	}

	TileIdRange::TileIdRange(unsigned int center) : min(center), max(center) {
	}

	TileIdRange::TileIdRange(unsigned int newMin, unsigned int newMax) : min(newMin), max(newMax) {
	}

	TileIdRange::TileIdRange(const TileIdRange &src) : min(src.min), max(src.max) {
	}

	bool TileIdRange::isWithinRange(unsigned int value) const {
		return (value = withoutFlipFlags(value)) >= min && value < max;
	}
}