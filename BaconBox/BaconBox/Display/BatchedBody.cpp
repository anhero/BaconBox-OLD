#include "BatchedBody.h"

namespace BaconBox {
	BatchedBody::BatchedBody() : Deactivable(), ManageableByKey(), Orderable() {
	}

	BatchedBody::BatchedBody(const BatchedBody &src) : Deactivable(src),
	    ManageableByKey(src), Orderable(src) {
	}

	BatchedBody::~BatchedBody() {
	}

	BatchedBody &BatchedBody::operator=(const BatchedBody &src) {
		this->Deactivable::operator=(src);
		this->ManageableByKey::operator=(src);
		this->Orderable::operator=(src);
		return *this;
	}

	void BatchedBody::setZ(int newZ) {
		this->Orderable::setZ(newZ);
		this->keyChange();
	}
}
