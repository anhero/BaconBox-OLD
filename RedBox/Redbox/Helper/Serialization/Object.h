/**
 * @file
 * @ingroup Serialization
 */
#ifndef RB_OBJECT_H
#define RB_OBJECT_H

#include <map>
#include <string>

namespace RedBox {
	class Value;

	typedef std::map<std::string, Value> Object;
}

#endif
