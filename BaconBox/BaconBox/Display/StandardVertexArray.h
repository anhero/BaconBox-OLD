/**
 * @file
 * @ingroup Display
 */
#ifndef RB_STANDARD_VERTICES_ARRAY_H
#define RB_STANDARD_VERTICES_ARRAY_H

#include "VertexArray.h"

namespace BaconBox {
	class StandardVertexArray : public VertexArray {
	public:
		/**
		 * Default constructor.
		 */
		StandardVertexArray();

		/**
		 * Parameterized constructor.
		 * @param newSize Size of the array at initialization.
		 * @param defaultValue Value to use to fill the array.
		 * @see BaconBox::StandardVertexArray::vertices
		 */
		explicit StandardVertexArray(SizeType newSize,
		                             ConstReference defaultValue = ValueType());

		/**
		 * Copy constructor.
		 * @param src StandardVertexArray to make a copy of.
		 */
		StandardVertexArray(const StandardVertexArray &src);

		/**
		 * Destructor.
		 */
		~StandardVertexArray();

		/**
		 * Assignment operator.
		 * @param src StandardVertexArray to make a copy of.
		 * @return Reference to the modified StandardVertexArray.
		 */
		StandardVertexArray &operator=(const StandardVertexArray &src);

		/**
		 * Gets the iterator pointing to the first vertex.
		 * @return Iterator pointing to the first vertex in the array.
		 */
		Iterator getBegin();

		/**
		 * Gets the constant iterator pointing to the first vertex.
		 * @return Const iterator pointing to the first vertex in the array.
		 */
		ConstIterator getBegin() const;

		/**
		 * Gets the iterator pointing to the end of the array (after the last
		 * vertex.
		 * @return Iterator pointing to the end of the array.
		 */
		Iterator getEnd();

		/**
		 * Gets the constant iterator pointing to the end of the array (after
		 * the last vertex).
		 * @return Const iterator pointing to the end of the array.
		 */
		ConstIterator getEnd() const;

		/**
		 * Gets the reverse iterator pointing to the first vertex.
		 * @return Reverse iterator pointing to the first vertex in the array.
		 */
		ReverseIterator getReverseBegin();

		/**
		 * Gets the constant reverse iterator pointing to the first vertex.
		 * @return Const reverse iterator pointing to the first vertex in the
		 * array.
		 */
		ConstReverseIterator getReverseBegin() const;

		/**
		 * Gets the reverse iterator pointing to the end of the array (after the
		 * last vertex, or before the first vertex because it's in reverse).
		 * @return Reverse terator pointing to the end of the array.
		 */
		ReverseIterator getReverseEnd();

		/**
		 * Gets the constant reverse iterator pointing to the end of the array
		 * (after the last vertex, or before the first vertex because it's
		 * in reverse).
		 * @return Const reverse iterator pointing to the end of the array.
		 */
		ConstReverseIterator getReverseEnd() const;

		/**
		 * Checks if the array is empty or not.
		 * @return True if the array is empty, false if not.
		 */
		bool isEmpty() const;

		/**
		 * Gets the array of vertices' size.
		 * @return Number of vertices the array contains.
		 */
		SizeType getNbVertices() const;

		/**
		 * Erases all the vertices.
		 */
		void clear();

		/**
		 * Inserts a vertex in the array.
		 * @param position The new vertex will be inserted before this position.
		 * @param value Value to insert.
		 * @return Iterator pointing to the vertex following the inserted
		 * vertex.
		 */
		Iterator insert(Iterator position, ConstReference value = ValueType());

		/**
		 * Inserts vertices in the array.
		 * @param position The new vertices will be inserted before this
		 * position.
		 * @param count Number of vertices to insert.
		 * @param value Value to insert.
		 */
		void insert(Iterator position, SizeType count, ConstReference value = ValueType());

		/**
		 * Inserts vertices to specified position in the vertex array.
		 * @param position Vertex before which the content will be inserted.
		 * @param first First vertex to be inserted.
		 * @param last Vertex after the last vertex to be inserted.
		 */
		void insert(Iterator position, Iterator first, Iterator last);

		/**
		 * Erases the specified vertex.
		 * @param position Iterator pointing to the vertex to erase.
		 * @return Iterator pointing to the vertex following the one erased.
		 */
		Iterator erase(Iterator position);

		/**
		 * Erases a bunch of vertices.
		 * @param first First vertex to erase.
		 * @param last Last vertex to erase.
		 * @return Iterator pointing to the vertex following the last one
		 * erased.
		 */
		Iterator erase(Iterator first, Iterator last);

		/**
		 * Inserts a vertex at the end of the array.
		 * @param newVertex Vertex to insert at the end of the array.
		 */
		void pushBack(ConstReference newVertex);

		/**
		 * Erases the last vertex in the array.
		 */
		void popBack();

		/**
		 * Resizes the array and fills up the newly created vertices with the
		 * one given.
		 * @param count New array's size.
		 * @param value Value to insert if the new size is bigger.
		 */
		void resize(SizeType count, ConstReference value = ValueType());

		/**
		 * Sets the capacity of the container to at least the given size. New
		 * storage is allocated if necessary.
		 * @param size New capacity of the container.
		 */
		void reserve(SizeType size);
	private:
		ContainerType vertices;
	};

}

#endif
