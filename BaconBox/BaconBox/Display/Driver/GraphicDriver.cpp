#include "GraphicDriver.h"

#include "Engine.h"

namespace BaconBox {
	GraphicDriver &GraphicDriver::getInstance() {
		return Engine::getGraphicDriver();
	}

	GraphicDriver::GraphicDriver() {
	}

	GraphicDriver::~GraphicDriver() {
	}
}
