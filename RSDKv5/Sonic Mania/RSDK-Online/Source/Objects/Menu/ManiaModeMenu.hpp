#pragma once
#include "RSDK-Online.hpp"

namespace GameLogic {

struct ManiaModeMenu : RSDK::GameObject::Entity {

    // ---------------
    // Enums & Structs
    // ---------------

    // ----------------
    // Static Variables
    // ----------------

    struct Static : RSDK::GameObject::Static {};

    struct ModStatic : RSDK::GameObject::Static {
        bool32 initialized;
    };

    // ----------------
    // Entity Variables
    // ----------------

    static void StaticUpdate();

    // ----------------------
    // Extra Entity Functions
    // ----------------------

    static void InitializeExtra();
    static void SetupActions();

    // -------------------
    // Static Declarations
    // -------------------

    MOD_DECLARE(ManiaModeMenu)
};

// ----------------
// Public Functions
// ----------------

extern void (*ManiaModeMenu_StartReturnToTitle)(void);

} // namespace GameLogic