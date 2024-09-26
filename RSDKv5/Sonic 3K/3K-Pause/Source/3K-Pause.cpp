#pragma once
#include "3K-Pause.hpp"

GlobalVariables *globals = nullptr;
ModConfig config;

using namespace RSDK;
using namespace GameLogic;

void CheckTouchEnabledCB(void *);

#if RETRO_USE_MOD_LOADER && GAME_CUSTOMLINKLOGIC
void LinkGameLogic(RSDK::EngineInfo *info)
{
    // ---------------------
    // Link Global Variables
    // ---------------------

    globals = (GlobalVariables *)Mod::GetGlobals();

    // -------------------------
    // Mod Config Initialization
    // -------------------------

    Mod::List::LoadModInfo("3K-Touch", NULL, NULL, NULL, &config.hasTouchControls);

    // ----------------------
    // Register Mod Callbacks
    // ----------------------

    Mod::AddModCallback(MODCB_ONSTAGELOAD, CheckTouchEnabledCB);
}

// it's 4:06 AM, this works well enough
void CheckTouchEnabledCB(void *)
{
    // This is a bit strange... but I wanted to make this in a way that it just 
    // works regardless of mod order, so let's just get the functions on StageLoad :D

    // These functions should NEVER be used without checking if hasTouchControls is true

    if (!Touch::CheckRect)
        PubFuncAssign(Touch::CheckRect, "3K-Touch", "Touch::CheckRect");

    if (!Touch::Control4Dir)
        PubFuncAssign(Touch::Control4Dir, "3K-Touch", "Touch::Control4Dir");

    if (!Touch::Control8Dir)
        PubFuncAssign(Touch::Control8Dir, "3K-Touch", "Touch::Control8Dir");

    if (!Touch::CheckRect || !Touch::Control4Dir || !Touch::Control8Dir)
        config.hasTouchControls = false;
}
#endif