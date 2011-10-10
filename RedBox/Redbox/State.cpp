#include "State.h"

#include <cassert>
#include <algorithm>

#include "Console.h"
#include "GraphicDriver.h"

namespace RedBox {
	const std::string State::DEFAULT_NAME = "State";

	State::State(const std::string &newName) : Updateable(), Renderable(),
		BodyManager<Layerable, Layerable::LessCompare>(),
		sigly::HasSlots<>(), camera(), name(newName) {
	}

	State::~State() {
	}

	void State::update() {
	}

	void State::render() {
	}

	const std::string &State::getName() const {
		return name;
	}

	void State::setName(const std::string &newName) {
		name = newName;
	}

	const Color &State::getBackgroundColor() const {
		return camera.getBackgroundColor();
	}

	void State::setBackgroundColor(const Color &newBackgroundColor) {
		camera.setBackgroundColor(newBackgroundColor);
	}

	const Camera &State::getCamera() const {
		return camera;
	}

	void State::onGetFocus() {
	}

	void State::onLoseFocus() {
	}

	void State::internalUpdate() {
		this->BodyManager<Layerable, Layerable::LessCompare>::internalUpdate();

		if (camera.isEnabled() && camera.isActive()) {
			camera.update();
		}

		update();
	}

	void State::internalRender() {
		if (camera.isEnabled() && camera.isVisible()) {
			camera.render();
		}

		// We check if there are bodies to be rendered.
		if (!bodies.empty()) {
			BodyMap::iterator i = bodies.begin();
			// We get the first body's scroll factor.
			Vector2 lastScrollFactor = (*i)->getScrollFactor();
			// We apply the scroll factor.
			GraphicDriver::getInstance().pushMatrix();
			GraphicDriver::getInstance().translate(Vector2(-(1.0f - lastScrollFactor.getX()) * camera.getXPosition(),
			                                               -(1.0f - lastScrollFactor.getY()) * camera.getYPosition()));

			// For each body.
			while (i != bodies.end()) {
				// We make sure it is enabled and visible.
				if ((*i)->isEnabled() && (*i)->isVisible()) {
					// We check if it has a scroll factor different than the
					// one already in place.
					if (lastScrollFactor != (*i)->getScrollFactor()) {
						// We remove the old scroll factor apply the new scroll
						// factor.
						lastScrollFactor = (*i)->getScrollFactor();
						GraphicDriver::getInstance().popMatrix();
						GraphicDriver::getInstance().pushMatrix();
						GraphicDriver::getInstance().translate(Vector2(-(1.0f - lastScrollFactor.getX()) * camera.getXPosition(),
						                                               -(1.0f - lastScrollFactor.getY()) * camera.getYPosition()));
					}

					// We render the body.
					(*i)->render();
				}

				++i;
			}

			GraphicDriver::getInstance().popMatrix();
		}

		render();

		if (!(camera.isEnabled() && camera.isVisible())) {
			camera.render();
		}
	}

	void State::internalOnGetFocus() {
		activateSlots();
		onGetFocus();
	}

	void State::internalOnLoseFocus() {
		deactivateSlots();
		onLoseFocus();
	}
}
