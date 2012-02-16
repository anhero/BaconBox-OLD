#include "TileMapVertexArray.h"

namespace RedBox {
	TileMapVertexArray::TileMapVertexArray(const std::string &newName,
	                                       const Vector2 &newPosition) :
		TileMapObject(newName, newPosition), Shapable<StandardVertexArray>() {
	}

	TileMapVertexArray::TileMapVertexArray(const TileMapVertexArray &src) :
		TileMapObject(src), Shapable<StandardVertexArray>(src) {
	}

	TileMapVertexArray::~TileMapVertexArray() {
	}

	TileMapVertexArray &TileMapVertexArray::operator=(const TileMapVertexArray &src) {
		this->TileMapObject::operator=(src);
		this->Shapable<StandardVertexArray>::operator=(src);

		return *this;
	}

	void TileMapVertexArray::move(float xDelta, float yDelta) {
		this->TileMapObject::move(xDelta, yDelta);
		getVertices().move(xDelta, yDelta);
	}

	const Vector2 TileMapVertexArray::getCentroid() const {
		return getVertices().getCentroid();
	}

	const Vector2 TileMapVertexArray::getSize() const {
		return getVertices().getSize();
	}

	float TileMapVertexArray::getWidth() const {
		return getVertices().getWidth();
	}

	float TileMapVertexArray::getHeight() const {
		return getVertices().getHeight();
	}
}
