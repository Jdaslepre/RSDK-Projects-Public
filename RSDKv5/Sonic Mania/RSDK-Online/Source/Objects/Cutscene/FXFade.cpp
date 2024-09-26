#include "RSDK-Online.hpp"

using namespace RSDK;

namespace GameLogic {

// -------------------
// Object Registration
// -------------------

MOD_REGISTER_OBJECT(FXFade);

// ----------------
// Public Functions
// ----------------

ManiaStateMachine(FXFade_State_FadeOut);

} // namespace GameLogic