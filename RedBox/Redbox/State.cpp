#include "State.h"

#include <cassert>
#include <algorithm>

#include "Console.h"
#include "GraphicDriver.h"
#include "DeleteHelper.h"

using namespace RedBox;

const std::string State::DEFAULT_NAME = "State";

State::State(const std::string& newName) : Object(), sigly::HasSlots<>(),
	name(newName) {
}

State::~State() {
	// We delete all the graphic bodies from the list of GraphicBodys that need
	// to be deleted.
	std::for_each(toDelete.begin(), toDelete.end(), DeletePointer());

	// We delete the graphic bodies that were waiting to be added.
	std::for_each(toAdd.begin(), toAdd.end(), DeletePointer());

	// We delete the graphic bodies.
	std::for_each(graphicBodies.begin(), graphicBodies.end(),
	              DeletePointerFromPair());
}

void State::addGraphicBody(GraphicBody* aGraphicBody) {
	if(aGraphicBody) {
		if(!aGraphicBody->isInState) {
			toAdd.push_front(aGraphicBody);
		} else {
			Console::print("Tried to add a GraphicBody that is already in a state.");
		}
	} else {
		Console::print("Tried to add an invalid GraphicBody (" + Console::toString(aGraphicBody) + ") to the state.");
	}
}


void State::render() {
}

void State::update() {
}

const std::string& State::getName() const {
	return name;
}

void State::setName(const std::string& newName) {
	name = newName;
}

void State::setBackgroundColor(const Color& newBackgroundColor) {
	camera.setBackgroundColor(newBackgroundColor);
}

const Color& State::getBackgroundColor() const {
	return camera.getBackgroundColor();
}

void State::onGetFocus() {
}

void State::onLoseFocus() {
}

void State::addGraphicBodyDirect(GraphicBody* aGraphicBody) {
	assert(aGraphicBody);

	if(!aGraphicBody->isInState) {
		aGraphicBody->resetLayerChanged();
		graphicBodies.insert(std::pair<Layer, GraphicBody*>(aGraphicBody->getLayer(),
		                     aGraphicBody));
		aGraphicBody->isInState = true;
	} else {
		Console::print("Tried to add a GraphicBody that is already in a state.");
	}
}

void State::internalUpdate() {
	// We add the graphic bodies to the multimap.
	std::for_each(toAdd.begin(), toAdd.end(), std::bind1st(std::mem_fun(&State::addGraphicBodyDirect), this));
	// We clear the temporary list of graphic bodies to add.
	toAdd.clear();

	// We update the graphic bodies.
	for(BodyMap::iterator i = graphicBodies.begin(); i != graphicBodies.end();
	        i++) {
		// We check if the delete flag is on.
		if(i->second->isToBeDeleted()) {
			// We put the GraphicBody in the list of GraphicBodys to delete.
			toDelete.push_back(i->second);
			// We remove the GraphicBody from the multimap.
			graphicBodies.erase(i);
		} else {
			if(i->second->isEnabled() && i->second->isActive()) {
				// We update the GraphicBody.
				i->second->update();

				// We check if the z value has changed.
				if(i->second->isLayerChanged()) {
					// If so, we put it at the right layer in the multimap.
					// To do that, we first put it in the list of GraphicBodys that
					// have had their z changed.
					layerChange.push_back(i->second);
					// We remove it from the multimap.
					graphicBodies.erase(i);
				}
			}
		}
	}

	// We delete all the graphic bodies from the list of GraphicBodys that need
	// to be deleted.
	std::for_each(toDelete.begin(), toDelete.end(), DeletePointer());
	// We clear the list.
	toDelete.clear();

	// Put the graphic bodies which have had their z changed back into the
	// multimap.
	for(std::list<GraphicBody*>::iterator i = layerChange.begin();
	        i != layerChange.end();
	        i++) {
		graphicBodies.insert(std::pair<Layer, GraphicBody*>((*i)->getLayer(), *i));
	}

	layerChange.clear();

	if(camera.isEnabled() && camera.isActive()) {
		camera.update();
	}
	update();
}

void State::internalRender() {
	if(camera.isEnabled() && camera.isVisible()) {
		camera.render();
	}

	if(!graphicBodies.empty()) {
		Layer lastLayer = graphicBodies.begin()->first;
		GraphicDriver::pushMatrix();
		GraphicDriver::translate(Vec2(-(1.0f - graphicBodies.begin()->second->getLayer().getScrollFactor().getX()) * camera.getXPosition(),
		                              -(1.0f - graphicBodies.begin()->second->getLayer().getScrollFactor().getY()) * camera.getYPosition()));

		for(BodyMap::iterator i = graphicBodies.begin();
		        i != graphicBodies.end(); i++) {
			if(i->second->isEnabled() && i->second->isVisible()) {
				if(lastLayer != i->first) {
					GraphicDriver::popMatrix();
					GraphicDriver::pushMatrix();
					GraphicDriver::translate(Vec2(-(1.0f - i->second->getLayer().getScrollFactor().getX()) * camera.getXPosition(),
					                              -(1.0f - i->second->getLayer().getScrollFactor().getY()) * camera.getYPosition()));
					lastLayer = i->first;
				}

				i->second->render();
			}
		}

		GraphicDriver::popMatrix();
	}

	render();

	if(!(camera.isEnabled() && camera.isVisible())) {
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
