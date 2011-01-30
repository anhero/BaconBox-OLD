#include "RenderInfo.h"

using namespace RedBox;

RenderInfo::RenderInfo(): textureID(0) {
	color[0] = 0;
	color[1] = 0;
	color[2] = 0;
	color[3] = 0;
}

RenderInfo::RenderInfo(int newTextureID, int* newColor) {
	textureID = newTextureID;
	if(newColor) {
		color[0] = newColor[0];
		color[1] = newColor[1];
		color[2] = newColor[2];
		color[3] = newColor[3];
	}
}
