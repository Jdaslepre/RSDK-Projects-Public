#pragma once
#include "RSDK-Online.hpp"

namespace GameLogic {

struct MenuParam : RSDK::GameObject::Entity {

    // ----------------
    // Static Variables
    // ----------------

    struct Static : RSDK::GameObject::Static {};
    struct ModStatic : RSDK::GameObject::Static {};

    // ----------------
    // Entity Variables
    // ----------------

    uint8 puyoSelection;
    uint8 bssSelection;
    char menuTag[0x100];
    int32 menuSelection;
    bool32 startedTAAttempt; // only used in pre-plus, goes unused by the time plus rolled around
    bool32 inTimeAttack;
    int32 replayID;
    int32 characterID;
    int32 zoneID;
    int32 actID;
    int32 timeAttackRank;
#if MANIA_USE_PLUS
    bool32 isEncoreMode;
    int32 replayUUID;
    bool32 viewReplay;
    bool32 showGhost;
    uint8 selectedReplay;
    uint8 replayRankID;
#else
    int32 timeScore;
#endif
    int32 unused2;
    int32 unused3;
    int32 unused4;
    int32 unused5;
    int32 vsZoneID;
    int32 vsActID;
    int32 creditsReturnToMenu;

    // -------------------
    // Static Declarations
    // -------------------

    MOD_DECLARE(MenuParam)
};

// ----------------
// Public Functions
// ----------------

extern MenuParam *(*MenuParam_GetParam)(void);

} // namespace GameLogic