/**
 * @file
 * @ingroup TileMap
 */
#ifndef RB_GRAPHIC_TILE_MAP_H
#define RB_GRAPHIC_TILE_MAP_H

#include <vector>

#include "Transformable.h"
#include "GraphicTileMapLayer.h"
#include "Iterators.h"

namespace RedBox {
	class TileMap;

	class GraphicTileMap : public Transformable {
	public:
		/// Type that contains the layers.
		typedef std::vector<GraphicTileMapLayer *> Container;

		typedef GraphicTileMapLayer ValueType;

		typedef GraphicTileMapLayer &Reference;

		typedef const GraphicTileMapLayer &ConstReference;

		typedef GraphicTileMapLayer *Pointer;

		typedef const GraphicTileMapLayer *ConstPointer;

		typedef Container::size_type SizeType;

		typedef Container::difference_type DifferenceType;

		typedef RandomAccessIterator<GraphicTileMap> Iterator;

		typedef RandomAccessConstIterator<GraphicTileMap> ConstIterator;

		typedef std::reverse_iterator<Iterator> ReverseIterator;

		typedef std::reverse_iterator<ConstIterator> ConstReverseIterator;

		/**
		 * Default and parameterized constructor.
		 * @param startingPosition Starting position of the graphic tile map.
		 */
		explicit GraphicTileMap(const Vector2 &startingPosition = Vector2());

		/**
		 * Parameterized constructor.
		 * @param map Tile map to load the graphic tile map from.
		 * @param startingPosition Starting position of the graphic tile map.
		 */
		explicit GraphicTileMap(const TileMap &map,
		                        const Vector2 &startingPosition = Vector2());

		/**
		 * Copy constructor.
		 * @param src Graphic tile map to make a copy of.
		 */
		GraphicTileMap(const GraphicTileMap &src);

		/**
		 * Destructor.
		 */
		~GraphicTileMap();

		/**
		 * Assignment operator overload.
		 * @param src Graphic tile map to copy.
		 * @return Reference to the modified instance.
		 */
		GraphicTileMap &operator=(const GraphicTileMap &src);

		using Transformable::move;

		/**
		 * Moves the Positionable horizontally and vertically.
		 * @param xDelta Value to add to the Positionable's horizontal position
		 * (in pixels). Positive value moves the Positionable to the right and a
		 * negative value moves the Positionable to the left.
		 * @param yDelta Value to add to the Positionable's vertical position (in
		 * pixels). Positive value moves the Positionable down and a negative
		 * value moves the Positionable up.
		 * @see RedBox::Positionable::move(const Vector2& delta);
		 * @see RedBox::Positionable::position
		 */
		void move(float xDelta, float yDelta);

		/**
		 * Gets the body's size. Can be overloaded for performance.
		 * @return Vector2 containing the width and height of the body.
		 */
		const Vector2 getSize() const;

		/**
		 * Gets the body's width.
		 * @return Width in pixels (by default).
		 */
		float getWidth() const;

		/**
		 * Gets the body's height.
		 * @return Height in pixels (by default).
		 */
		float getHeight() const;

		using Transformable::scaleFromPoint;

		/**
		 * Scales the body from a specific point.
		 * @param xScaling Horizontal scaling to apply. For example, if
		 * 2.0f is passed, the body will be twice as wide.
		 * @param yScaling Vertical scaling to apply. For example, if 2.0f is
		 * passed, the body will be twice as high.
		 * @param fromPoint Anchor point from which to apply the scaling.
		 * @see RedBox::Transformable::scaling
		 */
		void scaleFromPoint(float xScaling, float yScaling,
		                    const Vector2 &fromPoint);

		/**
		 * Rotates the graphic body from a point.
		 * @param rotationAngle Angle to rotate the graphic body.
		 * @param rotationPoint Origin point on which to apply the rotation.
		 * @see RedBox::Transformable::angle
		 */
		void rotateFromPoint(float rotationAngle,
		                     const Vector2 &rotationPoint);

		/**
		 * Constructs the graphic tile map from a tile map.
		 * @param map Tile map to load the graphic tile map from.
		 */
		void construct(const TileMap &map);

		/**
		 * Gets the layer from an index. Does not do bound checking.
		 * @param index Index of the layer.
		 * @return Reference to the layer.
		 */
		Reference operator[](SizeType index);

		/**
		 * Gets an iterator to the first body.
		 * @return Iterator to the first body.
		 */
		Iterator getBegin();

		/**
		 * Gets an iterator to the first body.
		 * @return Iterator to the first body.
		 */
		ConstIterator getBegin() const;

		/**
		 * Gets an iterator to the body following the last body. Acts as a
		 * placeholder, attempting to access it results in undefined behavior.
		 * @return Iterator to the body following the last body.
		 */
		Iterator getEnd();

		/**
		 * Gets an iterator to the body following the last body. Acts as a
		 * placeholder, attempting to access it results in undefined behavior.
		 * @return Iterator to the body following the last body.
		 */
		ConstIterator getEnd() const;

		/**
		 * Gets a reverse iterator to the first body of the reversed simple body
		 * manager. It corresponds to the last element of the non-reversed
		 * simple body manager.
		 * @return Reverse iterator to the first body.
		 */
		ReverseIterator getReverseBegin();

		/**
		 * Gets a reverse iterator to the first body of the reversed simple body
		 * manager. It corresponds to the last element of the non-reversed
		 * simple body manager.
		 * @return Reverse iterator to the first body.
		 */
		ConstReverseIterator getReverseBegin() const;

		/**
		 * Gets a reverse iterator to the body following the last body of the
		 * reversed simple body manager. It corresponds to the body preceding
		 * the first body of the non-reversed simple body manager. This body
		 * acts as a placeholder, attempting to access it results in undefined
		 * behavior.
		 * @return Reverse iterator to the body following the last body.
		 */
		ReverseIterator getReverseEnd();

		/**
		 * Gets a reverse iterator to the body following the last body of the
		 * reversed simple body manager. It corresponds to the body preceding
		 * the first body of the non-reversed simple body manager. This body
		 * acts as a placeholder, attempting to access it results in undefined
		 * behavior.
		 * @return Reverse iterator to the body following the last body.
		 */
		ConstReverseIterator getReverseEnd() const;

		/**
		 * Gets the number of bodies the manager currently manages.
		 * @return Number of bodies managed.
		 */
		SizeType getNbLayers() const;

		/**
		 * Checks wether or not the manager contains bodies.
		 * @return True if the manager contains bodies, false if not.
		 */
		bool isEmpty() const;

		/**
		 * Removes all bodies from the body manager.
		 */
		void clear();
	private:
		/// Contains the map's layers.
		Container layers;

		/**
		 * Frees all memory allocated by the layers.
		 */
		void free();
	};
}

#endif
