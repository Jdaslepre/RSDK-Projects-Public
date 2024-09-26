#pragma once
#include "3KTC.hpp"

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

    config.vDPadSize     = Mod::Settings::GetFloat("", "Config:vDPadSize", 1.0);
    config.vDPadOpacity  = Mod::Settings::GetFloat("", "Config:vDPadOpacity", .625);
    config.moveDPadPos.x = Mod::Settings::GetInteger("", "Config:moveDPadPosX", 56);
    config.moveDPadPos.y = Mod::Settings::GetInteger("", "Config:moveDPadPosY", 184);
    config.jumpDPadPos.x = Mod::Settings::GetInteger("", "Config:jumpDPadPosX", -56);
    config.jumpDPadPos.y = Mod::Settings::GetInteger("", "Config:jumpDPadPosY", 188);

    Mod::Settings::SetFloat("Config:vDPadSize", config.vDPadSize);
    Mod::Settings::SetFloat("Config:vDPadOpacity", config.vDPadOpacity);
    Mod::Settings::SetInteger("Config:moveDPadPosX", config.moveDPadPos.x);
    Mod::Settings::SetInteger("Config:moveDPadPosY", config.moveDPadPos.y);
    Mod::Settings::SetInteger("Config:jumpDPadPosX", config.jumpDPadPos.x);
    Mod::Settings::SetInteger("Config:jumpDPadPosY", config.jumpDPadPos.y);
    Mod::Settings::SaveSettings();

    // --------------------
    // Get Public Functions
    // --------------------

    PubFuncAssign(HUD_DrawNumbersBase10, NULL, "HUD::DrawNumbersBase10");
    PubFuncAssign(HUD_DrawNumbersBase16, NULL, "HUD::DrawNumbersBase16");
    PubFuncAssign(HUD_CharacterIndexFromID, NULL, "HUD::CharacterIndexFromID");
    PubFuncAssign(Player_CheckValidState, NULL, "Player::CheckValidState");

    config.usePathTracer = static_cast<bool *>(Mod::GetPublicFunction(0, "usePathTracer"));

    // --------------------
    // Set Public Functions
    // --------------------

    // Add a variable that allows other mods to detect if touch controls are enabled
    // this should be fine to do i think...
    Mod::AddPublicFunction("useTouchControls", INT_TO_VOID(config.useTouchControls));

    ADD_PUBLIC_FUNC(Touch::CheckRect);
    ADD_PUBLIC_FUNC(Touch::Control4Dir);
    ADD_PUBLIC_FUNC(Touch::Control8Dir);

    // -----------------
    // Get Object States
    // -----------------

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

    // add kapukapu input states for player - 8/2/24
}
#endif