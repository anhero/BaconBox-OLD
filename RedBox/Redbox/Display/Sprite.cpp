#include "Sprite.h"

#include "PlatformFlagger.h"

#include "TextureInfo.h"
#include "RenderStep.h"
#include "ResourceManager.h"
#include "Console.h"
#include "VerticesGroup.h"

using namespace RedBox;

Sprite::Sprite(): GraphicBody() {
}

Sprite::Sprite(const std::string& textureKey): GraphicBody() {
	TextureInfo* textureInfo = ResourceManager::getTexture(textureKey);

	if(textureInfo) {
		construct(textureInfo,
		          textureInfo->imageWidth,
		          textureInfo->imageHeight,
		          1);
	} else {
		Console::print("Tried to construct a sprite from an invalid image key: " + textureKey);
	}
}

Sprite::Sprite(TextureInfo* textureInfo): GraphicBody() {
	if(textureInfo) {
		construct(textureInfo,
		          textureInfo->imageWidth,
		          textureInfo->imageHeight,
		          1);
	} else {
		Console::print("Tried to construct a sprite from an invalid texture information: " + Console::toString(textureInfo));
	}
}

Sprite::Sprite(const std::string& textureKey,
               unsigned int frameWidth,
               unsigned int frameHeight,
               unsigned int nbFrames): GraphicBody() {
	construct(ResourceManager::getTexture(textureKey),
	          frameWidth,
	          frameHeight,
	          nbFrames);
}

Sprite::Sprite(TextureInfo* textureInfo,
               unsigned int frameWidth,
               unsigned int frameHeight,
               unsigned int nbFrames): GraphicBody() {
	construct(textureInfo,
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
	    i != renderSteps.end(); ++i) {
		if(*i) {
			(*i)->render();
		}
	}
}

void Sprite::mask() {
	for(std::list<RenderStep*>::iterator i = renderSteps.begin();
	    i != renderSteps.end(); ++i) {
		if(*i) {
			(*i)->mask();
		}
	}
}

void Sprite::unmask() {
	for(std::list<RenderStep*>::iterator i = renderSteps.begin();
	    i != renderSteps.end(); ++i) {
		if(*i) {
			(*i)->unmask();
		}
	}
}

void Sprite::update() {
	GraphicBody::update();

	// We update the render steps.
	for(std::list<RenderStep*>::iterator i = renderSteps.begin();
	    i != renderSteps.end(); ++i) {
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

void Sprite::setPosition(float newXPosition, float newYPosition) {
	GraphicBody::setPosition(newXPosition, newYPosition);
	vertices.setPosition(newXPosition, newYPosition);
}

const Vec2 Sprite::getSize() const {
	return vertices.getSize();
}

float Sprite::getWidth() const {
	return vertices.getWidth();
}

float Sprite::getHeight() const {
	return vertices.getHeight();
}

RenderStep* Sprite::addRenderStep(RenderStep* newRenderStep) {
	if(newRenderStep) {
		renderSteps.push_back(newRenderStep);
	} else {
		Console::print("Tried to add an NULL RenderStep to a Sprite.");
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
			Console::print("Tried to remove a RenderStep from a Sprite which does not contain it: " + Console::toString(renderStep));
		}
	} else {
		Console::print("Tried to remove a NULL RenderStep pointer from a sprite.");
	}
}

RenderStep* Sprite::getMainRenderStep() {
	if(renderSteps.empty()) {
		Console::print("Tried to get the main render step of a sprite that doesn't have any render steps, returning NULL.");
		Console::printTrace();
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

	if(mainRenderStep) {
		mainRenderStep->addMode(RenderStepMode::COLOR);
		mainRenderStep->setColor(color);
	} else {
		Console::print("Tried to set the color of a sprite that has no render steps.");
		Console::printTrace();
	}
}
VerticesGroup& Sprite::getVertices() {
	return vertices;
}

void Sprite::construct(TextureInfo* texInfo,
                       unsigned int frameWidth,
                       unsigned int frameHeight,
                       unsigned int nbFrames) {
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
		Console::print("Failed to load a sprite with the following texture information: " + Console::toString(texInfo));
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
	if(renderSteps.empty()) {
		Console::print("Tried to get the main render information of a sprite that doesn't have a main render step, returning NULL.");
		Console::printTrace();
		return NULL;
	} else {
		return &getMainRenderStep()->getRenderInfo();
	}
}

void Sprite::playAnimation(const std::string& name) {
	if(renderSteps.empty()) {
		Console::print("Tried to play an animation on a sprite that doesn't have any main render step.");
		Console::printTrace();
	} else {
		getMainRenderStep()->playAnimation(name);
	}
}

void Sprite::addAnimation(const std::string& name,
                          double timePerFrame,
                          int nbLoops,
                          unsigned int nbFrames, ...) {
	// We make sure there is a main render step.
	if(renderSteps.empty()) {
		Console::print("Tried to add an animation to a sprite that doesn't have a main render step.");
		Console::printTrace();
	} else {
		std::vector<unsigned int> framesVector(nbFrames);

		// We make sure it is trying to add an animation with at least one frame.
		if(nbFrames >= 1) {
			// We set the frame numbers to the added animation using the variable
			// parameters.
			va_list frames;
			va_start(frames, nbFrames);

			// We read the animation's frame indexes.
			for(std::vector<unsigned int>::iterator i = framesVector.begin();
			    i != framesVector.end();
			    ++i) {
				*i = va_arg(frames, unsigned int);
			}

			va_end(frames);

			getMainRenderInfo()->addAnimation(name, framesVector, timePerFrame, nbLoops);
		} else {
			Console::print("Failed to add the animation named \"" + name + "\" because it specified that it had 0 frames.");
			Console::printTrace();
		}
	}
}

void Sprite::setScaling(float xScaling, float yScaling) {
	if(xScaling && yScaling) {
		vertices.scale(Vec2(xScaling / getXScaling(), yScaling / getYScaling()));
		GraphicBody::setScaling(xScaling, yScaling);
		Vec2 tmp = vertices.getPosition();
		GraphicBody::setPosition(tmp.getX(), tmp.getY());
	} else {
		Console::print("Tried to set a scaling of 0 to a sprite.");
	}
}

void Sprite::setAngle(float newAngle) {
	if(newAngle != getAngle()) {
		vertices.rotate(newAngle - getAngle());
		GraphicBody::setAngle(newAngle);
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
		renderSteps.push_front(new RenderStep(*src.renderSteps.front()));
		renderSteps.front()->setVerticesGroup(&vertices);
		renderSteps.front()->updateVerticesData();
	} else {
		clean();
	}
}

void Sprite::clearRenderSteps() {
	for(std::list<RenderStep*>::iterator i = renderSteps.begin();
	    i != renderSteps.end(); ++i) {
		if(*i) {
			delete *i;
		}
	}

	renderSteps.clear();
}

Color Sprite::getMainColor() {
	RenderStep* mainRenderStep = getMainRenderStep();
	return mainRenderStep->getRenderInfo().getColor();
}

void Sprite::setMainAlpha(int alpha) {
	Color mainColor = getMainColor();
	setMainColor(Color(mainColor.getRed(), mainColor.getGreen(), mainColor.getBlue(), alpha));
}


void Sprite::setMask(Sprite* aMask, bool inversed) {
	if(aMask != NULL) {
		for(std::list<RenderStep*>::iterator i = renderSteps.begin();
		    i != renderSteps.end(); ++i) {
			if(*i) {
				(*i)->setMask(aMask);

				if(inversed) {
					(*i)->addMode(RenderStepMode::INVERSE_MASKED);

				} else {
					(*i)->addMode(RenderStepMode::MASKED);

				}
			}
		}
	}
}

GraphicBody* Sprite::clone() const {
	return new Sprite(*this);
}



	//void Sprite::setTexture(TextureInfo * aTextureInfo){
	//	getMainRenderInfo()->loadTexCoords(&vertices, aTextureInfo->imageWidth, aTextureInfo->imageHeight, 1, aTextureInfo);
	//}
	//void Sprite::setTexture(std::string key){
	//	setTexture(ResourceManager::getTexture(key));
	//}
