#pragma once
#include "GameAPI/Game.hpp"

using namespace RSDK;

namespace GameLogic {

struct SlotHUD : GameObject::Entity {

    // ----------------
    // Static Variables
    // ----------------

    struct Static : GameObject::Static {
        SpriteAnimation aniFrames;
        SpriteAnimation superButtonFrames; // unused
        SoundFX sfxClick;
        SoundFX sfxStarpost;
        bool32 showTAPrompt;
        int32 screenBorderType[PLAYER_COUNT];
        int32 swapCooldown;
        int32 stockFlashTimers[PLAYER_COUNT];
    };

    struct ModStatic : GameObject::Static {
        SpriteAnimation dpadFrames;
        Animator dpadAnimator;
        Animator dpadTouchAnimator;
        Vector2 dpadPos;
        int32 dpadAlpha[PLAYER_COUNT];
        Vector2 actionPos;
        int32 jumpAlpha[PLAYER_COUNT];
        Vector2 pausePos;
        int32 pauseAlpha[PLAYER_COUNT];
    };

    // ----------------
    // Entity Variables
    // ----------------

    StateMachine<SlotHUD> state;
    Vector2 ringsPos;
    Vector2 lifePos;
    int32 lifeFrameIDs[PLAYER_COUNT];
    int32 lives[PLAYER_COUNT];
    int32 field_a8;
    int32 field_ac;
    int32 ringFlashFrame;
    bool32 enableRingFlash;
    Animator hudElementsAnimator;
    Animator numbersAnimator;
    Animator hyperNumbersAnimator;
    Animator lifeIconAnimator;
    Animator lifeNamesAnimator;
    Animator lifeNumbersAnimator;
    Animator playerIDAnimator;
    Animator superIconAnimator;
    Animator superButtonAnimator;
    Animator thumbsUpIconAnimator;
    Animator thumbsUpButtonAnimator;
    Animator replayClapAnimator;
    Animator saveReplayButtonAnimator;
    uint8 extendedHUD;

    // ----------------------
    // Standard Entity Events
    // ----------------------

    void Create(void *data);
    void Draw(void);
    static void StageLoad(void);

    // ----------------------
    // Extra Entity Functions
    // ----------------------

    void DrawMobile(void);
    void DrawTouchControls(void);

    // -------------------
    // Static Declarations
    // -------------------

    MOD_DECLARE(SlotHUD)
};

} // namespace GameLogic