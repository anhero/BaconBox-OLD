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
	private:
		/// Contains the map's layers.
		Container layers;
	};
}

#endif