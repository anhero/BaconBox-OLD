#include "State.h"

#include <cassert>

#include "Debug.h"

using namespace RedBox;

State::State() : sigly::HasSlots<>() {
}

State::~State() {
	// We delete all the GraphicBodys from the list of GraphicBodys that need
	// to be deleted.
	for(std::list<GraphicBody*>::iterator i = toDelete.begin();
		i !=toDelete.end();
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
	for(std::multimap<int, GraphicBody*>::iterator i = GraphicBodys.begin();
		i != GraphicBodys.end(); ++i) {
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
			RB_ECHO("Tried to add a GraphicBody that is already in a state.");
		}
	} else {
		RB_ECHO("Tried to add an invalid GraphicBody (" << aGraphicBody << ") to the state.");
	}
}


void State::render() {
	camera.render();
	
    for(std::multimap<int, GraphicBody*>::iterator i=GraphicBodys.begin();
		i !=GraphicBodys.end();
		i++) {
		i->second->render();
	}
}

void State::update() {
	// We add the GraphicBodys to the multimap.
	for(std::list<GraphicBody*>::iterator i = toAdd.begin(); i != toAdd.end();
		i++) {
		addGraphicBodyDirect(*i);
	}
	toAdd.clear();
	// We loop through each of the GraphicBodys to update them.
	for(std::multimap<int, GraphicBody*>::iterator i = GraphicBodys.begin();
		i != GraphicBodys.end();
		i++) {
		// We check if the delete flag is on.
		if(i->second->isToBeDeleted()) {
			// We put the GraphicBody in the list of GraphicBodys to delete.
			toDelete.push_back(i->second);
			// We remove the GraphicBody from the multimap.
			GraphicBodys.erase(i);
		} else {
			// We update the GraphicBody.
			i->second->update();
			// We check if the z value has changed.
			if(i->second->isZChanged()) {
				// If so, we put it at the right z value in the multimap.
				// To do that, we first put it in the list of GraphicBodys that
				// have had their z changed.
				zChange.push_back(i->second);
				// We remove it from the multimap.
				GraphicBodys.erase(i);
			}
		}
	}
	
	// We delete all the GraphicBodys from the list of GraphicBodys that need
	// to be deleted.
	for(std::list<GraphicBody*>::iterator it=toDelete.begin();
		it !=toDelete.end();
		it++) {
		delete *it;
	}
	// We clear the list.
	toDelete.clear();
	
	// Put the GraphicBodys which have had their z changed back into the
	// multimap.
	for(std::list<GraphicBody*>::iterator it=zChange.begin();
		it !=zChange.end();
		it++) {
		GraphicBodys.insert(std::pair<int, GraphicBody*>((*it)->getZ(), *it));
	}
	zChange.clear();

	camera.update();
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
	activateSlots();
}

void State::onLoseFocus() {
	deactivateSlots();
}

void State::addGraphicBodyDirect(GraphicBody* aGraphicBody) {
	assert(aGraphicBody);
	if(!aGraphicBody->isInState) {
		aGraphicBody->resetZChanged();
		GraphicBodys.insert(std::pair<int, GraphicBody*>(aGraphicBody->getZ(),
													   aGraphicBody));
		aGraphicBody->isInState = true;
	} else {
		RB_ECHO("Tried to add a GraphicBody that is already in a state.");
	}
}
