#pragma once
#include "GameAPI/Game.hpp"

using namespace RSDK;

namespace GameLogic {

struct TitleSeq : GameObject::Entity {

    // ---------------
    // Enums & Structs
    // ---------------

    enum OptionTypes { OptionNone = -1, OptionSaveMenu, OptionCompetition, OptionNewBlueSpheres, OptionBlueSpheres, OptionLevelSelect };

    struct CheatStatus {
        union {
            uint64 mask;
            uint8 codes[8];
        } input;
        bool32 active;
    };

    // ----------------
    // Static Variables
    // ----------------

    struct Static : GameObject::Static {
        SoundFX sfxSega;
        SoundFX sfxButton;
        SoundFX sfxFail;
        SoundFX sfxStart;
        SoundFX sfxRing;
        uint16 unused;
        color colors[14];
        int32 timer;
        SceneLayer introLayer;
        int8 sonicIntroFrameTimes[12];
        int32 option;
        bool32 blueSpheresEnabled;
        uint8 matchLevelSelect[8];
        uint8 matchUnknown[7];
        uint8 matchUnknown2[12];
        CheatStatus statusLevelSelect;
        CheatStatus statusUnknown;
        CheatStatus statusUnknown2;
        uint8 seqCountLevelSelect;
        uint8 seqCountUnknown;
        uint8 seqCountUnknown2;
    };

    struct ModStatic : GameObject::Static {
        uint8 touchDown;
        int32 levelSelectCheatPos;
    };

    // ----------------------
    // Standard Entity Events
    // ----------------------

    void Create(void *data);
    static void StaticLoad(Static *sVars);

    // -------------
    // Object States
    // -------------

    static Action<void> State_WaitSEGA;
    static Action<void> State_Animate;
    static Action<void> State_WaitEx;

    // ----------------------
    // Extra Entity Functions
    // ----------------------

    static void CheckTouchCheatCodes(void);

    // -------------------
    // Static Declarations
    // -------------------

    MOD_DECLARE(TitleSeq)
};

// ----------------------
// Extra Entity Functions
// ----------------------

bool32 TitleSeq_State_WaitSEGA_Hook(bool32 skippedState);
bool32 TitleSeq_CheckSkip(bool32 skippedState);

} // namespace GameLogic