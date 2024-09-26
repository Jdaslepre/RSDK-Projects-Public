#include "RSDK-Online.hpp"

using namespace RSDK;

ManiaGlobalVariables *globals = nullptr;
ModConfig config;

using namespace GameLogic;

#if RETRO_USE_MOD_LOADER && GAME_CUSTOMLINKLOGIC
void LinkGameLogic(RSDK::EngineInfo *info) {

    // ---------------------
    // Link Global Variables
    // ---------------------

    globals = (ManiaGlobalVariables *)Mod::GetGlobals();

    // -------------------------
    // Mod Config Initialization
    // -------------------------

    config.host.Init("127.0.0.1");
    Mod::Settings::GetString(Mod::modID, "Network:host", &config.host, "127.0.0.1");

    config.port                  = Mod::Settings::GetInteger(Mod::modID, "Network:port", 50);
    config.useDynamicStateSystem = Mod::Settings::GetBool(Mod::modID, "Config:Dynamic State System", false);

    Mod::Settings::SaveSettings();

    // --------------------
    // Get Public Functions
    // --------------------

    // Cutscene
    PubFuncAssign(FXFade_State_FadeOut, NULL, "FXFade_State_FadeOut");

    // Global
    PubFuncAssign(Music_PlayTrack, NULL, "Music_PlayTrack");
    PubFuncAssign(Music_TransitionTrack, NULL, "Music_TransitionTrack");
    PubFuncAssign(Music_FadeOut, NULL, "Music_FadeOut");

    // Menu
    PubFuncAssign(ManiaModeMenu_StartReturnToTitle, NULL, "ManiaModeMenu_StartReturnToTitle");
    PubFuncAssign(MenuParam_GetParam, NULL, "MenuParam_GetParam");
    PubFuncAssign(MenuSetup_GetActiveMenu, NULL, "MenuSetup_GetActiveMenu");
    PubFuncAssign(MenuSetup_SetBGColors, NULL, "MenuSetup_SetBGColors");
    PubFuncAssign(UIControl_SetActiveMenu, NULL, "UIControl_SetActiveMenu");
    PubFuncAssign(UIControl_GetUIControl, NULL, "UIControl_GetUIControl");
    PubFuncAssign(UIControl_MatchMenuTag, NULL, "UIControl_MatchMenuTag");
    PubFuncAssign(UIDialog_CreateDialogOk, NULL, "UIDialog_CreateDialogOk");
    PubFuncAssign(UITransition_StartTransition, NULL, "UITransition_StartTransition");
    PubFuncAssign(UITransition_State_TransitionOut, NULL, "UITransition_State_TransitionOut");
    PubFuncAssign(UIWidgets_DrawRightTriangle, NULL, "UIWidgets_DrawRightTriangle");

    PlayerManage::GetStates();

    // --------------------
    // Register State Hooks
    // --------------------

    Mod::RegisterStateHook(UITransition_State_TransitionOut, UITransition_State_TransitionOut_Hook, true);

    if (config.useDynamicStateSystem) {
        PlayerManage::RegisterHooks();
    }

    // ----------------------
    // Register Mod Callbacks
    // ----------------------

    Mod::AddModCallback(MODCB_ONUPDATE, Misc::ModUpdateCB);

    // ---------------------
    // Initialize Networking
    // ---------------------

    InitNetwork();
}
#endif