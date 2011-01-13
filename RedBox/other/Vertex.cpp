#include "Vertex.h"

using namespace RedBox;

Vertex::Vertex() {
    position.setXPtr(NULL);
    position.setYPtr(NULL);
#ifdef REDBOX_PHYSICS_ENABLED
	oldPosition.setXPtr(NULL);
	oldPosition.setXPtr(NULL);
#endif
}

Vertex::Vertex(float posX, float posY ) {
	position.setX(posX);
	position.setY(posY);
#ifdef REDBOX_PHYSICS_ENABLED
	oldPosition.setX(posX);
	oldPosition.setY(posY);
#endif
}