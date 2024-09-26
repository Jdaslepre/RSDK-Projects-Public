#pragma once
#include "RSDK-Online.hpp"

namespace GameLogic {

struct UIShifter : RSDK::GameObject::Entity {

    // ----------------
    // Static Variables
    // ----------------

    struct Static : RSDK::GameObject::Static {
        RSDK::Animator animator;
        RSDK::SpriteAnimation aniFrames;
    };

    struct ModStatic : RSDK::GameObject::Static {};

    // ----------------
    // Entity Variables
    // ----------------

    RSDK::Vector2 shift;
    RSDK::Vector2 lastButtonShift;
    RSDK::Vector2 shiftOffset;
    int32 unused;
    RSDK::Vector2 startPos;
    UIControl *parent;

    // -------------------
    // Static Declarations
    // -------------------

    MOD_DECLARE(UIShifter)
};

} // namespace GameLogic