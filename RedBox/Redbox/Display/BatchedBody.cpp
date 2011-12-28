#include "BatchedBody.h"

namespace RedBox {
	BatchedBody::BatchedBody() : Deactivable(), Manageable(), Orderable() {
	}

	BatchedBody::BatchedBody(const BatchedBody &src) : Deactivable(src),
	    Manageable(src), Orderable(src) {
	}

	BatchedBody::~BatchedBody() {
	}

	BatchedBody &BatchedBody::operator=(const BatchedBody &src) {
		this->Deactivable::operator=(src);
		this->Manageable::operator=(src);
		this->Orderable::operator=(src);
		return *this;
	}

	void BatchedBody::setZ(int newZ) {
		this->Orderable::setZ(newZ);
		this->keyChange();
	}
}
