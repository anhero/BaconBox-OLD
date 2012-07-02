#include "BaconBox/Display/CollisionDetails.h"

namespace BaconBox {
	CollisionDetails::CollisionDetails() : overlap(0.0f), body1(NULL),
		body2(NULL), sidesBody1(), sidesBody2() {
	}

	CollisionDetails::CollisionDetails(const CollisionDetails &src) :
		overlap(src.overlap), body1(src.body1), body2(src.body2),
		sidesBody1(src.sidesBody1), sidesBody2(src.sidesBody2) {
	}

	CollisionDetails &CollisionDetails::operator=(const CollisionDetails &src) {
		if (this != &src) {
			overlap = src.overlap;
			body1 = src.body1;
			body2 = src.body2;
			sidesBody1 = src.sidesBody1;
			sidesBody2 = src.sidesBody2;
		}

		return *this;
	}
}
