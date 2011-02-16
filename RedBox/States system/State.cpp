#include "State.h"

#include "Debug.h"

using namespace RedBox;

State::State() {
}

void State::addRenderable(Renderable* aRenderable) {
	if(aRenderable) {
		aRenderable->resetZChanged();
		renderables.insert(std::pair<int, Renderable*>(aRenderable->getZ(), aRenderable));
	} else {
		$ECHO("Tried to add an invalid renderable (" << aRenderable << ") to the state.");
	}
}


void State::render() {
	camera.render();
	
    for(std::multimap<int, Renderable*>::iterator i=renderables.begin();
		i !=renderables.end();
		i++) {
		i->second->render();
	}
}

void State::update() {
	// We loop through each of the renderables to update them.
	for(std::multimap<int, Renderable*>::iterator i = renderables.begin();
		i != renderables.end();
		i++) {
		// We check if the delete flag is on.
		if(i->second->isToBeDeleted()) {
			// We put the renderable in the list of renderables to delete.
			toDelete.push_back(i->second);
			// We remove the renderable from the multimap.
			renderables.erase(i);
		} else {
			// We update the renderable.
			i->second->update();
			// We check if the z value has changed.
			if(i->second->isZChanged()) {
				// If so, we put it at the right z value in the multimap.
				// To do that, we first put it in the list of renderables that
				// have had their z changed.
				zChange.push_back(i->second);
				// We remove it from the multimap.
				renderables.erase(i);
			}
		}
	}
	
	// We delete all the renderables from the list of renderables that need
	// to be deleted.
	for(std::list<Renderable*>::iterator it=toDelete.begin();
		it !=toDelete.end();
		it++) {
		delete *it;
	}
	// We clear the list.
	toDelete.clear();
	
	// Put the renderables which have had their z changed back into the
	// multimap.
	for(std::list<Renderable*>::iterator it=zChange.begin();
		it !=zChange.end();
		it++) {
		renderables.insert(std::pair<int, Renderable*>((*it)->getZ(), *it));
	}
	zChange.clear();
}

const std::string& State::getName() const {
	return name;
}

void State::setName(const std::string& newName) {
	name = newName;
}