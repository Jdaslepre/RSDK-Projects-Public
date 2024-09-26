#pragma once
#include "RSDK-Online.hpp"

namespace GameLogic {

struct UIButtonPrompt : RSDK::GameObject::Entity {

    // ---------------
    // Enums & Structs
    // ---------------

    enum Types {
        TypeNone,
        TypeKeyboard,
        TypeXbox,
        TypePS4,
        TypeSwitch,
        TypeSaturnBlack,
        TypeSaturnWhite,
        TypeJoyconL,
        TypeJoyconR,
        TypeKeyboardFR,
        TypeKeyboardIT,
        TypeKeyboardGE,
        TypeKeyboardSP,
    };

    enum Anchors {
        AnchorNone,
        AnchorTopLeft_Row1,
        AnchorTopRight_Row1,
        AnchorTopLeft_Row2,
        AnchorTopRight_Row2,
    };

    enum Buttons {
        ButtonA,
        ButtonB,
        ButtonX,
        ButtonY,
        ButtonStart,
        ButtonSelect,
    };

    // ----------------
    // Static Variables
    // ----------------

    struct Static : RSDK::GameObject::Static {
        int32 type;
        int32 inputSlot;
        RSDK::SpriteAnimation aniFrames;
    };

    struct ModStatic : RSDK::GameObject::Static {};

    // ----------------
    // Entity Variables
    // ----------------

    RSDK::GameObject::Entity *parent;
    ManiaStateMachine(state);
    int32 timer;
    RSDK::Vector2 startPos;
    int32 promptID;
    int32 buttonID;
    uint8 headingAnchor;
    int32 unused;
    int32 prevPrompt;
    int32 prevButton;
    int32 mappings;
    bool32 textVisible;
    int32 scaleMax;
    int32 scaleSpeed;
    bool32 disableScale;
    RSDK::Vector2 touchSize;
    RSDK::Vector2 touchPos;
    bool32 touched;
    RSDK::Animator decorAnimator;
    RSDK::Animator buttonAnimator;
    RSDK::Animator promptAnimator;
    uint16 textSprite;

    // ----------------------
    // Standard Entity Events
    // ----------------------

    // -------------------
    // Static Declarations
    // -------------------

    MOD_DECLARE(UIButtonPrompt)
};

} // namespace GameLogic