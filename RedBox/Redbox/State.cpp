#include "State.h"

#include <cassert>

#include "Console.h"
#include "GraphicDriver.h"

using namespace RedBox;

const std::string State::DEFAULT_NAME = "State";

State::State(const std::string& newName) : Object(), sigly::HasSlots<>(),
name(newName) {
}

State::~State() {
	// We delete all the GraphicBodys from the list of GraphicBodys that need
	// to be deleted.
	for(std::list<GraphicBody*>::iterator i = toDelete.begin();
		i != toDelete.end();
		++i) {
		if(*i) {
			delete *i;
		}
	}
	// We delete the GraphicBodys that were waiting to be added.
	for(std::list<GraphicBody*>::iterator i = toAdd.begin(); i != toAdd.end();
		i++) {
		if(*i) {
			delete *i;
		}
	}

	// We delete the GraphicBodys.
	for(BodyMap::iterator i = graphicBodies.begin(); i != graphicBodies.end();
		++i) {
		if(i->second) {
			delete i->second;
		}
	}
}

void State::addGraphicBody(GraphicBody* aGraphicBody) {
	if(aGraphicBody) {
		if(!aGraphicBody->isInState) {
			toAdd.push_back(aGraphicBody);
		} else {
			Console::Print("Tried to add a GraphicBody that is already in a state.");
		}
	} else {
		Console::Print("Tried to add an invalid GraphicBody (" + Console::ToString(aGraphicBody) + ") to the state.");
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

void State::setBackgroundColor(const Color &newBackgroundColor) {
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
		Console::Print("Tried to add a GraphicBody that is already in a state.");
	}
}

void State::internalUpdate() {
	// We add the GraphicBodys to the multimap.
	for(std::list<GraphicBody*>::iterator i = toAdd.begin(); i != toAdd.end();
		i++) {
		addGraphicBodyDirect(*i);
	}
	toAdd.clear();
	// We loop through each of the GraphicBodys to update them.
	for(BodyMap::iterator i = graphicBodies.begin(); i != graphicBodies.end();
		i++) {
		// We check if the delete flag is on.
		if(i->second->isToBeDeleted()) {
			// We put the GraphicBody in the list of GraphicBodys to delete.
			toDelete.push_back(i->second);
			// We remove the GraphicBody from the multimap.
			graphicBodies.erase(i);
		} else {
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

	// We delete all the GraphicBodys from the list of GraphicBodys that need
	// to be deleted.
	for(std::list<GraphicBody*>::iterator i = toDelete.begin();
		i != toDelete.end();
		++i) {
		delete *i;
	}
	// We clear the list.
	toDelete.clear();

	// Put the GraphicBodys which have had their z changed back into the
	// multimap.
	for(std::list<GraphicBody*>::iterator i = layerChange.begin();
		i != layerChange.end();
		i++) {
		graphicBodies.insert(std::pair<Layer, GraphicBody*>((*i)->getLayer(), *i));
	}
	layerChange.clear();

	camera.update();
	update();
}

void State::internalRender() {
	camera.render();
	if(!graphicBodies.empty()) {
		Layer lastLayer = graphicBodies.begin()->first;
		GraphicDriver::pushMatrix();
		GraphicDriver::translate(Vec2(-(1.0f - graphicBodies.begin()->second->getLayer().getScrollFactor().getX()) * camera.getXPosition(),
									  -(1.0f - graphicBodies.begin()->second->getLayer().getScrollFactor().getY()) * camera.getYPosition()));
		for(BodyMap::iterator i = graphicBodies.begin();
			i != graphicBodies.end(); i++) {
			if(lastLayer != i->first) {
				GraphicDriver::popMatrix();
				GraphicDriver::pushMatrix();
				GraphicDriver::translate(Vec2(-(1.0f - i->second->getLayer().getScrollFactor().getX()) * camera.getXPosition(),
											  -(1.0f - i->second->getLayer().getScrollFactor().getY()) * camera.getYPosition()));
				lastLayer = i->first;
			}
			i->second->render();
		}
		GraphicDriver::popMatrix();
	}
	render();
}

void State::internalOnGetFocus() {
	activateSlots();
	onGetFocus();
}

void State::internalOnLoseFocus() {
	deactivateSlots();
	onLoseFocus();
}
