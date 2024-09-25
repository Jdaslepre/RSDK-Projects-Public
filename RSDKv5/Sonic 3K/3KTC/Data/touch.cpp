#include "3KTC.hpp"

using namespace RSDK;

namespace GameLogic {

int8 dirPressed = 0b0000;

int32 Touch::CheckRect(int32 x1, int32 y1, int32 x2, int32 y2, int32 *fx, int32 *fy) {
    if (fx)
        *fx = 0;
    if (fy)
        *fy = 0;

    for (int32 t = 0; t < touchInfo->count; ++t) {
        int32 tx = (int32)(touchInfo->x[t] * screenInfo->size.x);
        int32 ty = (int32)(touchInfo->y[t] * screenInfo->size.y);

        if (touchInfo->down[t]) {
            if (tx >= x1 && ty >= y1 && tx <= x2 && ty <= y2) {
                if (fx)
                    *fx = tx;
                if (fy)
                    *fy = ty;

                return t;
            }
        }
    }

    return -1;
}

// ---------------
// Input Functions
// ---------------

void Touch::Control4Dir(ControllerState *controller) {
    int32 tx = 0, ty = 0;
    if (Touch::CheckRect(0, 96, screenInfo->center.x, screenInfo->size.y, &tx, &ty) >= 0) {
        tx -= config.moveDPadPos.x;
        ty -= config.moveDPadPos.y;

        switch (((Math::ATan2(tx, ty) + 32) & 0xFF) >> 6) {
            case 0:
                if (!GET_BIT(dirPressed, 0)) {
                    controllerInfo->keyRight.press |= true;
                    if (controller)
                        controller->keyRight.press = true;
                }

                controllerInfo->keyRight.down |= true;
                if (controller)
                    controller->keyRight.down = true;
                dirPressed = 0b0001;
                break;

            case 1:
                if (!GET_BIT(dirPressed, 1)) {
                    controllerInfo->keyDown.press |= true;
                    if (controller)
                        controller->keyDown.press = true;
                }

                controllerInfo->keyDown.down |= true;
                if (controller)
                    controller->keyDown.down = true;
                dirPressed = 0b0010;
                break;

            case 2:
                if (!GET_BIT(dirPressed, 2)) {
                    controllerInfo->keyLeft.press |= true;
                    if (controller)
                        controller->keyLeft.press = true;
                }

                controllerInfo->keyLeft.down |= true;
                if (controller)
                    controller->keyLeft.down = true;
                dirPressed = 0b0100;
                break;

            case 3:
                if (!GET_BIT(dirPressed, 3)) {
                    controllerInfo->keyUp.press |= true;
                    if (controller)
                        controller->keyUp.press = true;
                }

                controllerInfo->keyUp.down |= true;
                if (controller)
                    controller->keyUp.down = true;
                dirPressed = 0b1000;
                break;
        }
    } else
        dirPressed = 0b0000;
}

void Touch::Control8Dir(ControllerState *controller) {
    int32 tx = 0, ty = 0;
    if (Touch::CheckRect(0, 96, screenInfo->center.x, screenInfo->size.y, &tx, &ty) >= 0) {
        tx -= config.moveDPadPos.x;
        ty -= config.moveDPadPos.y;

        switch (((Math::ATan2(tx, ty) + 16) & 0xFF) >> 5) {
            case 0:
                if (!GET_BIT(dirPressed, 0)) {
                    controllerInfo->keyRight.press |= true;
                    if (controller)
                        controller->keyRight.press = true;
                }

                controllerInfo->keyRight.down |= true;
                if (controller)
                    controller->keyRight.down = true;
                dirPressed = 0b0001;
                break;

            case 1:
                if (!GET_BIT(dirPressed, 0)) {
                    controllerInfo->keyRight.press |= true;
                    if (controller)
                        controller->keyRight.press = true;
                }
                if (!GET_BIT(dirPressed, 1)) {
                    controllerInfo->keyDown.press |= true;
                    if (controller)
                        controller->keyDown.press = true;
                }

                controllerInfo->keyRight.down |= true;
                controllerInfo->keyDown.down |= true;
                if (controller) {
                    controller->keyRight.down = true;
                    controller->keyDown.down  = true;
                }
                dirPressed = 0b0011;
                break;

            case 2:
                if (!GET_BIT(dirPressed, 1)) {
                    controllerInfo->keyDown.press |= true;
                    if (controller)
                        controller->keyDown.press = true;
                }

                controllerInfo->keyDown.down |= true;
                if (controller)
                    controller->keyDown.down = true;
                dirPressed = 0b0010;
                break;

            case 3:
                if (!GET_BIT(dirPressed, 1)) {
                    controllerInfo->keyDown.press |= true;
                    if (controller)
                        controller->keyDown.press = true;
                }
                if (!GET_BIT(dirPressed, 2)) {
                    controllerInfo->keyLeft.press |= true;
                    if (controller)
                        controller->keyLeft.press = true;
                }

                controllerInfo->keyDown.down |= true;
                controllerInfo->keyLeft.down |= true;
                if (controller) {
                    controller->keyDown.down = true;
                    controller->keyLeft.down = true;
                }
                dirPressed = 0b0110;
                break;

            case 4:
                if (!GET_BIT(dirPressed, 2)) {
                    controllerInfo->keyLeft.press |= true;
                    if (controller)
                        controller->keyLeft.press = true;
                }

                controllerInfo->keyLeft.down |= true;
                if (controller)
                    controller->keyLeft.down = true;
                dirPressed = 0b0100;
                break;

            case 5:
                if (!GET_BIT(dirPressed, 2)) {
                    controllerInfo->keyLeft.press |= true;
                    if (controller)
                        controller->keyLeft.press = true;
                }
                if (!GET_BIT(dirPressed, 3)) {
                    controllerInfo->keyUp.press |= true;
                    if (controller)
                        controller->keyUp.press = true;
                }

                controllerInfo->keyLeft.down |= true;
                controllerInfo->keyUp.down |= true;
                if (controller) {
                    controller->keyLeft.down = true;
                    controller->keyUp.down   = true;
                }
                dirPressed = 0b1100;
                break;

            case 6:
                if (!GET_BIT(dirPressed, 3)) {
                    controllerInfo->keyUp.press |= true;
                    if (controller)
                        controller->keyUp.press = true;
                }

                controllerInfo->keyUp.down |= true;
                if (controller)
                    controller->keyUp.down = true;
                dirPressed = 0b1000;
                break;

            case 7:
                if (!GET_BIT(dirPressed, 3)) {
                    controllerInfo->keyUp.press |= true;
                    if (controller)
                        controller->keyUp.press = true;
                }
                if (!GET_BIT(dirPressed, 0)) {
                    controllerInfo->keyRight.press |= true;
                    if (controller)
                        controller->keyRight.press = true;
                }

                controllerInfo->keyUp.down |= true;
                controllerInfo->keyRight.down |= true;
                if (controller) {
                    controller->keyUp.down    = true;
                    controller->keyRight.down = true;
                }
                dirPressed = 0b1001;
                break;
        }
    } else
        dirPressed = 0b0000;
}
} // namespace GameLogic