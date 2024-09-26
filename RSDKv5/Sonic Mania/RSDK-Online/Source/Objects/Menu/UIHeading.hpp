#pragma once
#include "RSDK-Online.hpp"

namespace GameLogic {

struct UIHeading : RSDK::GameObject::Entity {

    // ---------------
    // Enums & Structs
    // ---------------

    enum IDs {
        IDMainMenu,
        IDManiaMode,
        IDTimeAttack,
        IDCompetition,
        IDResults,
        IDOptions,
        IDExtras,
        IDLeaderboards,
        IDSecrets,
        IDPlayerSelect,
        IDZoneSelect,
        IDReplays,
        IDEncoreMode,
    };

    // ----------------
    // Static Variables
    // ----------------

    struct Static : RSDK::GameObject::Static {
        RSDK::SpriteAnimation textFrames;
    };

    struct ModStatic : RSDK::GameObject::Static {};

    // ----------------
    // Entity Variables
    // ----------------

    ManiaStateMachine(state);
    int32 unused;
    RSDK::Vector2 startPos;
    int32 headingID;
    RSDK::Animator headingAnimator;
    RSDK::Animator textAnimator;
    RSDK::SpriteAnimation textFrames;

    // ----------------------
    // Standard Entity Events
    // ----------------------
    
    // -------------------
    // Static Declarations
    // -------------------

    MOD_DECLARE(UIHeading)
};

} // namespace GameLogic