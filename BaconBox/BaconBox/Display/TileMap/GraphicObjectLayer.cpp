#include "BaconBox/Display/TileMap/GraphicObjectLayer.h"

#include <list>

#include "BaconBox/Display/TileMap/ObjectLayer.h"
#include "BaconBox/Display/TileMap/TileMap.h"
#include "BaconBox/Factory.h"

namespace BaconBox {
	GraphicObjectLayer::GraphicObjectLayer(const Vector2 &startingPosition) :
		GraphicTileMapLayer(startingPosition), currentMask(NULL) {
	}

	GraphicObjectLayer::GraphicObjectLayer(const ObjectLayer &layer,
	                                       const Vector2 &startingPosition) :
		GraphicTileMapLayer(startingPosition), currentMask(NULL) {
		construct(layer);
	}

	GraphicObjectLayer::GraphicObjectLayer(const GraphicObjectLayer &src) :
		GraphicTileMapLayer(src), currentMask(src.currentMask),
		sprites(src.sprites), inanimateSprites(src.inanimateSprites) {
	}

	GraphicObjectLayer::~GraphicObjectLayer() {
	}

	GraphicObjectLayer &GraphicObjectLayer::operator=(const GraphicObjectLayer &src) {
		this->GraphicTileMapLayer::operator=(src);

		if (this != &src) {
			currentMask = src.currentMask;
			sprites = src.sprites;
			inanimateSprites = src.inanimateSprites;
		}

		return *this;
	}

	void GraphicObjectLayer::move(float xDelta, float yDelta) {
		this->GraphicTileMapLayer::move(xDelta, yDelta);

		for (SpriteContainer::Iterator i = sprites.getBegin(); i != sprites.getEnd(); ++i) {
			i->move(xDelta, yDelta);
		}

		for (InanimateSpriteContainer::Iterator i = inanimateSprites.getBegin();
		     i != inanimateSprites.getEnd(); ++i) {
			i->move(xDelta, yDelta);
		}
	}

	const Vector2 GraphicObjectLayer::getSize() const {
		Vector2 result, min, max;
		bool notFirst = false;
		float tmp;

		for (SpriteContainer::ConstIterator i = sprites.getBegin();
		     i != sprites.getEnd(); ++i) {
			if (notFirst) {
				if (min.x > i->getXPosition()) {
					min.x = i->getXPosition();
				}

				if (min.y > i->getYPosition()) {
					min.y = i->getYPosition();
				}

				tmp = i->getXPosition() + i->getWidth();

				if (max.x < tmp) {
					max.x = tmp;
				}

				tmp = i->getYPosition() + i->getHeight();

				if (max.y < tmp) {
					max.y = tmp;
				}

			} else {
				min = i->getPosition();
				max = i->getPosition() + i->getSize();
				notFirst = true;
			}
		}

		for (InanimateSpriteContainer::ConstIterator i = inanimateSprites.getBegin();
		     i != inanimateSprites.getEnd(); ++i) {
			if (notFirst) {
				if (min.x > i->getXPosition()) {
					min.x = i->getXPosition();
				}

				if (min.y > i->getYPosition()) {
					min.y = i->getYPosition();
				}

				tmp = i->getXPosition() + i->getWidth();

				if (max.x < tmp) {
					max.x = tmp;
				}

				tmp = i->getYPosition() + i->getHeight();

				if (max.y < tmp) {
					max.y = tmp;
				}

			} else {
				min = i->getPosition();
				max = i->getPosition() + i->getSize();
				notFirst = true;
			}
		}

		return result;
	}

	float GraphicObjectLayer::getWidth() const {
		float result = 0.0f, min, max, tmp;
		bool notFirst = false;

		for (SpriteContainer::ConstIterator i = sprites.getBegin();
		     i != sprites.getEnd(); ++i) {
			if (notFirst) {
				if (min > i->getXPosition()) {
					min = i->getXPosition();
				}

				tmp = i->getXPosition() + i->getWidth();

				if (max < tmp) {
					max = tmp;
				}

			} else {
				min = i->getXPosition();
				max = i->getXPosition() + i->getWidth();
				notFirst = true;
			}
		}

		for (InanimateSpriteContainer::ConstIterator i = inanimateSprites.getBegin();
		     i != inanimateSprites.getEnd(); ++i) {
			if (notFirst) {
				if (min > i->getXPosition()) {
					min = i->getXPosition();
				}

				tmp = i->getXPosition() + i->getWidth();

				if (max < tmp) {
					max = tmp;
				}

			} else {
				min = i->getXPosition();
				max = i->getXPosition() + i->getWidth();
				notFirst = true;
			}
		}

		return result;
	}

	float GraphicObjectLayer::getHeight() const {
		float result = 0.0f, min, max, tmp;
		bool notFirst = false;

		for (SpriteContainer::ConstIterator i = sprites.getBegin();
		     i != sprites.getEnd(); ++i) {
			if (notFirst) {
				if (min > i->getYPosition()) {
					min = i->getYPosition();
				}

				tmp = i->getYPosition() + i->getHeight();

				if (max < tmp) {
					max = tmp;
				}

			} else {
				min = i->getYPosition();
				max = i->getYPosition() + i->getHeight();
				notFirst = true;
			}
		}

		for (InanimateSpriteContainer::ConstIterator i = inanimateSprites.getBegin();
		     i != inanimateSprites.getEnd(); ++i) {
			if (notFirst) {
				if (min > i->getYPosition()) {
					min = i->getYPosition();
				}

				tmp = i->getYPosition() + i->getHeight();

				if (max < tmp) {
					max = tmp;
				}

			} else {
				min = i->getYPosition();
				max = i->getYPosition() + i->getHeight();
				notFirst = true;
			}
		}

		return result;
	}

	void GraphicObjectLayer::scaleFromPoint(float xScaling, float yScaling,
	                                        const Vector2 &fromPoint) {
		this->GraphicTileMapLayer::scaleFromPoint(xScaling, yScaling, fromPoint);

		bool notFirst = false;
		Vector2 newPosition;

		for (SpriteContainer::Iterator i = sprites.getBegin();
		     i != sprites.getEnd(); ++i) {
			i->scaleFromPoint(xScaling, yScaling, fromPoint);

			if (notFirst) {
				if (newPosition.x > i->getXPosition()) {
					newPosition.x = i->getXPosition();
				}

				if (newPosition.y > i->getYPosition()) {
					newPosition.y = i->getYPosition();
				}

			} else {
				newPosition = i->getPosition();
				notFirst = true;
			}
		}

		for (InanimateSpriteContainer::Iterator i = inanimateSprites.getBegin();
		     i != inanimateSprites.getEnd(); ++i) {
			i->scaleFromPoint(xScaling, yScaling, fromPoint);

			if (notFirst) {
				if (newPosition.x > i->getXPosition()) {
					newPosition.x = i->getXPosition();
				}

				if (newPosition.y > i->getYPosition()) {
					newPosition.y = i->getYPosition();
				}

			} else {
				newPosition = i->getPosition();
				notFirst = true;
			}
		}

		this->GraphicTileMapLayer::move(newPosition.x - this->getXPosition(),
		                                newPosition.y - this->getYPosition());
	}

	void GraphicObjectLayer::rotateFromPoint(float rotationAngle,
	                                         const Vector2 &rotationPoint) {
		this->GraphicTileMapLayer::rotateFromPoint(rotationAngle, rotationPoint);

		bool notFirst = false;
		Vector2 newPosition;

		for (SpriteContainer::Iterator i = sprites.getBegin();
		     i != sprites.getEnd(); ++i) {
			i->rotateFromPoint(rotationAngle, rotationPoint);

			if (notFirst) {
				if (newPosition.x > i->getXPosition()) {
					newPosition.x = i->getXPosition();
				}

				if (newPosition.y > i->getYPosition()) {
					newPosition.y = i->getYPosition();
				}

			} else {
				newPosition = i->getPosition();
				notFirst = true;
			}
		}

		for (InanimateSpriteContainer::Iterator i = inanimateSprites.getBegin();
		     i != inanimateSprites.getEnd(); ++i) {
			i->rotateFromPoint(rotationAngle, rotationPoint);

			if (notFirst) {
				if (newPosition.x > i->getXPosition()) {
					newPosition.x = i->getXPosition();
				}

				if (newPosition.y > i->getYPosition()) {
					newPosition.y = i->getYPosition();
				}

			} else {
				newPosition = i->getPosition();
				notFirst = true;
			}
		}

		this->GraphicTileMapLayer::move(newPosition.x - this->getXPosition(),
		                                newPosition.y - this->getYPosition());
	}

	void GraphicObjectLayer::update() {
		sprites.update();
		inanimateSprites.update();
	}

	void GraphicObjectLayer::render() {
		sprites.render();
		inanimateSprites.render();
	}

	void GraphicObjectLayer::mask() {
		sprites.mask();
		inanimateSprites.mask();
	}

	void GraphicObjectLayer::unmask() {
		sprites.unmask();
		inanimateSprites.unmask();
	}

	Maskable *GraphicObjectLayer::getMask() const {
		return currentMask;
	}

	void GraphicObjectLayer::setMask(Maskable *newMask, bool inverted) {
		currentMask = newMask;

		sprites.setMask(newMask, inverted);
		inanimateSprites.setMask(newMask, inverted);
	}

	GraphicObjectLayer *GraphicObjectLayer::asObjectLayer() {
		return this;
	}

	const GraphicObjectLayer *GraphicObjectLayer::asObjectLayer() const {
		return this;
	}

	GraphicObjectLayer *GraphicObjectLayer::clone() const {
		return new GraphicObjectLayer(*this);
	}

	GraphicObjectLayer::SpriteContainer &GraphicObjectLayer::getSprites() {
		return sprites;
	}

	const GraphicObjectLayer::SpriteContainer &GraphicObjectLayer::getSprites() const {
		return sprites;
	}

	GraphicObjectLayer::InanimateSpriteContainer &GraphicObjectLayer::getInanimateSprites() {
		return inanimateSprites;
	}

	const GraphicObjectLayer::InanimateSpriteContainer &GraphicObjectLayer::getInanimateSprites() const {
		return inanimateSprites;
	}

	template <typename T>
	void loadObjects(const std::list<T *> &objects,
	                 const ObjectLayer &layer,
	                 GraphicObjectLayer &graphicLayer) {
		typedef std::list<T *> Container;

		// Variables used inside the loop.
		GraphicObjectLayer::SpriteContainer::Pointer tmpSprite;
		GraphicObjectLayer::InanimateSpriteContainer::Pointer tmpInanimateSprite;

		for (typename Container::const_iterator i = objects.begin();
		     i != objects.end(); ++i) {
			// We check if the type is derived from Sprite.
			tmpSprite = GenericFactory<GraphicObjectLayer::SpriteContainer::ValueType>::getInstance().create((*i)->getType());

			if (tmpSprite) {
				tmpSprite->setAlpha(layer.getOpacity());
				tmpSprite->construct(*(*i));
				tmpSprite->move(graphicLayer.getPosition());

				graphicLayer.getSprites().add(tmpSprite);

			} else {
				// We check if the type is derived from InanimateSprite.
				tmpInanimateSprite = GenericFactory<GraphicObjectLayer::InanimateSpriteContainer::ValueType>::getInstance().create((*i)->getType());

				if (tmpInanimateSprite) {
					tmpInanimateSprite->setAlpha(layer.getOpacity());
					tmpInanimateSprite->construct(*(*i));
					tmpInanimateSprite->move(graphicLayer.getPosition());

					graphicLayer.getInanimateSprites().add(tmpInanimateSprite);
				}
			}
		}
	}

	void GraphicObjectLayer::construct(const ObjectLayer &layer) {
		sprites.clear();
		inanimateSprites.clear();

		// We load the polygons.
		loadObjects(layer.getPolygons(), layer, *this);

		// We load the rectangles.
		loadObjects(layer.getRectangles(), layer, *this);

		// We load the tiles.
		loadObjects(layer.getTiles(), layer, *this);

		// We set the layer's visibility.
		this->setVisible(layer.isVisible());

		// We set the layer's z.
		TileMapUtility::readZ(layer.getProperties(), *this);
	}
}
