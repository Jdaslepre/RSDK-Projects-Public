#include "RSDK-Online.hpp"

using namespace RSDK;

namespace GameLogic {

// -------------------
// Object Registration
// -------------------

MOD_REGISTER_OBJECT(UIWidgets);

// ----------------
// Public Functions
// ----------------

void (*UIWidgets_DrawRightTriangle)(int32 x, int32 y, int32 size, int32 red, int32 green, int32 blue);

} // namespace GameLogic