#include "ManageableByKey.h"

namespace RedBox {
	ManageableByKey::ManageableByKey() : Keyable(), Manageable() {
	}

	ManageableByKey::ManageableByKey(const ManageableByKey &src) : Keyable(src),
		Manageable(src) {

	}

	ManageableByKey::~ManageableByKey() {
	}

	ManageableByKey &ManageableByKey::operator=(const ManageableByKey &src) {
		this->Keyable::operator=(src);
		this->Manageable::operator=(src);
		return *this;
	}
}