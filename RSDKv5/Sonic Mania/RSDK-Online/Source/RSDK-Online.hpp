#pragma once
#include "GameAPI/Game.hpp"

// -------------
// Configuration
// -------------

#define GAME_TYPE (GAMETYPE_MANIA)

struct ModConfig {
    RSDK::String host;
    int32 port;
    bool32 useDynamicStateSystem;
};
extern ModConfig config;

// ----------------
// Global Variables
// ----------------

struct ManiaGlobalVariables;
extern ManiaGlobalVariables *globals;

// ---------------------
// RSDKv5 ModAPI Helpers
// ---------------------

namespace RSDK {
namespace Mod {

// Essentially just an alias for Mod::GetPublicFunction
inline static auto PubFunc(const char *id, const char *functionName) { return (void (*)(void))Mod::GetPublicFunction(id, functionName); }
inline static auto PubFunc(const char *functionName) { return (void (*)(void))Mod::GetPublicFunction(NULL, functionName); }
template <typename T> inline static T PubFunc(const char *id, const char *functionName) { return (T)Mod::GetPublicFunction(id, functionName); }
template <typename T> inline static T PubFunc(const char *functionName) { return (T)Mod::GetPublicFunction(NULL, functionName); }

// Using T::SomeFunction as a state
template <typename T, typename X> inline void StateHook(T(X::*state), bool32 (*hook)(bool32 skippedState), bool32 priority) {
    modTable->RegisterStateHook(reinterpret_cast<void (*&)()>(state), hook, priority);
}

/*
// Using an RSDK::Action as a state
template <typename T, typename X> inline void StateHook(RSDK::Action<T> &state, bool32 (*hook)(bool32 skippedState), bool32 priority)
{
    modTable->RegisterStateHook(reinterpret_cast<void (*&)()>(state.action), hook, priority);
}
*/

} // namespace Mod
} // namespace RSDK

// Gets a function via specified name - and assigns the result to the pointer
#define PubFuncAssign(ptr, id, functionName) ptr = (decltype(ptr))Mod::GetPublicFunction(id, functionName)

// Gets a function via pointer's name - and assigns the result to said pointer
#define PubFuncAuto(id, ptr) ptr = (decltype(ptr))Mod::GetPublicFunction(id, #ptr)

// ------------
// Mania Extras
// ------------

#define ManiaStateMachine(name) void (*name)(void)
#if RETRO_USE_MOD_LOADER
#define StateMachine_Run(state) modTable->StateMachineRun(state)
#else
#define StateMachine_Run(state)                                                                                                                      \
    if (state) {                                                                                                                                     \
        state();                                                                                                                                     \
    }
#endif

struct ManiaUIEntity : RSDK::GameObject::Entity {
    ManiaStateMachine(state);
    void (*processButtonCB)(void);
    bool32 (*touchCB)(void);
    void (*actionCB)(void);
    void (*selectedCB)(void);
    void (*failCB)(void);
    void (*buttonEnterCB)(void);
    void (*buttonLeaveCB)(void);
    bool32 (*checkButtonEnterCB)(void);
    bool32 (*checkSelectedCB)(void);
    int32 timer;
    RSDK::Vector2 startPos;
    RSDK::GameObject::Entity *parent;
    RSDK::Vector2 touchPosSizeS;
    RSDK::Vector2 touchPosOffsetS;
    bool32 touchPressed;
    RSDK::Vector2 touchPosSizeM[4];   /*size of the touchPos: in 16-bit shifted format*/
    RSDK::Vector2 touchPosOffsetM[4]; /*offset of the touchPos: 0,0 is entity pos, negative is left/up, positive is right/down*/
    void (*touchPosCallbacks[4])(void);
    int32 touchPosCount;
    int32 touchPosID;
    bool32 isSelected;
    bool32 disabled;
};

// ---------------------
// RSDK-Online Mod Logic
// ---------------------

// forward declare
struct Misc;
struct MultiplayerData;

namespace GameLogic {

// Objects/Cutscene
struct FXFade;

// Objects/Global
struct Music;
struct Player;

// Objects/Menu
struct ManiaModeMenu;
struct MenuParam;
struct MenuSetup;
struct MultiplayerMenu;
struct UIBackground;
struct UIButton;
struct UIButtonPrompt;
struct UICarousel;
struct UICharButton;
struct UIControl;
struct UIDialog;
struct UIDiorama;
struct UIHeading;
struct UIMultiplayerPanel;
struct UIShifter;
struct UIText;
struct UITransition;
struct UIWidgets;

// Objects/NMMenu
struct NM_MenuSetup;

struct MainMenu;
struct MultiplayerHandler;

struct Camera;
struct HUD;

}

// include the actual code
#include "Networking/Misc.hpp"
#include "Networking/Networking.hpp"
#include "Networking/UserData.hpp"

#include "Objects/Cutscene/FXFade.hpp"

#include "Objects/Global/Music.hpp"
#include "Objects/Global/Player.hpp"
#include "Objects/Global/PlayerManage.hpp"

#include "Objects/Menu/ManiaModeMenu.hpp"
#include "Objects/Menu/MenuParam.hpp"
#include "Objects/Menu/MenuSetup.hpp"
#include "Objects/Menu/MultiplayerMenu.hpp"
#include "Objects/Menu/UIBackground.hpp"
#include "Objects/Menu/UIButton.hpp"
#include "Objects/Menu/UIButtonPrompt.hpp"
#include "Objects/Menu/UICarousel.hpp"
#include "Objects/Menu/UICharButton.hpp"
#include "Objects/Menu/UIControl.hpp"
#include "Objects/Menu/UIDialog.hpp"
#include "Objects/Menu/UIDiorama.hpp"
#include "Objects/Menu/UIHeading.hpp"
#include "Objects/Menu/UIMultiplayerPanel.hpp"
#include "Objects/Menu/UIShifter.hpp"
#include "Objects/Menu/UIText.hpp"
#include "Objects/Menu/UITransition.hpp"
#include "Objects/Menu/UIWidgets.hpp"

#include "Objects/NMMenu/NM_MenuSetup.hpp"

#include "Objects/MainMenu.hpp"
#include "Objects/MultiplayerHandler.hpp"

#include "Objects/Camera.hpp"
#include "Objects/HUD.hpp"