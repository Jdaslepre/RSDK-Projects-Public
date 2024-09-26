#include "../3KTC.hpp"

using namespace RSDK;

namespace GameLogic {

// -------------------
// Object Registration
// -------------------

MOD_REGISTER_OBJECT(S3K_SS_Player);

// -------------
// Object States
// -------------

Action<void> S3K_SS_Player::Input_Gamepad;

// ----------------------
// Extra Entity Functions
// ----------------------

bool32 S3K_SS_Player_Input_Gamepad_Hook(bool32 skippedState) {
    auto self = ((S3K_SS_Player *)sceneInfo->entity);

    if (self->controllerID < PLAYER_COUNT) {
        ControllerState *controller = &controllerInfo[self->controllerID];

        Touch::Control4Dir(controller);

        // fixes a bug with button vs touch
        bool32 touchedJump = false;
        if (Touch::CheckRect(screenInfo->center.x, 96, screenInfo->size.x, screenInfo->size.y, NULL, NULL) >= 0) {
            controllerInfo->keyA.down |= true;
            controller->keyA.down = true;
            touchedJump           = true;
        }

        bool32 touchedPause = false;
        if (Touch::CheckRect(screenInfo->center.x - 0x80, 0, screenInfo->center.x + 80, 0x40, NULL, NULL) >= 0) {
            controllerInfo->keyStart.down |= true;
            controller->keyStart.down = true;
            touchedPause              = true;
        }

        if (!S3K_SS_Player::modSVars->touchJump && touchedJump) {
            controllerInfo->keyA.press |= controllerInfo->keyA.down;
            controller->keyA.press |= controller->keyA.down;
        }
        S3K_SS_Player::modSVars->touchJump = controller->keyA.down;

        if (!S3K_SS_Player::modSVars->touchPause && touchedPause) {
            controllerInfo->keyStart.press |= controllerInfo->keyStart.down;
            controller->keyStart.press |= controller->keyStart.down;
        }
        S3K_SS_Player::modSVars->touchPause = controller->keyStart.down;
    }

    return false;
}

} // namespace GameLogic