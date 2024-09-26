#pragma once
#include "RSDK-Online.hpp"

namespace GameLogic {

struct MainMenu : RSDK::GameObject::Entity {

    // ----------------
    // Static Variables
    // ----------------

    struct Static : RSDK::GameObject::Static {
        UIControl *menuControl;
        UIButtonPrompt *confirmPrompt;
        UIDiorama *diorama;
    };

    struct ModStatic : RSDK::GameObject::Static {};

    // ----------------------
    // Standard Entity Events
    // ----------------------

    static void StaticUpdate();

    // -------------------
    // Static Declarations
    // -------------------

    MOD_DECLARE(MainMenu)
};

// ----------------
// Public Functions
// ----------------

extern bool32 (*MainMenu_BackPressCB_ReturnToTitle)(void);

} // namespace GameLogic