#include "TextureInfo.h"

#include "PlatformFlagger.h"

using namespace RedBox;

#ifdef RB_OPENGL
TextureInfo::TextureInfo(): textureId(0), poweredWidth(0), poweredHeight(0), colorFormat(ColorFormat::RGBA){
}
TextureInfo::TextureInfo(unsigned int newTextureId,
						 unsigned int newImageWidth,
						 unsigned int newImageHeight): textureId(newTextureId),
poweredWidth(newImageWidth), poweredHeight(newImageHeight), colorFormat(ColorFormat::RGBA) {
}
#else
TextureInfo::TextureInfo():poweredWidth(0), poweredHeight(0) {
}
TextureInfo::TextureInfo(unsigned int newImageWidth,
						 unsigned int newImageHeight):poweredWidth(newImageWidth),
poweredHeight(newImageHeight) {
}
#endif

namespace RedBox {
	std::ostream& operator<<(std::ostream& output, const TextureInfo& t) {
		output << "{";
#ifdef RB_OPENGL
		output << "textureId: " << t.textureId << ", ";
#endif
		output<< "poweredWidth: " << t.poweredWidth << ", poweredHeight: " << 
		t.poweredHeight << ", imageWidth: " << t.poweredWidth << ", imageHeight: " << 
		t.poweredHeight << "}";
		return output;
	}
}
