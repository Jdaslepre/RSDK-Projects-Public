#pragma once
#include "GameAPI/Game.hpp"

namespace GameLogic
{

struct S3K_SaveSlot : RSDK::GameObject::Entity {

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

    struct Static : RSDK::GameObject::Static {
    };
    struct ModStatic : RSDK::GameObject::Static {
    };

    // ----------------
    // Entity Variables
    // ----------------

    RSDK::StateMachine<S3K_SaveSlot> state;
    RSDK::Animator outlineAnimator;
    RSDK::Animator textAnimator;
    RSDK::Animator playerAnimator;
    RSDK::Animator signAnimator;
    RSDK::Animator zoneIconAnimator;
    RSDK::Animator numberAnimator;
    RSDK::Animator playerIconAnimator;
    RSDK::String text;
    uint8 pad[4];
    RSDK::Vector2 startPos;
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