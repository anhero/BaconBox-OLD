/**
 * @file
 */
#ifndef RB_TEXTURE_POINTER_H
#define RB_TEXTURE_POINTER_H

#include "BaconBox/ResourcePointer.h"
#include "BaconBox/ResourceManager.h"

namespace BaconBox {
	struct TextureInformation;
	typedef ResourcePointer<TextureInformation, &ResourceManager::getTexture> TexturePointer;
}

#endif // RB_TEXTURE_POINTER_H
