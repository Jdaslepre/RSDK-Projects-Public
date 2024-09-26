#pragma once
#include "RSDK-Online.hpp"

namespace GameLogic {

struct UIText : RSDK::GameObject::Entity {

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

    struct Static : RSDK::GameObject::Static {
        RSDK::SpriteAnimation aniFrames;
    };

    struct ModStatic : RSDK::GameObject::Static {};

    // ----------------
    // Entity Variables
    // ----------------

    ManiaStateMachine(state);
    ManiaStateMachine(stateDraw);
    RSDK::String text;
    RSDK::String tag;
    bool32 selectable;
    uint16 listID;
    int32 align;
    int32 data0;
    int32 data1;
    int32 data2;
    int32 data3;
    bool32 highlighted;
    RSDK::Animator animator;

    // -------------------
    // Static Declarations
    // -------------------

    MOD_DECLARE(UIText)
};

} // namespace GameLogic