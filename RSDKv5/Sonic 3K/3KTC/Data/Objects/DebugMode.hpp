#pragma once
#include "GameAPI/Game.hpp"

using namespace RSDK;

// ------------------
// Macros/Definitions
// ------------------

#define DEBUGMODE_OBJECT_COUNT (0x100)

namespace GameLogic {

struct DebugMode : GameObject::Entity {

    // ----------------
    // Static Variables
    // ----------------

    struct Static : GameObject::Static {
        int16 classIDs[DEBUGMODE_OBJECT_COUNT];
        StateMachine<DebugMode> draw[DEBUGMODE_OBJECT_COUNT];
        StateMachine<DebugMode> spawn[DEBUGMODE_OBJECT_COUNT];
        Animator animator;
        int32 itemID;
        int32 itemCount;
        bool32 debugActive;
        uint8 itemType;
        uint8 itemTypeCount;
        int32 unused1;
        int32 unused2;
    };

    struct ModStatic : GameObject::Static {
        SpriteAnimation aniFrames;
        Animator animator;
    };

    // ----------------------
    // Standard Entity Events
    // ----------------------

    void Update(void);
    void Draw(void);
    static void StageLoad(void);

    // -------------------
    // Static Declarations
    // -------------------

    MOD_DECLARE(DebugMode)
};
} // namespace GameLogic