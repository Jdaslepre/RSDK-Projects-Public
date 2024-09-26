#pragma once
#include "RSDK-Online.hpp"

namespace GameLogic {

struct UIButton : ManiaUIEntity {

    // ---------------
    // Enums & Structs
    // ---------------

    enum Alignments {
        AlignLeft,
        AlignCenter,
        AlignRight,
    };

    // ----------------
    // Static Variables
    // ----------------

    struct Static : RSDK::GameObject::Static {};
    struct ModStatic : RSDK::GameObject::Static {};

    // ----------------
    // Entity Variables
    // ----------------

    RSDK::Vector2 size;
    int32 listID;
    int32 frameID;
    int32 align;
    int32 choiceCount;
    uint8 choiceDir;
    bool32 invisible;
    bool32 assignsP1;
    bool32 freeBindP2;
    bool32 transition;
    bool32 stopMusic;
    bool32 isDisabled;
    int32 bgEdgeSize;
    int32 textBounceOffset;
    int32 buttonBounceOffset;
    int32 textBounceVelocity;
    int32 buttonBounceVelocity;
    bool32 textVisible;
    bool32 clearParentState;
    RSDK::Vector2 firstChoicePos;
    int32 selection;
    void (*choiceChangeCB)(void);
    RSDK::Animator animator;
    uint16 textFrames;
    int32 startListID;
    int32 startFrameID;

    // ----------------------
    // Standard Entity Events
    // ----------------------


    // -------------
    // Object States
    // -------------

    // -------------------
    // Static Declarations
    // -------------------

    MOD_DECLARE(UIButton)
};

} // namespace GameLogic