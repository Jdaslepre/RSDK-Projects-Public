#pragma once
#include "RSDK-Online.hpp"

// --------------------
// Macros / Definitions
// --------------------

#define PLAYERMANAGE_GETVAL(val, ptr) (p->val = src.val)
#define PLAYERMANAGE_SETVAL(val, ptr) (src.val = ptr->val)

#define PLAYERMANAGE_DEFINE_HOOK(name)                                                                                                               \
    bool32 name##_Hook(bool32 skippedState) {                                                                                                        \
        RSDK::currentState = #name;                                                                                                                  \
        return false;                                                                                                                                \
    }

#define PLAYERMANAGE_REGISTER_HOOK(name) (RSDK::Mod::RegisterStateHook(name, name##_Hook, true))

#define PLAYERMANAGE_MATCHSTATE(name, stateInstance)                                                                                                 \
    if (src.currentState == #name)                                                                                                                   \
    stateInstance = name

struct PlayerManage {

    // ---------------
    // Enums & Structs
    // ---------------

    struct AnimatorInst {
        int32 frameID;
        int32 animationID;
        int32 prevAnimationID;
        int32 speed;
        int32 timer;
        int32 frameDuration;
        int32 frameCount;
        int32 loopIndex;
        int32 rotationStyle;
    };

    struct PlayerData {
        RSDK::GameObject::Entity base;
        AnimatorInst animator;
        AnimatorInst tailAnimator;
        int32 minJogVelocity;
        int32 minRunVelocity;
        int32 minDashVelocity;
        int32 unused;
        int32 tailRotation;
        int32 tailDirection;
        RSDK::SpriteAnimation aniFrames;
        RSDK::SpriteAnimation tailFrames;
        uint16 animationReserve;
        uint16 playerID;
        int32 characterID;
        int32 rings;
        int32 ringExtraLife;
        int32 shield;
        int32 lives;
        int32 score;
        int32 score1UP;
        bool32 hyperRing;
        int32 timer;
        int32 outtaHereTimer;
        int32 abilityTimer;
        int32 spindashCharge;
        int32 abilityValue;
        int32 drownTimer;
        int32 invincibleTimer;
        int32 speedShoesTimer;
        int32 blinkTimer;
        int32 scrollDelay;
        int32 skidding;
        int32 pushing;
        int32 underwater;
        bool32 groundedStore;
        bool32 invertGravity;
        bool32 isChibi;
#if GAME_VERSION != VER_100
        bool32 isTransforming;
#endif
        int32 superState;
        int32 superRingLossTimer;
        int32 superBlendAmount;
        int32 superBlendState;
        bool32 sidekick;
        int32 scoreBonus;
        int32 jumpOffset;
        int32 collisionFlagH;
        int32 collisionFlagV;
        int32 topSpeed;
        int32 acceleration;
        int32 deceleration;
        int32 airAcceleration;
        int32 airDeceleration;
        int32 skidSpeed;
        int32 rollingFriction;
        int32 rollingDeceleration;
        int32 gravityStrength;
        int32 abilitySpeed;
        int32 jumpStrength;
        int32 jumpCap;
        int32 flailing;
        int32 sensorX[5];
        int32 sensorY;
        RSDK::Vector2 moveLayerPosition;
        int32 controllerID;
        int32 controlLock;
        bool32 up;
        bool32 down;
        bool32 left;
        bool32 right;
        bool32 jumpPress;
        bool32 jumpHold;
        bool32 applyJumpCap;
        int32 jumpAbilityState;
        int32 flyCarryTimer;
        RSDK::Vector2 flyCarrySidekickPos;
        RSDK::Vector2 flyCarryLeaderPos;
        uint8 deathType;
        bool32 forceRespawn;
#if MANIA_USE_PLUS
        bool32 isGhost;
#endif
        int32 abilityValues[8];
#if MANIA_USE_PLUS
        int32 uncurlTimer;
#endif
        // This is used for dynamic states
        const char *currentState;

        // These are used for direct states
        ManiaStateMachine(state);
        ManiaStateMachine(nextAirState);
        ManiaStateMachine(nextGroundState);
#if MANIA_USE_PLUS
        ManiaStateMachine(stateInputReplay);
#endif
        ManiaStateMachine(stateInput);
        ManiaStateMachine(stateAbility);
        ManiaStateMachine(statePeelout);
    };

    static PlayerData src;

    // ----------------------
    // Standard Entity Events
    // ----------------------

    static void InitDataSource(GameLogic::Player *p);
    static void ApplyDataSourceToPlayer(GameLogic::Player *p);

    // -------------------
    // Object State System
    // -------------------

    static void GetStates();
    static void RegisterHooks();
    static void HandleStates(GameLogic::Player *p);
};

// -------------------
// Object State System
// -------------------

// States
extern void (*Player_State_Static)();
extern void (*Player_State_Ground)();
extern void (*Player_State_Air)();
extern void (*Player_State_Roll)();
extern void (*Player_State_TubeRoll)();
extern void (*Player_State_TubeAirRoll)();
extern void (*Player_State_LookUp)();
extern void (*Player_State_Crouch)();
extern void (*Player_State_Spindash)();
extern void (*Player_State_Peelout)();
extern void (*Player_State_OuttaHere)();
extern void (*Player_State_Transform)();
extern void (*Player_State_Hurt)();
extern void (*Player_State_Death)();
extern void (*Player_State_Drown)();
extern void (*Player_State_DropDash)();
extern void (*Player_State_BubbleBounce)();
extern void (*Player_State_TailsFlight)();
extern void (*Player_State_FlyCarried)();
extern void (*Player_State_KnuxGlideLeft)();
extern void (*Player_State_KnuxGlideRight)();
extern void (*Player_State_KnuxGlideDrop)();
extern void (*Player_State_KnuxGlideSlide)();
extern void (*Player_State_KnuxWallClimb)();
extern void (*Player_State_KnuxLedgePullUp)();
#if MANIA_USE_PLUS
extern void (*Player_State_MightyHammerDrop)();
extern void (*Player_State_MightyUnspin)();
extern void (*Player_State_RayGlide)();
#endif
extern void (*Player_State_FlyToPlayer)();
extern void (*Player_State_ReturnToPlayer)();
extern void (*Player_State_HoldRespawn)();
extern void (*Player_State_EncoreRespawn)();
extern void (*Player_State_Victory)();
extern void (*Player_State_Bubble)();
extern void (*Player_State_WaterSlide)();
extern void (*Player_State_TransportTube)();

// State Hooks
bool32 Player_State_Static_Hook(bool32 skippedState);
bool32 Player_State_Ground_Hook(bool32 skippedState);
bool32 Player_State_Air_Hook(bool32 skippedState);
bool32 Player_State_Roll_Hook(bool32 skippedState);
bool32 Player_State_TubeRoll_Hook(bool32 skippedState);
bool32 Player_State_TubeAirRoll_Hook(bool32 skippedState);
bool32 Player_State_LookUp_Hook(bool32 skippedState);
bool32 Player_State_Crouch_Hook(bool32 skippedState);
bool32 Player_State_Spindash_Hook(bool32 skippedState);
bool32 Player_State_Peelout_Hook(bool32 skippedState);
bool32 Player_State_OuttaHere_Hook(bool32 skippedState);
bool32 Player_State_Transform_Hook(bool32 skippedState);
bool32 Player_State_Hurt_Hook(bool32 skippedState);
bool32 Player_State_Death_Hook(bool32 skippedState);
bool32 Player_State_Drown_Hook(bool32 skippedState);
bool32 Player_State_DropDash_Hook(bool32 skippedState);
bool32 Player_State_BubbleBounce_Hook(bool32 skippedState);
bool32 Player_State_TailsFlight_Hook(bool32 skippedState);
bool32 Player_State_FlyCarried_Hook(bool32 skippedState);
bool32 Player_State_KnuxGlideLeft_Hook(bool32 skippedState);
bool32 Player_State_KnuxGlideRight_Hook(bool32 skippedState);
bool32 Player_State_KnuxGlideDrop_Hook(bool32 skippedState);
bool32 Player_State_KnuxGlideSlide_Hook(bool32 skippedState);
bool32 Player_State_KnuxWallClimb_Hook(bool32 skippedState);
bool32 Player_State_KnuxLedgePullUp_Hook(bool32 skippedState);
#if MANIA_USE_PLUS
bool32 Player_State_MightyHammerDrop_Hook(bool32 skippedState);
bool32 Player_State_MightyUnspin_Hook(bool32 skippedState);
bool32 Player_State_RayGlide_Hook(bool32 skippedState);
#endif
bool32 Player_State_FlyToPlayer_Hook(bool32 skippedState);
bool32 Player_State_ReturnToPlayer_Hook(bool32 skippedState);
bool32 Player_State_HoldRespawn_Hook(bool32 skippedState);
bool32 Player_State_EncoreRespawn_Hook(bool32 skippedState);
bool32 Player_State_Victory_Hook(bool32 skippedState);
bool32 Player_State_Bubble_Hook(bool32 skippedState);
bool32 Player_State_WaterSlide_Hook(bool32 skippedState);
bool32 Player_State_TransportTube_Hook(bool32 skippedState);