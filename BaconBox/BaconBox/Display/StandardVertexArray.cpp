#include "StandardVertexArray.h"

namespace BaconBox {
	StandardVertexArray::StandardVertexArray() : VertexArray(),
		vertices() {
	}

	StandardVertexArray::StandardVertexArray(SizeType newSize,
	                                             ConstReference defaultValue) :
		VertexArray(), vertices(newSize, defaultValue) {
	}

	StandardVertexArray::StandardVertexArray(const StandardVertexArray &src) :
		VertexArray(src), vertices(src.vertices) {
	}

	StandardVertexArray::~StandardVertexArray() {
	}

	StandardVertexArray &StandardVertexArray::operator=(const BaconBox::StandardVertexArray &src) {
		if (this != &src) {
			vertices = src.vertices;
		}

		return *this;
	}

	StandardVertexArray::Iterator StandardVertexArray::getBegin() {
		return vertices.begin();
	}

	StandardVertexArray::ConstIterator StandardVertexArray::getBegin() const {
		return vertices.begin();
	}

	StandardVertexArray::Iterator StandardVertexArray::getEnd() {
		return vertices.end();
	}

	StandardVertexArray::ConstIterator StandardVertexArray::getEnd() const {
		return vertices.end();
	}

	StandardVertexArray::ReverseIterator StandardVertexArray::getReverseBegin() {
		return vertices.rbegin();
	}

	StandardVertexArray::ConstReverseIterator StandardVertexArray::getReverseBegin() const {
		return vertices.rbegin();
	}

	StandardVertexArray::ReverseIterator StandardVertexArray::getReverseEnd() {
		return vertices.rend();
	}

	StandardVertexArray::ConstReverseIterator StandardVertexArray::getReverseEnd() const {
		return vertices.rend();
	}

	bool StandardVertexArray::isEmpty() const {
		return vertices.empty();
	}

	StandardVertexArray::SizeType StandardVertexArray::getNbVertices() const {
		return vertices.size();
	}

	void StandardVertexArray::clear() {
		vertices.clear();
	}

	StandardVertexArray::Iterator StandardVertexArray::insert(Iterator position,
	                                                              ConstReference value) {
		return vertices.insert(position, value);
	}

	void StandardVertexArray::insert(Iterator position, SizeType count,
	                                   ConstReference value) {
		vertices.insert(position, count, value);
	}

	void StandardVertexArray::insert(Iterator position, Iterator first, Iterator last) {
		vertices.insert(position, first, last);
	}

	StandardVertexArray::Iterator StandardVertexArray::erase(Iterator position) {
		return vertices.erase(position);
	}

	StandardVertexArray::Iterator StandardVertexArray::erase(Iterator first,
	                                                             Iterator last) {
		return vertices.erase(first, last);
	}

	void StandardVertexArray::pushBack(ConstReference newVertex) {
		vertices.push_back(newVertex);
	}

	void StandardVertexArray::popBack() {
		vertices.pop_back();
	}

	void StandardVertexArray::resize(SizeType count, ConstReference value) {
		vertices.resize(count, value);
	}

	void StandardVertexArray::reserve(SizeType size) {
		vertices.reserve(size);
	}
}
