#include "BaconBox/Display/Driver/GraphicDriver.h"

#include "BaconBox/Engine.h"

namespace BaconBox {
	GraphicDriver &GraphicDriver::getInstance() {
		return Engine::getGraphicDriver();
	}

	GraphicDriver::GraphicDriver() {
	}

	GraphicDriver::~GraphicDriver() {
	}
}
