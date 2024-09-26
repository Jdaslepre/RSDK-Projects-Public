#pragma once
#include "RSDK-Online.hpp"

// ------------------
// Macros/Definitions
// ------------------

#define UIDIALOG_OPTION_COUNT (3)

namespace GameLogic {

struct UIDialog : RSDK::GameObject::Entity {

    // ---------------
    // Enums & Structs
    // ---------------

    enum Options {
        OptionYes,
        OptionNo,
        OptionOK,
        OptionCancel,
        OptionContinue,
    };

    // ----------------
    // Static Variables
    // ----------------

    struct Static : RSDK::GameObject::Static {
        UIDialog *activeDialog;
        UIControl *controlStore;
        ManiaStateMachine(controlStateStore);
    };

    struct ModStatic : RSDK::GameObject::Static {};

    // ----------------
    // Entity Variables
    // ----------------

    ManiaStateMachine(state);
    int32 timer;
    int32 closeDelay;
    RSDK::String textInfo;
    int32 buttonCount;
    RSDK::Vector2 bgRectSize;
    RSDK::Vector2 dialogPos;
    UIControl *parent;
    RSDK::GameObject::Entity *entityPtr;
    uint8 buttonFrames[UIDIALOG_OPTION_COUNT];
    ManiaStateMachine(callbacks[UIDIALOG_OPTION_COUNT]);
    bool32 closeOnSelect[UIDIALOG_OPTION_COUNT];
    UIButton *buttons[UIDIALOG_OPTION_COUNT];
    ManiaStateMachine(closeCB);
    bool32 playEventSfx;
    bool32 useAltColor;
    int32 lineLength[3];
    int32 lineCount;
    RSDK::Animator animator;

    // -------------------
    // Static Declarations
    // -------------------

    MOD_DECLARE(UIDialog)
};

// ----------------
// Public Functions
// ----------------

extern UIDialog *(*UIDialog_CreateDialogOk)(RSDK::String *text, void (*callback)(void), bool32 closeOnSelect);

} // namespace GameLogic