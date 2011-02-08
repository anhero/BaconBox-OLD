#include "Sprite.h"

#include "ResourceLoader.h"
#include "Debug.h"

using namespace RedBox;

#ifdef RB_PHYSICS_ENABLED
Sprite::Sprite(GraphicBody* parentBody): Renderable()
vertices.setParentGraphicBody(parentBody);
#else
Sprite::Sprite(): Renderable()
#endif
{
}

#ifdef RB_PHYSICS_ENABLED
Sprite::Sprite(const std::string& imageKey, GraphicBody* parentBody): Renderable()
#else
Sprite::Sprite(const std::string& imageKey): Renderable()
#endif
{
	TextureInfo* texInfo = ResourceLoader::getTexture(imageKey);
	if(texInfo) {
		construct(texInfo,
				  texInfo->imageWidth,
				  texInfo->imageHeight,
				  0.0f,
#ifdef RB_PHYSICS_ENABLED
				  0.0f,
				  parentBody);
#else
		0.0f);
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
				  0.0f,
#ifdef RB_PHYSICS_ENABLED
				  0.0f,
				  parentBody);
#else
		0.0f);
#endif
	} else {
		$ECHO("Tried to construct a sprite from an invalid texture information: " << texInfo);
	}
}

Sprite::Sprite(const std::string& imageKey,
			   float frameWidth,
			   float frameHeight,
			   float offsetX,
#ifdef RB_PHYSICS_ENABLED
			   float offsetY,
			   GraphicBody* parentBody): Renderable()
#else
float offsetY): Renderable()
#endif
{
	construct(ResourceLoader::getTexture(imageKey),
			  frameWidth,
			  frameHeight,
			  offsetX,
#ifdef RB_PHYSICS_ENABLED
			  offsetY,
			  parentBody);
#else
	offsetY);
#endif
}

Sprite::Sprite(TextureInfo* texInfo,
			   float frameWidth,
			   float frameHeight,
			   float offsetX,
#ifdef RB_PHYSICS_ENABLED
			   float offsetY,
			   GraphicBody* parentBody): Renderable()
#else
float offsetY): Renderable()
#endif
{
	construct(texInfo,
			  frameWidth,
			  frameHeight,
			  offsetX,
#ifdef RB_PHYSICS_ENABLED
			  offsetY,
			  parentBody);
#else
	offsetY);
#endif
}

#ifdef RB_PHYSICS_ENABLED
Sprite::Sprite(const Sprite& src):Renderable(src), edges(src.edges), 
vertices(src.vertices), renderSteps(src.renderSteps) 
#else
Sprite::Sprite(const Sprite& src):Renderable(src), vertices(src.vertices), 
renderSteps(src.renderSteps) 
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
	std::vector<Edge>::iterator i = edges.begin();
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
					   float frameWidth,
					   float frameHeight,
					   float offsetX,
#ifdef RB_PHYSICS_ENABLED
					   float offsetY,
					   GraphicBody* parentBody = NULL)
#else
float offsetY)
#endif
{
	if(texInfo) {
		// Generates the square vertices from the frame width and height.
		vertices.addVertices(0.0f, 0.0f, frameWidth, 0.0f, frameWidth, frameHeight, 0.0f, frameHeight);
		vertices.setParentSprite(this);
#ifdef RB_PHYSICS_ENABLED
		vertices.setParentGraphicBody(parentBody);
#endif
		RenderStep* initialRenderStep = new RenderStep(texInfo,
													   &vertices,
													   1,
													   1.0f,
													   offsetX,
													   offsetY);
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
