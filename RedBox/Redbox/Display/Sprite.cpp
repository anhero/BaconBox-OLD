#include "Sprite.h"

#include "PlatformFlagger.h"

#include "TextureInfo.h"
#include "RenderStep.h"
#include "ResourceManager.h"
#include "Debug.h"
#include "VerticesGroup.h"

using namespace RedBox;


Sprite::Sprite(): Renderable() {
}


Sprite::Sprite(const std::string& imageKey): Renderable()
{
	TextureInfo* texInfo = ResourceManager::getTexture(imageKey);
	if(texInfo) {
		construct(texInfo,
				  texInfo->imageWidth,
				  texInfo->imageHeight,
				  1

		);
	} else {
		RB_ECHO("Tried to construct a sprite from an invalid image key: " << imageKey);
	}
}


Sprite::Sprite(TextureInfo* texInfo): Renderable()
{
	if(texInfo) {
		construct(texInfo,
				  texInfo->imageWidth,
				  texInfo->imageHeight,
				  1
		);
	} else {
		RB_ECHO("Tried to construct a sprite from an invalid texture information: " << texInfo);
	}
}

Sprite::Sprite(const std::string& imageKey,
			   unsigned int frameWidth,
			   unsigned int frameHeight,
			   unsigned int nbFrames
): Renderable()
{
	construct(ResourceManager::getTexture(imageKey),
			  frameWidth,
			  frameHeight,
			  nbFrames
	);
}

Sprite::Sprite(TextureInfo* texInfo,
			   unsigned int frameWidth,
			   unsigned int frameHeight,
			   unsigned int nbFrames
): Renderable()
{
	construct(texInfo,
			  frameWidth,
			  frameHeight,
			  nbFrames
	);
}


Sprite::Sprite(const Sprite& src): Renderable(src) {
	copyFrom(src);
}

Sprite::~Sprite() {
	clean();
}

Sprite& Sprite::operator=(const Sprite& src) {
	Renderable::operator=(src);
	copyFrom(src);
	return *this;
}

void Sprite::render() {
	// We render the render steps.
	for(std::list<RenderStep*>::iterator i = renderSteps.begin();
		i != renderSteps.end();
		i++) {
		if(*i) {
			(*i)->render();
		}
	}
}

void Sprite::update() {
	Renderable::update();
	// We update the render steps.
	for(std::list<RenderStep*>::iterator i = renderSteps.begin();
		i != renderSteps.end();
		i++) {
		if(*i) {
			(*i)->update();
		}
	}
}

void Sprite::createVertex(float x, float y) {
	vertices.addVertex(x, y);
}




void Sprite::setXPosition(float x) {
	Renderable::setXPosition(x);
	vertices.setXPosition(x);
}
void Sprite::setYPosition(float y) {
	Renderable::setYPosition(y);
	vertices.setYPosition(y);
}
void Sprite::setPosition(float x, float y) {
	Renderable::setPosition(x, y);
	vertices.setPosition(x, y);
}
void Sprite::moveX(float deltaX) {
	Renderable::moveX(deltaX);
	vertices.moveX(deltaX);
}
void Sprite::moveY(float deltaY) {
	Renderable::moveY(deltaY);
	vertices.moveY(deltaY);
}
void Sprite::move(float deltaX, float deltaY) {
	Renderable::move(deltaX, deltaY);
	vertices.move(deltaX, deltaY);
}

float Sprite::getWidth() const {
	return vertices.getWidth();
}

float Sprite::getHeight() const {
	return vertices.getHeight();
}

std::pair<float, float> Sprite::getWidthHeight() const {
	return vertices.getWidthHeight();
}


RenderStep* Sprite::addRenderStep(RenderStep* newRenderStep) {
	if(newRenderStep) {
		renderSteps.push_back(newRenderStep);
	} else {
		RB_ECHO("Tried to add an NULL RenderStep to a Sprite.");
	}
	return newRenderStep;
}

void Sprite::removeRenderStep(RenderStep* renderStep) {
	if(renderStep) {
		// We look for the RenderStep to remove.
		bool notFound = true;
		std::list<RenderStep*>::iterator i = renderSteps.begin();
		while(notFound && i != renderSteps.end()) {
			if(*i == renderStep) {
				notFound = false;
				// We erase the found RenderStep.
				renderSteps.erase(i);
			}
			++i;
		}
		// If it wasn't found, we warn the user.
		if(notFound) {
			RB_ECHO("Tried to remove a RenderStep from a Sprite which does not contain it: " << renderStep);
		}
	} else {
		RB_ECHO("Tried to remove a NULL RenderStep pointer from a sprite.");
	}
}

RenderStep* Sprite::getMainRenderStep() {
	if(renderSteps.empty()) {
		return NULL;
	} else {
		return renderSteps.front();
	}
}

RenderStep* Sprite::getRenderStep(unsigned int position) {
	if(renderSteps.empty() || renderSteps.size() <= position) {
		return NULL;
	} else {
		unsigned int currentPosition = 0;
		std::list<RenderStep*>::iterator i = renderSteps.begin();
		while(currentPosition <= position) {
			++i;
			++currentPosition;
		}
		return *i;
	}
}
std::list<RenderStep*>& Sprite::getRenderSteps() {
	return renderSteps;
}

void Sprite::setMainColor(const Color& color){
	RenderStep * mainRenderStep = getMainRenderStep();
	mainRenderStep->addMode(RenderStepMode::COLOR);
	mainRenderStep->setColor(color);
}
VerticesGroup& Sprite::getVertices() {
	return vertices;
}

void Sprite::construct(TextureInfo* texInfo,
					   unsigned int frameWidth,
					   unsigned int frameHeight,
					   unsigned int nbFrames
)
{
	if(texInfo) {
		// Generates the square vertices from the frame width and height.
		vertices.addVertices(4,
							 0.0f, 0.0f,
							 static_cast<float>(frameWidth), 0.0f,
							 static_cast<float>(frameWidth), static_cast<float>(frameHeight),
							 0.0f, static_cast<float>(frameHeight));

		RenderStep* initialRenderStep = new RenderStep(texInfo,
													   &vertices,
													   frameWidth,
													   frameHeight,
													   nbFrames);
		renderSteps.push_back(initialRenderStep);
	} else {
		RB_ECHO("Failed to load a sprite with the following texture information: " << texInfo);
	}
}

void Sprite::clean() {
	clearRenderSteps();
}

void Sprite::copyFrom(const Sprite& src) {
	if(this != &src && &src) {
		clean();
		vertices = src.vertices;
		renderSteps.push_front(new RenderStep(*src.renderSteps.front()));
		renderSteps.front()->setVerticesGroup(&vertices);
		renderSteps.front()->updateVerticesData();
	} else {
		clean();
	}
}

void Sprite::clearRenderSteps() {
	for(std::list<RenderStep*>::iterator i = renderSteps.begin();
		i != renderSteps.end();
		i++) {
		if(*i) {
			delete *i;
		}
	}
	renderSteps.clear();
}

int Sprite::getMinX(){
	return vertices.getXPosition();
}
int Sprite::getMaxX(){
	return vertices.getXPosition() + vertices.getWidth();
}
int Sprite::getMinY(){
	return vertices.getYPosition();
}
int Sprite::getMaxY(){
	return vertices.getYPosition() + vertices.getHeight();
}

RenderInfo* Sprite::getMainRenderInfo() {
	if(getMainRenderStep()) {
		return &getMainRenderStep()->getRenderInfo();
	} else {
		return NULL;
	}
}

void Sprite::addAnimation(const std::string& name,
							  double timePerFrame,
							  int nbLoops,
							  unsigned int nbFrames, ... ) {
	
	
	std::vector<unsigned int> framesVector(nbFrames);
	
	// We make sure it is trying to add an animation with at least one frame.
	if(nbFrames >= 1) {
		// We set the frame numbers to the added animation using the variable
		// parameters.
		va_list frames;
		va_start(frames, nbFrames);
		for(std::vector<unsigned int>::iterator i = framesVector.begin();
			i != framesVector.end();
			++i) {
			*i = va_arg(frames, unsigned int);
		}
		va_end(frames);
		
		getMainRenderInfo()->addAnimation(name, framesVector, timePerFrame, nbLoops);
	} else {
		RB_ECHO("Failed to add the animation named : " << name);
	}
}

void Sprite::playAnimation(const std::string& name) {
	getMainRenderStep()->playAnimation(name);
}
