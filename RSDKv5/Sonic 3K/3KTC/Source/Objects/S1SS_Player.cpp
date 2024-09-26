#include "../3KTC.hpp"

using namespace RSDK;

namespace GameLogic {

// -------------------
// Object Registration
// -------------------

MOD_REGISTER_OBJECT(S1SS_Player);

// -------------
// Object States
// -------------

Action<void> S1SS_Player::State_Static;

// ----------------------
// Standard Entity Events
// ----------------------

void S1SS_Player::Update(void) {
    // S1SS_Player uses Player::Input_Gamepad which we've already
    // hooked - but due to the way that this object handles its
    // controls, we'll have to do this instead
    this->HandleTouchInputs();
    sVars->Super(SUPER_UPDATE);
}

// The v5U decomp isn't currently able to do super for
// StaticLoad, so here's a clone of it
void S1SS_Player::StaticLoad(Static *sVars) {
    RSDK_INIT_STATIC_VARS(S1SS_Player);

    sVars->aniFrames.Init();
    sVars->tailSpriteFrames.Init();

    sVars->ringExtraLife = 100;
    sVars->savedLives    = 3;
    sVars->savedScore1UP = 50000;
}

// ----------------------
// Extra Entity Functions
// ----------------------

void S1SS_Player::HandleTouchInputs(void) {
    if (this->controllerID < PLAYER_COUNT) {
        ControllerState *controller = &controllerInfo[this->controllerID];

        Touch::Control4Dir(controller);

        int32 jumpX = screenInfo->center.x;
        int32 jumpY = 96;

        // fixes a bug with button vs touch
        bool32 touchedJump = false;
        if (Touch::CheckRect(jumpX, jumpY, screenInfo->size.x, screenInfo->size.y, nullptr, nullptr) >= 0) {
            controllerInfo->keyA.down |= true;
            controller->keyA.down = true;
            touchedJump           = true;
        }

        bool32 touchedPause = false;
        if (CheckTouchPause()) {
            controllerInfo->keyStart.down |= true;
            controller->keyStart.down = true;
            touchedPause              = true;
        }

        bool32 touchedDebug = false;
        if (sceneInfo->debugMode) {
            if (Touch::CheckRect(0, 0, 112, 56, nullptr, nullptr) >= 0) {
                controllerInfo->keyX.down |= true;
                controller->keyX.down = true;
                touchedDebug          = true;
            }
        }

        if (!modSVars->touchJump && touchedJump) {
            controllerInfo->keyA.press |= controllerInfo->keyA.down;
            controller->keyA.press |= controller->keyA.down;
        }
        modSVars->touchJump = controller->keyA.down;

        if (!modSVars->touchDebug && touchedDebug) {
            controllerInfo->keyX.press |= controllerInfo->keyX.down;
            controller->keyX.press |= controller->keyX.down;
        }
        modSVars->touchDebug = controller->keyX.down;

        if (!modSVars->touchPause && touchedPause) {
            controllerInfo->keyStart.press |= controllerInfo->keyStart.down;
            controller->keyStart.press |= controller->keyStart.down;
        }
        modSVars->touchPause = controller->keyStart.down;
    }
}

} // namespace GameLogic