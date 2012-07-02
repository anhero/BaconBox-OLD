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

#include "BaconBox/Helper/StackPool.h"
#include "BaconBox/Display/AxisAlignedBoundingBox.h"
#include "BaconBox/Display/CollisionDetails.h"

namespace BaconBox {
	class Collidable;

	/**
	 * Represents a group of bodies used to optimize collisions between a lot of
	 * bodies. Uses a quadtree that needs to be reconstructed with the method
	 * update() when the bodies in the collision group are moved or when bodies
	 * are added or removed. To speed up the reconstruction of the quadtree,
	 * the collision group uses a pool of quad nodes.
	 * @see BaconBox::StackPool
	 * @ingroup Physics
	 */
	class CollisionGroup {
	public:
		/// Type used to represent the set of bodies contained in the group.
		typedef std::set<Collidable *> BodySet;

		/**
		 * Default depth of the quad tree and default depth used to calculate
		 * the number of quad nodes to initialize in the pool.
		 */
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
		 * Adds a body to the collision group. The collision group will need to
		 * be updated for this body to not be ignored when testing for
		 * collisions.
		 * @param newBody Pointer to the new body to add to the collision group.
		 *
		 */
		void add(Collidable *newBody);

		/**
		 * Removes a body from the collision group. The collision group will
		 * need to be updated after removing the body.
		 * @param body Pointer to the body to remove from the group.
		 */
		void remove(Collidable *body);

		/**
		 * Tests a body for collision with the collision group.
		 * @param body Pointer to the body to test collisions with.
		 * @return List of collision details that occured. If the list is empty,
		 * it means there were no collisions. In all the collision details,
		 * the first body is the one in the group and the second body is the one
		 * received in parameter here.
		 */
		const std::list<CollisionDetails> collide(Collidable *body);

		/**
		 * Tests collisions between two collision groups. You can test the
		 * current collision group with itself or with any other collision
		 * group.
		 * @param collisionGroup Pointer to the collision group to detect
		 * collisions with. Can be "this".
		 * @return List containing the collision details of all the detected
		 * collisions. If the list is empty, it means there were no collisions.
		 */
		const std::list<CollisionDetails> collide(CollisionGroup *collisionGroup);

		/**
		 * Tests collisions with itself. Effectively calls the function
		 * collide(this).
		 * @return List containing the collision details of all the detected
		 * collisions. If the list is empty, it means there were no collisions.
		 * @see BaconBox::collide(CollisionGroup *collisionGroup)
		 */
		const std::list<CollisionDetails> collide();

		/**
		 * Gets the set containing the bodies that are in the
		 * collision group.
		 * @return Reference to the set containing the bodies.
		 */
		BodySet &getBodies();

		/**
		 * Gets the set containing the bodies that are in the
		 * collision group.
		 * @return Const reference to the set containing the bodies.
		 */
		const BodySet &getBodies() const;

		/**
		 * Gets the maximum depth of the collision group's quadtree.
		 * @return Depth of the quadtree.
		 * @see BaconBox::CollisionGroup::depth
		 */
		unsigned int getDepth() const;

		/**
		 * Sets the maximum depth of the collision group's quadtree.
		 * @param newDepth New depth of the quadtree. For this new value to be
		 * taken into account, the collision group must be updated before
		 * testing for collisions.
		 */
		void setDepth(unsigned int newDepth);

		/**
		 * Gets the collision group's initial bounds.
		 * @return Reference to the collision group's bounds.
		 * @see BaconBox::CollisionGroup::bounds
		 */
		AxisAlignedBoundingBox &getBounds();

		/**
		 * Gets the collision group's initial bounds.
		 * @return Const eference to the collision group's bounds.
		 * @see BaconBox::CollisionGroup::bounds
		 */
		const AxisAlignedBoundingBox &getBounds() const;

		/**
		 * Gets the depth used to calculate and initialize the maximum size of
		 * the pool used to optimize the quadtree reconstruction speed.
		 * @return Depth used to calculate the maximum pool size for the
		 * quadtree nodes.
		 * @see BaconBox::CollisionGroup::poolDepth
		 */
		unsigned int getPoolDepth() const;

		/**
		 * Sets the depth used to calculate the maximum size of the pool. The
		 * collision group must be updated after calling this function before
		 * testing for collisions again.
		 * @param newPoolDepth New depth used to calculate the maximum size of
		 * the pool.
		 * @see BaconBox::CollisionGroup::poolDepth
		 */
		void setPoolDepth(unsigned int newPoolDepth);

		/**
		 * Clears the collision group of all bodies.
		 */
		void clear();
	private:
		/// List of pointers of collidables, contained by the quad nodes.
		typedef std::list<Collidable *> BodyList;

		/// Index number of the north west quad.
		static const unsigned int NW = 0;

		/// Index number of the north east quad.
		static const unsigned int NE = 1;

		/// Index number of the south west quad.
		static const unsigned int SW = 2;

		/// Index number of the south east quad.
		static const unsigned int SE = 3;

		/**
		 * Represents a node in the quadtree.
		 * @ingroup Physics
		 */
		struct QuadNode {
			/**
			 * Default constructor.
			 */
			QuadNode();
			/**
			 * Parameterized constructor.
			 * @param newBounds Starting bounds for the node.
			 */
			QuadNode(const AxisAlignedBoundingBox &newBounds);

			/// Quad's bounds.
			AxisAlignedBoundingBox bounds;

			/// Quad subdivisions.
			QuadNode *nodes[4];

			/// List of collidable bodies in the node.
			BodyList boxes;
		};

		/**
		 * Calculates the size of the pool for a specific depth.
		 * @param depth Depth to use to calculate the pool size.
		 * @return Maximum size of the pool to use. It corresponds to
		 * ceil((1 - 4^depth) / (1 - 4)).
		 */
		static StackPool<QuadNode>::SizeType calculatePoolSize(unsigned int depth);

		/**
		 * Gets a new and available quad. From the pool if there's one available
		 * else it dynamically allocates one.
		 * @return Pointer to a new quad.
		 */
		QuadNode *getNewQuad();

		/**
		 * Gets a new and available quad. From the pool if there's one available
		 * else it dynamically allocates one. Sets the new quad's bounds with
		 * the ones given.
		 * @param newBounds Bounds to set to the new quad.
		 * @return Pointer to a new quad.
		 */
		QuadNode *getNewQuad(const AxisAlignedBoundingBox &newBounds);

		/**
		 * Inserts a new body in the subdivisions of the quadtree's roots.
		 * @param newBox Colliding box of the new body.
		 * @param newBody Pointer to the new body to insert in the quadtree.
		 */
		void subInsert(const AxisAlignedBoundingBox &newBox, Collidable *newBody);

		/**
		 * Inserts a new body higher than the root. Makes the root bigger until
		 * the new body can fit in it.
		 * @param newBox Colliding box of the new body.
		 * @param newBody Pointer to the new body to insert in the quadtree.
		 */
		void supInsert(const AxisAlignedBoundingBox &newBox, Collidable *newBody);

		/**
		 * Clears the pool overflow.
		 */
		void clearOverflow();

		/// Set of pointers to bodies that make up the collision group.
		BodySet bodies;

		/// Root quad node.
		QuadNode *root;

		/**
		 * Maximum depth of the quadtree. If the collision group contains bodies
		 * that are outside the initial bounds, the bounds will be adjusted and
		 * the depth will increment temporarily using the tmpDepth member.
		 * @see BaconBox::CollisionGroup::bounds
		 * @see BaconBox::CollisionGroup::tmpDepth
		 */
		unsigned int depth;

		/**
		 * Temporary depth. Might be higher than the normal depth if there were
		 * bodies outside the bounds when the collision group was updated.
		 * @see BaconBox::CollisionGroup::depth
		 */
		unsigned int tmpDepth;

		/**
		 * Bounds of the collision group. Not necessarily the same as final
		 * root's bounds. The tree will grow upwards if there are bodies outside
		 * the bounds found here.
		 */
		AxisAlignedBoundingBox bounds;

		/// Depth used to calculate the maximum size of the pool.
		unsigned int poolDepth;

		/**
		 * Pool of quad nodes used to optimize the collision group's quad tree's
		 * construction.
		 */
		StackPool<QuadNode> quadPool;

		/**
		 * Used to contain pointers to quad nodes if the pool overflows.
		 */
		std::deque<QuadNode *> quadOverflow;
	};
}

#endif
