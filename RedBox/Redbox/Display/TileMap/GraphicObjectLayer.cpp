#include "GraphicObjectLayer.h"

#include "ObjectLayer.h"
#include "TileMap.h"

namespace RedBox {
	GraphicObjectLayer::GraphicObjectLayer(const Vector2 &startingPosition) :
		GraphicTileMapLayer(startingPosition), currentMask(NULL) {
	}

	GraphicObjectLayer::GraphicObjectLayer(const ObjectLayer &src,
	                                       const Vector2 &startingPosition) :
		GraphicTileMapLayer(startingPosition), currentMask(NULL) {
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
				if (min.getX() > i->getXPosition()) {
					min.setX(i->getXPosition());
				}

				if (min.getY() > i->getYPosition()) {
					min.setY(i->getYPosition());
				}

				tmp = i->getXPosition() + i->getWidth();

				if (max.getX() < tmp) {
					max.setX(tmp);
				}

				tmp = i->getYPosition() + i->getHeight();

				if (max.getY() < tmp) {
					max.setY(tmp);
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
				if (min.getX() > i->getXPosition()) {
					min.setX(i->getXPosition());
				}

				if (min.getY() > i->getYPosition()) {
					min.setY(i->getYPosition());
				}

				tmp = i->getXPosition() + i->getWidth();

				if (max.getX() < tmp) {
					max.setX(tmp);
				}

				tmp = i->getYPosition() + i->getHeight();

				if (max.getY() < tmp) {
					max.setY(tmp);
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
		
		for (InanimateSpriteContainer::ConstIterator i = inanimateSprites.getBegin();
			 i != inanimateSprites.getEnd(); ++i) {
			
		}
	}
}