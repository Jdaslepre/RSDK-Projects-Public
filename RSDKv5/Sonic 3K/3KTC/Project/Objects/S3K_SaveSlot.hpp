#pragma once
#include "GameAPI/Game.hpp"

using namespace RSDK;

namespace GameLogic {

struct S3K_SaveSlot : GameObject::Entity {

    // ---------------
    // Enums & Structs
    // ---------------
    enum Types {
        TypeInactive = -1,
        TypeNoSave,
        TypeSave,
        TypeDelete,
    };

    enum Characters {
        SonicAndTails,
        Knuckles,
        Tails,
        Sonic,
#if ORIGINS_USE_PLUS
        Amy,
        AmyAndTails,
#endif
    };

    // ----------------
    // Static Variables
    // ----------------

    struct Static : GameObject::Static {};

    struct ModStatic : GameObject::Static {};

    // ----------------
    // Entity Variables
    // ----------------

    StateMachine<S3K_SaveSlot> state;
    Animator outlineAnimator;
    Animator textAnimator;
    Animator playerAnimator;
    Animator signAnimator;
    Animator zoneIconAnimator;
    Animator numberAnimator;
    Animator playerIconAnimator;
    String text;
    uint8 pad[4];
    Vector2 startPos;
    uint8 type;
    uint8 slotID;
    uint8 saveActive;
    uint8 showClearText;
    uint8 zoneID;
    uint16 emeralds;
    uint8 lives;
    uint8 continues;
    uint8 characterID;
    uint8 allowCharacterSelection;
    uint8 allowZoneSelection;

    // ----------------------
    // Standard Entity Events
    // ----------------------

    // -------------
    // Object States
    // -------------

    // ----------------------
    // Extra Entity Functions
    // ----------------------

    // -------------------
    // Static Declarations
    // -------------------

    MOD_DECLARE(S3K_SaveSlot)
};

// ----------------------
// Extra Entity Functions
// ----------------------

} // namespace GameLogic