/**
 * @file
 */
#ifndef RB_ITERATORS_H
#define RB_ITERATORS_H

#include <iterator>

namespace BaconBox {
	template <typename Container>
	class BidirectionalIterator {
	public:
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef typename Container::ValueType value_type;
		typedef typename Container::DifferenceType difference_type;
		typedef typename Container::Reference reference;
		typedef typename Container::Pointer pointer;

		BidirectionalIterator() {}
		explicit BidirectionalIterator(typename Container::Container::iterator newIt) : it(newIt) {}
		BidirectionalIterator(const BidirectionalIterator<Container> &src) : it(src.it) {}

		BidirectionalIterator<Container> &operator=(const BidirectionalIterator<Container> &src) {
			it = src.it;
			return *this;
		}

		bool operator==(const BidirectionalIterator<Container> &other) const {
			return it == other.it;
		}

		bool operator!=(const BidirectionalIterator<Container> &other) const {
			return it != other.it;
		}

		BidirectionalIterator<Container> &operator++() {
			++it;
			return *this;
		}

		BidirectionalIterator<Container> operator++(int) {
			BidirectionalIterator<Container> result(*this);
			++it;
			return result;
		}

		BidirectionalIterator<Container> &operator--() {
			--it;
			return *this;
		}

		BidirectionalIterator<Container> operator--(int) {
			BidirectionalIterator<Container> result(*this);
			--it;
			return result;
		}

		reference operator*() const {
			return *(*it);
		}

		pointer operator->() const {
			return *it;
		}
	private:
		typename Container::Container::iterator it;
	};

	template <typename Container>
	class BidirectionalConstIterator {
	public:
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef typename Container::ValueType value_type;
		typedef typename Container::DifferenceType difference_type;
		typedef typename Container::ConstReference reference;
		typedef typename Container::ConstPointer pointer;

		BidirectionalConstIterator() {}
		BidirectionalConstIterator(const BidirectionalConstIterator<Container> &src) : it(src.it) {}
		explicit BidirectionalConstIterator(typename Container::Container::const_iterator newIt) : it(newIt) {}
		BidirectionalConstIterator(const BidirectionalIterator<Container> &src) : it(src.it) {}

		BidirectionalConstIterator<Container> &operator=(const BidirectionalConstIterator<Container> &src) {
			it = src.it;
			return *this;
		}

		bool operator==(const BidirectionalConstIterator<Container> &other) const {
			return it == other.it;
		}

		bool operator!=(const BidirectionalConstIterator<Container> &other) const {
			return it != other.it;
		}

		BidirectionalConstIterator<Container> &operator++() {
			++it;
			return *this;
		}

		BidirectionalConstIterator<Container> operator++(int) {
			BidirectionalIterator<Container> result(*this);
			++it;
			return result;
		}

		BidirectionalConstIterator<Container> &operator--() {
			--it;
			return *this;
		}

		BidirectionalConstIterator<Container> operator--(int) {
			BidirectionalIterator<Container> result(*this);
			--it;
			return result;
		}

		reference operator*() const {
			return *(*it);
		}

		pointer operator->() const {
			return *it;
		}
	private:
		typename Container::Container::const_iterator it;
	};

	template <typename Container>
	class RandomAccessIterator {
	public:
		typedef std::random_access_iterator_tag iterator_category;
		typedef typename Container::ValueType value_type;
		typedef typename Container::DifferenceType difference_type;
		typedef typename Container::Reference reference;
		typedef typename Container::Pointer pointer;

		RandomAccessIterator() {}
		explicit RandomAccessIterator(typename Container::Container::iterator newIt) : it(newIt) {}
		RandomAccessIterator(const RandomAccessIterator<Container> &src) : it(src.it) {}

		RandomAccessIterator<Container> &operator=(const RandomAccessIterator<Container> &src) {
			it = src.it;
			return *this;
		}

		bool operator==(const RandomAccessIterator<Container> &other) const {
			return it == other.it;
		}

		bool operator!=(const RandomAccessIterator<Container> &other) const {
			return it != other.it;
		}

		bool operator<(const RandomAccessIterator<Container> &other) const {
			return it < other.it;
		}

		bool operator>(const RandomAccessIterator<Container> &other) const {
			return it > other.it;
		}

		bool operator<=(const RandomAccessIterator<Container> &other) const {
			return it <= other.it;
		}

		bool operator>=(const RandomAccessIterator<Container> &other) const {
			return it >= other.it;
		}

		RandomAccessIterator<Container> &operator++() {
			++it;
			return *this;
		}

		RandomAccessIterator<Container> operator++(int) {
			RandomAccessIterator<Container> result(*this);
			++it;
			return result;
		}

		RandomAccessIterator<Container> &operator--() {
			--it;
			return *this;
		}

		RandomAccessIterator<Container> operator--(int) {
			RandomAccessIterator<Container> result(*this);
			--it;
			return result;
		}

		RandomAccessIterator<Container> &operator+=(difference_type n) {
			it += n;
			return *this;
		}

		RandomAccessIterator<Container> operator+(difference_type n) const {
			return RandomAccessIterator<Container>(*this) += n;
		}

		template <typename T> friend RandomAccessIterator<T> operator+(typename RandomAccessIterator<T>::difference_type n,
		                                                               const RandomAccessIterator<T> &i);

		RandomAccessIterator<Container> &operator-=(difference_type n) {
			it -= n;
			return *this;
		}

		RandomAccessIterator<Container> operator-(difference_type n) const {
			return RandomAccessIterator<Container>(*this) -= n;
		}

		template <typename T> friend RandomAccessIterator<T> operator-(typename RandomAccessIterator<T>::difference_type n,
		                                                               const RandomAccessIterator<T> &i);

		reference operator*() const {
			return *(*it);
		}

		pointer operator->() const {
			return *it;
		}

		reference operator[](difference_type index) {
			return *(it[0]);
		}
	private:
		typename Container::Container::iterator it;
	};

	template <typename Container>
	RandomAccessIterator<Container> operator+(typename RandomAccessIterator<Container>::difference_type n,
	                                          const RandomAccessIterator<Container> &i) {
		return RandomAccessIterator<Container>(i) += n;
	}

	template <typename Container>
	RandomAccessIterator<Container> operator-(typename RandomAccessIterator<Container>::difference_type n,
	                                          const RandomAccessIterator<Container> &i) {
		return RandomAccessIterator<Container>(i) -= n;
	}

	template <typename Container>
	class RandomAccessConstIterator {
	public:
		typedef std::random_access_iterator_tag iterator_category;
		typedef typename Container::ValueType value_type;
		typedef typename Container::DifferenceType difference_type;
		typedef typename Container::ConstReference reference;
		typedef typename Container::ConstPointer pointer;

		RandomAccessConstIterator() {}
		explicit RandomAccessConstIterator(typename Container::Container::const_iterator newIt) : it(newIt) {}
		RandomAccessConstIterator(const RandomAccessConstIterator<Container> &src) : it(src.it) {}

		RandomAccessConstIterator<Container> &operator=(const RandomAccessConstIterator<Container> &src) {
			it = src.it;
			return *this;
		}

		bool operator==(const RandomAccessConstIterator<Container> &other) const {
			return it == other.it;
		}

		bool operator!=(const RandomAccessConstIterator<Container> &other) const {
			return it != other.it;
		}

		bool operator<(const RandomAccessConstIterator<Container> &other) const {
			return it < other.it;
		}

		bool operator>(const RandomAccessConstIterator<Container> &other) const {
			return it > other.it;
		}

		bool operator<=(const RandomAccessConstIterator<Container> &other) const {
			return it <= other.it;
		}

		bool operator>=(const RandomAccessConstIterator<Container> &other) const {
			return it >= other.it;
		}

		RandomAccessConstIterator<Container> &operator++() {
			++it;
			return *this;
		}

		RandomAccessConstIterator<Container> operator++(int) {
			RandomAccessConstIterator<Container> result(*this);
			++it;
			return result;
		}

		RandomAccessConstIterator<Container> &operator--() {
			--it;
			return *this;
		}

		RandomAccessConstIterator<Container> operator--(int) {
			RandomAccessConstIterator<Container> result(*this);
			--it;
			return result;
		}

		RandomAccessConstIterator<Container> &operator+=(difference_type n) {
			it += n;
			return *this;
		}

		RandomAccessConstIterator<Container> operator+(difference_type n) const {
			return RandomAccessConstIterator<Container>(*this) += n;
		}

		template <typename T> friend RandomAccessConstIterator<T> operator+(typename RandomAccessConstIterator<T>::difference_type n,
		                                                                    const RandomAccessConstIterator<T> &i);

		RandomAccessConstIterator<Container> &operator-=(difference_type n) {
			it -= n;
			return *this;
		}

		RandomAccessConstIterator<Container> operator-(difference_type n) const {
			return RandomAccessConstIterator<Container>(*this) -= n;
		}

		template <typename T> friend RandomAccessConstIterator<T> operator-(typename RandomAccessConstIterator<T>::difference_type n,
		                                                                    const RandomAccessConstIterator<T> &i);

		reference operator*() const {
			return *(*it);
		}

		pointer operator->() const {
			return *it;
		}

		reference operator[](difference_type index) {
			return *(it[0]);
		}
	private:
		typename Container::Container::const_iterator it;
	};

	template <typename Container>
	RandomAccessConstIterator<Container> operator+(typename RandomAccessConstIterator<Container>::difference_type n,
	                                               const RandomAccessConstIterator<Container> &i) {
		return RandomAccessConstIterator<Container>(i) += n;
	}

	template <typename Container>
	RandomAccessConstIterator<Container> operator-(typename RandomAccessConstIterator<Container>::difference_type n,
	                                               const RandomAccessConstIterator<Container> &i) {
		return RandomAccessConstIterator<Container>(i) -= n;
	}
}

#endif
