#include "BaconBox/Helper/CollisionGroup.h"

#include <cassert>
#include <cmath>

#include <algorithm>
#include <queue>

#include "BaconBox/Helper/DeleteHelper.h"

#include "BaconBox/Display/Collidable.h"

namespace BaconBox {
	CollisionGroup::CollisionGroup(const AxisAlignedBoundingBox &newBounds,
	                               unsigned int newDepth,
	                               unsigned int newPoolDepth) : bodies(),
		root(NULL), depth(newDepth), tmpDepth(), bounds(newBounds), poolDepth(newPoolDepth),
		quadPool(calculatePoolSize(newDepth)), quadOverflow() {
	}

	CollisionGroup::CollisionGroup(const CollisionGroup &src) : bodies(src.bodies),
		root(NULL), depth(src.depth), tmpDepth(), bounds(src.bounds),
		poolDepth(src.poolDepth), quadPool(src.quadPool.getMaxSize()),
		quadOverflow() {
	}

	CollisionGroup::~CollisionGroup() {
		clearOverflow();
	}

	CollisionGroup &CollisionGroup::operator=(const CollisionGroup &src) {
		if (this != &src) {
			bodies = src.bodies;
			root = NULL;
			depth = src.depth;
			bounds = src.bounds;
			poolDepth = src.poolDepth;
			quadPool.reset(src.quadPool.getMaxSize());
			clearOverflow();
			quadOverflow.clear();
		}

		return *this;
	}

	void CollisionGroup::update() {
		if (!bodies.empty()) {
			// We reset the pool and the quadtree.
			quadPool.reset();
			clearOverflow();
			quadOverflow.clear();

			// We initialize the root node.
			root = getNewQuad(bounds);

			tmpDepth = depth;

			// We add all the bodies in the quad tree.
			AxisAlignedBoundingBox tmpBox;

			for (BodySet::iterator i = bodies.begin(); i != bodies.end(); ++i) {
				tmpBox = (*i)->getAxisAlignedBoundingBox();

				// If the box is completely within the root node's bounds.
				if (tmpBox.isCompletelyInside(root->bounds)) {
					// We insert the box in the root or one of its subdivision.
					subInsert(tmpBox, *i);

				} else {
					// We create a node parent to the current root and make
					// this new node the new root. Repeat until we find a
					// size in which the body's box fits.
					supInsert(tmpBox, *i);
				}
			}
		}
	}

	void CollisionGroup::add(Collidable *newBody) {
		if (newBody) {
			bodies.insert(newBody);
		}
	}

	void CollisionGroup::remove(Collidable *body) {
		bodies.erase(body);
	}

	const std::list<CollisionDetails> CollisionGroup::collide(Collidable *body) {
		std::list<CollisionDetails> result;
		AxisAlignedBoundingBox tmpBox = body->getAxisAlignedBoundingBox();

		// We make sure the body has chances to collide with the group. To do
		// that, we check if the body's bounding box overlaps with the root
		// node's bounds.
		if (root && tmpBox.overlaps(root->bounds)) {
			// Queue containing the nodes to test collision with.
			std::queue<QuadNode *> nodeStack;
			nodeStack.push(root);

			bool oldResult;
			std::pair<bool, CollisionDetails> tmpDetails;

			// As long as we haven't tested collision with all the concerned
			// nodes.
			while (!nodeStack.empty()) {
				oldResult = false;

				// We collide with all of the node's bodies.
				for (BodyList::iterator i = nodeStack.front()->boxes.begin(); i != nodeStack.front()->boxes.end(); ++i) {
					// We collide the two bodies.
					tmpDetails = (*i)->collide(body);

					// If there was a collision.
					if (tmpDetails.first) {
						// We take note to update the bounding box when the loop
						// is over.
						oldResult = true;
						// We make sure the result's bool is set to true.
						// We add the collision details to the list.
						result.push_back(tmpDetails.second);
					}
				}

				// If the box used to test overlapping with node bounds needs to
				// be updated.
				if (oldResult) {
					tmpBox = body->getAxisAlignedBoundingBox();
				}

				// We get all the nodes that need to be tested.
				for (unsigned int i = 0; i < 4; ++i) {
					// If the box overlaps with the node's bounds.
					if (nodeStack.front()->nodes[i] && nodeStack.front()->nodes[i]->bounds.overlaps(tmpBox)) {
						// We add the node to the end of the queue.
						nodeStack.push(nodeStack.front()->nodes[i]);
					}
				}

				// We are done with this node, we pop it from the front of the
				// line.
				nodeStack.pop();
			}
		}

		return result;
	}

	const std::list<CollisionDetails> CollisionGroup::collide(CollisionGroup *collisionGroup) {
		std::list<CollisionDetails> result;

		std::list<CollisionDetails> tmpDetails;

		for (BodySet::iterator i = collisionGroup->bodies.begin(); i != collisionGroup->bodies.end(); ++i) {
			// We make the body collide with the quad tree.
			tmpDetails = this->collide(*i);

			result.insert(result.end(), tmpDetails.begin(), tmpDetails.end());
		}

		return result;
	}

	const std::list<CollisionDetails> CollisionGroup::collide() {
		return this->collide(this);
	}

	CollisionGroup::BodySet &CollisionGroup::getBodies() {
		return bodies;
	}

	const CollisionGroup::BodySet &CollisionGroup::getBodies() const {
		return bodies;
	}

	unsigned int CollisionGroup::getDepth() const {
		return depth;
	}

	void CollisionGroup::setDepth(unsigned int newDepth) {
		depth = newDepth;
	}

	AxisAlignedBoundingBox &CollisionGroup::getBounds() {
		return bounds;
	}

	const AxisAlignedBoundingBox &CollisionGroup::getBounds() const {
		return bounds;
	}

	unsigned int CollisionGroup::getPoolDepth() const {
		return poolDepth;
	}

	void CollisionGroup::setPoolDepth(unsigned int newPoolDepth) {
		poolDepth = newPoolDepth;
		quadPool.reset(calculatePoolSize(newPoolDepth));
	}

	void CollisionGroup::clear() {
		quadPool.reset();
		clearOverflow();
		quadOverflow.clear();
		root = NULL;
		tmpDepth = depth;
	}

	StackPool<CollisionGroup::QuadNode>::SizeType CollisionGroup::calculatePoolSize(unsigned int depth) {
		return static_cast<StackPool<CollisionGroup::QuadNode>::SizeType>(ceil((1.0 - pow(4.0, static_cast<double>(depth))) / -3.0));
	}

	CollisionGroup::QuadNode *CollisionGroup::getNewQuad() {
		QuadNode *result = quadPool.getFirst();

		if (result) {
			result->boxes.clear();
			result->nodes[NW] = NULL;
			result->nodes[NE] = NULL;
			result->nodes[SW] = NULL;
			result->nodes[SE] = NULL;

		} else {
			result = *quadOverflow.insert(quadOverflow.end(), new QuadNode());
		}

		return result;
	}

	CollisionGroup::QuadNode *CollisionGroup::getNewQuad(const AxisAlignedBoundingBox &newBounds) {
		QuadNode *result = quadPool.getFirst();

		if (result) {
			result->bounds = newBounds;
			result->boxes.clear();
			result->nodes[NW] = NULL;
			result->nodes[NE] = NULL;
			result->nodes[SW] = NULL;
			result->nodes[SE] = NULL;

		} else {
			result = *quadOverflow.insert(quadOverflow.end(), new QuadNode(newBounds));
		}

		return result;
	}

	void CollisionGroup::subInsert(const AxisAlignedBoundingBox &newBox, Collidable *newBody) {
		// We start from the root node.
		QuadNode *currentNode = root;
		unsigned int currentDepth = tmpDepth;

		// We loop until we set the current node to NULL, meaning the new box
		// is inserted.
		AxisAlignedBoundingBox tmpBounds;
		unsigned int i;

		while (currentNode && currentDepth) {
			tmpBounds = AxisAlignedBoundingBox(currentNode->bounds.getPosition(), currentNode->bounds.getSize() * 0.5f);
			i = 0;

			// For each quad.
			while (i < 4) {
				switch (i) {
				case NW:
					// First case, already initialized correctly.
					break;

				case NE:
					tmpBounds.setPosition(currentNode->bounds.getXPosition() + tmpBounds.getWidth(),
					                      currentNode->bounds.getYPosition());
					break;

				case SW:
					tmpBounds.setPosition(currentNode->bounds.getXPosition(),
					                      currentNode->bounds.getYPosition() + tmpBounds.getHeight());
					break;

				case SE:
					tmpBounds.setPosition(currentNode->bounds.getPosition() + tmpBounds.getSize());
					break;

				default:
					break;
				}

				// If the new box fits completely inside the quad's bounds.
				if (newBox.isCompletelyInside(tmpBounds)) {
					// If the node doesn't already exist, we initialize it.
					if (!currentNode->nodes[i]) {
						currentNode->nodes[i] = getNewQuad(tmpBounds);
					}

					// We go deeper into the quad tree.
					currentNode = currentNode->nodes[i];
					--currentDepth;

					// We set it to five to get out of the loop and to make sure
					// it doesn't insert the new box directly into the new
					// current node before checking it.
					i = 5;

				} else {
					++i;
				}
			}

			// If the new box doesn't fit completely into any of the quads,
			// we insert it into the current node's list of boxes.
			if (i == 4) {
				currentNode->boxes.push_back(newBody);
				currentNode = NULL;
			}
		}

		// If we reached the bottom of the tree and the box hasn't been
		// inserted yet, we insert it into the current node, even if it isn't
		// the smallest quad the box could fit into.
		if (!currentDepth && currentNode) {
			currentNode->boxes.push_back(newBody);
		}
	}

	void CollisionGroup::supInsert(const AxisAlignedBoundingBox &newBox, Collidable *newBody) {
		// We initialize the first current node as the root.
		QuadNode *newRoot, *currentNode = root;
		bool right, bottom;

		// As long as the current node is not NULL.
		while (currentNode) {
			// We determine where the current node will be in the new root node.
			right = newBox.getLeft() < currentNode->bounds.getLeft();
			bottom = newBox.getTop() < currentNode->bounds.getTop();

			// We get a new quad node for the new root node.
			newRoot = getNewQuad();
			// We set the new root node's size.
			newRoot->bounds.setSize(currentNode->bounds.getSize() * 2.0f);


			// We position the new root node.
			if (right) {
				newRoot->bounds.moveX(-currentNode->bounds.getWidth());
			}

			if (bottom) {
				newRoot->bounds.moveY(-currentNode->bounds.getHeight());
			}

			// We make the currentNode a child node of the new root node.
			newRoot->nodes[static_cast<unsigned int>(right) + static_cast<unsigned int>(bottom) * 2] = root;

			// We increase the temporary depth because we made the quad tree
			// grow upwards.
			++tmpDepth;

			// If the new box fits completely inside the new root node.
			if (newBox.isCompletelyInside(newRoot->bounds)) {
				// We set the new root.
				root = newRoot;
				// We make sure to stop the looping.
				currentNode = NULL;
				// We insert the new box in the new root node.
				subInsert(newBox, newBody);

			} else {
				// We continue making the quad tree bigger.
				currentNode = newRoot;
			}
		}
	}

	void CollisionGroup::clearOverflow() {
		std::for_each(quadOverflow.begin(), quadOverflow.end(), DeletePointerDirect());
	}

	CollisionGroup::QuadNode::QuadNode() : bounds(), boxes() {
		nodes[NW] = NULL;
		nodes[NE] = NULL;
		nodes[SW] = NULL;
		nodes[SE] = NULL;
	}

	CollisionGroup::QuadNode::QuadNode(const AxisAlignedBoundingBox &newBounds) :
		bounds(newBounds), boxes() {
		nodes[NW] = NULL;
		nodes[NE] = NULL;
		nodes[SW] = NULL;
		nodes[SE] = NULL;
	}
}
