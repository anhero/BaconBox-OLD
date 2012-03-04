#include "GraphicTileLayer.h"

#include "TileLayer.h"
#include "Tileset.h"
#include "TileMap.h"
#include "ShapeFactory.h"
#include "TextureInformation.h"
#include "TexturePointer.h"
#include "TileMapUtility.h"
#include "CollisionGroup.h"

namespace RedBox {
	GraphicTileLayer::GraphicTileLayer(const Vector2 &startingPosition) :
		GraphicTileMapLayer(startingPosition), currentMask(NULL), batches() {
	}

	GraphicTileLayer::GraphicTileLayer(const TileLayer &layer,
	                                   const Vector2 &startingPosition) :
		GraphicTileMapLayer(startingPosition), currentMask(NULL), batches() {
		this->construct(layer);
	}

	GraphicTileLayer::GraphicTileLayer(const GraphicTileLayer &src) :
		GraphicTileMapLayer(src), currentMask(src.currentMask), batches() {
		for (BatchMap::const_iterator i = src.batches.begin();
		     i != src.batches.end(); ++i) {
			batches.insert(std::make_pair(i->first, new RenderBatch<BatchedInanimateGraphicElement<Collidable> >(*i->second)));
		}
	}

	GraphicTileLayer::~GraphicTileLayer() {
	}

	GraphicTileLayer &GraphicTileLayer::operator=(const GraphicTileLayer &src) {
		this->GraphicTileMapLayer::operator=(src);

		if (this != &src) {
			currentMask = src.currentMask;
			free();
			batches.clear();

			for (BatchMap::const_iterator i = src.batches.begin();
			     i != src.batches.end(); ++i) {
				batches.insert(std::make_pair(i->first, new RenderBatch<BatchedInanimateGraphicElement<Collidable> >(*i->second)));
			}
		}

		return *this;
	}

	void GraphicTileLayer::move(float xDelta, float yDelta) {
		this->GraphicTileMapLayer::move(xDelta, yDelta);

		for (BatchMap::iterator i = batches.begin(); i != batches.end(); ++i) {
			for (RenderBatch<BatchedInanimateGraphicElement<Collidable> >::BodyMap::iterator j = i->second->getBegin();
			     j != i->second->getEnd(); ++j) {
				(*j)->move(xDelta, yDelta);
			}
		}
	}

	const Vector2 GraphicTileLayer::getSize() const {
		Vector2 result;

		if (!batches.empty()) {
			bool notFirst = false;
			Vector2 min, max;
			float tmp;

			for (BatchMap::const_iterator i = batches.begin(); i != batches.end(); ++i) {
				for (RenderBatch<BatchedInanimateGraphicElement<Collidable> >::BodyMap::const_iterator j = i->second->getBegin();
				     j != i->second->getEnd(); ++j) {
					if (notFirst) {
						if (min.getX() > (*j)->getXPosition()) {
							min.setX((*j)->getXPosition());
						}

						if (min.getY() > (*j)->getYPosition()) {
							min.setY((*j)->getYPosition());
						}

						tmp = (*j)->getXPosition() + (*j)->getWidth();

						if (max.getX() < tmp) {
							max.setX(tmp);
						}

						tmp = (*j)->getYPosition() + (*j)->getHeight();

						if (max.getY() < tmp) {
							max.setY(tmp);
						}

					} else {
						min = (*j)->getPosition();
						max = (*j)->getPosition() + (*j)->getSize();
						notFirst = true;
					}
				}
			}

			result = max - min;
		}

		return result;
	}

	float GraphicTileLayer::getWidth() const {
		float result = 0.0f;

		if (!batches.empty()) {
			bool notFirst = false;
			float min, max;
			float tmp;

			for (BatchMap::const_iterator i = batches.begin(); i != batches.end(); ++i) {
				for (RenderBatch<BatchedInanimateGraphicElement<Collidable> >::BodyMap::const_iterator j = i->second->getBegin();
				     j != i->second->getEnd(); ++j) {
					if (notFirst) {
						if (min > (*j)->getXPosition()) {
							min = (*j)->getXPosition();
						}

						tmp = (*j)->getXPosition() + (*j)->getWidth();

						if (max < tmp) {
							max = tmp;
						}

					} else {
						min = (*j)->getXPosition();
						max = (*j)->getXPosition() + (*j)->getWidth();
						notFirst = true;
					}
				}
			}

			result = max - min;
		}

		return result;
	}

	float GraphicTileLayer::getHeight() const {
		float result = 0.0f;

		if (!batches.empty()) {
			bool notFirst = false;
			float min, max;
			float tmp;

			for (BatchMap::const_iterator i = batches.begin(); i != batches.end(); ++i) {
				for (RenderBatch<BatchedInanimateGraphicElement<Collidable> >::BodyMap::const_iterator j = i->second->getBegin();
				     j != i->second->getEnd(); ++j) {
					if (notFirst) {
						if (min > (*j)->getYPosition()) {
							min = (*j)->getYPosition();
						}

						tmp = (*j)->getYPosition() + (*j)->getHeight();

						if (max < tmp) {
							max = tmp;
						}

					} else {
						min = (*j)->getYPosition();
						max = (*j)->getYPosition() + (*j)->getHeight();
						notFirst = true;
					}
				}
			}

			result = max - min;
		}

		return result;
	}

	void GraphicTileLayer::scaleFromPoint(float xScaling, float yScaling,
	                                      const Vector2 &fromPoint) {
		this->GraphicTileMapLayer::scaleFromPoint(xScaling, yScaling, fromPoint);

		bool notFirst = false;
		Vector2 newPosition;

		for (BatchMap::iterator i = batches.begin(); i != batches.end(); ++i) {
			for (RenderBatch<BatchedInanimateGraphicElement<Collidable> >::BodyMap::iterator j = i->second->getBegin();
			     j != i->second->getEnd(); ++j) {
				(*j)->scaleFromPoint(xScaling, yScaling, fromPoint);

				if (notFirst) {
					if (newPosition.getX() > (*j)->getXPosition()) {
						newPosition.setX((*j)->getXPosition());
					}

					if (newPosition.getY() > (*j)->getYPosition()) {
						newPosition.setY((*j)->getYPosition());
					}

				} else {
					newPosition = (*j)->getPosition();
					notFirst = true;
				}
			}
		}

		this->GraphicTileMapLayer::move(newPosition.getX() - this->getXPosition(),
		                                newPosition.getY() - this->getYPosition());
	}

	void GraphicTileLayer::rotateFromPoint(float rotationAngle,
	                                       const Vector2 &rotationPoint) {
		this->GraphicTileMapLayer::rotateFromPoint(rotationAngle, rotationPoint);

		bool notFirst = false;
		Vector2 newPosition;

		for (BatchMap::iterator i = batches.begin(); i != batches.end(); ++i) {
			for (RenderBatch<BatchedInanimateGraphicElement<Collidable> >::BodyMap::iterator j = i->second->getBegin();
			     j != i->second->getEnd(); ++j) {
				(*j)->rotateFromPoint(rotationAngle, rotationPoint);

				if (notFirst) {
					if (newPosition.getX() > (*j)->getXPosition()) {
						newPosition.setX((*j)->getXPosition());
					}

					if (newPosition.getY() > (*j)->getYPosition()) {
						newPosition.setY((*j)->getYPosition());
					}

				} else {
					newPosition = (*j)->getPosition();
					notFirst = true;
				}
			}
		}

		this->GraphicTileMapLayer::move(newPosition.getX() - this->getXPosition(),
		                                newPosition.getY() - this->getYPosition());
	}

	void GraphicTileLayer::update() {
		for (BatchMap::iterator i = batches.begin(); i != batches.end(); ++i) {
			i->second->update();
		}
	}

	void GraphicTileLayer::render() {
		for (BatchMap::iterator i = batches.begin(); i != batches.end(); ++i) {
			i->second->render();
		}
	}

	void GraphicTileLayer::mask() {
		for (BatchMap::iterator i = batches.begin(); i != batches.end(); ++i) {
			i->second->mask();
		}
	}

	void GraphicTileLayer::unmask() {
		for (BatchMap::iterator i = batches.begin(); i != batches.end(); ++i) {
			i->second->unmask();
		}
	}

	Maskable *GraphicTileLayer::getMask() const {
		return currentMask;
	}

	void GraphicTileLayer::setMask(Maskable *newMask, bool inverted) {
		currentMask = newMask;

		for (BatchMap::iterator i = batches.begin(); i != batches.end(); ++i) {
			i->second->setMask(newMask, inverted);
		}
	}

	GraphicTileLayer *GraphicTileLayer::asTileLayer() {
		return this;
	}

	const GraphicTileLayer *GraphicTileLayer::asTileLayer() const {
		return this;
	}

	GraphicTileLayer *GraphicTileLayer::clone() const {
		return new GraphicTileLayer(*this);
	}

	void GraphicTileLayer::construct(const TileLayer &layer) {
		free();
		batches.clear();
		// Variables used within the "for" loop.
		RenderBatch<BatchedInanimateGraphicElement<Collidable> >::ValueType *tmpTile = NULL;
		const Tileset *tileset;
		TileLayer::DataContainer::const_iterator::difference_type tileIndex;
		Color tmpColor;
		
		// We add all the tiles.
		for (TileLayer::DataContainer::const_iterator i = layer.getTiles().begin();
		     i != layer.getTiles().end(); ++i) {
			// We find the tileset the tile id belongs to.
			tileset = layer.parentMap.getTileset(*i);

			// If the tile id is valid, we should have a valid tileset.
			if (tileset && tileset->getTextureInformation()) {
				// We initialize the new tile.
				tmpTile = new BatchedInanimateGraphicElement<Collidable>();

				// We set the tile's texture information (optional).
				tmpTile->setTextureInformation(tileset->getTextureInformation());

				// We calculate the tile's position.
				tileIndex = i - layer.getTiles().begin();
				tmpTile->setPosition(Vector2::scalarMultiplication(layer.parentMap.getTileSize(), Vector2(static_cast<float>(tileIndex % layer.getWidthInTiles()), static_cast<float>(tileIndex / layer.getWidthInTiles()))) + this->getPosition() + (layer.parentMap.getTileHeight() - tileset->getTileHeight()));

				// We initialize the vertices.
				tmpTile->getVertices().resize(4);
				ShapeFactory::createRectangle(tileset->getTileSize(), tmpTile->getPosition(), &tmpTile->getVertices());

				// We load the texture coordinates.
				tileset->loadTextureCoordinates(*i, tmpTile->getTextureCoordinates());
				
				// We set the tile's opacity.
				tmpTile->setAlpha(layer.getOpacity());

				// We add the new tile to the right batch.
				getBatch(tmpTile->getTextureInformation())->add(tmpTile);
			}
		}
		
		// We set the layer's visibility.
		this->setVisible(layer.isVisible());
		
		// We set the layer's z.
		TileMapUtility::readZ(layer.getProperties(), *this);
	}

	void GraphicTileLayer::addToCollisionGroup(CollisionGroup &group) {
		for (BatchMap::iterator i = batches.begin(); i != batches.end(); ++i) {
			for (RenderBatch<BatchedInanimateGraphicElement<Collidable> >::BodyMap::iterator j = i->second->getBegin();
				 j != i->second->getEnd(); ++j) {
				group.add(*j);
			}
		}
	}

	void GraphicTileLayer::free() {
		for (BatchMap::iterator i = batches.begin(); i != batches.end(); ++i) {
			delete i->second;
		}
	}
	
	GraphicTileLayer::BatchMap::mapped_type GraphicTileLayer::getBatch(TextureInformation *textureInformation) {
		std::pair<BatchMap::iterator, bool> inserted = batches.insert(BatchMap::value_type(textureInformation, NULL));
		
		if (inserted.second) {
			inserted.first->second = new RenderBatch<BatchedInanimateGraphicElement<Collidable> >(textureInformation);
		}
		
		return inserted.first->second;
	}
}
