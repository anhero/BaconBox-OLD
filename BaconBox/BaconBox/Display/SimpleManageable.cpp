#include "BaconBox/Display/SimpleManageable.h"

namespace BaconBox {
	SimpleManageable::SimpleManageable() : Disableable(), Manageable() {
	}

	SimpleManageable::SimpleManageable(const SimpleManageable &src) :
		Disableable(src), Manageable(src) {
	}

	SimpleManageable::~SimpleManageable() {
	}

	SimpleManageable &SimpleManageable::operator=(const SimpleManageable &src) {
		this->Disableable::operator=(src);
		this->Manageable::operator=(src);
		return *this;
	}
}
