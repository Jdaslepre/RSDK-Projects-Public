#pragma once
#include "GameAPI/Game.hpp"

namespace GameLogic {

struct SlotHUD : RSDK::GameObject::Entity {

    // ----------------
    // Static Variables
    // ----------------

    struct Static : RSDK::GameObject::Static {
        RSDK::SpriteAnimation aniFrames;
        RSDK::SpriteAnimation superButtonFrames; // unused
        RSDK::SoundFX sfxClick;
        RSDK::SoundFX sfxStarpost;
        bool32 showTAPrompt;
        int32 screenBorderType[PLAYER_COUNT];
        int32 swapCooldown;
        int32 stockFlashTimers[PLAYER_COUNT];
    };

    struct ModStatic : RSDK::GameObject::Static {
        RSDK::SpriteAnimation dpadFrames;
        RSDK::Animator dpadAnimator;
        RSDK::Animator dpadTouchAnimator;
        RSDK::Vector2 dpadPos;
        int32 dpadAlpha[PLAYER_COUNT];
        RSDK::Vector2 actionPos;
        int32 jumpAlpha[PLAYER_COUNT];
        RSDK::Vector2 pausePos;
        int32 pauseAlpha[PLAYER_COUNT];
    };

    // ----------------
    // Entity Variables
    // ----------------

    RSDK::StateMachine<SlotHUD> state;
    RSDK::Vector2 ringsPos;
    RSDK::Vector2 lifePos;
    int32 lifeFrameIDs[PLAYER_COUNT];
    int32 lives[PLAYER_COUNT];
    int32 field_a8;
    int32 field_ac;
    int32 ringFlashFrame;
    bool32 enableRingFlash;
    RSDK::Animator hudElementsAnimator;
    RSDK::Animator numbersAnimator;
    RSDK::Animator hyperNumbersAnimator;
    RSDK::Animator lifeIconAnimator;
    RSDK::Animator lifeNamesAnimator;
    RSDK::Animator lifeNumbersAnimator;
    RSDK::Animator playerIDAnimator;
    RSDK::Animator superIconAnimator;
    RSDK::Animator superButtonAnimator;
    RSDK::Animator thumbsUpIconAnimator;
    RSDK::Animator thumbsUpButtonAnimator;
    RSDK::Animator replayClapAnimator;
    RSDK::Animator saveReplayButtonAnimator;
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