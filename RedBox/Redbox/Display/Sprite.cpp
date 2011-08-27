#include "Sprite.h"

#include <cassert>

#include "TextureInfo.h"
#include "ResourceManager.h"
#include "Console.h"
#include "TextureInfo.h"
#include "AnimationParameters.h"
#include "Engine.h"
#include "GraphicDriver.h"

using namespace RedBox;

Sprite::Sprite(): GraphicBody(), vertices(), renderInfo(), renderModes(),
	animationPaused(false), animationCounter(0.0) {
}

Sprite::Sprite(const std::string& textureKey) : GraphicBody(), vertices(),
	renderInfo(), renderModes(), animationPaused(false), animationCounter(0.0) {
	TextureInfo* textureInfo = ResourceManager::getTexture(textureKey);

	if(textureInfo) {
		construct(textureInfo,
		          textureInfo->imageWidth,
		          textureInfo->imageHeight,
		          1u);

	} else {
		Console::print("Tried to construct a sprite from an invalid image key: " + textureKey);
	}
}

Sprite::Sprite(TextureInfo* textureInfo): GraphicBody(), vertices(),
	renderInfo(), renderModes(), animationPaused(false), animationCounter(0.0) {
	if(textureInfo) {
		construct(textureInfo,
		          textureInfo->imageWidth,
		          textureInfo->imageHeight,
		          1u);

	} else {
		Console::print("Tried to construct a sprite from an invalid texture information: " + Console::toString(textureInfo));
	}
}

Sprite::Sprite(const std::string& textureKey,
               unsigned int frameWidth,
               unsigned int frameHeight,
               unsigned int nbFrames): GraphicBody(), vertices(), renderInfo(),
	renderModes(), animationPaused(false), animationCounter(0.0) {
	construct(ResourceManager::getTexture(textureKey),
	          frameWidth,
	          frameHeight,
	          nbFrames);
}

Sprite::Sprite(TextureInfo* textureInfo,
               unsigned int frameWidth,
               unsigned int frameHeight,
               unsigned int nbFrames): GraphicBody(), vertices(), renderInfo(),
	renderModes(), animationPaused(false), animationCounter(0.0) {
	construct(textureInfo,
	          frameWidth,
	          frameHeight,
	          nbFrames);
}

Sprite::Sprite(const Sprite& src): GraphicBody(src), vertices(src.vertices),
	renderInfo(src.renderInfo), renderModes(src.renderModes),
	animationPaused(animationPaused), animationCounter(src.animationCounter) {
}

Sprite::~Sprite() {
}

Sprite& Sprite::operator=(const Sprite& src) {
	this->GraphicBody::operator=(src);

	if(this != &src) {
		vertices = src.vertices;
		renderInfo = src.renderInfo;
		renderModes = src.renderModes;
		animationPaused = src.animationPaused;
		animationCounter = src.animationCounter;
	}

	return *this;
}

void Sprite::update() {
	this->GraphicBody::update();

	// We check if the sprite is not paused, animated and if its animation is
	// valid.
	if(!animationPaused && renderInfo.isAnimated() &&
	   renderInfo.getCurrentAnimation() != "") {
		// We get the sprite's animation's information.
		AnimationParameters* animation = renderInfo.getAnimationParameters(renderInfo.getCurrentAnimation());

		// If the animation exists.
		if(animation) {
			// We make sure there is a time between frames so we don't get in
			// an infinite loop.
			if(animation->timePerFrame > 0.0) {
				// We increment the animation counter.
				animationCounter += Engine::getSinceLastUpdate();

				// We increment the frames if needed.
				while(animationCounter >= animation->timePerFrame) {
					renderInfo.incrementFrame();
					animationCounter -= animation->timePerFrame;
				}

			} else {
				renderInfo.incrementFrame();
			}
		}
	}
}

void Sprite::render() {
	// We make sure there are vertices to render.
	if(vertices.getVerticesCount() > 0) {
		// We check which graphic driver method to use.
		if(renderModes.isSet(RenderMode::SHAPE)) {
			// We check if we have a texture to render.
			if(renderModes.isSet(RenderMode::TEXTURE)) {
				// We check if we are rendering a mask.
				if(renderModes.isSet(RenderMode::MASKED) || renderModes.isSet(RenderMode::INVERSE_MASKED)) {
					GraphicBody* mask = this->getMask();
					assert(mask);
					mask->mask();
					// Masked with texture.
                    CArray<Vector2> test = vertices.getVertices();
					GraphicDriver::drawMaskedShapeWithTextureAndColor(test,
					                                                  renderInfo,
					                                                  renderModes.isSet(RenderMode::INVERSE_MASKED));
					mask->unmask();

				} else {
					// We render with the texture.
					GraphicDriver::drawShapeWithTextureAndColor(vertices.getVertices(),
					                                            renderInfo);
				}

			} else if(renderModes.isSet(RenderMode::COLOR)) {
				// We render with the color only.
				GraphicDriver::drawShapeWithColor(vertices.getVertices(),
				                                  renderInfo);
			}
		}
	}
}

void Sprite::mask() {
	if(vertices.getVerticesCount() > 0 ) {
		GraphicDriver::drawMaskShapeWithTextureAndColor(vertices.getVertices(),
		                                                renderInfo);
	}
}

void Sprite::unmask() {
	if(vertices.getVerticesCount() > 0) {
		GraphicDriver::unmask(vertices.getVertices(), renderInfo);
	}
}

GraphicBody* Sprite::getMask() {
	return renderInfo.getMask();
}

void Sprite::setMask(GraphicBody* newMask, bool inversed) {
	if(newMask) {
		renderInfo.setMask(newMask);
		renderModes.set(RenderMode::MASKED, false);
		renderModes.set(RenderMode::INVERSE_MASKED, false);

		if(inversed) {
			renderModes.set(RenderMode::INVERSE_MASKED, true);

		} else {
			renderModes.set(RenderMode::MASKED, true);
		}
	}
}

void Sprite::createVertex(float x, float y) {
	vertices.addVertex(x, y);
}

Vector2 Sprite::getPositionCenter() const {
	return Vector2(getXPosition() + getWidth() * 0.5f,
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

const Vector2 Sprite::getSize() const {
	return vertices.getSize();
}

float Sprite::getWidth() const {
	return vertices.getWidth();
}

float Sprite::getHeight() const {
	return vertices.getHeight();
}

const Color& Sprite::getMainColor() const {
	return renderInfo.getColor();
}

void Sprite::setMainColor(const Color& newColor) {
	renderModes.set(RenderMode::COLOR);
	renderInfo.setColor(newColor);
}

uint8_t Sprite::getMainAlpha() const {
	return renderInfo.getColor().getAlpha();
}

void Sprite::setMainAlpha(int32_t newAlpha) {
	Color tmpColor = getMainColor();
	tmpColor.setAlpha(newAlpha);
	setMainColor(tmpColor);
}

VerticesGroup& Sprite::getVertices() {
	return vertices;
}

const VerticesGroup& Sprite::getVertices() const {
	return vertices;
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

RenderInfo& Sprite::getRenderInfo() {
	return renderInfo;
}

const RenderInfo& Sprite::getRenderInfo() const {
	return renderInfo;
}

bool Sprite::isAnimationPaused() const {
	return animationPaused;
}

void Sprite::playAnimation(const std::string& name) {
	// We check if the animation really exists.
	if(renderInfo.animationExists(name)) {
		// We make sure the animation isn't already playing.
		if(renderInfo.getCurrentAnimation() != name) {
			// We set the new current animation and start the animaiton at the
			// first frame.
			renderInfo.setCurrentAnimation(name);
			renderInfo.setCurrentFrame(0);
			renderInfo.resetCurrentNbLoops();
			animationCounter = 0.0;
			animationPaused = false;
		}
	}
}

void Sprite::pauseAnimation() {
	animationPaused = true;
}

void Sprite::resumeAnimation() {
	animationPaused = false;
}

const std::string& Sprite::getCurrentAnimation() const {
	return renderInfo.getCurrentAnimation();
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

		// We read the animation's frame indexes.
		for(std::vector<unsigned int>::iterator i = framesVector.begin();
		    i != framesVector.end();
		    ++i) {
			*i = va_arg(frames, unsigned int);
		}

		va_end(frames);
		renderInfo.addAnimation(name, framesVector, timePerFrame, nbLoops);

	} else {
		Console::print("Failed to add the animation named \"" + name + "\" because it specified that it had 0 frames.");
		Console::printTrace();
	}
}

const FlagSet<RenderMode>& Sprite::getRenderModes() const {
	return renderModes;
}

void Sprite::setRenderModes(const FlagSet<RenderMode>& newRenderModes) {
	renderModes = newRenderModes;
}

void Sprite::addRenderModes(const FlagSet<RenderMode>& newRenderModes) {
	renderModes |= newRenderModes;
}

void Sprite::addRenderMode(RenderMode newRenderMode) {
	renderModes.set(newRenderMode);
}

void Sprite::removeRenderModes(const FlagSet<RenderMode>& renderModesToRemove) {
	renderModes.reset(renderModesToRemove);
}

void Sprite::removeRenderMode(RenderMode renderModeToRemove) {
	renderModes.reset(renderModeToRemove);
}

void Sprite::setScaling(float newXScaling, float newYScaling) {
	if(newXScaling && newYScaling) {
		vertices.scale(Vector2(newXScaling / getXScaling(), newYScaling / getYScaling()));
		GraphicBody::setScaling(newXScaling, newYScaling);
		Vector2 tmp = vertices.getPosition();
		GraphicBody::setPosition(tmp.getX(), tmp.getY());

	} else {
		Console::print("Tried to set a scaling of 0 to a sprite.");
	}
}

void Sprite::rotateFromPoint(float rotationAngle, const Vector2& rotationPoint) {
	this->GraphicBody::rotateFromPoint(rotationAngle, rotationPoint);

	if(rotationAngle != 0.0f) {
		vertices.rotate(rotationAngle, rotationPoint);
		Vector2 tmp = vertices.getPosition();
		GraphicBody::setPosition(tmp.getX(), tmp.getY());
	}
}

GraphicBody* Sprite::clone() const {
	return new Sprite(*this);
}

void Sprite::construct(TextureInfo* textureInfo,
                       unsigned int frameWidth,
                       unsigned int frameHeight,
                       unsigned int nbFrames) {
	if(textureInfo) {
		// Generates the square vertices from the frame width and height.
		vertices.addVertices(4,
		                     0.0f, 0.0f,
		                     static_cast<float>(frameWidth), 0.0f,
		                     static_cast<float>(frameWidth), static_cast<float>(frameHeight),
		                     0.0f, static_cast<float>(frameHeight));
		renderInfo.loadTexCoords(vertices, frameWidth, frameHeight, nbFrames,
		                         textureInfo);
		renderModes.reset();
		renderModes.set(RenderMode::SHAPE);
		renderModes.set(RenderMode::TEXTURE);
		renderModes.set(RenderMode::COLOR);

	} else {
		Console::print("Failed to load a sprite with the following texture information: " + Console::toString(textureInfo));
	}
}

