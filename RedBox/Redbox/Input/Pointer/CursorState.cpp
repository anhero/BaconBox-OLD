#include "CursorState.h"

using namespace RedBox;

CursorState::CursorState(unsigned int nbButtons, float x, float y):
buttons(std::vector<bool>(nbButtons, false)), 
previousButtons(std::vector<bool>(nbButtons, false)), position(Vec2(x, y)) {
}
