#include "PlatformFlagger.h"

#ifdef RB_PHYSICS_ENABLED

#include "LinkData.h"

using namespace RedBox;

LinkData::LinkData():length(0.0f), frontMaxAngle(0.0f), frontMinAngle(0.0f),
backMaxAngle(0.0f), backMinAngle(0.0f) {
}

LinkData::LinkData(float newLength, 
				   float newFrontMaxAngle,
				   float newFrontMinAngle,
				   float newBackMaxAngle, 
				   float newBackMinAngle):length(newLength),
frontMaxAngle(newFrontMaxAngle), frontMinAngle(newFrontMinAngle),
backMaxAngle(newBackMaxAngle), backMinAngle(newBackMinAngle) {
}

namespace RedBox {
	std::ostream& operator<<(std::ostream& output, const LinkData& l) {
		output << "{length: " << l.length << "f, frontMaxAngle: " << 
		l.frontMaxAngle << "f, frontMinAngle: " << l.frontMinAngle << 
		"f, backMaxAngle: " << l.backMaxAngle << "f, backMinAngle: " << 
		l.backMinAngle << "f}";
		return output;
	}
}
#endif