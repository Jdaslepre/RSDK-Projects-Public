#pragma once
#include "RSDK-Online.hpp"

namespace GameLogic {

struct MenuSetup : RSDK::GameObject::Entity {

    // ---------------
    // Enums & Structs
    // ---------------

    enum MenuIDs {
        IDMain,
        IDTimeAttack,
        IDCompetition,
        IDSaveSelect,
#if MANIA_USE_PLUS
        IDEncore,
#endif
    };

    // ----------------
    // Static Variables
    // ----------------

    struct Static : RSDK::GameObject::Static {
        int32 unused1;
        bool32 initializedMenuReturn;
        bool32 initializedMenu;
        bool32 initializedAPI;
        bool32 initializedSaves;
        int32 unused2;
        int32 unused3;
        FXFade *fxFade;
#if !MANIA_USE_PLUS
        UIButtonPrompt *delSavePrompt;
        void *mainMenu;
        void *timeAttack;
        void *timeAttackZones;
        void *leaderboards;
        void *leaderboardWidget;
        UIButtonPrompt *leaderboardPrompt;
        UIControl *competition;
        UIControl *competitionRules;
        UIControl *competitionZones;
        UIControl *competitionRound;
        void *roundLabel;
        void *roundScoreboard;
        UIControl *competitionTotal;
        void *totalLabel;
        void *totalScoreboard;
        UIControl *saveSelect;
        UIControl *noSaveMode;
        UIControl *secrets;
        UIControl *extras;
        UIControl *options;
        UIButtonPrompt *optionsPrompt;
        UIControl *video;
        UIControl *video_win;
        UIControl *sound;
        UIControl *controls_win;
        UIControl *controls_KB;
        UIControl *controls_PS4;
        UIControl *controls_XB1;
        UIControl *controls_NX;
        UIControl *controls_NX_Grip;
        UIControl *controls_NX_JoyCon;
        UIControl *controls_NX_Pro;
        UIControl *language;
        int32 unused4;
        int32 unused5;
        int32 vsTotalTimer;
        int32 unused6;
        UIDialog *connectingDlg;
#endif
    };

    struct ModStatic : RSDK::GameObject::Static {};

    // ----------------
    // Entity Variables
    // ----------------

    ManiaStateMachine(state);
    ManiaStateMachine(callback);
    int32 timer;
    int32 delay;
    int32 fadeShift;
    int32 fadeTimer;
    int32 fadeColor;

    // ----------------------
    // Standard Entity Events
    // ----------------------

    void Update();

    // ----------------------
    // Extra Entity Functions
    // ----------------------

    static void SetBGColors();

    // -------------------
    // Static Declarations
    // -------------------

    MOD_DECLARE(MenuSetup)
};

// ----------------
// Public Functions
// ----------------

extern int32 (*MenuSetup_GetActiveMenu)(void);
extern void (*MenuSetup_SetBGColors)(void);

} // namespace GameLogic