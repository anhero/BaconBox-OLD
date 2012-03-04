#include "GraphicTileMap.h"

#include "TileMap.h"
#include "TileLayer.h"
#include "ObjectLayer.h"
#include "GraphicTileLayer.h"
#include "GraphicObjectLayer.h"
#include "State.h"
#include "TileMapUtility.h"
#include "Factory.h"
#include "Sprite.h"
#include "InanimateSprite.h"

#define LOAD_FACTORY if(!loaded) { loaded = true; loadFactory(); }

namespace RedBox {
	static bool loaded = false;
	void loadFactory();
	GraphicTileMap::GraphicTileMap(const Vector2 &startingPosition) :
		Transformable(startingPosition) {
		LOAD_FACTORY;
	}

	GraphicTileMap::GraphicTileMap(const TileMap &map,
	                               const Vector2 &startingPosition) :
		Transformable(startingPosition) {
		LOAD_FACTORY;
		construct(map);
	}

	GraphicTileMap::GraphicTileMap(const TileMap &map, int zIncrement,
	                               int zStart,
	                               const Vector2 &startingPosition) :
		Transformable(startingPosition) {
		LOAD_FACTORY
		construct(map, zIncrement, zStart);
	}

	GraphicTileMap::GraphicTileMap(const GraphicTileMap &src) :
		Transformable(src), layers(src.layers.size(), NULL) {
		Container::iterator dstLayer = layers.begin();
		Container::const_iterator srcLayer = src.layers.begin();

		while (dstLayer != layers.end()) {
			*dstLayer = (*srcLayer)->clone();
			++dstLayer;
			++srcLayer;
		}
	}

	GraphicTileMap::~GraphicTileMap() {
		free();
	}

	GraphicTileMap &GraphicTileMap::operator=(const GraphicTileMap &src) {
		this->Transformable::operator=(src);

		if (this != &src) {
			free();
			layers.clear();

			layers.resize(src.layers.size(), NULL);

			Container::iterator dstLayer = layers.begin();
			Container::const_iterator srcLayer = src.layers.begin();

			while (dstLayer != layers.end()) {
				*dstLayer = (*srcLayer)->clone();
				++dstLayer;
				++srcLayer;
			}
		}

		return *this;
	}

	void GraphicTileMap::move(float xDelta, float yDelta) {
		this->Transformable::move(xDelta, yDelta);

		for (Iterator i = getBegin(); i != getEnd(); ++i) {
			i->move(xDelta, yDelta);
		}
	}

	const Vector2 GraphicTileMap::getSize() const {
		if (!isEmpty()) {
			ConstIterator i = getBegin();
			Vector2 min = i->getPosition(), max = i->getPosition() + i->getSize(), tmp;

			++i;

			while (i != getEnd()) {
				if (min.getX() > i->getXPosition()) {
					min.setX(i->getXPosition());
				}

				if (min.getY() > i->getYPosition()) {
					min.setY(i->getYPosition());
				}

				tmp = i->getPosition() + i->getSize();

				if (max.getX() < tmp.getX()) {
					max.setX(tmp.getX());
				}

				if (max.getY() < tmp.getY()) {
					max.setY(tmp.getY());
				}

				++i;
			}

			return max - min;

		} else {
			return Vector2();
		}
	}

	float GraphicTileMap::getWidth() const {
		if (!isEmpty()) {
			ConstIterator i = getBegin();
			float min = i->getXPosition(), max = i->getXPosition() + i->getWidth(), tmp;

			++i;

			while (i != getEnd()) {
				if (min > i->getXPosition()) {
					min = i->getXPosition();
				}

				tmp = i->getXPosition() + i->getWidth();

				if (max < tmp) {
					max = tmp;
				}

				++i;
			}

			return max - min;

		} else {
			return 0.0f;
		}
	}

	float GraphicTileMap::getHeight() const {
		if (!isEmpty()) {
			ConstIterator i = getBegin();
			float min = i->getYPosition(), max = i->getYPosition() + i->getHeight(), tmp;

			++i;

			while (i != getEnd()) {
				if (min > i->getYPosition()) {
					min = i->getYPosition();
				}

				tmp = i->getYPosition() + i->getHeight();

				if (max < tmp) {
					max = tmp;
				}

				++i;
			}

			return max - min;

		} else {
			return 0.0f;
		}
	}

	void GraphicTileMap::scaleFromPoint(float xScaling, float yScaling,
	                                    const Vector2 &fromPoint) {
		this->Transformable::scaleFromPoint(xScaling, yScaling, fromPoint);

		if (!isEmpty()) {
			Iterator i = getBegin();
			Vector2 min = i->getPosition();
			i->scaleFromPoint(xScaling, yScaling, fromPoint);

			++i;

			while (i != getEnd()) {
				i->scaleFromPoint(xScaling, yScaling, fromPoint);

				if (min.getX() > i->getXPosition()) {
					min.setX(i->getXPosition());
				}

				if (min.getY() > i->getYPosition()) {
					min.setY(i->getYPosition());
				}

				++i;
			}

			this->Transformable::move(min.getX() - getXPosition(),
			                          min.getY() - getYPosition());
		}
	}

	void GraphicTileMap::rotateFromPoint(float rotationAngle,
	                                     const Vector2 &rotationPoint) {
		this->Transformable::rotateFromPoint(rotationAngle, rotationPoint);

		if (!isEmpty()) {
			Iterator i = getBegin();
			Vector2 min = i->getPosition();
			i->rotateFromPoint(rotationAngle, rotationPoint);

			++i;

			while (i != getEnd()) {
				i->rotateFromPoint(rotationAngle, rotationPoint);

				if (min.getX() > i->getXPosition()) {
					min.setX(i->getXPosition());
				}

				if (min.getY() > i->getYPosition()) {
					min.setY(i->getYPosition());
				}

				++i;
			}

			this->Transformable::move(min.getX() - getXPosition(),
			                          min.getY() - getYPosition());
		}
	}

	void GraphicTileMap::construct(const TileMap &map, int zIncrement,
	                               int zStart) {
		free();
		layers.clear();
		int z = zStart;

		for (TileMap::LayerContainer::const_iterator i = map.getLayers().begin();
		     i != map.getLayers().end(); ++i) {
			if (*i) {
				if ((*i)->asTileLayer()) {
					layers.push_back(new GraphicTileLayer(*(*i)->asTileLayer(), getPosition()));

				} else {
					layers.push_back(new GraphicObjectLayer(*(*i)->asObjectLayer(), getPosition()));
				}

				layers.back()->setZ(z);
			}

			z += zIncrement;
		}
	}

	void GraphicTileMap::construct(const TileMap &map) {
		construct(map, TileMapUtility::readZIncrement(map.getProperties()),
		          TileMapUtility::readZStart(map.getProperties()));
	}

	void GraphicTileMap::addToState(State &state) {
		for (Container::iterator i = layers.begin(); i != layers.end(); ++i) {
			state.add(*i);
		}
	}

	GraphicTileMap::Reference GraphicTileMap::operator[](GraphicTileMap::SizeType index) {
		return *layers[index];
	}

	GraphicTileMap::Iterator GraphicTileMap::getBegin() {
		return Iterator(layers.begin());
	}

	GraphicTileMap::ConstIterator GraphicTileMap::getBegin() const {
		return ConstIterator(layers.begin());
	}

	GraphicTileMap::Iterator GraphicTileMap::getEnd() {
		return Iterator(layers.end());
	}

	GraphicTileMap::ConstIterator GraphicTileMap::getEnd() const {
		return ConstIterator(layers.end());
	}

	GraphicTileMap::ReverseIterator GraphicTileMap::getReverseBegin() {
		return ReverseIterator(Iterator(layers.end()));
	}

	GraphicTileMap::ConstReverseIterator GraphicTileMap::getReverseBegin() const {
		return ConstReverseIterator(ConstIterator(layers.end()));
	}

	GraphicTileMap::ReverseIterator GraphicTileMap::getReverseEnd() {
		return ReverseIterator(Iterator(layers.begin()));
	}

	GraphicTileMap::ConstReverseIterator GraphicTileMap::getReverseEnd() const {
		return ConstReverseIterator(ConstIterator(layers.begin()));
	}

	GraphicTileMap::SizeType GraphicTileMap::getNbLayers() const {
		return layers.size();
	}

	bool GraphicTileMap::isEmpty() const {
		return layers.empty();
	}

	void GraphicTileMap::clear() {
		free();
		layers.clear();
	}

	void GraphicTileMap::free() {
		for (Container::iterator i = layers.begin(); i != layers.end(); ++i) {
			if ((*i)->isManaged()) {
				(*i)->setToBeDeleted(true);

			} else {
				delete *i;
			}
		}
	}

	void loadFactory() {
		RBRegisterClass(Sprite, Sprite);
		RBRegisterClass(InanimateSprite, InanimateSprite);
	}
}
