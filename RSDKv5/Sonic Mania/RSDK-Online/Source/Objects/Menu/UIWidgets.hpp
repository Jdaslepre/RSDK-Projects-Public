#pragma once
#include "RSDK-Online.hpp"

namespace GameLogic {

struct UIWidgets : RSDK::GameObject::Entity {

    // ----------------
    // Static Variables
    // ----------------

    struct Static : RSDK::GameObject::Static {};
    struct ModStatic : RSDK::GameObject::Static {};

    // ----------------
    // Entity Variables
    // ----------------

    // -------------------
    // Static Declarations
    // -------------------

    MOD_DECLARE(UIWidgets)
};

// ----------------
// Public Functions
// ----------------

extern void (*UIWidgets_DrawRightTriangle)(int32 x, int32 y, int32 size, int32 red, int32 green, int32 blue);

} // namespace GameLogic