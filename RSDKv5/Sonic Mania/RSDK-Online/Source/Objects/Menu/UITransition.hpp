#pragma once
#include "RSDK-Online.hpp"

namespace GameLogic {

struct UITransition : RSDK::GameObject::Entity {

    // ----------------
    // Static Variables
    // ----------------

    struct Static : RSDK::GameObject::Static {};
    struct ModStatic : RSDK::GameObject::Static {};
    
    // -------------------
    // Static Declarations
    // -------------------

    MOD_DECLARE(UITransition)
};

// ----------------
// Public Functions
// ----------------

extern void (*UITransition_StartTransition)(void (*callback)(void), int32 delay);
extern ManiaStateMachine(UITransition_State_TransitionOut);

// ------------------
// Object State Hooks
// ------------------

bool32 UITransition_State_TransitionOut_Hook(bool32 skippedState);

} // namespace GameLogic