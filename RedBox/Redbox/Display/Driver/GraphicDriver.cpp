#include "GraphicDriver.h"

#include "Engine.h"

namespace RedBox {
	GraphicDriver &GraphicDriver::getInstance() {
		return Engine::getGraphicDriver();
	}

	GraphicDriver::GraphicDriver() {
	}

	GraphicDriver::~GraphicDriver() {
	}
}
