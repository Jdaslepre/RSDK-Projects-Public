#pragma once
#include "GameAPI/Game.hpp"

#define CheckTouchPause()                                                                                                                            \
    (!sceneInfo->debugMode ? Touch::CheckRect(screenInfo->size.x - 0x80, 0, screenInfo->size.x, 0x40, nullptr, nullptr) >= 0                         \
                           : Touch::CheckRect(screenInfo->size.x - 0x80, 0, screenInfo->size.x, 0x20, nullptr, nullptr) >= 0)

#define CheckAnyTouch() (Touch::CheckRect(0, 0, screenInfo->size.x, screenInfo->size.y, nullptr, nullptr))

namespace GameLogic
{
namespace Touch
{

extern int32 (*CheckRect)(int32 x1, int32 y1, int32 x2, int32 y2, int32 *fx, int32 *fy);
extern void (*Control4Dir)(RSDK::ControllerState *controller);
extern void (*Control8Dir)(RSDK::ControllerState *controller);

} // namespace Touch
} // namespace GameLogic