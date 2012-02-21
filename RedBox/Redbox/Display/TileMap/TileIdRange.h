/**
 * @file
 */
#ifndef RB_TILE_ID_RANGE_H
#define RB_TILE_ID_RANGE_H

namespace RedBox {
	/**
	 * Represents a range. A range has a minimum value and a maximum value. The
	 * maximum value is excluded from the range.
	 * @tparam ValueType Type of the value that represent the limits of the
	 * range.
	 * @ingroup Helper
	 */
	struct TileIdRange {
		struct Comparator {
			bool operator()(const TileIdRange &first,
			                const TileIdRange &second) const;
		};

		/**
		 * Removes the tile flipping flags. Used to get the real global tile
		 * id.
		 * @param value Value to remove the flags from.
		 * @return Value given with the tile flipping flags removed.
		 */
		static unsigned int withoutFlipFlags(unsigned int value);

		/**
		 * Checks wether or not the tile is flipped horizontally.
		 * @param value Tile id to check.
		 * @return True if it's flipped horizontally, false if not.
		 */
		static bool isFlippedHorizontally(unsigned int value);

		/**
		 * Checks wether or not the tile is flipped vertically.
		 * @param value Tile id to check.
		 * @return True if it's flipped vertically, false if not.
		 */
		static bool isFlippedVertically(unsigned int value);

		/**
		 * Checks wether or not the tile is flipped diagonally.
		 * @param value Tile id to check.
		 * @return True if it's flipped diagonally, false if not.
		 */
		static bool isFlippedDiagonally(unsigned int value);

		/**
		 * Flips a tile horizontally.
		 * @param value Tile id of the tile to flip.
		 * @return Tile id flipped.
		 */
		static unsigned int flipHorizontally(unsigned int value);

		/**
		 * Flips a tile vertically.
		 * @param value Tile id of the tile to flip.
		 * @return Tile id flipped.
		 */
		static unsigned int flipVertically(unsigned int value);

		/**
		 * Flips a tile diagonally.
		 * @param value Tile id of the tile to flip.
		 * @return Tile id flipped.
		 */
		static unsigned int flipDiagonally(unsigned int value);

		/**
		 * Default constructor.
		 */
		TileIdRange();

		/**
		 * Implicit constructor.
		 * @param center Value to set to both the min and the max values.
		 */
		TileIdRange(unsigned int center);

		/**
		 * Parameterized constructor.
		 * @param newMin Minimum value of the range.
		 * @param newMax Maximum value of the range (not included).
		 */
		TileIdRange(unsigned int newMin, unsigned int newMax);

		/**
		 * Copy constructor.
		 * @param src Range to copy.
		 */
		TileIdRange(const TileIdRange &src);

		/**
		 * Checks whether or not the received value fits within the range.
		 * @param value Value to check.
		 * @return True if the value fits within the range, false if not.
		 */
		bool isWithinRange(unsigned int value) const;

		/// Minimum value in the range (included).
		unsigned int min;

		/// Maximum value in the range (excluded).
		unsigned int max;
	};
}

#endif // RB_TILE_ID_RANGE_H
