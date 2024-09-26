#pragma once
#include "GameAPI/Game.hpp"

namespace GameLogic {

struct S1SS_Player : RSDK::GameObject::Entity {

    // ---------------
    // Enums & Structs
    // ---------------

    enum GravityTypes {
        GravityGround,
        GravityAir,
    };

    // ----------------
    // Static Variables
    // ----------------

    struct Static : RSDK::GameObject::Static {
        RSDK::SpriteAnimation aniFrames;
        RSDK::SpriteAnimation tailSpriteFrames;
        uint8 gap8[28];
        int32 rings;
        int32 ringExtraLife;
        uint8 gap2C[4];
        int32 savedLives;
        int32 savedScore;
        int32 savedScore1UP;
    };

    struct ModStatic : RSDK::GameObject::Static {
        uint8 touchJump;
        uint8 touchDebug;
        uint8 touchPause;
        uint8 touchSuper;
        uint8 touchSwap;
    };

    // ----------------
    // Entity Variables
    // ----------------

    int32 rings;
    int32 lives;
    int32 score;
    int32 ringExtraLife;
    int32 score1UP;
    bool32 hyperRing;
    uint8 shield;
    uint16 playerID;
    uint8 gap7C[4];
    RSDK::StateMachine<S1SS_Player> state;
    Camera *camera;
    RSDK::Animator animator;
    RSDK::Animator tailAnimator;
    int32 tailRotation;
    int32 tailDirection;
    RSDK::SpriteAnimation aniFrames;
    uint8 gapD8[2];
    int32 characterID;
    uint8 gapE8[16];
    RSDK::StateMachine<S1SS_Player> stateInput;
    uint8 controllerID;
    char paddings[7];
    bool32 up;
    bool32 down;
    bool32 left;
    bool32 right;
    bool32 jumpPress;
    bool32 jumpHold;
    int32 unkn128;
    int32 gravity;
    RSDK::Vector2 worldVelocity;
    RSDK::Vector2 moveVelocity;
    int32 moveSpeed;
    bool32 isGhost;
    int32 abilityValues[8];
    void *abilityPtrs[8];
    int32 collisionFlags;
    uint8 padding2[20];
    int32 rotateBlockTimer;
    int32 upDownBlockTimer;
    uint16 animationSpeed;
    int32 field_1cc;

    // ----------------------
    // Standard Entity Events
    // ----------------------

    void Update(void);
    static void StaticLoad(Static *sVars);

    // -------------
    // Object States
    // -------------

    static RSDK::Action<void> State_Static;

    // ----------------------
    // Extra Entity Functions
    // ----------------------

    void HandleTouchInputs(void);

    // -------------------
    // Static Declarations
    // -------------------

    MOD_DECLARE(S1SS_Player)
};
} // namespace GameLogic