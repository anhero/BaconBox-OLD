#include "Sprite.h"

#include "PlatformFlagger.h"

#include <cfloat>

#include "TextureInfo.h"
#include "RenderStep.h"
#include "ResourceManager.h"
#include "Console.h"
#include "VerticesGroup.h"

using namespace RedBox;

Sprite::Sprite(): GraphicBody() {
}


Sprite::Sprite(const std::string& imageKey): GraphicBody(),
	scaling(Vec2(1.0f, 1.0f)), angle(0.0f) {
	TextureInfo* texInfo = ResourceManager::getTexture(imageKey);

	if(texInfo) {
		construct(texInfo,
		          texInfo->imageWidth,
		          texInfo->imageHeight,
		          1);
	} else {
		Console::Print("Tried to construct a sprite from an invalid image key: " + imageKey);
	}
}

Sprite::Sprite(TextureInfo* texInfo): GraphicBody(), scaling(Vec2(1.0f, 1.0f)),
	angle(0.0f) {
	if(texInfo) {
		construct(texInfo,
		          texInfo->imageWidth,
		          texInfo->imageHeight,
		          1);
	} else {
		Console::Print("Tried to construct a sprite from an invalid texture information: " + Console::ToString(texInfo));
	}
}

Sprite::Sprite(const std::string& imageKey,
               unsigned int frameWidth,
               unsigned int frameHeight,
               unsigned int nbFrames
              ): GraphicBody(), scaling(Vec2(1.0f, 1.0f)), angle(0.0f) {
	construct(ResourceManager::getTexture(imageKey),
	          frameWidth,
	          frameHeight,
	          nbFrames);
}

Sprite::Sprite(TextureInfo* texInfo,
               unsigned int frameWidth,
               unsigned int frameHeight,
               unsigned int nbFrames
              ): GraphicBody(), scaling(Vec2(1.0f, 1.0f)), angle(0.0f) {
	construct(texInfo,
	          frameWidth,
	          frameHeight,
	          nbFrames);
}


Sprite::Sprite(const Sprite& src): GraphicBody(src) {
	copyFrom(src);
}

Sprite::~Sprite() {
	clean();
}

Sprite& Sprite::operator=(const Sprite& src) {
	GraphicBody::operator=(src);
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
	GraphicBody::update();

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

Vec2 Sprite::getPositionCenter() const {
	return Vec2(getXPosition() + getWidth() * 0.5f,
	            getYPosition() + getHeight() * 0.5f);
}

float Sprite::getXPositionCenter() const {
	return getXPosition() + getWidth() * 0.5f;
}

float Sprite::getYPositionCenter() const {
	return getYPosition() + getHeight() * 0.5f;
}

void Sprite::setXPosition(float x) {
	GraphicBody::setXPosition(x);
	vertices.setXPosition(x);
}
void Sprite::setYPosition(float y) {
	GraphicBody::setYPosition(y);
	vertices.setYPosition(y);
}
void Sprite::setPosition(float x, float y) {
	GraphicBody::setPosition(x, y);
	vertices.setPosition(x, y);
}
void Sprite::moveX(float deltaX) {
	GraphicBody::moveX(deltaX);
	vertices.moveX(deltaX);
}
void Sprite::moveY(float deltaY) {
	GraphicBody::moveY(deltaY);
	vertices.moveY(deltaY);
}
void Sprite::move(float deltaX, float deltaY) {
	GraphicBody::move(deltaX, deltaY);
	vertices.move(deltaX, deltaY);
}

float Sprite::getWidth() const {
	return vertices.getWidth();
}

float Sprite::getHeight() const {
	return vertices.getHeight();
}

Vec2 Sprite::getWidthHeight() const {
	return vertices.getWidthHeight();
}

RenderStep* Sprite::addRenderStep(RenderStep* newRenderStep) {
	if(newRenderStep) {
		renderSteps.push_back(newRenderStep);
	} else {
		Console::Print("Tried to add an NULL RenderStep to a Sprite.");
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
			Console::Print("Tried to remove a RenderStep from a Sprite which does not contain it: " + Console::ToString(renderStep));
		}
	} else {
		Console::Print("Tried to remove a NULL RenderStep pointer from a sprite.");
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

void Sprite::setMainColor(const Color& color) {
	RenderStep* mainRenderStep = getMainRenderStep();
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
                      ) {
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
		Console::Print("Failed to load a sprite with the following texture information: " + Console::ToString(texInfo));
	}
}

float Sprite::getMinX() const {
	return vertices.getXPosition();
}

float Sprite::getMaxX() const {
	return vertices.getXPosition() + vertices.getWidth();
}

float Sprite::getMinY() const {
	return vertices.getYPosition();
}

float Sprite::getMaxY() const {
	return vertices.getYPosition() + vertices.getHeight();
}

RenderInfo* Sprite::getMainRenderInfo() {
	if(getMainRenderStep()) {
		return &getMainRenderStep()->getRenderInfo();
	} else {
		return NULL;
	}
}

void Sprite::playAnimation(const std::string& name) {
	getMainRenderStep()->playAnimation(name);
}

void Sprite::addAnimation(const std::string& name,
                          double timePerFrame,
                          int nbLoops,
                          unsigned int nbFrames, ...) {


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
		Console::Print("Failed to add the animation named : " + name);
	}
}

void Sprite::setScaling(const Vec2& newScaling) {
	setScaling(newScaling.getX(), newScaling.getY());
}

void Sprite::setScaling(float xScaling, float yScaling) {
	if(xScaling && yScaling) {
		vertices.scale(Vec2(xScaling / scaling.getX(), yScaling / scaling.getY()));
		scaling = Vec2(xScaling, yScaling);
		Vec2 tmp = vertices.getPosition();
		GraphicBody::setPosition(tmp.getX(), tmp.getY());
	} else {
		Console::Print("Tried to set a scaling of 0 to a sprite.");
	}
}

void Sprite::addToScaling(Vec2 scalingToAdd) {
	if(scalingToAdd.getX() + scaling.getX() == 0.0f) {
		if(scalingToAdd.getX() > 0.0f) {
			scalingToAdd.addToX(FLT_MIN);
		} else if(scalingToAdd.getX() < 0.0f) {
			scalingToAdd.addToX(-FLT_MIN);
		}
	}

	if(scalingToAdd.getY() + scaling.getY() == 0.0f) {
		if(scalingToAdd.getY() > 0.0f) {
			scalingToAdd.addToY(FLT_MIN);
		} else if(scalingToAdd.getY() < 0.0f) {
			scalingToAdd.addToY(-FLT_MIN);
		}
	}

	vertices.scale(Vec2((scaling.getX() + scalingToAdd.getX()) / scaling.getX(),
	                    (scaling.getY() + scalingToAdd.getY()) / scaling.getY()));
}

void Sprite::addToScaling(float xScaling, float yScaling) {
	if(xScaling || yScaling) {
		if(xScaling + scaling.getX() == 0.0f) {
			if(xScaling > 0.0f) {
				xScaling += FLT_MIN;
			} else if(xScaling < 0.0f) {
				xScaling -= FLT_MIN;
			}
		}

		if(yScaling + scaling.getY() == 0.0f) {
			if(yScaling > 0.0f) {
				yScaling += FLT_MIN;
			} else if(yScaling < 0.0f) {
				yScaling -= FLT_MIN;
			}
		}

		vertices.scale(Vec2((scaling.getX() + xScaling) / scaling.getX(),
		                    (scaling.getY() + yScaling) / scaling.getY()));
	}
}

void Sprite::setXScaling(float newXScaling) {
	setScaling(newXScaling, scaling.getY());
}

void Sprite::setYScaling(float newYScaling) {
	setScaling(scaling.getX(), newYScaling);
}

const Vec2& Sprite::getScaling() const {
	return scaling;
}

float Sprite::getXScaling() const {
	return scaling.getX();
}

float Sprite::getYScaling() const {
	return scaling.getY();
}

float Sprite::getAngle() const {
	return angle;
}

void Sprite::setAngle(float newAngle) {
	if(newAngle != angle) {
		vertices.rotate(-angle);
		angle = newAngle;
		vertices.rotate(angle);
		Vec2 tmp = vertices.getPosition();
		GraphicBody::setPosition(tmp.getX(), tmp.getY());
	}
}

void Sprite::addToAngle(float angleToAdd) {
	if(angleToAdd) {
		if(angleToAdd < 0.0f) {
			angleToAdd += 360.0f;
		} else if(angleToAdd > 360.0f) {
			angleToAdd -= 360.0f;
		}

		angle += angleToAdd;

		if(angle < 0.0f) {
			angle += 360.0f;
		} else if(angle > 360.0f) {
			angle -= 360.0f;
		}

		vertices.rotate(angleToAdd);
		Vec2 tmp = vertices.getPosition();
		GraphicBody::setPosition(tmp.getX(), tmp.getY());
	}
}

void Sprite::clean() {
	clearRenderSteps();
}

void Sprite::copyFrom(const Sprite& src) {
	if(this != &src && &src) {
		clean();
		vertices = src.vertices;
		scaling = src.scaling;
		angle = src.angle;
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

