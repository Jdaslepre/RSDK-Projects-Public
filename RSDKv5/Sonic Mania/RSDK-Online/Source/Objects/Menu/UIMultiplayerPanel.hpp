#pragma once
#include "RSDK-Online.hpp"

namespace GameLogic {

struct UIMultiplayerPanel : RSDK::GameObject::Entity {

    // ---------------
    // Enums & Structs
    // ---------------

    enum CodeLabels {
        LabelHostCode,
        LabelWaitingForPlayer,
    };

    // ----------------
    // Static Variables
    // ----------------

    struct Static : RSDK::GameObject::Static {
        RSDK::SpriteAnimation aniFrames;
        RSDK::SoundFX sfxBleep;
        RSDK::SoundFX sfxAccept;
    };

    struct ModStatic : RSDK::GameObject::Static {};

    // ----------------
    // Entity Variables
    // ----------------

    RSDK::StateMachine<UIMultiplayerPanel> state;
    RSDK::StateMachine<UIMultiplayerPanel> stateDraw;
    bool32 initializedDraw;
    RSDK::Animator UIElementAnimator;
    RSDK::Animator RoomCodeAnimator;
    int16 currentSelection;
    uint16 left;
    uint16 right;
    uint16 up;
    uint16 down;
    uint16 start;
    UIText *codeLabel[2];
    void *c;
    UIText *enterCodeLabel[8];
    void *ca[2];
    //
    int32 sendReceieveValue;

    int32 timer;
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
    int32 selectedButton;
    // NativeEntity_TextLabel *codeLabel[3];
    int32 roomCode;
    // NativeEntity_TextLabel *enterCodeLabel[8];
    // NativeEntity_TextLabel *enterCodeSlider[2];

    //

    int32 panelSize;
    int32 topListID;
    int32 topFrameID;
    int32 botListID;
    int32 botFrameID;
    bool32 botAlignRight;
    bool32 botHidden;
    RSDK::Vector2 startPos;
    RSDK::Vector2 size;
    RSDK::Vector2 drawPosTop;
    RSDK::Vector2 drawPosBottom;
    RSDK::Hitbox hitbox;
    RSDK::Animator topAnimator;
    RSDK::Animator botAnimator;
    RSDK::SpriteAnimation textFrames;

    // ----------------------
    // Standard Entity Events
    // ----------------------

    void Create(void *data);
    void Update();
    void Draw();
    static void StageLoad();

    // ----------------------
    // Extra Entity Functions
    // ----------------------

    void InputSetup();
    void TestSelectionRange(int16 max);
    void DrawBackground();
    void DrawRoomCode(int32 v);

    // -------------
    // Object States
    // -------------

    void State_Init();
    void State_Lobby();
    void State_Hosting();
    void State_Joining();

    // ------------------
    // Object Draw States
    // ------------------

    void State_DrawLobby();
    void State_DrawHosting();
    void State_DrawJoining();

    // -------------------
    // Static Declarations
    // -------------------

    MOD_DECLARE(UIMultiplayerPanel)
};

} // namespace GameLogic