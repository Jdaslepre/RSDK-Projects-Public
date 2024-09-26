#include "RSDK-Online.hpp"

using namespace RSDK;

namespace GameLogic {

// -------------------
// Object Registration
// -------------------

MOD_REGISTER_OBJECT(UITransition);

// ----------------
// Public Functions
// ----------------

void (*UITransition_StartTransition)(void (*callback)(void), int32 delay);
ManiaStateMachine(UITransition_State_TransitionOut);

// ------------------
// Object State Hooks
// ------------------

bool32 UITransition_State_TransitionOut_Hook(bool32 skippedState) {
    MenuSetup::SetBGColors();
    return false;
}

} // namespace GameLogic