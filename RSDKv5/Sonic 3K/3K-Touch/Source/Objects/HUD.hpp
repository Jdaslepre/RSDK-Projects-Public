#pragma once
#include "..\3KTC.hpp"

namespace GameLogic {

struct HUD : RSDK::GameObject::Entity {

    // ---------------
    // Enums & Structs
    // ---------------

    enum OffsetTypes {
        OffsetScore,
        OffsetTime,
        OffsetRings,
        OffsetLife,
    };

    // ----------------
    // Static Variables
    // ----------------

    struct Static : RSDK::GameObject::Static {
        RSDK::SpriteAnimation aniFrames;
        RSDK::SpriteAnimation superButtonFrames;
        RSDK::SoundFX sfxClick;
        RSDK::SoundFX sfxStarpost;
        bool32 showTAPrompt;
        bool32 replaySaveEnabled;
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
        RSDK::Vector2 superPos;
        int32 superAlpha[PLAYER_COUNT];
        RSDK::Vector2 pausePos;
        int32 pauseAlpha[PLAYER_COUNT];
    };

    // ----------------
    // Entity Variables
    // ----------------

    RSDK::StateMachine<HUD> state;
    RSDK::Vector2 scorePos;
    RSDK::Vector2 timePos;
    RSDK::Vector2 ringsPos;
    RSDK::Vector2 lifePos;
    int32 lifeFrameIDs[PLAYER_COUNT];
    int32 lives[PLAYER_COUNT];
    int32 targetPos;
    int32 actionPromptPos;
    RSDK::StateMachine<HUD> vsStates[PLAYER_COUNT];
    RSDK::Vector2 vsScorePos[PLAYER_COUNT];
    RSDK::Vector2 vsTimePos[PLAYER_COUNT];
    RSDK::Vector2 vsRingsPos[PLAYER_COUNT];
    RSDK::Vector2 vsLifePos[PLAYER_COUNT];
    int32 vsTargetPos[PLAYER_COUNT];
    int32 screenID;
    int32 timeFlashFrame;
    int32 ringFlashFrame;
    bool32 enableTimeFlash;
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

    MOD_DECLARE(HUD)
};

// ----------------
// Public Functions
// ----------------

extern void (*HUD_DrawNumbersBase10)(RSDK::Animator *animator, RSDK::Vector2 *drawPos, int32 value, int32 digitCount);
extern void (*HUD_DrawNumbersBase16)(HUD *entity, RSDK::Vector2 *drawPos, int32 value);
extern int32 (*HUD_CharacterIndexFromID)(int32 characterID);

} // namespace GameLogic