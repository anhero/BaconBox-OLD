#include "TextureInfo.h"

#include "PlatformFlagger.h"

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

namespace RedBox {
	std::ostream& operator<<(std::ostream& output, const TextureInfo& t) {
		output << "{";
#ifdef RB_OPENGL
		output << "textureId: " << t.textureId << ", ";
#endif
		output<< "imageWidth: " << t.imageWidth << ", imageHeight: " << 
		t.imageHeight << "}";
		return output;
	}
}
