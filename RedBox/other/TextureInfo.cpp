//
//  TextureInfo.cpp
//  RedBox
//
//  Created by Adam Labranche on 11-01-21.
//  Copyright 2011 Illogical Studios. All rights reserved.
//

#include "TextureInfo.h"

using namespace RedBox;

#ifdef RB_OPENGL
TextureInfo::TextureInfo(): textureId(0), imageWidth(0), imageHeight(0) {
}
TextureInfo::TextureInfo(unsigned int newTextureId,
			unsigned int newImageWidth,
			unsigned int newImageHeight): textureId(newTextureId),
imageWidth(newImageWidth), imageHeight(newImageHeight) {
}
#else
TextureInfo::TextureInfo():imageWidth(0), imageHeight(0) {
}
TextureInfo::TextureInfo(unsigned int newImageWidth,
						 unsigned int newImageHeight):imageWidth(newImageWidth),
imageHeight(newImageHeight) {
}
#endif

std::ostream& RedBox::operator<<(std::ostream& output, const TextureInfo& t) {
	output << "{";
#ifdef RB_OPENGL
	output << "textureId: " << t.textureId << ", ";
#endif
	output<< "imageWidth: " << t.imageWidth << ", imageHeight: " << 
	t.imageHeight << "}";
	return output;
}