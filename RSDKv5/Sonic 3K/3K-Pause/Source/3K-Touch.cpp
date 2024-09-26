#pragma once
#include "3K-Pause.hpp"

namespace GameLogic
{
namespace Touch
{

int32 (*CheckRect)(int32 x1, int32 y1, int32 x2, int32 y2, int32 *fx, int32 *fy) = nullptr;
void (*Control4Dir)(RSDK::ControllerState *controller) = nullptr;
void (*Control8Dir)(RSDK::ControllerState *controller) = nullptr;

} // namespace Touch
} // namespace GameLogic