/**
 * @file
 * @ingroup Group
 */
#include "Vertex.h"
#include <vector>
#include <list>
#ifndef RB_COLLIDER_H
#define RB_COLLIDER_H

namespace RedBox{
	/** 
	 *
     * @ingroup Group
     */
	class Collider{
	public:
		Vertex  * getCenter();
		virtual int getMinX() = 0;
		virtual int getMaxX() = 0;
		virtual int getMinY() = 0;
		virtual int getMaxY() = 0;
		
		bool collide(Collider * aCollider);
		bool collide(std::list<Collider*> * colliderGroup);

		
		static bool collide(Collider * aCollider, std::list<Collider*> * colliderGroup);
		static bool collide(Collider * firstCollider, Collider * secondCollider);
		
		
		bool overlap(Collider * aCollider);
		bool overlap(std::list<Collider*> * colliderGroup);
		
		
		static bool overlap(Collider * aCollider, std::list<Collider*> * colliderGroup);
		static bool overlap(Collider * firstCollider, Collider * secondCollider);
		
	protected:
		
		Vertex * center;
		
		void setRadius(int radius);
		int getRadius();
		enum {
			rectangle,
			circle
		} ColliderType;
	private:
		
	};
}

#endif
