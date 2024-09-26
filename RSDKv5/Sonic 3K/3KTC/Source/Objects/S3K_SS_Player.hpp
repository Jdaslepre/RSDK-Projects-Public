#pragma once
#include "GameAPI/Game.hpp"

namespace GameLogic {

struct S3K_SS_Player : RSDK::GameObject::Entity {

    // ----------------
    // Static Variables
    // ----------------

    struct Static : RSDK::GameObject::Static {
        uint16 jumpPressState;
        uint16 sphereBounceDelay;
        RSDK::SpriteAnimation sonicFrames;
        RSDK::SpriteAnimation tailsFrames;
        RSDK::SpriteAnimation knuxFrames;
#if ORIGINS_USE_PLUS
        RSDK::SpriteAnimation amyFrames;
#endif
        RSDK::SpriteAnimation mightyFrames;
        RSDK::SpriteAnimation rayFrames;
        RSDK::SoundFX sfxJump;
    };

    struct ModStatic : RSDK::GameObject::Static {
        uint8 touchJump;
        uint8 touchPause;
    };

    // ----------------
    // Entity Variables
    // ----------------

    int32 gravityStrength;
    bool32 sidekick;
    RSDK::StateMachine<S3K_SS_Player> stateInput;
    int32 controllerID;
    bool32 up;
    bool32 down;
    bool32 left;
    bool32 right;
    bool32 jumpPress;
    RSDK::Animator animator;
    RSDK::Animator tailAnimator;
    RSDK::SpriteAnimation aniFrames;
    int32 characterID;

    // -------------
    // Object States
    // -------------

    static RSDK::Action<void> Input_Gamepad;

    // -------------------
    // Static Declarations
    // -------------------

    MOD_DECLARE(S3K_SS_Player)
};

// ----------------------
// Extra Entity Functions
// ----------------------

bool32 S3K_SS_Player_Input_Gamepad_Hook(bool32 skippedState);

} // namespace GameLogic