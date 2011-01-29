#ifndef __TEXTURE_INFO_H
#define __TEXTURE_INFO_H

namespace RedBox {
	struct TextureInfo {
#ifdef RB_OPENGL
		unsigned int textureID;
#endif
		unsigned int imageWidth;
		unsigned int imageHeight;
	};
}
#endif