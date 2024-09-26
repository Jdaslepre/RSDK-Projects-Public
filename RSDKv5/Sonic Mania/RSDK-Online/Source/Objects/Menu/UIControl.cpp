#include "RSDK-Online.hpp"

using namespace RSDK;

namespace GameLogic {

// -------------------
// Object Registration
// -------------------

MOD_REGISTER_OBJECT(UIControl);

// ----------------
// Public Functions
// ----------------

void (*UIControl_SetActiveMenu)(UIControl *entity);
UIControl *(*UIControl_GetUIControl)(void);
void (*UIControl_MatchMenuTag)(const char *text);

} // namespace GameLogic