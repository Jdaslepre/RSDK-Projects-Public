#pragma once
#include "GameAPI/Game.hpp"

using namespace RSDK;

namespace GameLogic {

struct S3K_SS_Player : GameObject::Entity {

    // ----------------
    // Static Variables
    // ----------------

    struct Static : GameObject::Static {
        uint16 jumpPressState;
        uint16 sphereBounceDelay;
        SpriteAnimation sonicFrames;
        SpriteAnimation tailsFrames;
        SpriteAnimation knuxFrames;
#if ORIGINS_USE_PLUS
        SpriteAnimation amyFrames;
#endif
        SpriteAnimation mightyFrames;
        SpriteAnimation rayFrames;
        SoundFX sfxJump;
    };

    struct ModStatic : GameObject::Static {
        uint8 touchJump;
        uint8 touchPause;
    };

    // ----------------
    // Entity Variables
    // ----------------

    int32 gravityStrength;
    bool32 sidekick;
    StateMachine<S3K_SS_Player> stateInput;
    int32 controllerID;
    bool32 up;
    bool32 down;
    bool32 left;
    bool32 right;
    bool32 jumpPress;
    Animator animator;
    Animator tailAnimator;
    SpriteAnimation aniFrames;
    int32 characterID;

    // -------------
    // Object States
    // -------------

    static Action<void> Input_Gamepad;

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