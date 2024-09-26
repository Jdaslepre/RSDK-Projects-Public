#pragma once
#include "RSDK-Online.hpp"

namespace GameLogic {

struct UICarousel : RSDK::GameObject::Entity {

    // ----------------
    // Static Variables
    // ----------------

    struct Static : RSDK::GameObject::Static {
        RSDK::SpriteAnimation aniFrames;
        RSDK::Animator animator;
    };

    struct ModStatic : RSDK::GameObject::Static {};

    // ----------------
    // Entity Variables
    // ----------------

    RSDK::Vector2 shift;
    RSDK::Vector2 clipSize;
    RSDK::Vector2 clipOffset;
    int32 unused1;
    int32 unused2;
    int32 unused3;
    RSDK::GameObject::Entity *unused4;
    int32 unused5;
    int32 scrollOffset;
    int32 virtualIndex;
    int32 unused6;
    RSDK::Vector2 startPos;
    int32 buttonID;
    int32 minOffset;
    int32 maxOffset;
    RSDK::Vector2 offset;
    UIControl *parent;

    // -------------------
    // Static Declarations
    // -------------------

    MOD_DECLARE(UICarousel)
};

} // namespace GameLogic