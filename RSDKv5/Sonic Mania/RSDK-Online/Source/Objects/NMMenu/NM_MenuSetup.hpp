#pragma once
#include "RSDK-Online.hpp"

namespace GameLogic {

struct NM_MenuSetup : RSDK::GameObject::Entity {

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
        color bgColor[3];
    };
    struct ModStatic : RSDK::GameObject::Static {};

    // ----------------
    // Entity Variables
    // ----------------

    RSDK::StateMachine<NM_MenuSetup> state;
    RSDK::StateMachine<NM_MenuSetup> stateDraw;
    uint16 fade;

    // ----------------------
    // Standard Entity Events
    // ----------------------

    void Create(void *data);
    void Update();
    void Draw();
    static void StageLoad();

    static void ReturnToTitle();

    // -------------
    // Object States
    // -------------

    void State_Init();
    void State_FadeIn();
    void State_Idle();
    void State_WaitForRegular();
    void State_DisplayError();
    void State_Exit();

    // -----------
    // Draw States
    // -----------

    void Draw_Fade();
    void Draw_None();

    // -------------------
    // Static Declarations
    // -------------------

    MOD_DECLARE(NM_MenuSetup)
};
} // namespace GameLogic