#pragma once
#include "GameAPI/Game.hpp"

// ------------------
// Macros/Definitions
// ------------------

#define DEBUGMODE_OBJECT_COUNT (0x100)

namespace GameLogic {

struct DebugMode : RSDK::GameObject::Entity {

    // ----------------
    // Static Variables
    // ----------------

    struct Static : RSDK::GameObject::Static {
        int16 classIDs[DEBUGMODE_OBJECT_COUNT];
        RSDK::StateMachine<DebugMode> draw[DEBUGMODE_OBJECT_COUNT];
        RSDK::StateMachine<DebugMode> spawn[DEBUGMODE_OBJECT_COUNT];
        RSDK::Animator animator;
        int32 itemID;
        int32 itemCount;
        bool32 debugActive;
        uint8 itemType;
        uint8 itemTypeCount;
        int32 unused1;
        int32 unused2;
    };

    struct ModStatic : RSDK::GameObject::Static {
        RSDK::SpriteAnimation aniFrames;
        RSDK::Animator animator;
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