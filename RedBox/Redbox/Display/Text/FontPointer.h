/**
 * @file
 */
#ifndef RB_FONT_POINTER_H
#define RB_FONT_POINTER_H

#include "ResourcePointer.h"
#include "ResourceManager.h"

namespace RedBox {
	class Font;
	typedef ResourcePointer<Font, &ResourceManager::getFont> FontPointer;
}

#endif // RB_FONT_POINTER_H
