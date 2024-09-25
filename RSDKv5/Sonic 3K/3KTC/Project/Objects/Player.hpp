#pragma once
#include "GameAPI/Game.hpp"

using namespace RSDK;

namespace GameLogic {

struct Player : GameObject::Entity {

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
        ANI_WALK_ANGLED,
        ANI_FALL,
        ANI_FALL_ANGLED,
        ANI_JOG,
        ANI_JOG_ANGLED,
        ANI_RUN,
        ANI_RUN_ANGLED,
        ANI_DASH,
        ANI_DASH_ANGLED,
        ANI_JUMP,
        ANI_SPRING_TWIRL,
        ANI_SPRING_DIAGONAL,
        ANI_SKID,
        ANI_SKID_TURN,
        ANI_SPINDASH,
        ANI_PUSH,
        ANI_HURT,
        ANI_DIE,
        ANI_DROWN,
        ANI_BALANCE_1,
        ANI_BALANCE_2,
        ANI_TREMBLE,
        ANI_SPRING_CS,
        ANI_STAND_CS,
        ANI_FAN,
        ANI_VICTORY,
        ANI_OUTTA_HERE,
        ANI_HANGGIMMICK,
        ANI_HANGBACKWARDS,
        ANI_HANGPLAYER,
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
        ANI_FLUME,
        ANI_SLOPE_SLIDE,
        ANI_TRANSFORM,
        ANI_SPRING_CS_REV,
        ANI_HANG_TWIRL,
        ANI_CONTINUE,
        ANI_CONTINUE_UP,
        ANI_CYLINDERWALKOUTER,
        ANI_CYLINDERWALKINNER,
        ANI_RAPPELBARSWING,
        ANI_RAPPELDOWN,
        ANI_HORIZONTALBARHANG,
        ANI_BARRELUP,
        ANI_BARRELMIDUP,
        ANI_BARRELMID,
        ANI_BARRELMIDDOWN,
        ANI_BARRELDOWN,
        ANI_ABILITY_0,
        ANI_ABILITY_1,
        ANI_ABILITY_2,
        ANI_ABILITY_3,
        ANI_ABILITY_4,
        ANI_ABILITY_5,
        ANI_ABILITY_6,
        ANI_ABILITY_7,
        ANI_ABILITY_8,
        ANI_ABILITY_9,
        ANI_ABILITY_10,
        ANI_ABILITY_11,
        ANI_ABILITY_12,
        ANI_ABILITY_13,

        ANI_AIR_WALK, // leftovers(?)
        ANI_SPRING_DIAG,
        ANI_HANG,

        // Sonic Ability Anim Aliases
        ANI_DROPDASH          = ANI_ABILITY_0,
        ANI_WHISTLE           = ANI_ABILITY_1,
        ANI_HALFCYLINDERSKATE = ANI_ABILITY_2,
        ANI_SPINHANDLE        = ANI_ABILITY_3,
        ANI_CLIMBING          = ANI_ABILITY_4,
        ANI_PEELOUT           = ANI_ABILITY_5,
        ANI_PEELOUTANGLED     = ANI_ABILITY_6,

        // Tails Ability Anim Aliases
        ANI_RAPPELDOWNLEGBENT = ANI_ABILITY_0,
        ANI_DASHANGLED1       = ANI_ABILITY_1,
        ANI_DASHANGLED2       = ANI_ABILITY_2,
        ANI_DASHVERTICAL      = ANI_ABILITY_3,
        ANI_CYLINDERSPIN      = ANI_ABILITY_4,
        ANI_FLY               = ANI_ABILITY_5,
        ANI_FLY_TIRED         = ANI_ABILITY_6,
        ANI_FLY_LIFT          = ANI_ABILITY_7,
        ANI_FLY_LIFT_DOWN     = ANI_ABILITY_8,
        ANI_FLY_LIFT_TIRED    = ANI_ABILITY_9,
        ANI_SWIM              = ANI_ABILITY_10,
        ANI_SWIM_TIRED        = ANI_ABILITY_11,
        ANI_SWIM_LIFT         = ANI_ABILITY_12,
        ANI_NEW_ANIMATION_83  = ANI_ABILITY_13, // lol

        // Knux Ability Anim Aliases
        ANI_LEDGE_PULL_UP = ANI_ABILITY_0,
        ANI_GLIDE         = ANI_ABILITY_1,
        ANI_GLIDE_DROP    = ANI_ABILITY_2,
        ANI_GLIDE_LAND    = ANI_ABILITY_3,
        ANI_GLIDE_SLIDE   = ANI_ABILITY_4,
        ANI_CLIMB_IDLE    = ANI_ABILITY_5,
        ANI_CLIMB_UP      = ANI_ABILITY_6,
        ANI_CLIMB_DOWN    = ANI_ABILITY_7,

        // Amy Ability Anim Aliases
        ANI_HAMMER_JUMP  = ANI_ABILITY_0,
        ANI_HAMMER_DASH  = ANI_ABILITY_1,
        ANI_HAMMER_THROW = ANI_ABILITY_2,
        ANI_HAMMER       = ANI_ABILITY_3,
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

    enum HyperAbilityStates {
        HyperStateNone,
        HyperStateActive,
        HyperStateHyperDash,
        HyperStateHyperSlam,
        StateStartHyperDash,
        HyperStateStartHyperSlam,
    };

    enum SuperStates {
        StateNone,
        StateFadeIn,
        StateSuper,
        StateFadeOut,
        StateDone,
    };

    enum SpriteTypes {
        ClassicSprites,
        ManiaSprites,
    };

    enum TransformModes {
        TransformEmeralds, // Use emeralds to decide
        TransformSuper,    // force transform to super
        TransformHyper,    // force transform to hyper
        TransformAuto,     // force transform to super/hyper depending on emeralds
    };

    struct RSDKPathTracer {
        uint8 field_0;
        uint8 field_1;
        int16 outerLeft;
        uint8 field_4;
        int16 outerRight;
        uint8 field_8;
        int16 outerTop;
        uint8 field_C;
        uint8 field_D;
        uint16 outerBottom;
        uint8 field_10;
        uint8 mode;
        uint8 prevMode;
        uint8 field_13;
        uint8 field_14;
        uint8 field_15;
        uint8 field_16;
        uint8 field_17;
        void *field_18; // useCollisionOffset?
        void *field_20;
        int16 angle;
        int16 angle5;
        int16 angle6;
        int16 angle4;
        int16 angle2;
        int16 angle3;
        uint8 field_34;
        uint8 field_35;
        uint8 field_36;
        uint8 field_37;
        GameObject::Entity *lastRightBoxCollision;
        GameObject::Entity *lastLeftBoxCollision;
        GameObject::Entity *lastBottomBoxCollision;
        GameObject::Entity *lastTopBoxCollision;
        uint8 field_58;
        uint8 field_59;
        uint8 field_5A;
        uint8 field_5B;
        int32 bottomFlag;
        int32 topFlag;
        int32 rightFlag;
        int32 leftFlag;
        int32 xLocked;
    };

    static Hitbox FallbackHitbox;

    // ----------------
    // Static Variables
    // ----------------

    struct Static : GameObject::Static {
        int32 sonicPhysicsTable[64];
        int32 sonicPhysicsTableComp[24];
        int32 tailsPhysicsTable[64];
        int32 tailsPhysicsTableComp[24];
        int32 knuxPhysicsTable[64];
        int32 knuxPhysicsTableComp[24];
        int32 mightyPhysicsTable[64];
        int32 rayPhysicsTable[64];
#if ORIGINS_USE_PLUS
        int32 amyPhysicsTable[64];
        int32 amyPhysicsTableComp[24];
#endif
        int32 unknown0784[24]; // Unknown type

        color superPalette_Sonic[30];
        color superPalette_Sonic_Water1[30];
        color superPalette_Sonic_Water2[30];
        color hyperPalette_Sonic[54];
        color hyperPalette_Sonic_Water1[54];
        color hyperPalette_Sonic_Water2[54];
        color *activeSuperPalette_Sonic;
        color *activeSuperPalette_Sonic_Water;
        color *activeHyperPalette_Sonic;
        color *activeHyperPalette_Sonic_Water;
        color superPalette_Tails[18];
        color superPalette_Tails_Water1[18];
        color superPalette_Tails_Water2[18];
        color *activeSuperPalette_Tails;
        color *activeSuperPalette_Tails_Water;
        color superPalette_Knux[33];
        color superPalette_Knux_Water1[33];
        color superPalette_Knux_Water2[33];
        color *activeSuperPalette_Knux;
        color *activeSuperPalette_Knux_Water;
        color superPalette_Amy[55];
        color superPalette_Amy_Water1[55];
        color superPalette_Amy_Water2[55];
        color *activeSuperPalette_Amy;
        color *activeSuperPalette_Amy_Water;

        float spindashChargeSpeeds[13];
        Hitbox instaShieldHitbox;
        Hitbox shieldHitbox;
        bool32 cantSwap;

        int32 playerCount;
        int32 maxPlayerCount;
        uint16 upState;
        uint16 downState;
        uint16 leftState;
        uint16 rightState;
        uint16 jumpPressState;
        uint16 jumpHoldState;
        int32 nextLeaderPosID;
        int32 lastLeaderPosID;
        Vector2 leaderPositionBuffer[16];
        Vector2 targetLeaderPosition;
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

        SpriteAnimation sonicFrames;
        SpriteAnimation superFrames;
        SpriteAnimation tailsFrames;
        SpriteAnimation tailSpriteFrames;
        SpriteAnimation knuxFrames;
#if ORIGINS_USE_PLUS
        SpriteAnimation amyFrames;
#endif
        int32 unknown1248; // Unknown type

        SoundFX sfxJump;
        SoundFX sfxRoll;
        SoundFX sfxCharge;
        SoundFX sfxRelease;
        SoundFX sfxPeelCharge;
        SoundFX sfxPeelRelease;
        SoundFX sfxDropdash;
        SoundFX sfxLoseRings;
        SoundFX sfxHurt;
        SoundFX sfxPimPom;
        SoundFX sfxSkidding;
        SoundFX sfxGrab;
        SoundFX sfxFlying;
        bool32 playingFlySfx;
        SoundFX sfxTired;
        bool32 playingTiredSfx;
        SoundFX sfxLand;
        SoundFX sfxSlide;
        SoundFX sfxOuttaHere;
        SoundFX sfxTransform2;
        SoundFX sfxSwap;
        SoundFX sfxSwapFail;
        SoundFX sfxUnused[4]; // Maybe
        SoundFX sfxEarthquake;
#if ORIGINS_USE_PLUS
        SoundFX sfxHammerJump;
        SoundFX sfxHammerDash;
        SoundFX sfxHammerHit;
#endif
        int32 unknown1290;
        bool32 gotHit[PLAYER_COUNT];
        StateMachine<Player> configureGhostCB;
        bool32 (*canSuperCB)(bool32 isHUD);
        int32 superDashCooldown;
        uint16 lookUpDelay;
        uint16 lookUpDistance;

        bool32 showHitbox;
        int32 finishedInput;
    };

    struct ModStatic : GameObject::Static {
        uint8 touchJump;
        uint8 touchDebug;
        uint8 touchPause;
        uint8 touchSuper;
        uint8 touchSwap;
    };

    // ----------------
    // Entity Variables
    // ----------------

    RSDKPathTracer pathTracer;
    int32 rings;
    int32 lives;
    int32 score;
    int32 ringExtraLife;
    int32 score1UP;
    bool32 hyperRing;
    uint8 shield;
    StateMachine<Player> state;
    StateMachine<Player> nextAirState;
    StateMachine<Player> nextGroundState;
    StateMachine<Player> stateGravity;
    Camera *camera;
    Animator animator;
    Animator tailAnimator;
    int32 minJogVelocity;
    int32 minRunVelocity;
    int32 minDashVelocity;
    int32 unused; // the only unused variable in the player struct, I cant find a ref to it anywhere so...
    int32 tailRotation;
    int32 tailDirection;
    SpriteAnimation aniFrames;
    SpriteAnimation tailFrames;
    uint16 animationReserve; // what anim to return to after SpringTwirl/SpringDiagonal has finished and the player is falling downwards
    uint16 playerID;
    Hitbox *outerbox;
    Hitbox *innerbox;
    int32 characterID;
    int32 hurtAirborneTimer; // I don't actually know what this is. it counts up when you are hit until you land, as well as hold up and down to move
                             // the camera.
    int32 timer;             // where player timer ACTUALLY is. this one is responsible for many things, such as: player idle animation.
    int32 abilityTimer;      // handles ability timers for certain things, spindash being one of them.
    int32 spindashCharge;    // handles the pitch of the spindash. note: it never goes down. why? i dunno.
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
    bool32 invertGravity; // technically not used, but it still has effects on the player's control if forced to 1 on cheat engine. comes from Mania's
                          // FBZ invert gravity sections?
    bool32 isChibi;       // This is still in Sonic 3. Wild.
    bool32 isTransforming;
    bool32 disableGravity;
    int32 superState;
    int32 superRingLossTimer;
    int32 superBlendAmount;
    int32 superBlendState;
    int32 superBlendTimer;
    uint8 superColorIndex;
    uint8 superColorCount;
    uint8 superTableIndex;
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
    uint32 flailing; // bitfield for flailing.
    int32 sensorX[5];
    int32 sensorY;
    Vector2 moveLayerPosition;
    Vector2 lastMoveLayerPosition;
    StateMachine<Player> stateInputReplay;
    StateMachine<Player> stateInput;
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
    StateMachine<Player> stateAbility;
    StateMachine<Player> statePeelout;
    int32 flyCarryTimer;
    Vector2 flyCarrySidekickPos;
    Vector2 flyCarryLeaderPos;
    uint8 deathType;
    bool32 forceRespawn; // Mania Leftover, encore respawn.
    bool32 isGhost;      // ??? Mania time trial ghost LOL
    int32 abilityValues[8];
    void *abilityPtrs[8];
    int32 uncurlTimer;
    int32 spriteType;
    bool32 disableGroundAnims;
    StateMachine<Player> storedStateInput;
    Vector2 spikeDir;
    int32 statsKillCount; // Kill counts are used for achievements
    int32 statsSpindashKillCount;
    int32 statsCycloneKillCount; // In Origins this is likely referred as Rhino.
    int32 statsUnused0;
    int32 statsUnused1;
    int32 hyperAbilityState;
    bool32 isHyper;
    bool32 disableMovementProcessing;
    char unknown3[4];         // there's something here, i dont know what it is.
    int32 abilityChargeTimer; // Amy's hammer ability charge.
    int32 enableAbilityCharge;

    // ----------------------
    // Standard Entity Events
    // ----------------------

    static void StaticLoad(Static *sVars);

    // -------------
    // Object States
    // -------------

    static Action<void> State_Victory;
    static Action<void> Input_Gamepad;

    // ----------------------
    // Extra Entity Functions
    // ----------------------

    bool32 CanTransform(void);
    bool32 CanSwap(void);

    // -------------------
    // Static Declarations
    // -------------------

    MOD_DECLARE(Player)
};

// ----------------
// Public Functions
// ----------------

extern bool32 (*Player_CheckValidState)(Player *player);

// ----------------------
// Extra Entity Functions
// ----------------------

bool32 Player_Input_Gamepad_Hook(bool32 skippedState);

} // namespace GameLogic