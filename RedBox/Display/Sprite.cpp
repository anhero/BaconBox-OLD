#include "Sprite.h"

#include "PlatformFlagger.h"

#include "TextureInfo.h"
#include "RenderStep.h"
#include "GraphicBody.h"
#include "ResourceManager.h"
#include "Debug.h"
#include "Edge.h"
#include "VerticesGroup.h"

using namespace RedBox;

#ifdef RB_PHYSICS_ENABLED
Sprite::Sprite(GraphicBody* parentBody): Renderable() {
	vertices.setParentSprite(this);
	vertices.setParentGraphicBody(parentBody);
}
#else
Sprite::Sprite(): Renderable() {
	vertices.setParentSprite(this);
}
#endif

#ifdef RB_PHYSICS_ENABLED
Sprite::Sprite(const std::string& imageKey, GraphicBody* parentBody): Renderable()
#else
Sprite::Sprite(const std::string& imageKey): Renderable()
#endif
{
	TextureInfo* texInfo = ResourceManager::getTexture(imageKey);
	if(texInfo) {
		construct(texInfo,
				  texInfo->imageWidth,
				  texInfo->imageHeight,
				  1
#ifdef RB_PHYSICS_ENABLED
				  , parentBody);
#else
		);
#endif
	} else {
		$ECHO("Tried to construct a sprite from an invalid image key: " << imageKey);
	}
}

#ifdef RB_PHYSICS_ENABLED
Sprite::Sprite(TextureInfo* texInfo, GraphicBody* parentBody): Renderable()
#else
Sprite::Sprite(TextureInfo* texInfo): Renderable()
#endif
{
	if(texInfo) {
		construct(texInfo,
				  texInfo->imageWidth,
				  texInfo->imageHeight,
				  1
#ifdef RB_PHYSICS_ENABLED
				  , parentBody);
#else
		);
#endif
	} else {
		$ECHO("Tried to construct a sprite from an invalid texture information: " << texInfo);
	}
}

Sprite::Sprite(const std::string& imageKey,
			   unsigned int frameWidth,
			   unsigned int frameHeight,
			   unsigned int nbFrames
#ifdef RB_PHYSICS_ENABLED
			   , GraphicBody* parentBody): Renderable()
#else
): Renderable()
#endif
{
	construct(ResourceManager::getTexture(imageKey),
			  frameWidth,
			  frameHeight,
			  nbFrames
#ifdef RB_PHYSICS_ENABLED
			  , parentBody);
#else
	);
#endif
}

Sprite::Sprite(TextureInfo* texInfo,
			   unsigned int frameWidth,
			   unsigned int frameHeight,
			   unsigned int nbFrames
#ifdef RB_PHYSICS_ENABLED
			   , GraphicBody* parentBody): Renderable()
#else
): Renderable()
#endif
{
	construct(texInfo,
			  frameWidth,
			  frameHeight,
			  nbFrames
#ifdef RB_PHYSICS_ENABLED
			  , parentBody);
#else
	);
#endif
}

#ifdef RB_PHYSICS_ENABLED
Sprite::Sprite(const Sprite& src):Renderable(src), renderSteps(src.renderSteps),
vertices(src.vertices), edges(src.edges)
#else
Sprite::Sprite(const Sprite& src):Renderable(src), renderSteps(src.renderSteps), vertices(src.vertices)
#endif
{
    //copyFrom(src);
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
	vertices.addVertex(x, y, this);
}

float Sprite::getXPosition() const {
	return vertices.getXPosition();
}
float Sprite::getYPosition() const {
	return vertices.getYPosition();
}
std::pair<float, float> Sprite::getPosition() const {
	return vertices.getPosition();
}
void Sprite::setXPosition(float x) {
	vertices.setXPosition(x);
}
void Sprite::setYPosition(float y) {
	vertices.setYPosition(y);
}
void Sprite::setPosition(float x, float y) {
	vertices.setPosition(x, y);
}
void Sprite::moveX(float deltaX) {
	vertices.moveX(deltaX);
}
void Sprite::moveY(float deltaY) {
	vertices.moveY(deltaY);
}
void Sprite::move(float deltaX, float deltaY) {
	vertices.move(deltaX, deltaY);
}

void Sprite::warnVerticesOfDeletion() {
    vertices.warnVerticesOfDeletion();
}

RenderStep* Sprite::addRenderStep(RenderStep* newRenderStep) {
	if(newRenderStep) {
		renderSteps.push_back(newRenderStep);
	} else {
		$ECHO("Tried to add an NULL RenderStep to a Sprite.");
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
			$ECHO("Tried to remove a RenderStep from a Sprite which does not contain it: " << renderStep);
		}
	} else {
		$ECHO("Tried to remove a NULL RenderStep pointer from a sprite.");
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

#ifdef RB_PHYSICS_ENABLED
void Sprite::createEdge(Vertex* firstVertex, Vertex* secondVertex) {
    // We make sure the pointers to the vertices given are valid.
    // They have to be different and they have to be part of the vertices group.
    if(firstVertex != secondVertex && vertices.containsVertices(firstVertex, secondVertex)) {
        // We add the edge to the list.
		edges.push_back(Edge(firstVertex, secondVertex));
    }
}

void Sprite::setParentGraphicBody(GraphicBody* body) {
	vertices.setParentGraphicBody(body);
}

void Sprite::removeEdge(Edge* edge) {
	bool notFound = true;
	std::list<Edge>::iterator i = edges.begin();
	// We search for the edge to delete.
	while(notFound && i != edges.end()) {
        // If we found it.
        if(edge == &(*i)) {
			// We make sure to stop the loop.
            notFound = false;
            // We remove it from the list.
            edges.erase(i);
        } else {
            // If we haven't found it, we go to the next one.
            i++;
        }
	}       
}
#endif
void Sprite::construct(TextureInfo* texInfo,
					   unsigned int frameWidth,
					   unsigned int frameHeight,
					   unsigned int nbFrames
#ifdef RB_PHYSICS_ENABLED
					   , GraphicBody* parentBody)
#else
)
#endif
{
	if(texInfo) {
		// Generates the square vertices from the frame width and height.
		vertices.addVertices(4,
							 0.0f, 0.0f,
							 static_cast<float>(frameWidth), 0.0f,
							 static_cast<float>(frameWidth), static_cast<float>(frameHeight),
							 0.0f, static_cast<float>(frameHeight));
		vertices.setParentSprite(this);
#ifdef RB_PHYSICS_ENABLED
		vertices.setParentGraphicBody(parentBody);
#endif
		RenderStep* initialRenderStep = new RenderStep(texInfo,
													   &vertices,
													   frameWidth,
													   frameHeight,
													   nbFrames);
		renderSteps.push_back(initialRenderStep);
	} else {
		$ECHO("Failed to load a sprite with the following texture information: " << texInfo);
	}
}

void Sprite::clean() {
	clearRenderSteps();
	vertices.warnVerticesOfDeletion();
#ifdef RB_PHYSICS_ENABLED
    edges.clear();
#endif
}

void Sprite::copyFrom(const Sprite& src) {
    if(this != &src && &src) {
        renderSteps = src.renderSteps;
        vertices = src.vertices;
#ifdef RB_PHYSICS_ENABLED
        edges = src.edges;
#endif
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
