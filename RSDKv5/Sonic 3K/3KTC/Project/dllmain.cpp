#pragma once
#include "3KTC.hpp"

GlobalVariables *globals = nullptr;
ModConfig config;

using namespace RSDK;
using namespace GameLogic;

#if RETRO_USE_MOD_LOADER && GAME_CUSTOMLINKLOGIC
#if RETRO_REV02
void LinkGameLogic(RSDK::EngineInfo *info)
{
    LinkModLogic(info, RSDK::Mod::modID);
#else
void LinkGameLogic(RSDK::EngineInfo info)
{
    LinkModLogic(&info, RSDK::Mod::modID);
#endif

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

    GetPublicFuncAssign(HUD_DrawNumbersBase10, NULL, "HUD::DrawNumbersBase10");
    GetPublicFuncAssign(HUD_DrawNumbersBase16, NULL, "HUD::DrawNumbersBase16");
    GetPublicFuncAssign(HUD_CharacterIndexFromID, NULL, "HUD::CharacterIndexFromID");

    config.usePathTracer = static_cast<bool *>(Mod::GetPublicFunction(0, "usePathTracer"));

    // --------------------
    // Set Public Functions
    // --------------------

    // Add a variable that allows other mods to detect if touch controls are enabled
    // this should be fine to do i think...
    Mod::AddPublicFunction("useTouchControls", INT_TO_VOID(config.useTouchControls));

    // -----------------
    // Get Object States
    // -----------------

    LevelSelect::State_Navigate.Set(Ext::PubFunc<Type_VoidPtr>("LevelSelect::State_Navigate"));
    Player::State_Victory.Set(Ext::PubFunc<Type_VoidPtr>("Player::State_Victory"));
    Player::Input_Gamepad.Set(Ext::PubFunc<Type_VoidPtr>("Player::Input_Gamepad"));
    S1SS_Player::State_Static.Set(Ext::PubFunc<Type_VoidPtr>("S1SS_Player::State_Static"));
    S3K_SaveMenu::State_Navigate.Set(Ext::PubFunc<Type_VoidPtr>("S3K_SaveMenu::State_Navigate"));
    S3K_SaveMenu::State_CursorMove.Set(Ext::PubFunc<Type_VoidPtr>("S3K_SaveMenu::State_CursorMove"));
    S3K_SS_Player::Input_Gamepad.Set(Ext::PubFunc<Type_VoidPtr>("S3K_SS_Player::Input_Gamepad"));
    TitleSeq::State_WaitSEGA.Set(Ext::PubFunc<Type_VoidPtr>("TitleSeq::State_WaitSEGA"));
    TitleSeq::State_Animate.Set(Ext::PubFunc<Type_VoidPtr>("TitleSeq::State_Animate"));
    TitleSeq::State_WaitEx.Set(Ext::PubFunc<Type_VoidPtr>("TitleSeq::State_WaitEx"));

    // --------------------
    // Register State Hooks
    // --------------------

    Ext::StateHook<void, LevelSelect>(LevelSelect::State_Navigate, LevelSelect_State_Navigate_Hook, true);
    Ext::StateHook<void, Player>(Player::Input_Gamepad, Player_Input_Gamepad_Hook, true);
    Ext::StateHook<void, S3K_SS_Player>(S3K_SS_Player::Input_Gamepad, S3K_SS_Player_Input_Gamepad_Hook, true);
    Ext::StateHook<void, TitleSeq>(TitleSeq::State_WaitSEGA, TitleSeq_State_WaitSEGA_Hook, true);
    Ext::StateHook<void, TitleSeq>(TitleSeq::State_Animate, TitleSeq_CheckSkip, true);
    Ext::StateHook<void, TitleSeq>(TitleSeq::State_WaitEx, TitleSeq_CheckSkip, true);

    // add kapukapu input states for player - 8/2/24
}

#endif