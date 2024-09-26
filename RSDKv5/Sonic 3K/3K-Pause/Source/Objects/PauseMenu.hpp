#pragma once
#include "GameAPI/Game.hpp"

namespace GameLogic
{

struct PauseMenu : RSDK::GameObject::Entity {

    enum Buttons {
        MenuUnselected = -1,
        ButtonContinue,
        ButtonRestart,
        ButtonExit = 3,
    };

    // ----------------
    // Static Variables
    // ----------------

    struct Static : RSDK::GameObject::Static {
    };

    struct ModStatic : RSDK::GameObject::Static {
        RSDK::SpriteAnimation aniFrames;
        RSDK::SoundFX sfxBleep;
        RSDK::SoundFX sfxAccept;
        RSDK::SoundFX sfxWoosh;

        bool32 disableEvents;
        bool32 activeChannels[0x10];
    };

    // ----------------
    // Entity Variables
    // ----------------

    RSDK::StateMachine<PauseMenu> state;
    RSDK::StateMachine<PauseMenu> stateDraw;
    RSDK::Animator animator;
    RSDK::Animator selectionAnimator;
    RSDK::Vector2 drawPos;
    RSDK::Vector2 pauseBarPos;

    bool32 physicalControls;

    int32 timer;
    uint8 backgroundAlpha;
    int32 lineX;

    uint8 selectedIndex;

    bool32 disableRestart;
    uint8 triggerPlayer;
    int32 timerThreshold;
    int32 pauseBarHeight;

    //
    int32 up;
    int32 down;
    int32 start;

    // ----------------------
    // Standard Entity Events
    // ----------------------

    void Create(void *data);
    void Draw();
    void Update();
    void LateUpdate();
    static void StaticUpdate();
    static void StageLoad();
    static void StaticLoad(Static *sVars);
    static void Serialize();

    // ----------------------
    // Extra Entity Functions
    // ----------------------

    void DrawPauseRect(int32 y);
    void DrawSpikes();
    void PauseSound();
    void ResumeSound();
    void StopSound();

    void Action_Accept();
    void Action_TouchButton(int32 buttonIndex, int32 y);

    // -------------
    // Object States
    // -------------

    void State_StartPause();
    void State_SlideIn();
    void State_SpritesFadeIn();
    void State_Controls();
    void State_Confirmed();
    void State_ResumeGame();
    void State_ExitLevel();

    // -----------
    // Draw States
    // -----------

    void Draw_Init();
    void Draw_Controls();
    void Draw_Confirmed();
    void Draw_ResumeGame();
    void Draw_ExitLevel();

    // -------------------
    // Static Declarations
    // -------------------

    MOD_DECLARE(PauseMenu)
};
} // namespace GameLogic