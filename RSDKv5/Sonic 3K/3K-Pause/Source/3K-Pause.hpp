#pragma once
#define GAME_TYPE (2)

#include "GameAPI/Game.hpp"

// -------------
// Configuration
// -------------

struct ModConfig {
    bool32 hasTouchControls;
    bool32 forceTouchControls;
};

extern ModConfig config;

// ----------------
// Global Variables
// ----------------

// forward declare
struct GlobalVariables;

extern GlobalVariables *globals;

struct GlobalVariables {
    struct Constructor {
        Constructor() { RegisterGlobals((void **)&globals, sizeof(GlobalVariables), &GlobalVariables::Init); }
    };

    static Constructor c;

#if RETRO_REV0U
    static void Init(void *g);
#endif

    uint8 gameMode;
    int32 playerID;
    int32 specialCleared;
    int32 specialRingID;
    int32 blueSpheresID;
    int32 blueSpheresInit;
    int32 atlEnabled;
    int32 atlEntityCount;
#if GAME_VERSION == VER_104
    int32 atlEntitySlot[0x120];
    void *atlEntityData[0x120 * 0x114];
#else
    int32 atlEntitySlot[0x20];
    int32 atlEntityData[0x20 * 0x400];
#endif
    int32 saveLoaded;
    int32 saveRAM[0x1C00];
    int32 saveSlotID;
    int32 noSaveSlot[0x100];
    int32 menuParam[0x4000];
    int32 itemMode;
    bool32 suppressTitlecard;
    bool32 suppressAutoMusic;
    int32 competitionSession[0x4000];
    int32 medalMods;
    int32 parallaxOffset[0x100];
    int32 enableIntro;
    int32 optionsLoaded;
    int32 optionsRAM[0x80];
    int32 presenceID;
    int32 medallionDebug;
    int32 noSave;
    int32 notifiedAutosave;
    int32 recallEntities;
    int32 restartRings;
    int32 restart1UP;
    int32 restartPowerups;
    RSDK::Vector2 restartPos[4];
    int32 restartSlot[4];
    int32 restartDir[4];
    int32 restartMinutes;
    int32 restartSeconds;
    int32 restartMilliseconds;
    int32 restartScore;
    int32 restartScore1UP;
    int32 restartLives[4];
    int32 restartMusicID;
    bool32 restartFlags;
    int32 unkn_C334C;
    int32 showExtendedTimeHUD;
    int32 overrideRestart;
    int32 overrideUnknown;
    RSDK::Vector2 overrideRestartPos[PLAYER_COUNT];
    int32 overrideRestartSlot[PLAYER_COUNT];
    int32 overrideRestartDir[PLAYER_COUNT];
    int32 overrideRestartMinutes;
    int32 overrideRestartSeconds;
    int32 overrideRestartMilliseconds;
    int32 tempMinutes;
    int32 tempSeconds;
    int32 tempMilliseconds;
    int32 persistentTimer;
    int32 tempFlags;
    int32 continues;
    bool32 initCoolBonus;
    int32 coolBonus[PLAYER_COUNT];
    int32 replayWriteBuffer[0x40000];
    int32 replayReadBuffer[0x40000];
    int32 replayTempWBuffer[0x40000];
    int32 replayTempRBuffer[0x40000];
    int32 replayTableID;
    int32 replayTableLoaded;
    int32 taTableID;
    int32 taTableLoaded;
    int32 stock;
    int32 characterFlags;
    bool32 vapeMode;
    int32 secrets;
    int32 unk_4C33F4;
    bool32 soundTestEnabled;
    bool32 superMusicEnabled;
    int32 playerSpriteStyle;
    int32 gameSpriteStyle;
    int32 ostStyle;
    int32 starpostStyle;
    bool32 stageFinished;
    int32 field_447C14;
    int32 storedOverrideUnknown;
    int32 atlCameraBoundsL[PLAYER_COUNT];
    int32 atlCameraBoundsR[PLAYER_COUNT];
    int32 atlCameraBoundsT[PLAYER_COUNT];
    int32 atlCameraBoundsB[PLAYER_COUNT];
    RSDK::Vector2 atlCameraPos[PLAYER_COUNT];
    RSDK::Vector2 atlOffset;
    int32 unknownValues[4];
    int32 unknownValues2[4];
    int32 field_447CA4;
    bool32 tileCollisionMode;
    uint8 gravityDir;
    uint8 blueSpheresSeed[4];
    bool32 blueSpheresHasPerfect;
    int32 field_447CB8; // blueSpheresLevel?
    int32 field_447CBC;
    int32 field_447CC0;
    int32 field_447CC4;
    int32 field_447CC8;
    uint8 field_447CCC;
    int32 field_447CD0;
    bool32 disableLives;
    int32 mirrorMode;
    int32 useManiaBehavior;
    int32 coinCount;
    bool32 showHUD;
    bool32 somethingRelatedToLives;
    uint8 gap4C34DC[34];
    bool32 hasPlusDLC;
    bool32 playMode;
    int32 callbackParam0;
    int32 callbackParam1;
    int32 callbackParam2;
    int32 callbackParam3;
    bool32 hudEnable;
    bool32 useCoins;
    bool32 forceKillPlayer;
    int32 missionCondition;
    int32 missionFunctionNo;
    int32 missionValue;
    int32 missionEnd;
    int32 continueFlag;
    bool32 skipSaveSelect;
    int32 unkn_447D40;
    bool32 bossOneLife;
    int32 unkn_447D48;
    int32 callbackResult;
    bool32 skipTitleIntro;
    bool32 allowRetries;
    bool32 clearBlueSpheres;
    int32 unkn_4C3564;
    int32 unkn_4C3568;
    int32 unkn_4C356C;
    int32 unkn_4C3570;
    int32 unkn_4C3574;
    int32 statsParam7;
    int32 statsParam8;
    int32 statsParam2;
    int32 unkn_4C3584;
    int32 unkn_4C3588;
    bool32 waitSSRetry;
};

// ---------------------
// RSDKv5 ModAPI Helpers
// ---------------------

namespace RSDK
{

template <typename R> struct Action {

    R (Action::*action)();

    inline void Init() { action = nullptr; }

    template <typename T> inline bool Set(R (T::*action)())
    {
        // converts from T:: -> Action:: without the compiler interfering :]
        union {
            R (T::*in)();
            R (Action::*out)();
        };
        in = action;

        this->action = out;
        return true;
    }

    inline bool Set(R (*action)())
    {
        // converts from T:: -> Action:: without the compiler interfering :]
        union {
            R (*in)();
            R (Action::*out)();
        };
        in = action;

        this->action = out;
        return true;
    }

    template <typename T> inline R SetAndRun(R (T::*action)(), void *self = nullptr)
    {
        bool applied = Set(action);

        if (applied)
            return Run(self);

        return R();
    }

    template <typename T> inline R SetAndRun(R (*action)(), void *self = nullptr)
    {
        bool applied = Set(action);

        if (applied)
            return Run(self);

        return R();
    }

    inline R Run(void *self)
    {
        if (action) {
            return (((Action *)self)->*action)();
        }

        return R();
    }

    template <typename T> inline bool Matches(void *other)
    {
        // converts from Action:: -> void (*)() without the compiler interfering :]
        union {
            R *in;
            R (Action::*out)();
        };
        in = other;

        return action == out;
    }

    template <typename T> inline bool Matches(R (T::*other)()) { return action == (R(Action::*)())other; }

    inline bool Matches(Action *other)
    {
        if (other == nullptr)
            return action == nullptr;
        else
            return action == other->action;
    }

    inline void Copy(Action *other)
    {
        if (other == nullptr)
            this->action = nullptr;
        else
            this->action = other->action;
    }

    // Equals
    inline void operator=(const Action &rhs) { this->Copy((Action *)&rhs); }

    // Conditionals
    inline bool operator==(const Action &rhs) { return this->Matches((Action *)&rhs); }
    inline bool operator!=(const Action &rhs) { return !(*this == rhs); }
};

namespace Mod
{

// Essentially just an alias for Mod::GetPublicFunction
inline static auto PubFunc(const char *id, const char *functionName) { return (void (*)(void))Mod::GetPublicFunction(id, functionName); }
inline static auto PubFunc(const char *functionName) { return (void (*)(void))Mod::GetPublicFunction(NULL, functionName); }
template <typename T> inline static T PubFunc(const char *id, const char *functionName) { return (T)Mod::GetPublicFunction(id, functionName); }
template <typename T> inline static T PubFunc(const char *functionName) { return (T)Mod::GetPublicFunction(NULL, functionName); }

// Using T::SomeFunction as a state
template <typename T, typename X> inline void StateHook(T(X::*state), bool32 (*hook)(bool32 skippedState), bool32 priority)
{
    modTable->RegisterStateHook(reinterpret_cast<void (*&)()>(state), hook, priority);
}

// Using an RSDK::Action as a state
template <typename T, typename X> inline void StateHook(RSDK::Action<T> &state, bool32 (*hook)(bool32 skippedState), bool32 priority)
{
    modTable->RegisterStateHook(reinterpret_cast<void (*&)()>(state.action), hook, priority);
}

} // namespace Mod
} // namespace RSDK

// Gets a function via specified name - and assigns the result to the pointer
#define PubFuncAssign(ptr, id, functionName) ptr = (decltype(ptr))Mod::GetPublicFunction(id, functionName)

// Gets a function via pointer's name - and assigns the result to said pointer
#define PubFuncAuto(id, ptr) ptr = (decltype(ptr))Mod::GetPublicFunction(id, #ptr)

#define ManiaStateMachine(name) void (*name)(void)
#define Type_StateMachine       void (*)(void)

// ---------------
// Sonic 3K Extras
// ---------------

enum HUDEnableTypes {
    HUDENABLE_OFF,
    HUDENABLE_ON,
};

#define GET_STOCK_ID(stockNum) (((globals->stock >> (8 * ((stockNum)-1))) & 0xFF))

// ------------------
// 3K-Pause Mod Logic
// ------------------

namespace GameLogic
{
struct PauseMenu;
struct Player;
} // namespace GameLogic

#include "Objects/PauseMenu.hpp"
#include "Objects/Player.hpp"