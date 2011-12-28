#include "BatchedBody.h"

namespace RedBox {
	BatchedBody::BatchedBody() : Disableable(), Manageable(), Orderable() {
	}

	BatchedBody::BatchedBody(const BatchedBody &src) : Disableable(src),
	    Manageable(src), Orderable(src) {
	}

	BatchedBody::~BatchedBody() {
	}

	BatchedBody &BatchedBody::operator=(const BatchedBody &src) {
		this->Disableable::operator=(src);
		this->Manageable::operator=(src);
		this->Orderable::operator=(src);
		return *this;
	}

	void BatchedBody::setZ(int newZ) {
		this->Orderable::setZ(newZ);
		this->keyChange();
	}
}
