#pragma once
#include "3K-Pause.hpp"

GlobalVariables *globals = nullptr;
ModConfig config;

using namespace RSDK;
using namespace GameLogic;

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

    // --------------------
    // Get Public Functions
    // --------------------

    // These functions should NEVER be used without checking if hasTouchControls is true
    PubFuncAssign(Touch::CheckRect, "3K-Touch", "Touch::CheckRect");
    PubFuncAssign(Touch::Control4Dir, "3K-Touch", "Touch::Control4Dir");
    PubFuncAssign(Touch::Control8Dir, "3K-Touch", "Touch::Control8Dir");

    // it's 4:06 AM, this works well enough
    if (!Touch::CheckRect || !Touch::Control4Dir || !Touch::Control8Dir)
        config.hasTouchControls = false;

    // --------------------
    // Set Public Functions
    // --------------------

    // -----------------
    // Get Object States
    // -----------------
    /*
    auto Func1  = Mod::PubFunc("LevelSelect::State_Navigate");
    auto Func2  = Mod::PubFunc("Player::State_Victory");
    auto Func3  = Mod::PubFunc("Player::Input_Gamepad");
    auto Func4  = Mod::PubFunc("S1SS_Player::State_Static");
    auto Func5  = Mod::PubFunc("S3K_SaveMenu::State_Navigate");
    auto Func6  = Mod::PubFunc("S3K_SaveMenu::State_CursorMove");
    auto Func7  = Mod::PubFunc("S3K_SS_Player::Input_Gamepad");
    auto Func8  = Mod::PubFunc("TitleSeq::State_WaitSEGA");
    auto Func9  = Mod::PubFunc("TitleSeq::State_Animate");
    auto Func10 = Mod::PubFunc("TitleSeq::State_WaitEx");

    LevelSelect::State_Navigate.Set(Func1);
    Player::State_Victory.Set(Func2);
    Player::Input_Gamepad.Set(Func3);
    S1SS_Player::State_Static.Set(Func4);
    S3K_SaveMenu::State_Navigate.Set(Func5);
    S3K_SaveMenu::State_CursorMove.Set(Func6);
    S3K_SS_Player::Input_Gamepad.Set(Func7);
    TitleSeq::State_WaitSEGA.Set(Func8);
    TitleSeq::State_Animate.Set(Func9);
    TitleSeq::State_WaitEx.Set(Func10);

    // --------------------
    // Register State Hooks
    // --------------------

    Mod::StateHook<void, LevelSelect>(LevelSelect::State_Navigate, LevelSelect_State_Navigate_Hook, true);
    Mod::StateHook<void, Player>(Player::Input_Gamepad, Player_Input_Gamepad_Hook, true);
    Mod::StateHook<void, S3K_SS_Player>(S3K_SS_Player::Input_Gamepad, S3K_SS_Player_Input_Gamepad_Hook, true);
    Mod::StateHook<void, TitleSeq>(TitleSeq::State_WaitSEGA, TitleSeq_State_WaitSEGA_Hook, true);
    Mod::StateHook<void, TitleSeq>(TitleSeq::State_Animate, TitleSeq_CheckSkip, true);
    Mod::StateHook<void, TitleSeq>(TitleSeq::State_WaitEx, TitleSeq_CheckSkip, true);
    */
}
#endif