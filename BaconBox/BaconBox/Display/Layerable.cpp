#include "Layerable.h"

namespace BaconBox {
	bool Layerable::LessCompare::operator()(const Layerable *l1,
	                                        const Layerable *l2) {
		return (l1 && l2) && ((!l1->isHud() && l2->isHud()) || (!l1->isHud() && !l2->isHud() && (l1->getZ() < l2->getZ() ||
		                                                        (l1->getZ() == l2->getZ() &&
		                                                         (l1->getXScrollFactor() < l2->getXScrollFactor() ||
		                                                          (l1->getXScrollFactor() == l2->getXScrollFactor() &&
		                                                           l1->getYScrollFactor() < l2->getYScrollFactor()))))) ||
		                      (l1->isHud() && l2->isHud() && l1->getZ() < l2->getZ()));
	}

	Layerable::Layerable() : Disableable(), ManageableByKey(), Orderable(),
		Scrollable() {
	}

	Layerable::Layerable(const Layerable &src) : Disableable(src),
		ManageableByKey(src), Orderable(src), Scrollable(src) {
	}

	Layerable::~Layerable() {
	}

	Layerable &Layerable::operator=(const Layerable &src) {
		this->Disableable::operator=(src);
		this->ManageableByKey::operator=(src);
		this->Orderable::operator=(src);
		this->Scrollable::operator=(src);
		return *this;
	}

	void Layerable::setZ(int newZ) {
		this->Orderable::setZ(newZ);
		this->keyChange();
	}

	void Layerable::setScrollFactor(float newXScrollFactor,
	                                float newYScrollFactor) {
		this->Scrollable::setScrollFactor(newXScrollFactor, newYScrollFactor);
		this->keyChange();
	}

	void Layerable::setHud(bool newHud) {
		this->Scrollable::setHud(newHud);
		this->keyChange();
	}
}
