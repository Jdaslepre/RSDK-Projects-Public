#pragma once
#include "RSDK-Online.hpp"

namespace GameLogic {

struct MultiplayerMenu : RSDK::GameObject::Entity {

    // ---------------
    // Enums & Structs
    // ---------------

    // ----------------
    // Static Variables
    // ----------------

    struct Static : RSDK::GameObject::Static {
        UIControl *pselControl;
        UIControl *pselControl_Legacy;
        UIControl *lobbyControl;
        UIControl *multiplayerControl;
        bool32 isMenuActive;
    };

    struct ModStatic : RSDK::GameObject::Static {};

    // ----------------
    // Entity Variables
    // ----------------

    RSDK::StateMachine<MultiplayerMenu> state;
    RSDK::StateMachine<MultiplayerMenu> stateNext;
    RSDK::StateMachine<MultiplayerMenu> stateDraw;
    RSDK::StateMachine<MultiplayerMenu> stateDrawNext;
    float timer;
    float scale;
    // NativeEntity_MenuBG *bg;
    // NativeEntity_TextLabel *label;
    // NativeEntity_DialogPanel *dialog;
    // MeshInfo *meshPanel;
    // MeshAnimator animator;
    // MatrixF renderMatrix;
    // MatrixF matrixTemp;
    // MatrixF matrix3;
    // byte textureArrows;
    uint8 backPressed;
    int32 arrowAlpha;
    int8 touchedUpID;
    int8 touchedDownID;
    // NativeEntity_PushButton *buttons[MULTIPLAYERSCREEN_BUTTON_COUNT];
    int32 selectedButton;
    uint8 flipDir;
    float rotationY;
    // NativeEntity_TextLabel *codeLabel[3];
    int32 roomCode;
    // NativeEntity_TextLabel *enterCodeLabel[8];
    // NativeEntity_TextLabel *enterCodeSlider[2];

    // ----------------------
    // Standard Entity Events
    // ----------------------

    void Create(void *data);
    void Update();
    static void StaticUpdate();
    static void StageLoad();

    // ----------------------
    // Extra Entity Functions
    // ----------------------

    // Callbacks
    static void OpenPlayerSelect_CB();
    static void OpenLobby_CB();
    static void CharButton_ActionCB();

    static void Initialize();
    void StartOrExit();

    // -------------
    // Object States
    // -------------

    void State_Enter();
    void State_Main();
    void State_Action();
    void State_Exit();
    void State_Flip(); // remove?
    void State_HostScr();
    void State_JoinScr();
    void State_StartGame();
    void State_DialogWait();

    // -------------------
    // Static Declarations
    // -------------------

    RSDK_DECLARE(MultiplayerMenu)
};

} // namespace GameLogic