#pragma once
#include "RSDK-Online.hpp"

// ------------------
// Macros/Definitions
// ------------------

#if MANIA_USE_PLUS
#define UIBACKGROUND_BGCOLOR_COUNT (21)
#else
#define UIBACKGROUND_BGCOLOR_COUNT (15)
#endif

namespace GameLogic {

struct UIBackground : RSDK::GameObject::Entity {

    // ---------------
    // Enums & Structs
    // ---------------

    // ----------------
    // Static Variables
    // ----------------

    struct Static : RSDK::GameObject::Static {
        color bgColors[UIBACKGROUND_BGCOLOR_COUNT];
        color *activeColors;
        RSDK::SpriteAnimation aniFrames;
    };

    struct ModStatic : RSDK::GameObject::Static {};

    // ----------------
    // Entity Variables
    // ----------------

    ManiaStateMachine(stateDraw);
    int32 type;
    int32 timer;
    RSDK::Animator animator;

    // -------------------
    // Static Declarations
    // -------------------

    MOD_DECLARE(UIBackground)
};
} // namespace GameLogic