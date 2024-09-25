#pragma once
#include "GameAPI/Game.hpp"

using namespace RSDK;

namespace GameLogic {

struct HUD : GameObject::Entity {

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

    struct Static : GameObject::Static {
        SpriteAnimation aniFrames;
        SpriteAnimation superButtonFrames;
        SoundFX sfxClick;
        SoundFX sfxStarpost;
        bool32 showTAPrompt;
        bool32 replaySaveEnabled;
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
        Vector2 superPos;
        int32 superAlpha[PLAYER_COUNT];
        Vector2 pausePos;
        int32 pauseAlpha[PLAYER_COUNT];
    };

    // ----------------
    // Entity Variables
    // ----------------

    StateMachine<HUD> state;
    Vector2 scorePos;
    Vector2 timePos;
    Vector2 ringsPos;
    Vector2 lifePos;
    int32 lifeFrameIDs[PLAYER_COUNT];
    int32 lives[PLAYER_COUNT];
    int32 targetPos;
    int32 actionPromptPos;
    StateMachine<HUD> vsStates[PLAYER_COUNT];
    Vector2 vsScorePos[PLAYER_COUNT];
    Vector2 vsTimePos[PLAYER_COUNT];
    Vector2 vsRingsPos[PLAYER_COUNT];
    Vector2 vsLifePos[PLAYER_COUNT];
    int32 vsTargetPos[PLAYER_COUNT];
    int32 screenID;
    int32 timeFlashFrame;
    int32 ringFlashFrame;
    bool32 enableTimeFlash;
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

    MOD_DECLARE(HUD)
};

// ----------------
// Public Functions
// ----------------

extern void (*HUD_DrawNumbersBase10)(Animator *animator, Vector2 *drawPos, int32 value, int32 digitCount);
extern void (*HUD_DrawNumbersBase16)(HUD *entity, Vector2 *drawPos, int32 value);
extern int32 (*HUD_CharacterIndexFromID)(int32 characterID);

} // namespace GameLogic