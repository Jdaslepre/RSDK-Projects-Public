#pragma once
#include "GameAPI/Game.hpp"

using namespace RSDK;

namespace GameLogic {

struct Camera : GameObject::Entity {

    // ----------------
    // Static Variables
    // ----------------

    struct Static : GameObject::Static {
        Vector2 centerBounds;
        Vector2 lastCenterBounds;
        int32 field_14;
        int32 field_18;
        int32 field_1C;
    };

    struct ModStatic : GameObject::Static {};

    // ----------------
    // Entity Variables
    // ----------------

    StateMachine<Camera> state;
    Entity *target;
    int32 screenID;
    Vector2 center;
    Vector2 targetMoveVel;
    Vector2 lastPos;
    Vector2 shakePos;
    Vector2 shakeDuration;
    Vector2 shakeTimer;
    Vector2 lookPos;
    Vector2 offset;
    bool32 disableYOffset;
    int32 centerY;
    int32 adjustY;
    int32 lerpPercent;
    int32 lerpSpeed;
    int32 lerpType;
    Vector2 endLerpPos;
    Vector2 startLerpPos;
    Vector2 unknown3;
    Vector2 boundsOffset;
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