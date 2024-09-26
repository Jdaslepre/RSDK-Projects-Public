#pragma once
#include "GameAPI/Game.hpp"

namespace GameLogic {

struct Camera : RSDK::GameObject::Entity {

    // ----------------
    // Static Variables
    // ----------------

    struct Static : RSDK::GameObject::Static {
        RSDK::Vector2 centerBounds;
        RSDK::Vector2 lastCenterBounds;
        int32 field_14;
        int32 field_18;
        int32 field_1C;
    };

    struct ModStatic : RSDK::GameObject::Static {
    };

    // ----------------
    // Entity Variables
    // ----------------

    RSDK::StateMachine<Camera> state;
    RSDK::GameObject::Entity *target;
    int32 screenID;
    RSDK::Vector2 center;
    RSDK::Vector2 targetMoveVel;
    RSDK::Vector2 lastPos;
    RSDK::Vector2 shakePos;
    RSDK::Vector2 shakeDuration;
    RSDK::Vector2 shakeTimer;
    RSDK::Vector2 lookPos;
    RSDK::Vector2 offset;
    bool32 disableYOffset;
    int32 centerY;
    int32 adjustY;
    int32 lerpPercent;
    int32 lerpSpeed;
    int32 lerpType;
    RSDK::Vector2 endLerpPos;
    RSDK::Vector2 startLerpPos;
    RSDK::Vector2 unknown3;
    RSDK::Vector2 boundsOffset;
    int32 boundsL;
    int32 boundsR;
    int32 boundsT;
    int32 boundsB;
    int32 field_10C;

    // -------------------
    // Static Declarations
    // -------------------

    MOD_DECLARE(Camera)
};
} // namespace GameLogic