#pragma once
#include "GameAPI/Game.hpp"

namespace GameLogic {

struct S3K_SaveMenu : RSDK::GameObject::Entity {

    // ----------------
    // Static Variables
    // ----------------

    struct Static : RSDK::GameObject::Static {
        RSDK::SoundFX sfxButton;
        RSDK::SoundFX sfxSlot;
        RSDK::SoundFX sfxBumper;
        RSDK::SoundFX sfxWarp;
        int32 fl_c;
        int32 timer;
        uint8 deletingSave;
        uint8 transitionScene;
        uint8 isNewSave; // probably wrong actually
        uint8 pad[3];
        uint8 fl_1a;
    };

    struct ModStatic : RSDK::GameObject::Static {
        RSDK::SpriteAnimation aniFrames;
        RSDK::Animator animator;
        uint8 touchDown;
        uint8 backActionPending;
        //
     
        int32 dragTouchX;
        int32 autoButtonMoveVelocity;
        int32 dragTouchDistance;
        int32 lastDragTouchDistance;
        int32 buttonMovePos;
        int32 lastButtonMovePos;
        int32 targetButtonMovePos;

        int32 touchState;

        RSDK::StateMachine<S3K_SaveMenu> stateInput;
    };

    // ----------------
    // Entity Variables
    // ----------------

    RSDK::StateMachine<S3K_SaveMenu> state;
    RSDK::StateMachine<S3K_SaveMenu> stateDraw;
    uint16 fade;
    uint8 gap80[4];
    RSDK::Animator textAnimator;
    RSDK::Animator animator;
    int32 cursorPos;
    uint16 activeSaveSlot;
    RSDK::String menuText;

    // ----------------------
    // Standard Entity Events
    // ----------------------

    void Update();
    void Draw();
    static void StageLoad();
    static void StaticLoad(Static *sVars);

    // -------------
    // Object States
    // -------------

    static RSDK::Action<void> State_Navigate;
    static RSDK::Action<void> State_CursorMove;

    // ----------------------
    // Extra Entity Functions
    // ----------------------

    void Action_Back();
    void Action_DragScreen();
    void Draw_Back();

    void StateInput_HandleDrag();
    void StateInput_HandleMovement();
    void StateInput_Move();

    // -------------------
    // Static Declarations
    // -------------------

    MOD_DECLARE(S3K_SaveMenu)
};

// ----------------------
// Extra Entity Functions
// ----------------------

} // namespace GameLogic