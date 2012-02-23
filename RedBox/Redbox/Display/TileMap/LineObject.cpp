#include "LineObject.h"

#include "ObjectLayer.h"

namespace RedBox {
	void LineObject::setName(const std::string &newName) {
		if (!parentLayer.getLine(newName)) {
			this->TileMapVertexArray::setName(newName);
			parentLayer.dirtyLineNames = true;
		}
	}

	LineObject::LineObject(const std::string &newName,
	                       const Vector2 &newPosition,
	                       const ObjectLayer &newParentLayer) :
		TileMapVertexArray(newName, newPosition, newParentLayer) {
	}

	LineObject::LineObject(const LineObject &src,
	                       const ObjectLayer &newParentLayer) :
		TileMapVertexArray(src, newParentLayer) {
	}

	LineObject::~LineObject() {
	}
}
