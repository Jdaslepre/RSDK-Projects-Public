#pragma once
#include "RSDK-Online.hpp"

namespace GameLogic {

struct UIDiorama : RSDK::GameObject::Entity {

    // ---------------
    // Enums & Structs
    // ---------------

    enum DioramaIDs {
        IDManiaMode,
        IDPlusUpsell,
        IDEncoreMode,
        IDTimeAttack,
        IDCompetition,
        IDOptions,
        IDExtras,
        IDExit,
    };

    enum DioramaAlts {
        AltRun,
        AltJog,
        AltLoop,
    };

    // ----------------
    // Static Variables
    // ----------------

    struct Static : RSDK::GameObject::Static {};
    struct ModStatic : RSDK::GameObject::Static {};

    // ----------------
    // Entity Variables
    // ----------------

    int32 dioramaID;
    int32 lastDioramaID;
    int32 timer;
    uint8 parentActivity;
    bool32 needsSetup;
    ManiaStateMachine(state);
    ManiaStateMachine(stateDraw);
    UIControl *parent;
    int32 maskColor;
    RSDK::Vector2 dioramaPos;
    RSDK::Vector2 dioramaSize;
    RSDK::Animator maskAnimator;
    RSDK::Animator staticAnimator;
    int32 values[16];
    RSDK::Vector2 vectors[16];
    RSDK::Animator animators[16];
    RSDK::String texts[16];

    // ----------------------
    // Standard Entity Events
    // ----------------------

    // -------------
    // Object States
    // -------------

    // -------------------
    // Static Declarations
    // -------------------

    MOD_DECLARE(UIDiorama)
};

} // namespace GameLogic