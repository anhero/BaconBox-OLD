/**
 * @file
 */
#ifndef RB_FONT_POINTER_H
#define RB_FONT_POINTER_H

#include "BaconBox/ResourcePointer.h"
#include "BaconBox/ResourceManager.h"

namespace BaconBox {
	class Font;
	typedef ResourcePointer<Font, &ResourceManager::getFont> FontPointer;
}

#endif // RB_FONT_POINTER_H
