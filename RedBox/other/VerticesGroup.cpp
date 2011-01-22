#include "VerticesGroup.h"

using namespace RedBox;

VerticesGroup::VerticesGroup() {
}

VerticesGroup::VerticesGroup(const VerticesGroup& src) {
    copyFrom(src);
}

VerticesGroup::~VerticesGroup() {
}

VerticesGroup& VerticesGroup::operator=(const VerticesGroup& src) {
	copyFrom(src);
	return *this;
}

void VerticesGroup::addVertex(float x, float y, Sprite* sprite, 
                              GraphicBody* graphicBody) {
	// We resize the verticesData and add its new floats.
    verticesData.resize(verticesData.size() + 2);
    verticesData[verticesData.size()-1] = y;
    verticesData[verticesData.size()-2] = x;
    
	resetPointers();
	
	// We add the new vertex to the list.
    if(vertices.size() == 1) {
		vertices.push_back(&(verticesData[verticesData.size()-2]), &(verticesData[verticesData.size()-1]), sprite, graphicBody);
    } else {
		vertices.push_back(&(verticesData[verticesData.size()-2]), &(verticesData[verticesData.size()-1]), vertices.front().getParentSprite(), vertices.front().getParentGraphicBody());
    }
}

void VerticesGroup::deleteVertex(Vertex* vertexToDelete) {
	// We remove the vertex from the list, but we take not of its pointer to
	// its x value.
	float* xPtr = NULL;
	std::list<Vertex>::iterator itr = vertices.begin();
	int nbVerticesData = vertices.size() * 2;
	while(itr != vertices.end()) {
		if(vertexTodelete == &(*itr)) {
			xPtr = itr->getPosition().getXPtr();
			vertices.erase(itr);
			itr = vertices.end();
		} else {
			itr++;
		}
	}
	// We remove the vertex's data from the vector.
	if(xPtr != NULL) {
		std::vector<float>::iterator i = verticesData.begin();
		while(i != verticesData.end()) {
			if(xPtr == &(*i)) {
				i = verticesData.erase(i);
				verticesData.erase(i);
			}
		}
	}
	// We re-set the pointers.
	resetPointers();
}

std::vector<Vertex>& VerticesGroup::getVertices() {
    return vertices;
}
std::vector<float>& VerticesGroup::getVerticesData() {
    return verticesData;
}

bool VerticesGroup::containsVertices(Vertex* firstVertex, Vertex* secondVertex) {
    std::list<Vertex>::iterator i = vertices.begin();
    bool firstNotFound = true, secondNotFound = true;
    while((firstNotFound || secondNotFound) && i != vertices.end()) {
        if(&(*i) == firstVertex) {
            firstNotFound = false;
        }
        if(&(*i) == secondVertex) {
            secondNotFound = false;
        }
        i++;
    }
    return !(firstNotFound || secondNotFound);
}

void VerticesGroup::warnVerticesOfDeletion() {
    for(std::list<Vertex>::iterator i = vertices.begin(); i != vertices.end(); i++) {
        i->dontDeleteLinks();
    }
}

void VerticesGroup::setParentSprite(Sprite* sprite) {
    for(std::list<Vertex>::iterator i = vertices.begin(); i != vertices.end(); i++) {
        i->setParentSprite(sprite);
    }
}

void VerticesGroup::setParentGraphicBody(GraphicBody* body) {
    for(std::list<Vertex>::iterator i = vertices.begin(); i != vertices.end(); i++) {
        i->setParentGraphicBody(body);
    }
}

void VerticesGroup::resetPointers() {
    // We reset the vertices' pointers to the correct new floats.
	int i = 0;
	std::list<Vertex>::iterator itr = vertices.begin();
	while(i < vertices.size() && itr != vertices.end()) {
        itr->getPosition().setIsPtr(true);
        itr->getPosition().setYPtr(&(verticesData[i*2+1]));
        itr->getPosition().setXPtr(&(verticesData[i*2]));
		i++;
		itr++;
	}
}

void VerticesGroup::copyFrom(const VerticesGroup& src) {
    // We make sure the recieved VertexGroup isn't the instance and isn't null.
	if(this != &src && &src) {
        // Free all of the instance's allocated memory.
        clean();
        verticesData = src.verticesData;
        vertices.resize(src.vertices.size());
		int i = 0;
		for(std::list<Vertex>::iterator itr = vertices.begin(); i != vertices.end(); i++) {
			itr->getPosition().setIsPtr(true);
			itr->getPosition().setYPtr(&(verticesData[i*2+1]));
			itr->getPosition().setXPtr(&(verticesData[i*2]));
			i++;
		}
	}
}

void VerticesGroup::clean() {
    verticesData.clear();
    vertices.clear();
}

std::ostream& RedBox::operator<<(std::ostream& output, const VerticesGroup& vg) {
    output << "VertexGroup:{verticesData:[";
    int vSize = vg.vertices.size() * 2;
    for(int i = 0; i < vSize; i++){
        output << vg.verticesData[i];
        if(i != vSize - 1) {
            output << ", ";
        }
    }
    output << "], vertices:[";
	for(std::list<Vertex>::iterator i = vg.vertices.begin(); i != vg.verties.end(); i++) {
		output << i->position;
		if(*i != vg.vertices.back()) {
			output << ", ";
		}
	}
    output << "}";
    return output;
}
