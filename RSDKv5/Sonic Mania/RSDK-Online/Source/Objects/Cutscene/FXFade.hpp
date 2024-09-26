#pragma once
#include "RSDK-Online.hpp"

namespace GameLogic {

struct FXFade : RSDK::GameObject::Entity {

    // ----------------
    // Static Variables
    // ----------------

    struct Static : RSDK::GameObject::Static {};
    struct ModStatic : RSDK::GameObject::Static {};

    // ----------------
    // Entity Variables
    // ----------------

    ManiaStateMachine(state);
    int32 timer;
    int32 speedIn;
    int32 wait;
    int32 speedOut;
    uint32 color;
    bool32 oneWay;
    bool32 eventOnly;
    bool32 overHUD;
    bool32 fadeOutBlack;
#if MANIA_USE_PLUS
    bool32 transitionScene;
#endif

    // -------------------
    // Static Declarations
    // -------------------

    MOD_DECLARE(FXFade)
};

// ----------------
// Public Functions
// ----------------

extern ManiaStateMachine(FXFade_State_FadeOut);

} // namespace GameLogic