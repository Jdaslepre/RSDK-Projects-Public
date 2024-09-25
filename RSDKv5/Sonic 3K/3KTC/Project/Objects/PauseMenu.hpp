#pragma once
#include "GameAPI/Game.hpp"

using namespace RSDK;

namespace GameLogic
{

struct PauseMenu : RSDK::GameObject::Entity {

    // Enums & Structs
    enum PauseMenuStates {
        PAUSEMENU_START_PAUSE,
        PAUSEMENU_SLIDE_IN,
        PAUSEMENU_SPRITES_FADE_IN,
        PAUSEMENU_CONTROLS,
        PAUSEMENU_CONFIRMED,
        PAUSEMENU_RESUME_GAME,
        PAUSEMENU_EXIT_LEVEL,
    };

    // Object/Static Vars
    struct Static : RSDK::GameObject::Static {

    };

    struct ModStatic : GameObject::Static {
        SoundFX sfxBleep;
        SoundFX sfxAccept;
        SoundFX sfxWoosh;
        bool32 disableEvents;

        bool32 activeChannels[0x10];
        SpriteAnimation aniFrames;
    };

    // Entity Vars
    StateMachine<PauseMenu> state;
    // StateMachine<PauseMenu> stateDraw;

    ControllerState *controller;

    // yes this will be sorted

    int32 backgroundAlpha;

    int32 timer;

    uint8 triggerPlayer;
    bool32 disableRestart;

    int32 paused;
    int32 fadeTimer;
    bool32 (*disconnectCheck)();
    int32 forcePaused;
    Animator animator;
    Animator plrSelectorAnimator;

    int32 temp0;
    int32 temp1;
    int32 temp2;

    int32 stateDraw;
    Vector2 spikePos;
    int32 animationTimer;

    int32 timerThreshold;
    int32 selectedButton;
    int32 spritesXPos;
    Vector2 blackBarPos;
    Vector2 drawPos;
    int32 blackBarHeight;
    int32 blockRestart;

    // Standard Entity Events
    void Create(void *data);
    void Draw();
    void Update();
    void LateUpdate();
    static void StaticUpdate();
    static void StageLoad();
    static void StaticLoad(Static *sVars);
    static void Serialize();

#if RETRO_INCLUDE_EDITOR
    static void EditorLoad();
    void EditorDraw();
#endif

    // Extra Entity Functions
    void PauseSound();
    void ResumeSound();
    void StopSound();

    // States
    void State_StartPause();
    void State_SlideIn();
    void State_SpritesFadeIn();
    void State_Controls();
    void State_Confirmed();
    void State_ResumeGame();
    void State_ExitLevel();

    // Draw States
    void Draw_SpritesFadeIn();
    void Draw_Controls();
    void Draw_Confirmed();
    void Draw_ResumeGame();
    void Draw_ExitLevel();

    MOD_DECLARE(PauseMenu)
};
} // namespace GameLogic