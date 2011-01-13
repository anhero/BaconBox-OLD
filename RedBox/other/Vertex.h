#ifndef __VERTEX_H__
#define __VERTEX_H__

#include "Vec2.h"
#include "Edge.h"

namespace RedBox{
    class Edge;
    struct Vertex {
        Vec2 position;
#ifdef REDBOX_PHYSICS_ENABLED
        Vec2 oldPosition;
        Vec2 acceleration;
#endif
        Vertex();
        Vertex(float posX, float posY);
    };
}
#endif