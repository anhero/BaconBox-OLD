/**
 * @file
 * @ingroup Helper
 */
#ifndef RB_SHAPE_FACTORY_H
#define RB_SHAPE_FACTORY_H

#include "BaconBox/Vector2.h"

namespace BaconBox {
	class VertexArray;
	/**
	 * Class used to calculate the vertices of different shapes.
	 * @ingroup Helper
	 */
	class ShapeFactory {
	public:
		/**
		 * Calculates the vertices of a regular polygon. If any of the
		 * parameters' requirements are not met, the polygon isn't calculated.
		 * @param nbSides Number of sides of the regular polygon to generate.
		 * Must be 3 or higher.
		 * @param sideLength Length of the sides (in pixels by default). It must
		 * be higher than 0.
		 * @param position Position of the upper left corner of the polygon.
		 * @param vertices Pointer to the vertices array to modify. It must
		 * have a number of vertices equal to the number of sides received.
		 */
		static void createRegularPolygon(unsigned int nbSides, float sideLength,
		                                 const Vector2 &position,
		                                 VertexArray *vertices);

		/**
		 * Calculates the vertices of a rectangle. If any of the parameters'
		 * requirements are not met, the rectangle isn't calculated.
		 * @param size Vector containing the width and the height of the
		 * rectangle to create. Both values must be higher than 0.
		 * @param position Position of the upper left corner of the rectangle.
		 * @param vertices Pointer to the vertices array to modify. It must
		 * have precisely 4 vertices.
		 */
		static void createRectangle(const Vector2 &size,
		                            const Vector2 &position,
		                            VertexArray *vertices);

		/**
		 * Calculates the vertices of a square. If any of the parameters'
		 * requirements are not met, the square isn't calculated.
		 * @param sideLength Length of the square's sides (in pixels by
		 * default). Must be higher than 0.
		 * @param position Position of the upper left corner of the square.
		 * @param vertices Pointer to the vertices array to modify. It must
		 * have precisely 4 vertices.
		 */
		static void createSquare(float sideLength,
		                         const Vector2 &position,
		                         VertexArray *vertices);
	private:
		/**
		 * Private constructor. Declared private so no ShapeFactory can be
		 * instantiated.
		 */
		ShapeFactory();
	};
}

#endif
