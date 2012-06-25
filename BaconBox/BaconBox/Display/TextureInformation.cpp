#include "TextureInformation.h"

#include "PlatformFlagger.h"
#include "MathHelper.h"

namespace BaconBox {

#if defined (RB_OPENGL) || defined (RB_OPENGLES)
	TextureInformation::TextureInformation(): textureId(0), colorFormat(ColorFormat::RGBA),
		poweredWidth(0), poweredHeight(0), imageWidth(0), imageHeight(0) {
	}

	TextureInformation::TextureInformation(unsigned int newTextureId,
	                                       unsigned int newImageWidth,
	                                       unsigned int newImageHeight): textureId(newTextureId),
		colorFormat(ColorFormat::RGBA),
		poweredWidth(MathHelper::nextPowerOf2(newImageWidth)),
		poweredHeight(MathHelper::nextPowerOf2(newImageHeight)),
		imageWidth(newImageWidth), imageHeight(newImageHeight) {
	}
#else
	TextureInformation::TextureInformation(): poweredWidth(0), poweredHeight(0), imageWidth(0),
		imageHeight(0) {
	}
	TextureInformation::TextureInformation(unsigned int newImageWidth,
	                                       unsigned int newImageHeight): poweredWidth(MathHelper::nextPowerOf2(newImageWidth)),
		poweredHeight(MathHelper::nextPowerOf2(newImageHeight)),
		imageWidth(newImageWidth), imageHeight(newImageHeight) {
	}
#endif

	std::ostream &operator<<(std::ostream &output, const TextureInformation &t) {
		output << "{";
#if defined (RB_OPENGL) || defined (RB_OPENGLES)
		output << "textureId: " << t.textureId << ", ";
#endif
		output << "poweredWidth: " << t.poweredWidth << ", poweredHeight: " <<
		       t.poweredHeight << ", imageWidth: " << t.poweredWidth << ", imageHeight: " <<
		       t.poweredHeight << "}";
		return output;
	}
}
