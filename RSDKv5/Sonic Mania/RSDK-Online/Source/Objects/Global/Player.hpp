#pragma once
#include "RSDK-Online.hpp"

namespace GameLogic {

struct Player : RSDK::GameObject::Entity {

    // ---------------
    // Enums & Structs
    // ---------------

    enum PlayerAnimationIDs {
        ANI_IDLE,
        ANI_BORED_1,
        ANI_BORED_2,
        ANI_LOOK_UP,
        ANI_CROUCH,
        ANI_WALK,
        ANI_AIR_WALK,
        ANI_JOG,
        ANI_RUN,
        ANI_DASH,
        ANI_JUMP,
        ANI_SPRING_TWIRL,
        ANI_SPRING_DIAGONAL,
        ANI_SKID,
        ANI_SKID_TURN,
        ANI_SPINDASH,
        ANI_ABILITY_0,
        ANI_PUSH,
        ANI_HURT,
        ANI_DIE,
        ANI_DROWN,
        ANI_BALANCE_1,
        ANI_BALANCE_2,
        ANI_SPRING_CS,
        ANI_STAND_CS,
        ANI_FAN,
        ANI_VICTORY,
        ANI_OUTTA_HERE,
        ANI_HANG,
        ANI_HANG_MOVE,
        ANI_POLE_SWING_V,
        ANI_POLE_SWING_H,
        ANI_SHAFT_SWING,
        ANI_TURNTABLE,
        ANI_TWISTER,
        ANI_SPIRAL_RUN,
        ANI_STICK,
        ANI_PULLEY_HOLD,
        ANI_SHIMMY_IDLE,
        ANI_SHIMMY_MOVE,
        ANI_BUBBLE,
        ANI_BREATHE,
        ANI_RIDE,
        ANI_CLING,
        ANI_BUNGEE,
        ANI_TWIST_RUN,
#if MANIA_USE_PLUS
        ANI_FLUME,
#endif
        ANI_TRANSFORM,
        ANI_ABILITY_1,
        ANI_ABILITY_2,
        ANI_ABILITY_3,
        ANI_ABILITY_4,
        ANI_ABILITY_5,
        ANI_ABILITY_6,
        ANI_ABILITY_7,

        // Sonic Ability Anim Aliases
        ANI_DROPDASH = ANI_ABILITY_0,
        ANI_PEELOUT  = ANI_ABILITY_1,

        // Tails Ability Anim Aliases
        ANI_FLY            = ANI_ABILITY_1,
        ANI_FLY_TIRED      = ANI_ABILITY_2,
        ANI_FLY_LIFT       = ANI_ABILITY_3,
        ANI_FLY_LIFT_TIRED = ANI_ABILITY_4,
        ANI_SWIM           = ANI_ABILITY_5,
        ANI_SWIM_TIRED     = ANI_ABILITY_6,
        ANI_SWIM_LIFT      = ANI_ABILITY_7,

        // Knux Ability Anim Aliases
        ANI_LEDGE_PULL_UP = ANI_ABILITY_0,
        ANI_GLIDE         = ANI_ABILITY_1,
        ANI_GLIDE_DROP    = ANI_ABILITY_2,
        ANI_GLIDE_LAND    = ANI_ABILITY_3,
        ANI_GLIDE_SLIDE   = ANI_ABILITY_4,
        ANI_CLIMB_IDLE    = ANI_ABILITY_5,
        ANI_CLIMB_UP      = ANI_ABILITY_6,
        ANI_CLIMB_DOWN    = ANI_ABILITY_7,

#if MANIA_USE_PLUS
        // Mighty Ability Anim Aliases
        ANI_HAMMERDROP = ANI_ABILITY_0,
        ANI_UNSPIN     = ANI_ABILITY_1,

        // Ray Ability Anim Aliases
        ANI_HANG2    = ANI_ABILITY_0,
        ANI_FLY_UP   = ANI_ABILITY_1,
        ANI_FLY_DOWN = ANI_ABILITY_2,
#endif
    };

    // for "characterID" in editor
    enum PlayerCharacterIDS {
        PLAYER_CHAR_NONE,
        PLAYER_CHAR_SONIC,
        PLAYER_CHAR_TAILS,
        PLAYER_CHAR_SONIC_TAILS,
        PLAYER_CHAR_KNUX,
        PLAYER_CHAR_SONIC_KNUX,
        PLAYER_CHAR_TAILS_KNUX,
        PLAYER_CHAR_SONIC_TAILS_KNUX,
    };

    enum ShieldTypes {
        SHIELD_NONE,
        SHIELD_BLUE,
        SHIELD_BUBBLE,
        SHIELD_FIRE,
        SHIELD_LIGHTNING,
    };

    enum DeathTypes {
        DeathTypeNone,
        PLAYER_DEATH_DIE_USESFX,
        PLAYER_DEATH_DIE_NOSFX,
        PLAYER_DEATH_DROWN,
    };

    enum HurtTypes {
        HurtNone,
        HurtHasShield,
        HurtRingLoss,
        HurtDie,
    };

    enum SuperStates {
        StateNone,
        StateFadeIn,
        StateSuper,
        StateFadeOut,
        StateDone,
    };

    static RSDK::Hitbox FallbackHitbox;

    // ----------------
    // Static Variables
    // ----------------

    struct Static : RSDK::GameObject::Static {
        int32 sonicPhysicsTable[64];
        int32 tailsPhysicsTable[64];
        int32 knuxPhysicsTable[64];
        int32 mightyPhysicsTable[64];
        int32 rayPhysicsTable[64];
        color superPalette_Sonic[18];
        color superPalette_Tails[18];
        color superPalette_Knux[18];
        color superPalette_Mighty[18];
        color superPalette_Ray[18];
        color superPalette_Sonic_HCZ[18];
        color superPalette_Tails_HCZ[18];
        color superPalette_Knux_HCZ[18];
        color superPalette_Mighty_HCZ[18];
        color superPalette_Ray_HCZ[18];
        color superPalette_Sonic_CPZ[18];
        color superPalette_Tails_CPZ[18];
        color superPalette_Knux_CPZ[18];
        color superPalette_Mighty_CPZ[18];
        color superPalette_Ray_CPZ[18];
        bool32 cantSwap;
        int32 playerCount;
        uint16 upState;
        uint16 downState;
        uint16 leftState;
        uint16 rightState;
        uint16 jumpPressState;
        uint16 jumpHoldState;
        int32 nextLeaderPosID;
        int32 lastLeaderPosID;
        RSDK::Vector2 leaderPositionBuffer[16];
        RSDK::Vector2 targetLeaderPosition;
        int32 autoJumpTimer;
        int32 respawnTimer;
        int32 aiInputSwapTimer;
        bool32 disableP2KeyCheck;
        int32 rings;
        int32 ringExtraLife;
        int32 powerups;
        int32 savedLives;
        int32 savedScore;
        int32 savedScore1UP;
        RSDK::SpriteAnimation sonicFrames;
        RSDK::SpriteAnimation superFrames;
        RSDK::SpriteAnimation tailsFrames;
        RSDK::SpriteAnimation tailsTailsFrames;
        RSDK::SpriteAnimation knuxFrames;
        RSDK::SpriteAnimation mightyFrames;
        RSDK::SpriteAnimation rayFrames;
        RSDK::SoundFX sfxJump;
        RSDK::SoundFX sfxRoll;
        RSDK::SoundFX sfxCharge;
        RSDK::SoundFX sfxRelease;
        RSDK::SoundFX sfxPeelCharge;
        RSDK::SoundFX sfxPeelRelease;
        RSDK::SoundFX sfxDropdash;
        RSDK::SoundFX sfxLoseRings;
        RSDK::SoundFX sfxHurt;
        RSDK::SoundFX sfxPimPom;
        RSDK::SoundFX sfxSkidding;
        RSDK::SoundFX sfxGrab;
        RSDK::SoundFX sfxFlying;
        bool32 playingFlySfx;
        RSDK::SoundFX sfxTired;
        bool32 playingTiredSfx;
        RSDK::SoundFX sfxLand;
        RSDK::SoundFX sfxSlide;
        RSDK::SoundFX sfxOuttahere;
        RSDK::SoundFX sfxTransform2;
        RSDK::SoundFX sfxSwap;
        RSDK::SoundFX sfxSwapFail;
        RSDK::SoundFX sfxMightyDeflect;
        RSDK::SoundFX sfxMightyDrill;
        RSDK::SoundFX sfxMightyLand;
        RSDK::SoundFX sfxMightyUnspin;
        int32 raySwoopTimer;
        int32 rayDiveTimer;
        bool32 gotHit[PLAYER_COUNT];
        ManiaStateMachine(configureGhostCB);
        bool32 (*canSuperCB)(bool32 isHUD);
        int32 superDashCooldown;
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

    ManiaStateMachine(state);
    ManiaStateMachine(nextAirState);
    ManiaStateMachine(nextGroundState);
    Camera *camera;
    RSDK::Animator animator;
    RSDK::Animator tailAnimator;
    int32 minJogVelocity;
    int32 minRunVelocity;
    int32 minDashVelocity;
    int32 unused; // the only used variable in the player struct, I cant find a ref to it anywhere so...
    int32 tailRotation;
    int32 tailDirection;
    RSDK::SpriteAnimation aniFrames;
    RSDK::SpriteAnimation tailFrames;
    uint16 animationReserve; // what anim to return to after SpringTwirl/SpringDiagonal has finished and the player is falling downwards
    uint16 playerID;
    RSDK::Hitbox *outerbox;
    RSDK::Hitbox *innerbox;
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
    int32 underwater;     // 0 = not in water, 1 = in palette water, else water entityID
    bool32 groundedStore; // prev frame's onGround value
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
#if MANIA_USE_PLUS
    ManiaStateMachine(stateInputReplay);
#endif
    ManiaStateMachine(stateInput);
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
    ManiaStateMachine(stateAbility);
    ManiaStateMachine(statePeelout);
    int32 flyCarryTimer;
    RSDK::Vector2 flyCarrySidekickPos;
    RSDK::Vector2 flyCarryLeaderPos;
    uint8 deathType;
    bool32 forceRespawn;
#if MANIA_USE_PLUS
    bool32 isGhost;
#endif
    int32 abilityValues[8];
    void *abilityPtrs[8];
#if MANIA_USE_PLUS
    int32 uncurlTimer;
#endif

    // ----------------------
    // Standard Entity Events
    // ----------------------
    
    void Update();

    // -------------------
    // Static Declarations
    // -------------------

    MOD_DECLARE(Player)
};

// ----------------
// Public Functions
// ----------------

extern bool32 (*Player_CheckValidState)(Player *player);

} // namespace GameLogic