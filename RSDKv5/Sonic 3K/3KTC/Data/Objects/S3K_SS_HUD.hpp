#pragma once
#include "GameAPI/Game.hpp"

using namespace RSDK;

namespace GameLogic {

struct S3K_SS_HUD : GameObject::Entity {

    // ----------------
    // Static Variables
    // ----------------

    struct Static : GameObject::Static {
        SpriteAnimation aniFrames;
    };

    struct ModStatic : GameObject::Static {
        SpriteAnimation dpadFrames;
        Animator dpadAnimator;
        Animator dpadTouchAnimator;
        Vector2 dpadPos;
        int32 dpadAlpha;
        Vector2 actionPos;
        Vector2 pausePos;
        int32 pauseAlpha;
    };

    // ----------------
    // Entity Variables
    // ----------------

    Animator sphereAnimator;
    Animator ringAnimator;
    Animator numbersAnimator;

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