#pragma once
#include "RSDK-Online.hpp"

namespace GameLogic {

struct MultiplayerHandler : RSDK::GameObject::Entity {

    // ---------------
    // Enums & Structs
    // ---------------

    enum DCErrorTypes {
        ErrorNone,
        PlayerDisconnected,
        ConnectionTimeOut,
        RoomFull,
        ConnectionRetryFailed,
        RoomInvalid,
    };

    // ----------------
    // Static Variables
    // ----------------

    struct Static : RSDK::GameObject::Static {
        uint16 tintLookupTable[1 << 16];
    };

    struct ModStatic : RSDK::GameObject::Static {};

    // ----------------
    // Entity Variables
    // ----------------

    RSDK::StateMachine<MultiplayerHandler> state;
    bool32 hasError;
    float timer;
    char buf[0x30];

    // ----------------------
    // Standard Entity Events
    // ----------------------

    void Create(void *data);
    void Update();

    // ----------------------
    // Extra Entity Functions
    // ----------------------

    void SetupDialogTint();

    // -------------
    // Object States
    // -------------

    void State_Idle();
    void State_WaitForRegular();
    void State_DisplayError();
    void State_Exit();

    // -------------------
    // Static Declarations
    // -------------------

    MOD_DECLARE(MultiplayerHandler)
};
} // namespace GameLogic