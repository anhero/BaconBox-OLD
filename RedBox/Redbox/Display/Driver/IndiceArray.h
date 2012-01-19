/**
 * @file
 */
#ifndef RB_INDICE_ARRAY_H
#define RB_INDICE_ARRAY_H

#include <vector>
#include <list>

#include "StandardVertexArray.h"

namespace RedBox {
	typedef std::vector<unsigned short> IndiceArray;
	typedef std::list<std::pair<StandardVertexArray::SizeType, IndiceArray::size_type> > IndiceArrayList;
}

#endif // RB_INDICE_ARRAY_H
