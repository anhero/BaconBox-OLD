#include "Array.h"

#include <algorithm>

#include "Value.h"

namespace BaconBox {
	Array::Array() : values(NULL), nbValues(0u) {
	}

	Array::Array(SizeType startingSize) : values((startingSize) ? (new Value[startingSize]) : (NULL)) , nbValues(startingSize) {
	}

	Array::Array(SizeType startingSize, const Value &defaultValue) : values((startingSize) ? (new Value[startingSize]) : (NULL)), nbValues(startingSize) {
		for (SizeType i = 0; i < nbValues; ++i) {
			values[i] = defaultValue;
		}
	}

	Array::Array(const Array &src) : values((src.nbValues) ? (new Value[src.nbValues]) : (NULL)), nbValues(src.nbValues) {
		for (SizeType i = 0; i < nbValues; ++i) {
			values[i] = src.values[i];
		}
	}

	Array::~Array() {
		if (values) {
			delete [] values;
			values = NULL;
		}
	}

	Array &Array::operator=(const Array &src) {
		if (this != &src) {
			if (values) {
				delete [] values;
			}

			values = new Value[src.nbValues];
			nbValues = src.nbValues;
		}

		return *this;
	}

	Value &Array::operator[](SizeType index) {
		return values[index];
	}

	const Value &Array::operator[](SizeType index) const {
		return values[index];
	}

	Array::SizeType Array::getSize() const {
		return nbValues;
	}

	void Array::setSize(SizeType newSize) {
		if (newSize > 0) {
			if (newSize != nbValues) {
				Value *newValues = new Value[newSize];
				SizeType smallerSize = std::min(nbValues, newSize);

				for (SizeType i = 0; i < smallerSize; ++i) {
					newValues[i] = values[i];
				}

				if (values) {
					delete [] values;
				}

				values = newValues;
			}

		} else if (values) {
			delete [] values;
			values = NULL;
		}
	}

	void Array::setSize(SizeType newSize, const Value &defaultValue) {
		if (newSize > 0) {
			if (newSize != nbValues) {
				Value *newValues = new Value[newSize];
				SizeType tmpSize = std::min(nbValues, newSize);

				for (SizeType i = 0; i < tmpSize; ++i) {
					newValues[i] = values[i];
				}

				for (SizeType i = nbValues; i < newSize; ++i) {
					newValues[i] = defaultValue;
				}

				if (values) {
					delete [] values;
				}

				values = newValues;
			}

		} else if (values) {
			delete [] values;
			values = NULL;
		}
	}
}
