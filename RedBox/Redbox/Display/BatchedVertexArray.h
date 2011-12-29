/**
 * @file
 */
#ifndef RB_BATCHED_VERTICES_ARRAY_H
#define RB_BATCHED_VERTICES_ARRAY_H

#include <algorithm>

#include "VertexArray.h"
#include "RenderBatch.h"

namespace RedBox {
	template <typename T>
	class BatchedVertexArray : public VertexArray {
		template <typename U> friend class RenderBatchParent;
		template <typename U, bool ANIMATABLE> friend class RenderBatchMiddle;
		template <typename U, typename V> friend class BatchedGraphic;
	public:
		BatchedVertexArray() : VertexArray(), begin(0), nbVertices(0),
			batch(NULL), vertices(NULL) {
		}

		/**
		 * Parameterized constructor. Links the vertex array with a render
		 * batch.
		 * @param newBegin Index of the first vertex in the batch.
		 * @param newNbVertices Number of vertices the array has.
		 * @param newBatch Pointer to the batch containing the vertices.
		 */
		BatchedVertexArray(SizeType newBegin, SizeType newNbVertices,
		                   RenderBatch<T> *newBatch) : VertexArray(),
			begin(newBegin), nbVertices(newNbVertices), batch(newBatch),
			vertices(NULL) {
		}

		/**
		 * Parameterized constructor. Creates a vertex array not yet linked with
		 * a render batch.
		 * @param newNbVertices Number of vertices to create.
		 * @param defaultValue Value to initialize the vertices with.
		 * @param newBatch Pointer to the parent batch. NULL by default.
		 */
		BatchedVertexArray(SizeType newNbVertices,
		                   const ValueType &defaultValue = ValueType(),
		                   RenderBatch<T> *newBatch = NULL) : VertexArray(),
			begin(0), nbVertices(newNbVertices), batch(NULL),
			vertices(new ContainerType(newNbVertices, defaultValue)) {
		}

		/**
		 * Copy constructor.
		 * @param src Batched vertex array to make a copy of.
		 */
		BatchedVertexArray(const BatchedVertexArray<T> &src) : VertexArray(src),
			begin(0), nbVertices(src.nbVertices), batch(NULL),
			vertices(new ContainerType(nbVertices)) {
			std::copy(src.getBegin(), src.getEnd(), vertices->begin());
		}

		/**
		 * Destructor.
		 */
		~BatchedVertexArray() {
			if (vertices) {
				delete vertices;
			}
		}

		/**
		 * Gets the iterator pointing to the first vertex.
		 * @return Iterator pointing to the first vertex in the array.
		 */
		Iterator getBegin() {
			if (batch) {
				return batch->vertices.getBegin() + begin;

			} else if (vertices) {
				return vertices->begin();

			} else {
				return Iterator();
			}
		}

		/**
		 * Gets the constant iterator pointing to the first vertex.
		 * @return Const iterator pointing to the first vertex in the array.
		 */
		ConstIterator getBegin() const {
			if (batch) {
				return batch->vertices.getBegin() + begin;

			} else if (vertices) {
				return vertices->begin();

			} else {
				return ConstIterator();
			}
		}

		/**
		 * Gets the iterator pointing to the end of the array (after the last
		 * vertex.
		 * @return Iterator pointing to the end of the array.
		 */
		Iterator getEnd() {
			if (batch) {
				return batch->vertices.getBegin() + begin + nbVertices;

			} else if (vertices) {
				return vertices->end();

			} else {
				return Iterator();
			}
		}

		/**
		 * Gets the constant iterator pointing to the end of the array (after
		 * the last vertex).
		 * @return Const iterator pointing to the end of the array.
		 */
		ConstIterator getEnd() const {
			if (batch) {
				return batch->vertices.getBegin() + begin + nbVertices;

			} else if (vertices) {
				return vertices->end();

			} else {
				return ConstIterator();
			}
		}

		/**
		 * Gets the reverse iterator pointing to the first vertex.
		 * @return Reverse iterator pointing to the first vertex in the array.
		 */
		ReverseIterator getReverseBegin() {
			if (batch) {
				return batch->vertices.getReverseBegin() + (batch->vertices.getNbVertices() - begin - nbVertices);

			} else if (vertices) {
				return vertices->rbegin();

			} else {
				return ReverseIterator();
			}
		}

		/**
		 * Gets the constant reverse iterator pointing to the first vertex.
		 * @return Const reverse iterator pointing to the first vertex in the
		 * array.
		 */
		ConstReverseIterator getReverseBegin() const {
			if (batch) {
				return batch->vertices.getReverseBegin() + (batch->vertices.getNbVertices() - begin - nbVertices);

			} else if (vertices) {
				return vertices->rbegin();

			} else {
				return ConstReverseIterator();
			}
		}

		/**
		 * Gets the reverse iterator pointing to the end of the array (after the
		 * last vertex, or before the first vertex because it's in reverse).
		 * @return Reverse terator pointing to the end of the array.
		 */
		ReverseIterator getReverseEnd() {
			if (batch) {
				return batch->vertices.getReverseBegin() + (batch->vertices.getNbVertices() - begin);

			} else if (vertices) {
				return vertices->rend();

			} else {
				return ReverseIterator();
			}
		}

		/**
		 * Gets the constant reverse iterator pointing to the end of the array
		 * (after the last vertex, or before the first vertex because it's
		 * in reverse).
		 * @return Const reverse iterator pointing to the end of the array.
		 */
		ConstReverseIterator getReverseEnd() const {
			if (batch) {
				return batch->vertices.getReverseBegin() + (batch->vertices.getNbVertices() - begin);

			} else if (vertices) {
				return vertices->rend();

			} else {
				return ConstReverseIterator();
			}
		}

		/**
		 * Checks if the array is empty or not.
		 * @return True if the array is empty, false if not.
		 */
		bool isEmpty() const {
			return nbVertices == 0;
		}

		/**
		 * Gets the array of vertices' size.
		 * @return Number of vertices the array contains.
		 */
		SizeType getNbVertices() const {
			return nbVertices;
		}

		/**
		 * Erases all the vertices.
		 */
		void clear() {
			if (batch) {
				this->erase(this->getBegin(), this->getEnd());

			} else if (vertices) {
				vertices->clear();
				nbVertices = 0;
			}
		}

		/**
		 * Inserts a vertex in the array.
		 * @param position The new vertex will be inserted before this position.
		 * @param value Value to insert.
		 * @return Iterator pointing to the vertex following the inserted
		 * vertex.
		 */
		Iterator insert(Iterator position, ConstReference value = ValueType()) {
			if (batch) {
				SizeType tmp = position - batch->vertices.getBegin();

				if (tmp >= begin && tmp - begin <= nbVertices) {
					batch->addVertices(tmp, 1);

					*(batch->vertices.getBegin() + tmp) = value;

					++nbVertices;

					if (tmp == begin) {
						--begin;
					}
				}

				return batch->vertices.getBegin() + tmp + 1;

			} else if (vertices) {
				++nbVertices;
				return vertices->insert(position, value);

			} else {
				return Iterator();
			}
		}

		/**
		 * Inserts vertices in the array.
		 * @param position The new vertices will be inserted before this
		 * position.
		 * @param count Number of vertices to insert.
		 * @param value Value to insert.
		 */
		void insert(Iterator position, SizeType count, ConstReference value = ValueType()) {
			if (batch) {
				SizeType tmp = position - batch->vertices.getBegin();

				if (tmp >= begin && tmp - begin <= nbVertices) {
					batch->addVertices(tmp, count);

					for (SizeType i = tmp; i < tmp + count; ++i) {
						*(batch->vertices.getBegin() + i) = value;
					}

					nbVertices += count;

					if (tmp == begin) {
						begin -= count;
					}
				}

			} else if (vertices) {
				vertices->insert(position, count, value);
				nbVertices += count;
			}
		}

		/**
		 * Erases the specified vertex.
		 * @param position Iterator pointing to the vertex to erase.
		 * @return Iterator pointing to the vertex following the one erased.
		 */
		Iterator erase(Iterator position) {
			if (batch) {
				SizeType tmp = position - batch->vertices.getBegin();

				if (tmp >= begin && tmp - begin < nbVertices) {
					batch->removeVertices(tmp, 1);

					--nbVertices;

					if (tmp == begin) {
						++begin;
					}
				}

				return batch->vertices.getBegin() + tmp;

			} else if (vertices) {
				--nbVertices;
				return vertices->erase(position);

			} else {
				return Iterator();
			}
		}

		/**
		 * Erases a bunch of vertices.
		 * @param first First vertex to erase.
		 * @param last Last vertex to erase.
		 * @return Iterator pointing to the vertex following the last one
		 * erased.
		 */
		Iterator erase(Iterator first, Iterator last) {
			if (batch) {
				SizeType tmpFirst = first - batch->vertices.getBegin();
				SizeType tmpLast = last - batch->vertices.getBegin();

				if (tmpLast > tmpFirst && tmpFirst >= begin &&
				    tmpLast <= begin + nbVertices) {
					batch->removeVertices(tmpFirst, tmpLast - tmpFirst);
				}

				return batch->vertices.getBegin() + tmpFirst;

			} else if (vertices) {
				return vertices->erase(first, last);

			} else {
				return Iterator();
			}
		}

		/**
		 * Inserts a vertex at the end of the array.
		 * @param newVertex Vertex to insert at the end of the array.
		 */
		void pushBack(ConstReference newVertex) {
			if (batch) {
				this->insert(this->getEnd(), 1, newVertex);

			} else if (vertices) {
				vertices->push_back(newVertex);
			}
		}

		/**
		 * Erases the last vertex in the array.
		 */
		void popBack() {
			if (batch) {
				if (nbVertices) {
					this->erase(this->getEnd() - 1);
				}

			} else if (vertices) {
				vertices->pop_back();
			}
		}

		/**
		 * Resizes the array and fills up the newly created vertices with the
		 * one given.
		 * @param count New array's size.
		 * @param value Value to insert if the new size is bigger.
		 */
		void resize(SizeType count, ConstReference value = ValueType()) {
			if (batch) {
				if (count > nbVertices) {
					this->insert(this->getEnd(), count - nbVertices, value);

				} else if (count < nbVertices) {
					this->erase(this->getBegin() + (nbVertices - count), this->getEnd());
				}

			} else if (vertices) {
				vertices->resize(count, value);
				nbVertices = count;
			} else {
				vertices = new ContainerType(count, value);
				nbVertices = count;
			}
		}

	private:
		/**
		 * Creates a backup copy of the vertices from the batch.
		 */
		void unlinkVertices() {
			if (batch && !vertices) {
				vertices = new ContainerType(nbVertices);
				std::copy(this->getBegin(), this->getEnd(), vertices->begin());
			}
		}

		/// Index in the batch where the vertices begin.
		SizeType begin;

		/// Number of vertices.
		SizeType nbVertices;

		/// Pointer to the parent batch.
		RenderBatchParent<T> *batch;

		/// Pointer to the temporary array of vertices.
		ContainerType *vertices;
	};

}

#endif // RB_BATCHED_VERTICES_ARRAY_H
