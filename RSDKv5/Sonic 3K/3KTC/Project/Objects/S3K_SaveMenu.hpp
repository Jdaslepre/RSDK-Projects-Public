#pragma once
#include "GameAPI/Game.hpp"

using namespace RSDK;

namespace GameLogic {

struct S3K_SaveMenu : GameObject::Entity {

    // ----------------
    // Static Variables
    // ----------------

    struct Static : GameObject::Static {
        SoundFX sfxButton;
        SoundFX sfxSlot;
        SoundFX sfxBumper;
        SoundFX sfxWarp;
        int32 fl_c;
        int32 timer;
        uint8 deletingSave;
        uint8 transitionScene;
        uint8 isNewSave; // probably wrong actually
        uint8 pad[3];
        uint8 fl_1a;
    };

    struct ModStatic : GameObject::Static {
        SpriteAnimation aniFrames;
        Animator animator;
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

        StateMachine<S3K_SaveMenu> stateInput;
    };

    // ----------------
    // Entity Variables
    // ----------------

    StateMachine<S3K_SaveMenu> state;
    StateMachine<S3K_SaveMenu> stateDraw;
    uint16 fade;
    uint8 gap80[4];
    Animator textAnimator;
    Animator animator;
    FixedPoint cursorPos;
    uint16 activeSaveSlot;
    String menuText;

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

    static Action<void> State_Navigate;
    static Action<void> State_CursorMove;

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