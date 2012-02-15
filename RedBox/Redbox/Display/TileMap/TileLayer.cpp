#include "TileLayer.h"

#include <algorithm>

#include "TileMap.h"

namespace RedBox {

	TileLayer *TileLayer::asTileLayer() {
		return this;
	}

	const TileLayer *TileLayer::asTileLayer() const {
		return this;
	}

	TileLayer::~TileLayer() {
	}

	void TileLayer::applyTilesetDestruction(const TileIdRange &toDestroy) {
		unsigned int tmpLength = toDestroy.max - toDestroy.min;

		for (DataContainer::iterator i = data.begin(); i != data.end(); ++i) {
			if (toDestroy.isWithinRange(*i)) {
				*i = 0;

			} else if (*i >= toDestroy.max) {
				*i -= tmpLength;
			}
		}
	}

	void TileLayer::setSizeInTiles(const TileCoordinate &newSizeInTiles,
	                               const TileCoordinate &offset) {
		// If only one of the sizes is changed, we call the correct function.
		if (newSizeInTiles.getX() == parentMap->getWidthInTiles()) {
			setHeightInTiles(newSizeInTiles.getY(), offset.getY());

		} else if (newSizeInTiles.getY() == parentMap->getHeightInTiles()) {
			setWidthInTiles(newSizeInTiles.getX(), offset.getX());

		} else {
			// If there is data to take into account when resizing.
			if (!data.empty()) {
				if (newSizeInTiles.getX() < parentMap->getWidthInTiles()) {
					if (newSizeInTiles.getY() < parentMap->getHeightInTiles()) {
						// New width and new height are lower.
						// We calculate the number of tile data's to skip
						// at the end of each row.
						const DataContainer::size_type offsetIncrement = parentMap->getWidthInTiles() - newSizeInTiles.getX();
						// We calculate the new size of the tile data vector.
						const DataContainer::size_type newSize = newSizeInTiles.getX() * newSizeInTiles.getY();
						// We initialize our index iterators.
						DataContainer::size_type currentOffset = 0;
						DataContainer::size_type i = 0;

						// We loop through the tile data and keep the left most
						// data on each row.
						do {
							data[i] = data[i + currentOffset];
							++i;

							if (i % newSizeInTiles.getX() == 0) {
								currentOffset += offsetIncrement;
							}
						} while (i < newSize);

						// We resize the tile data vector.

					} else {
						// New width is lower and new height is higher.
						setWidthInTiles(newSizeInTiles.getX(), 0);
						setHeightInTiles(newSizeInTiles.getY(), offset.getY());
					}

				} else {
					if (newSizeInTiles.getY() < parentMap->getHeightInTiles()) {
						// New width is higher and new height is lower.

						// We calculate the position of the first column after
						// the left margin caused by the horizontal offset.
						const unsigned int leftMargin = std::min(std::max(offset.getX(), 0),
						                                         newSizeInTiles.getX() - parentMap->getWidthInTiles());
						// We calculate the position of the first column of the
						// right margin caused by the horizontal offset.
						const unsigned int rightMargin = leftMargin + parentMap->getWidthInTiles();

						// We calculate the index of first the tile data that
						// we'll use to loop backwards.
						DataContainer::size_type oldIndex = data.size() - (parentMap->getHeightInTiles() - newSizeInTiles.getY()) * parentMap->getWidthInTiles();

						// we calculate the new size of the tile data vector.
						const DataContainer::size_type newSize = newSizeInTiles.getX() * newSizeInTiles.getY();

						// If the new size is bigger, we resize the data vector now.
						if (newSize > data.size()) {
							data.resize(newSize, 0u);
						}

						// We initialize our row and column indexes.
						unsigned int row = newSizeInTiles.getY();
						unsigned int column;

						// We loop through the tile data to apply the horizontal
						// offset.
						do {
							--row;
							column = newSizeInTiles.getX();

							do {
								--column;

								if (column < leftMargin || column >= rightMargin) {
									data[row * newSizeInTiles.getX() + column] = 0u;

								} else {
									--oldIndex;
									data[row + newSizeInTiles.getX() + column] = data[oldIndex];
								}
							} while (column > 0);
						} while (row > 0);

						// If the new size of the tile data vector is smaller,
						// we resize it now.
						if (newSize < data.size()) {
							data.resize(newSize);
						}

					} else {
						// New width and new height are higher.
						// We calculate ALL the margins.
						const unsigned int leftMargin = std::min(std::max(offset.getX(), 0), newSizeInTiles.getX() - parentMap->getWidthInTiles());
						const unsigned int rightMargin = leftMargin + parentMap->getWidthInTiles();
						const unsigned int topMargin = std::min(std::max(offset.getY(), 0), newSizeInTiles.getY() - parentMap->getHeightInTiles());
						const unsigned int bottomMargin = topMargin + parentMap->getHeightInTiles();

						// We get the first index of the original data that
						// we'll use to loop backwards.
						DataContainer::size_type oldIndex = data.size();

						// We resize the tile data vector.
						data.resize(newSizeInTiles.getX() * newSizeInTiles.getY(),
						            0u);

						// We initialize our row and column indexes that we'll
						// use to loop backwards.
						unsigned int row = newSizeInTiles.getY();
						unsigned int column;

						// We loop through the tile data to apply the offsets.
						do {
							--row;
							column = newSizeInTiles.getX();

							if (row >= topMargin && row < bottomMargin) {
								do {
									--column;

									if (column >= leftMargin && column < rightMargin) {
										--oldIndex;
										data[row * newSizeInTiles.getX() + column] = data[oldIndex];

									} else {
										data[row * newSizeInTiles.getX() + column] = 0u;
									}
								} while (column > 0);

							} else {
								do {
									--column;
									data[row * newSizeInTiles.getX() + column] = 0u;
								} while (column > 0);
							}
						} while (row > 0);
					}
				}

			} else if (newSizeInTiles.getX() > 0 && newSizeInTiles.getY() > 0) {
				// We can resize and put 0's to all the new tile data.
				data.resize(newSizeInTiles.getX() * newSizeInTiles.getY(), 0u);
			}
		}
	}

	void TileLayer::setWidthInTiles(int newWidth, int offset) {
		// If we're making the map bigger.
		if (newWidth > parentMap->getWidthInTiles()) {
			// If the map already contained data (which means the width AND the
			// height are greater than 0.
			if (!data.empty()) {
				// We get the index of the first column after the left margin.
				const unsigned int leftMargin = std::min(std::max(offset, 0),
				                                         newWidth - parentMap->getHeightInTiles());
				// We get the first index that's in the right margin.
				const unsigned int rightMargin = leftMargin + parentMap->getWidthInTiles();

				// We take note of the size before resizing, we'll use that to
				// get the index of the last element and loop backwards.
				DataContainer::size_type oldIndex = data.size();

				// We resize the tile data to the new size.
				data.resize(newWidth * parentMap->getHeightInTiles());

				// We initialize our row and column indexes.
				unsigned int row = parentMap->getHeightInTiles();
				unsigned int column;

				// We loop in the tile data to apply the offset.
				do {
					--row;
					column = newWidth;

					do {
						--column;

						if (column  < leftMargin || column >= rightMargin) {
							data[row * newWidth + column] = 0u;

						} else {
							--oldIndex;
							data[row * newWidth + column] = data[oldIndex];
						}
					} while (column > 0u);
				} while (row > 0u);

			} else {
				// There was no data yet, so we simply fill the data with 0's.
				// If the height is still equal to 0, this call to resize
				// will not do anything...
				data.resize(newWidth * parentMap->getHeightInTiles());
			}

		} else if (newWidth < parentMap->getWidthInTiles()) {
			// We calculate the number of columns to remove and skip on each
			// row.
			const DataContainer::size_type offsetIncrement = parentMap->getWidthInTiles() - newWidth;
			// We calculate the new size of the tile data vector.
			const DataContainer::size_type newSize = newWidth * parentMap->getHeightInTiles();
			// We initialize our current offset and our index iterator to 0.
			DataContainer::size_type currentOffset = 0;
			DataContainer::size_type i = 0;

			// We loop through the tile data and keep the left most data.
			do {
				data[i] = data[i + currentOffset];
				++i;

				if (i % newWidth == 0) {
					currentOffset += offsetIncrement;
				}
			} while (i < newSize);

			// We reduce the size of the tile data vector.
			data.resize(newSize);
		}
	}

	void TileLayer::setHeightInTiles(int newHeight, int offset) {
		// If we are making the map bigger.
		if (newHeight > parentMap->getHeightInTiles()) {
			// If there is no offset or if the height was already 0.
			if (offset <= 0 || parentMap->getHeightInTiles() <= 0) {
				// We simply resize it and fill the new tiles with 0.
				data.resize(parentMap->getWidthInTiles() * newHeight, 0u);

			} else {
				const unsigned int width = static_cast<unsigned int>(parentMap->getWidthInTiles());
				// We calculate the position of the top and the bottom margins.
				const unsigned int topMargin = std::min(std::max(offset, 0),
				                                        newHeight - parentMap->getHeightInTiles());
				const unsigned int bottomMargin = topMargin + parentMap->getHeightInTiles();

				// We take note of the size before resizing, we'll use that
				// to get the index of the last element and loop backwards.
				DataContainer::size_type oldIndex = data.size();

				// We resize the data vector.
				data.resize(width * newHeight, 0u);

				// We declare our row and column that we'll use to loop
				// through the vector.
				unsigned int row = newHeight;
				unsigned int column;

				// We loop through the data and move the tile id's to apply
				// the offset.
				do {
					--row;
					column = width;

					if (row >= topMargin && row < bottomMargin) {
						do {
							--column;
							--oldIndex;
							data[row * width + column] = data[oldIndex];
						} while (column > 0);

					} else {
						do {
							--column;
							data[row * width + column] = 0u;
						} while (column > 0);
					}
				} while (row > 0u);
			}

		} else if (newHeight < parentMap->getHeightInTiles()) {
			data.resize(parentMap->getWidthInTiles() * newHeight);
		}
	}
}
