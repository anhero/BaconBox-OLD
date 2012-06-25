/**
 * @file
 * @ingroup TileMap
 */
#ifndef RB_TILE_COORDINATE_H
#define RB_TILE_COORDINATE_H

namespace BaconBox {
	template <typename ValueType>
	class TileCoordinateT {
	public:
		static const TileCoordinateT<ValueType> getSum(const TileCoordinateT<ValueType> &first,
		                                              const TileCoordinateT<ValueType> &second) {
			return TileCoordinateT<ValueType>(first.x + second.x, first.y + second.y);
		}

		static const TileCoordinateT<ValueType> getDifference(const TileCoordinateT<ValueType> &first,
		                                                     const TileCoordinateT<ValueType> &second) {
			return TileCoordinateT<ValueType>(first.x - second.x, first.y - second.y);
		}

		TileCoordinateT() : x(0), y(0) {
		}

		TileCoordinateT(ValueType newX, ValueType newY) : x(newX), y(newY) {
		}

		TileCoordinateT(const TileCoordinateT<ValueType> &src) : x(src.x), y(src.y) {
		}

		TileCoordinateT<ValueType> &operator=(const TileCoordinateT<ValueType> &src) {
			if (this != &src) {
				x = src.x;
				y = src.y;
			}

			return *this;
		}

		bool operator==(const TileCoordinateT<ValueType> &other) const {
			return x == other.x && y == other.y;
		}

		bool operator!=(const TileCoordinateT<ValueType> &other) const {
			return !(*this == other);
		}

		bool operator<(const TileCoordinateT<ValueType> &other) const {
			return x + y < other.x + other.y;
		}

		bool operator<=(const TileCoordinateT<ValueType> &other) const {
			return x + y <= other.x + other.y;
		}

		bool operator>(const TileCoordinateT<ValueType> &other) const {
			return x + y > other.x + other.y;
		}

		bool operator>=(const TileCoordinateT<ValueType> &other) const {
			return x + y >= other.x + other.y;
		}

		TileCoordinateT<ValueType> &operator+=(const TileCoordinateT<ValueType> &rhs) {
			x += rhs.x;
			y += rhs.y;
			return *this;
		}

		TileCoordinateT<ValueType> &operator+=(ValueType rhs) {
			x += rhs;
			y += rhs;
			return *this;
		}

		TileCoordinateT<ValueType> &operator-=(const TileCoordinateT<ValueType> &rhs) {
			x -= rhs.x;
			y -= rhs.y;
			return *this;
		}

		TileCoordinateT<ValueType> &operator-=(ValueType rhs) {
			x -= rhs;
			y -= rhs;
			return *this;
		}

		TileCoordinateT<ValueType> &operator*=(ValueType rhs) {
			x *= rhs;
			y *= rhs;
			return *this;
		}

		TileCoordinateT<ValueType> &operator/=(ValueType rhs) {
			x /= rhs;
			y /= rhs;
			return *this;
		}

		const TileCoordinateT<ValueType> operator+(const TileCoordinateT<ValueType> &other) const {
			return TileCoordinateT<ValueType>(*this) += other;
		}

		const TileCoordinateT<ValueType> operator-(const TileCoordinateT<ValueType> &other) const {
			return TileCoordinateT<ValueType>(*this) -= other;
		}

		const TileCoordinateT<ValueType> operator*(ValueType other) const {
			return TileCoordinateT<ValueType>(*this) *= other;
		}

		const TileCoordinateT<ValueType> operator/(ValueType other) const {
			return TileCoordinateT<ValueType>(*this) /= other;
		}

		ValueType getX() const {
			return x;
		}
		void setX(ValueType newX) {
			x = newX;
		}

		void addToX(ValueType deltaX) {
			x += deltaX;
		}

		void subtractFromX(ValueType deltaX) {
			x -= deltaX;
		}

		void multiplyXBy(ValueType factorX) {
			x *= factorX;
		}

		void divideXBy(ValueType divisorX) {
			y /= divisorX;
		}

		ValueType getY() const {
			return y;
		}

		void setY(ValueType newY) {
			y = newY;
		}

		void addToY(ValueType deltaY) {
			y += deltaY;
		}

		void subtractFromY(ValueType deltaY) {
			y -= deltaY;
		}

		void multiplyYBy(ValueType factorY) {
			y *= factorY;
		}

		void divideYBy(ValueType divisorY) {
			y /= divisorY;
		}

		void setXY(ValueType newX, ValueType newY) {
			x = newX;
			y = newY;
		}

		void setXY(const TileCoordinateT<ValueType> &newXY) {
			*this = newXY;
		}

		void addToXY(const TileCoordinateT<ValueType> &delta) {
			x += delta.x;
			y += delta.y;
		}

		void addToXY(ValueType deltaX, ValueType deltaY) {
			x += deltaX;
			y += deltaY;
		}

		void addToXY(ValueType deltaXY) {
			x += deltaXY;
			y += deltaXY;
		}

		void subtractFromXY(const TileCoordinateT<ValueType> &delta) {
			x -= delta.x;
			y -= delta.y;
		}

		void subtractFromXY(ValueType deltaX, ValueType deltaY) {
			x -= deltaX;
			y -= deltaY;
		}

		void subtractFromXY(ValueType deltaXY) {
			x -= deltaXY;
			y -= deltaXY;
		}

		void multiplyXYBy(const TileCoordinateT<ValueType> &factor) {
			x *= factor.x;
			y *= factor.y;
		}

		void multiplyXYBy(ValueType factorX, ValueType factorY) {
			x *= factorX;
			y *= factorY;
		}

		void multiplyXYBy(ValueType factorXY) {
			x *= factorXY;
			y *= factorXY;
		}

		void divideXYBy(const TileCoordinateT<ValueType> &divisor) {
			x /= divisor.x;
			y /= divisor.y;
		}

		void divideXYBy(ValueType divisorX, ValueType divisorY) {
			x /= divisorX;
			y /= divisorY;
		}

		void divideXYBy(ValueType divisorXY) {
			x /= divisorXY;
			y /= divisorXY;
		}

	private:
		ValueType x;
		ValueType y;
	};

	typedef TileCoordinateT<int> TileCoordinate;
}

#endif // RB_TILE_COORDINATE_H
