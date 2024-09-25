#pragma
#define GAME_TYPE (GAMETYPE_S3)

#include "GameAPI/Game.hpp"

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

enum HUDEnableTypes {
    HUDENABLE_OFF,
    HUDENABLE_ON,
};

#define GET_STOCK_ID(stockNum) (((globals->stock >> (8 * ((stockNum)-1))) & 0xFF))

#include "config.hpp"
#include "extensions.hpp"

#if RETRO_USE_MOD_LOADER
extern "C" {
DLLExport bool32 LinkModLogic(RSDK::EngineInfo *info, const char *modID);
}
#endif

// ------------
// Game Objects
// ------------

// Forward Declarations
namespace GameLogic
{

RSDK_TYPEDEF(Touch);

RSDK_TYPEDEF(Camera);
RSDK_TYPEDEF(DebugMode);
RSDK_TYPEDEF(HUD);
RSDK_TYPEDEF(LevelSelect);
RSDK_TYPEDEF(Player);
RSDK_TYPEDEF(S1SS_Player);
RSDK_TYPEDEF(S3K_SaveMenu);
RSDK_TYPEDEF(S3K_SaveSlot);
RSDK_TYPEDEF(S3K_SS_HUD);
RSDK_TYPEDEF(S3K_SS_Player);
RSDK_TYPEDEF(SlotHUD);
RSDK_TYPEDEF(TitleElement);
RSDK_TYPEDEF(TitleSeq);

} // namespace GameLogic

// Helpers
#include "Touch.hpp"

#include "Objects/Camera.hpp"
#include "Objects/DebugMode.hpp"
#include "Objects/HUD.hpp"
#include "Objects/LevelSelect.hpp"
#include "Objects/Player.hpp"
#include "Objects/S1SS_Player.hpp"
#include "Objects/S3K_SaveMenu.hpp"
#include "Objects/S3K_SaveSlot.hpp"
#include "Objects/S3K_SS_HUD.hpp"
#include "Objects/S3K_SS_Player.hpp"
#include "Objects/SlotHUD.hpp"
#include "Objects/TitleElement.hpp"
#include "Objects/TitleSeq.hpp"