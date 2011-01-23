#include "State.h"

using namespace RedBox;

void State::addRenderable(Renderable* aRenderable){
    renderables.insert(pair<int, Renderable*>(aRenderable->getZ(), aRenderable));
}


void State::render(){
	//iterator to render every f***ing renderable
    for(std::multimap<int, Renderable*>::iterator i=renderables.begin(); i !=renderables.end();i++){
		i->second->render();
	}
}

void State::update(){
	
	std::multimap<int, Renderable*>::iterator i=renderables.begin();
    while(i !=renderables.end()){
		//check the delete flag of the rederables
		//IF TRUE Transfer the renderable from the map to the toDelete list
		if(i->second->isToBeDeleted()) {
			
			toDelete.push_back(i->second);
			//erase the current renderable from the map, also point the iterator to the next in the map
			i = renderables.erase(i);
		} else {
			
			i->second->update();
			if(i->second->isZChanged()){
				
				zChange.push_back(i->second);
				//erase the current renderable from the map, also point the iterator to the next in the map
				i = renderables.erase(i);
			} else {
				i++;
			}
		}
	}
	
	// delete all renderables which have to be
	for(std::list<Renderable*>::iterator it=toDelete.begin(); it !=toDelete.end();it++){
		delete it->second;
	}
	
	toDelete.clear();
	
	//Transfert the renderable from zChange list to the renderables map
	for(std::list<Renderable*>::iterator it=zChange.begin(); it !=zChange.end();it++){
		renderables.insert(pair<int, Renderable*>(it->second->getZ(), it->second));
	}
	zChange.clear();
}