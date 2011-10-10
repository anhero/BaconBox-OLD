#include "StandardVerticesArray.h"

namespace RedBox {
	StandardVerticesArray::StandardVerticesArray() : VerticesArray(),
		vertices() {
	}

	StandardVerticesArray::StandardVerticesArray(SizeType newSize,
	                                             ConstReference defaultValue) :
		VerticesArray(), vertices(newSize, defaultValue) {
	}

	StandardVerticesArray::StandardVerticesArray(const StandardVerticesArray &src) :
		VerticesArray(src), vertices(src.vertices) {
	}

	StandardVerticesArray::~StandardVerticesArray() {
	}

	StandardVerticesArray &StandardVerticesArray::operator=(const RedBox::StandardVerticesArray &src) {
		if (this != &src) {
			vertices = src.vertices;
		}

		return *this;
	}

	StandardVerticesArray::Iterator StandardVerticesArray::getBegin() {
		return vertices.begin();
	}

	StandardVerticesArray::ConstIterator StandardVerticesArray::getBegin() const {
		return vertices.begin();
	}

	StandardVerticesArray::Iterator StandardVerticesArray::getEnd() {
		return vertices.end();
	}

	StandardVerticesArray::ConstIterator StandardVerticesArray::getEnd() const {
		return vertices.end();
	}

	StandardVerticesArray::ReverseIterator StandardVerticesArray::getReverseBegin() {
		return vertices.rbegin();
	}

	StandardVerticesArray::ConstReverseIterator StandardVerticesArray::getReverseBegin() const {
		return vertices.rbegin();
	}

	StandardVerticesArray::ReverseIterator StandardVerticesArray::getReverseEnd() {
		return vertices.rend();
	}

	StandardVerticesArray::ConstReverseIterator StandardVerticesArray::getReverseEnd() const {
		return vertices.rend();
	}

	bool StandardVerticesArray::isEmpty() const {
		return vertices.empty();
	}

	StandardVerticesArray::SizeType StandardVerticesArray::getNbVertices() const {
		return vertices.size();
	}

	void StandardVerticesArray::clear() {
		vertices.clear();
	}

	StandardVerticesArray::Iterator StandardVerticesArray::insert(Iterator position,
	                                                              ConstReference value) {
		return vertices.insert(position, value);
	}

	void StandardVerticesArray::insert(Iterator position, SizeType count,
	                                   ConstReference value) {
		vertices.insert(position, count, value);
	}

	StandardVerticesArray::Iterator StandardVerticesArray::erase(Iterator position) {
		return vertices.erase(position);
	}

	StandardVerticesArray::Iterator StandardVerticesArray::erase(Iterator first,
	                                                             Iterator last) {
		return vertices.erase(first, last);
	}

	void StandardVerticesArray::pushBack(ConstReference newVertex) {
		vertices.push_back(newVertex);
	}

	void StandardVerticesArray::popBack() {
		vertices.pop_back();
	}

	void StandardVerticesArray::resize(SizeType count, ConstReference value) {
		vertices.resize(count, value);
	}
}
