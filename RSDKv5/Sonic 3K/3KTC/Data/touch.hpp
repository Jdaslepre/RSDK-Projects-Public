#pragma once
#include "GameAPI/Game.hpp"

using namespace RSDK;

// ------------------
// Macros/Definitions
// ------------------

// #define CheckTouchPause() (Touch::CheckRect(screenInfo->size.x - 0x80, 0, screenInfo->size.x, 0x40, 0, 0) >= 0)

#define CheckTouchPause()                                                                                                                            \
    (!sceneInfo->debugMode ? Touch::CheckRect(screenInfo->size.x - 0x80, 0, screenInfo->size.x, 0x40, 0, 0) >= 0                                     \
                           : Touch::CheckRect(screenInfo->size.x - 0x80, 0, screenInfo->size.x, 0x20, 0, 0) >= 0)

#define CheckAnyTouch() (Touch::CheckRect(0, 0, screenInfo->size.x, screenInfo->size.y, 0, 0) >= 0)

namespace GameLogic {
struct Touch {
    static int32 CheckRect(int32 x1, int32 y1, int32 x2, int32 y2, int32 *fx, int32 *fy);
    static void Control4Dir(ControllerState *controller);
    static void Control8Dir(ControllerState *controller);
};
} // namespace GameLogic