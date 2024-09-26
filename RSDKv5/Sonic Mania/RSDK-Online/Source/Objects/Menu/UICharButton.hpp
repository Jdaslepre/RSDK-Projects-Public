#pragma once
#include "RSDK-Online.hpp"

namespace GameLogic {

struct UICharButton : ManiaUIEntity {

    // ---------------
    // Enums & Structs
    // ---------------

    // ----------------
    // Static Variables
    // ----------------

    struct Static : RSDK::GameObject::Static {
        RSDK::SpriteAnimation aniFrames;
    };

    struct ModStatic : RSDK::GameObject::Static {};

    // ----------------
    // Entity Variables
    // ----------------

    uint8 characterID;
    int32 triBounceVelocity;
    int32 triBounceOffset;
    int32 playerBounceVelocity;
    int32 playerBounceOffset;
    int32 unused;
    RSDK::Animator unusedAnimator;
    RSDK::Animator playerAnimator;
    RSDK::Animator shadowAnimator;
    RSDK::Animator nameAnimator;

    // -------------
    // Object States
    // -------------


    // -------------------
    // Static Declarations
    // -------------------

    MOD_DECLARE(UICharButton)
};
} // namespace GameLogic