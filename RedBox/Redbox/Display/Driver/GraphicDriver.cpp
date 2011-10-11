#include "GraphicDriver.h"

#include "PlatformFlagger.h"

#include RB_GRAPHIC_DRIVER_INCLUDE

namespace RedBox {
	GraphicDriver &GraphicDriver::getInstance() {
		return RB_GRAPHIC_DRIVER;
	}

	GraphicDriver::GraphicDriver() {
	}

	GraphicDriver::~GraphicDriver() {
	}
}
