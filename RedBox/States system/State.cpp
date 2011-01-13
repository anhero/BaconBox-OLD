
#include "State.h"
using namespace RedBox;

State::State(): quakeness(0.0), quakedecay(0.0), theCamera(NULL), 
bgMusic(NULL) {
	//TODO: Initialize finch where it should be initialized
#ifdef __APPLE__
#if defined(TARGET_IPHONE_SIMULATOR) || defined(TARGET_OS_IPHONE)
	[[Finch alloc] init];
	//TODO: Place in a config file or something
	[UIApplication  sharedApplication].idleTimerDisabled = YES;
#endif //Target iPhone
#endif //__APPLE__
	theCamera = new Camera(SCREEN_WIDTH, SCREEN_HEIGHT, landscapeLeft); //Magic number!!!! TODO: Change it!

	initialized = false;
	
}

State::~State() {
	if(theCamera) delete theCamera;

	for(std::list<GraphicObject*>::iterator i = graphicObjects.begin(); i != graphicObjects.end(); i++) {
		if(*i) delete *i;
	}
	for(std::list<HudElement*>::iterator i = hudGraphicObjects.begin(); i != hudGraphicObjects.end(); i++) {
		if(*i) delete *i;
	}
	for(std::list<SpriteEmitter*>::iterator i = spriteEmitters.begin(); i != spriteEmitters.end(); i++) {
		if(*i) delete *i;
	}
	for (std::list<GraphicString*>::iterator i = uiStringObjects.begin(); i != uiStringObjects.end(); i++) {
		if(*i) delete *i;
	}
	for(std::map<std::string, SoundFX*>::iterator i = soundEffects.begin(); i != soundEffects.end(); i++) {
		delete i->second;
		//i->second = NULL;
	}
	
	if(bgMusic) {
		bgMusic->stop();
		delete bgMusic;
	}
}
//add a Graphic object in  the hud list
HudElement* State::addHudGraphicObject(HudElement *aGraphicObject, bool useDefaultZ){
	if (aGraphicObject) {
		if (aGraphicObject->getTouchSound() != "" && aGraphicObject->getTouchSoundPath() != "") {
			registerSoundEffect(aGraphicObject->getTouchSound(), aGraphicObject->getTouchSoundPath());
		}
		hudGraphicObjects.push_back(aGraphicObject);
		//hudGraphicObjects->AddNode(aGraphicObject);
		if(useDefaultZ)
			aGraphicObject->setZ(State::HUD_Z);
		renderables[aGraphicObject->getZ()].push_back(aGraphicObject);
		aGraphicObject->setParentState(this);
	}
	return aGraphicObject;
}

GraphicString* State::addGraphicString(GraphicString *aGraphicString, bool useDefaultZ) {
	uiStringObjects.push_back(aGraphicString);
	if(useDefaultZ)
		aGraphicString->setZ(State::HUD_Z);
	renderables[aGraphicString->getZ()].push_back(aGraphicString);
	return aGraphicString;
}



// Add a Graphic object in  the passive sprites list
GraphicObject* State::addGraphicObject(GraphicObject *aGraphicObject, bool useDefaultZ){
	if (aGraphicObject) {
		// We add the graphic object to the list.
		graphicObjects.push_back(aGraphicObject);
		// If we are asked to use the default Z, we do so.
		if(useDefaultZ)
			aGraphicObject->setZ(State::DEFAULT_Z);
		// We add the graphic object to the renderables using his Z.
		renderables[aGraphicObject->getZ()].push_back(aGraphicObject);
	}
	// We return the graphic object returned.
	return aGraphicObject;
}

void State::addSpriteEmitter(SpriteEmitter* aSpriteEmitter, bool useDefaultZ) {
	//spriteEmitters->AddNode(aSpriteEmitter);
	if (aSpriteEmitter) {
		spriteEmitters.push_back(aSpriteEmitter);
		if(useDefaultZ)
			aSpriteEmitter->setZ(State::DEFAULT_SPRITEEMITTER_Z);
		renderables[aSpriteEmitter->getZ()].push_back(aSpriteEmitter);
	}
}

void State::removeRenderable(Renderable* toRemove) {
	// We make sure the renderable pointer is valid.
	if(toRemove) {
		// We remove all the elements in the list that are the pointer to remove.
		renderables[toRemove->getZ()].remove(toRemove);
	}
}

void State::updateQuake() {
	// If there is screenshaking to do.
	if (quakeness > 0.0) {
		// We set random offsets to the camera.
		theCamera->setOffsetX(Random::getRandomInteger(static_cast<int>(quakeness) * -1, static_cast<int>(quakeness)));
		theCamera->setOffsetY(Random::getRandomInteger(static_cast<int>(quakeness) * -1, static_cast<int>(quakeness)));
		// We reduce the screen shaking force.
		quakeness -= State::QUAKE_DT * quakedecay;
	} else if (quakeness < 0.0) {
		// We reset the offset.
		theCamera->setOffsetX(0.0);
		theCamera->setOffsetY(0.0);
	}
}

void State::update() {
	// update the screenshaking.
	updateQuake();
	
	/*GraphicObject * aGraphicObject;
	 
	 graphicObjects->Rewind();
	 while (!graphicObjects->End()) {
	 aGraphicObject = graphicObjects->GetCurrentContent();
	 if (aGraphicObject->isAlive()) {
	 aGraphicObject->update();
	 }
	 else {
	 removeRenderable(aGraphicObject);
	 graphicObjects->RemoveCurrent();
	 }
	 graphicObjects->Next();
	 
	 }*/

	// We update the graphic objects.
	for (std::list<GraphicObject*>::iterator i = graphicObjects.begin(); i != graphicObjects.end(); /* We increment in the loop, not here... */) {
		
		// We check if the graphic object is alive and if its openGLDrawer is constructed.
		if ((*i)->isAlive() && (*i)->isConstructed()) {
			// We update the graphic object.
			(*i)->update();
			// We increment the iterator.
			i++;
		} else {
			// We remove the graphic object from the rendering list.
			removeRenderable(*i);
			// We delete the graphic object.
			delete *i;
			// We remove the graphic object from the graphic object list.
			i = graphicObjects.erase(i);
		}
	}
	
	/*spriteEmitters->Rewind();
	while(!spriteEmitters->End()) {
		spriteEmitters->GetCurrentContent()->update();
		if(spriteEmitters->GetCurrentContent()->isDone()) {
			removeRenderable(spriteEmitters->GetCurrentContent());
			spriteEmitters->RemoveCurrent();
			if(!spriteEmitters->End()) spriteEmitters->Next();
		} else {
			spriteEmitters->Next();
		}
	}*/
	// We update the sprite emitter.
	for (std::list<SpriteEmitter*>::iterator i = spriteEmitters.begin(); i != spriteEmitters.end(); /* We increment in the loop, not here... */) {
		
		// We check if the sprite emitter is alive and if its openGLDrawer is constructed.
		if ((*i)->isDone()) {
			// We remove the sprite emitter from the rendering list.
			removeRenderable(*i);
			// We delete the sprite emitter.
			delete *i;
			// We remove the sprite emitter from the graphic object list.
			i = spriteEmitters.erase(i);
		} else {
			// We update the sprite emitter.
			(*i)->update();
			// We increment the iterator.
			i++;
		}
	}
	
	// We update the HUD graphic objects.
	for (std::list<HudElement*>::iterator i = hudGraphicObjects.begin(); i != hudGraphicObjects.end(); /* We increment in the loop, not here... */) {
		
		// We check if the graphic object is alive and if its openGLDrawer is constructed.
		if ((*i)->isAlive()) {
			// We update the graphic object.
			(*i)->update();
			// We increment the iterator.
			i++;
		} else {
			// We remove the graphic object from the rendering list.
			removeRenderable(*i);
			// We delete the graphic object.
			delete *i;
			// We remove the graphic object from the graphic object list.
			i = hudGraphicObjects.erase(i);
		}
	}
}

void State::render() {
	theCamera->render();
	std::list<Renderable*>::iterator j;
	for(std::map<int, std::list<Renderable*> >::iterator i = renderables.begin(); i != renderables.end(); i++) {
		for (j = i->second.begin(); j != i->second.end(); j++) {
			if(theCamera->isInViewport(*j)) (*j)->render();
		}
	}
	/*graphicObjectsRender();
	 spriteEmitters->Rewind();
	 while(!spriteEmitters->End()) {
	 if(theCamera->isInViewport(spriteEmitters->GetCurrentContent())) {
	 spriteEmitters->GetCurrentContent()->render();
	 }
	 spriteEmitters->Next();
	 }
	 hudRender();
	 
	 uiStringObjects->Rewind();
	 while(!uiStringObjects->End()) {
	 uiStringObjects->GetCurrentContent()->render();
	 uiStringObjects->Next();
	 }*/
}

void State::initializeState() {
	for (std::list<GraphicObject*>::iterator i = graphicObjects.begin(); i != graphicObjects.end(); i++) {
		(*i)->initDrawer();
	}
	for (std::list<HudElement*>::iterator i = hudGraphicObjects.begin(); i != hudGraphicObjects.end(); i++) {
		(*i)->initDrawer();
	}
	for (std::list<SpriteEmitter*>::iterator i = spriteEmitters.begin(); i != spriteEmitters.end(); i++) {
		(*i)->initDrawer();
	}
	initialized = true;
}

bool State::isInitialized(){
	return initialized;
}
std::string State::getName(){
	return name;
}

State * State::getCurrentState(){
	return RedBoxEngine::getCurrentState();
}
void State::registerSoundEffect(const std::string& name, const std::string& path) {
	if(soundEffects[name]) delete soundEffects[name];
	soundEffects[name] = new SoundFX(RESOURCE_PATH_FOR(path), 5);
}
void State::playSoundEffect(const std::string& name) {
	if(soundEffects[name]) soundEffects[name]->play();
}

bool State::isSoundRegistered(const std::string& name) const {
	return soundEffects.find(name) != soundEffects.end();
}

bool State::touchesBegan(NSSet * touches){
	UITouch * touch = [touches anyObject];
	CGPoint location = [touch locationInView: [touch view]];
	
	Position touchPosition = theCamera->screenToWorldCoordinate(location.x, location.y);
	
	bool touchHitAnObject = false;
	//int hudElementsCount = hudGraphicObjects.size();
	//HudElement ** hudElements = hudGraphicObjects->GetArrayRepresentation();
	
	for (std::list<HudElement*>::iterator i = hudGraphicObjects.begin(); i != hudGraphicObjects.end() && !touchHitAnObject; i++) {
		HudElement* aGraphicObject = *i;
		BoundingBox bound = aGraphicObject->getBound();
		if(bound.positionInBound(touchPosition.x, touchPosition.y))
		{
			touchHitAnObject = true;
			aGraphicObject->touchBegan();
			playSoundEffect(aGraphicObject->getTouchSound());
			return true;
		}

	}
	return false;
	/*for (int i =0; i < hudElementsCount && !touchHitAnObject; i++) {
		HudElement * aGraphicObject = hudElements[i];
		BoundingBox bound = aGraphicObject->getBound();
		if(bound.positionInBound(touchPosition.x, touchPosition.y))
		{
			touchHitAnObject = true;
			aGraphicObject->touchBegan();
			playSoundEffect(aGraphicObject->getTouchSound());
		   return;

		}
	}*/
}

bool State::touchesEnded(NSSet * touches){
	UITouch * touch = [touches anyObject];
	CGPoint location = [touch locationInView: [touch view]];
	
	Position touchPosition = theCamera->screenToWorldCoordinate(location.x, location.y);
	
	bool touchHitAnObject = false;
	//int hudElementsCount = hudGraphicObjects->GetCount();
	//HudElement ** hudElements = hudGraphicObjects->GetArrayRepresentation();
	
	for (std::list<HudElement*>::iterator i = hudGraphicObjects.begin(); i != hudGraphicObjects.end() && !touchHitAnObject; i++) {
		HudElement* aGraphicObject = *i;
		BoundingBox bound = aGraphicObject->getBound();
		if(bound.positionInBound(touchPosition.x, touchPosition.y))
		{
			touchHitAnObject = true;
			aGraphicObject->touchEnded();
			return true;
		}
	}
	return false;
	/*for (int i =0; i < hudElementsCount && !touchHitAnObject; i++) {
		HudElement * aGraphicObject = hudElements[i];
		BoundingBox bound = aGraphicObject->getBound();
		if(bound.positionInBound(touchPosition.x, touchPosition.y))
		{
			touchHitAnObject = true;
			aGraphicObject->touchEnded();
		   return;
		}
	}*/
}
int State::getScreenWidth() {
	return theCamera->getScreenWidth();
}
int State::getScreenHeight() {
	return theCamera->getScreenHeight();
}
void State::startQuake(double quakeness, double quakedecay) {
	if (quakeness > this->quakeness) {
		this->quakeness = quakeness;
		this->quakedecay = quakedecay;
	}
}

void State::stopQuake() {
	quakeness = 0.0;
	quakedecay = 0.0;
	theCamera->setOffsetX(0.0);
	theCamera->setOffsetY(0.0);
}

void State::setBgMusic(const std::string& bgMusicPath) {
	if (bgMusic) {
		bgMusic->stop();
		delete bgMusic;
		bgMusic = NULL;
	}
	bgMusic = new BackgroundMusic(RESOURCE_PATH_FOR(bgMusicPath));
}
void State::stopMusic() {
	if(bgMusic) {
		bgMusic->stop();
	}
}
void State::startMusic() {
	if(bgMusic) {
		bgMusic->playInLoop();
	}
}

void State::pauseMusic()  {
	if(bgMusic) {
		bgMusic->pause();
	}
}

void State::setIphoneOrientation(IPhoneOrientationEnum orientation) {
	theCamera->setIphoneOrientation(orientation);
}

void State::resumeMusic() {
	if (bgMusic) {
		bgMusic->resume();
	}
}

IPhoneOrientationEnum State::getIphoneOrientation(){
	return theCamera->getIphoneOrientation();
}