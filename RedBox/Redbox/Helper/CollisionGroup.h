/**
 * @file
 * @ingroup Physics
 */
#ifndef RB_COLLISION_GROUP_H
#define RB_COLLISION_GROUP_H

#include <set>
#include <list>
#include <deque>
#include <utility>

#include "StackPool.h"
#include "AxisAlignedBoundingBox.h"
#include "CollisionDetails.h"

namespace RedBox {
	class Collidable;

	/**
	 * Represents a group of bodies used to optimize collisions between a lot of
	 * bodies.
	 * @ingroup Physics
	 */
	class CollisionGroup {
	public:
		typedef std::set<Collidable *> BodySet;

		static const unsigned int DEFAULT_DEPTH = 5;

		/**
		 * Constructor. Initializes the collision group's quadtree's bounds and
		 * depth.
		 * @param newBounds Starting bounds for the collision group's quadtree.
		 * If bodies are added and are outside those bounds, the quadtree
		 * will grow upwards to make the body fit in. It might just make the
		 * quadtree lest optimized.
		 * @param newDepth Starting depth for the collision group's quadtree. If
		 * a body outside the bounds is added to the group, the depth will
		 * temporarily increase to make the body fit in the quadtree.
		 * @param newPoolDepth Depth used to calculate the number of quad nodes
		 * to initialize in the pool. The pool is used to optimize the speed
		 * of the quadtree's construction. The same depth as the maximum depth
		 * is usually a good choice.
		 */
		explicit CollisionGroup(const AxisAlignedBoundingBox &newBounds,
		                        unsigned int newDepth = DEFAULT_DEPTH,
								unsigned int newPoolDepth = DEFAULT_DEPTH);

		/**
		 * Copy constructor. Makes a copy of the given collision group. Must be
		 * updated for its collide() functions to work properly, even if the
		 * source collision group was already updated correctly.
		 * @param src Collision group to mak a copy of.
		 */
		CollisionGroup(const CollisionGroup &src);

		/**
		 * Destructor.
		 */
		~CollisionGroup();

		/**
		 * Assignment operator.
		 * @param src Collision group to make a copy of.
		 * @return Reference to the modified collision group. Must be updated
		 * before the collide function can work properly.
		 */
		CollisionGroup &operator=(const CollisionGroup &src);

		/**
		 * Reconstructs the quadtree to get ready for collision testing.
		 */
		void update();

		/**
		 * Adds a body to the collision group.
		 * @param newBody Pointer to the new body to add to the collision group.
		 */
		void add(Collidable *newBody);

		/**
		 * Removes a body from the collision group.
		 * @param body Pointer to the body to remove from the group.
		 */
		void remove(Collidable *body);

		/**
		 * Test a body for collision with the collision group.
		 * @return True if the body collides with at least one of the group's
		 * bodies.
		 */
		const std::list<CollisionDetails> collide(Collidable *body);

		const std::list<CollisionDetails> collide(CollisionGroup *collisionGroup);

		const std::list<CollisionDetails> collide();

		BodySet &getBodies();

		const BodySet &getBodies() const;

		unsigned int getDepth() const;

		void setDepth(unsigned int newDepth);

		AxisAlignedBoundingBox &getBounds();

		const AxisAlignedBoundingBox &getBounds() const;

		unsigned int getPoolDepth() const;

		void setPoolDepth(unsigned int newPoolDepth);
	private:
		typedef std::list<Collidable *> BodyList;

		static const unsigned int NW = 0;
		static const unsigned int NE = 1;
		static const unsigned int SW = 2;
		static const unsigned int SE = 3;

		struct QuadNode {
			QuadNode();
			QuadNode(const AxisAlignedBoundingBox &newBounds);
			AxisAlignedBoundingBox bounds;
			QuadNode *nodes[4];
			BodyList boxes;
		};

		static StackPool<QuadNode>::SizeType calculatePoolSize(unsigned int depth);

		QuadNode *getNewQuad();
		QuadNode *getNewQuad(const AxisAlignedBoundingBox &newBounds);

		void subInsert(const AxisAlignedBoundingBox &newBox, Collidable *newBody);
		void supInsert(const AxisAlignedBoundingBox &newBox, Collidable *newBody);

		void clearOverflow();

		BodySet bodies;
		QuadNode *root;
		unsigned int depth;
		unsigned int tmpDepth;

		AxisAlignedBoundingBox bounds;

		unsigned int poolDepth;
		StackPool<QuadNode> quadPool;
		std::deque<QuadNode *> quadOverflow;
	};
}

#endif
