#pragma once
#include "GameAPI/Game.hpp"

using namespace RSDK;

namespace GameLogic {

struct LevelSelect : GameObject::Entity {

    // ---------------
    // Enums & Structs
    // ---------------

    enum DPadFrameIDs {
        // Up
        DpadUp,
        DpadUpPressed,
        // Down
        DpadDown,
        DpadDownPressed,
        // Left
        DpadLeft,
        DpadLeftPressed,
        // Right
        DpadRight,
        DpadRightPressed,
    };

    enum ButtonFrameIDs {
        ButtonGo,
        ButtonPlay,
        ButtonGoDown,
        ButtonPlayDown,
    };

    // ----------------
    // Static Variables
    // ----------------

    struct Static : GameObject::Static {
        int32 bgAniDuration;
        int32 bgAniDurationTable[4];
        int32 cheat_RickyMode[9];
        int32 cheat_AllEmeralds[5];
        int32 cheat_MaxContinues[9];
        int32 cheat_SwapGameMode[9];
        int32 cheat_UnlockAllMedals[9];
        int32 cheat_SuperDash[9];
        int32 cheat_MaxControl[5];
        int32 cheat_ToggleSuperMusic[9];
        int32 bgAniFrame;
        int32 startMusicID;
        int32 soundTestMax;
        SoundFX sfxFail;
        SoundFX sfxRing;
        SoundFX sfxEmerald;
        SoundFX sfxContinue;
        SoundFX sfxMedalCaught;
        SoundFX sfxHotlineBusy;
        SoundFX sfxLoseRings;
        int32 *cheatCodePtrs[8];
        int32 cheatCodePos[8];
        void (*checkCheatActivated[8])();
    };

    struct ModStatic : GameObject::Static {
        SpriteAnimation aniFrames;
        Animator animator;
        uint8 pressed;
        uint8 pressedLR;
    };

    // ----------------
    // Entity Variables
    // ----------------

    // this stuff is most likely inaccurate to Sonic 3 Origins
    // these variables come from S3KT
    // i'll verify this soon

    StateMachine<LevelSelect> state;
    StateMachine<LevelSelect> stateDraw;
    int32 timer;
    int32 labelID;
    int32 soundTestID;
    int32 leaderCharacterID;
    int32 sidekickCharacterID;
    void *zoneNameLabels[64];
    void *stageIDLabels[64];
    void *soundTestLabel;
    void *zoneIcon;
    void *player1Icon;
    void *player2Icon;
    void *pinballLabel;
    int32 labelCount;
    int32 offsetUFO;
    int32 offsetBSS;
    int32 unused1;
    int32 unused2;
    int32 unused3;
    int32 unused4;

    // ----------------------
    // Standard Entity Events
    // ----------------------

    void Draw(void);
    static void StageLoad(void);
    static void StaticLoad(Static *sVars);

    // -------------
    // Object States
    // -------------

    static Action<void> State_Navigate;

    // -------------------
    // Static Declarations
    // -------------------

    MOD_DECLARE(LevelSelect)
};

// ----------------------
// Extra Entity Functions
// ----------------------

bool32 LevelSelect_State_Navigate_Hook(bool32 skippedState);

} // namespace GameLogic