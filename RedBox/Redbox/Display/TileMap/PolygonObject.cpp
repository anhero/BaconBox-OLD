#include "PolygonObject.h"

#include "ObjectLayer.h"

namespace RedBox {
	void PolygonObject::setName(const std::string &newName) {
		if (!parentLayer.getPolygon(newName)) {
			this->TileMapVertexArray::setName(newName);
			parentLayer.dirtyPolygonNames = true;
		}
	}

	PolygonObject::PolygonObject(const std::string &newName,
	                             const Vector2 &newPosition,
	                             const ObjectLayer &newParentLayer) :
		TileMapVertexArray(newName, newPosition, newParentLayer) {
	}

	PolygonObject::PolygonObject(const PolygonObject &src,
	                             const ObjectLayer &newParentLayer) :
		TileMapVertexArray(src, newParentLayer) {
	}

	PolygonObject::~PolygonObject() {
	}
}
