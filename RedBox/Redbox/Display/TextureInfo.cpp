#include "TextureInfo.h"

#include "PlatformFlagger.h"
#include "MathHelper.h"

using namespace RedBox;

#ifdef RB_OPENGL
TextureInfo::TextureInfo(): textureId(0), colorFormat(ColorFormat::RGBA),
	poweredWidth(0), poweredHeight(0), imageWidth(0), imageHeight(0) {
}

TextureInfo::TextureInfo(unsigned int newTextureId,
                         unsigned int newImageWidth,
                         unsigned int newImageHeight): textureId(newTextureId),
	colorFormat(ColorFormat::RGBA),
	poweredWidth(MathHelper::nextPowerOf2(newImageWidth)),
	poweredHeight(MathHelper::nextPowerOf2(newImageHeight)),
	imageWidth(newImageWidth), imageHeight(newImageHeight) {
}
#else
TextureInfo::TextureInfo(): poweredWidth(0), poweredHeight(0), imageWidth(0),
	imageHeight(0) {
}
TextureInfo::TextureInfo(unsigned int newImageWidth,
                         unsigned int newImageHeight): poweredWidth(MathHelper::nextPowerOf2(newImageWidth)),
	poweredHeight(MathHelper::nextPowerOf2(newImageHeight)),
	imageWidth(newImageWidth), imageHeight(newImageHeight) {
}
#endif

namespace RedBox {
	std::ostream &operator<<(std::ostream &output, const TextureInfo &t) {
		output << "{";
#ifdef RB_OPENGL
		output << "textureId: " << t.textureId << ", ";
#endif
		output << "poweredWidth: " << t.poweredWidth << ", poweredHeight: " <<
		       t.poweredHeight << ", imageWidth: " << t.poweredWidth << ", imageHeight: " <<
		       t.poweredHeight << "}";
		return output;
	}
}
