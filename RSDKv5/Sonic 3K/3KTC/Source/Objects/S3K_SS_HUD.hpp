#pragma once
#include "GameAPI/Game.hpp"

namespace GameLogic {

struct S3K_SS_HUD : RSDK::GameObject::Entity {

    // ----------------
    // Static Variables
    // ----------------

    struct Static : RSDK::GameObject::Static {
        RSDK::SpriteAnimation aniFrames;
    };

    struct ModStatic : RSDK::GameObject::Static {
        RSDK::SpriteAnimation dpadFrames;
        RSDK::Animator dpadAnimator;
        RSDK::Animator dpadTouchAnimator;
        RSDK::Vector2 dpadPos;
        int32 dpadAlpha;
        RSDK::Vector2 actionPos;
        RSDK::Vector2 pausePos;
        int32 pauseAlpha;
    };

    // ----------------
    // Entity Variables
    // ----------------

    RSDK::Animator sphereAnimator;
    RSDK::Animator ringAnimator;
    RSDK::Animator numbersAnimator;

    // ----------------------
    // Standard Entity Events
    // ----------------------

    void Draw(void);
    static void StageLoad(void);

    // ----------------------
    // Extra Entity Functions
    // ----------------------

    void DrawTouchControls(void);

    // -------------------
    // Static Declarations
    // -------------------

    MOD_DECLARE(S3K_SS_HUD)
};
} // namespace GameLogic