#pragma once

struct ModConfig {
    float vDPadSize;
    float vDPadOpacity;
    RSDK::Vector2 moveDPadPos;
    RSDK::Vector2 jumpDPadPos;
    // not actually part of the config
    // just needed a place to put these
    bool *usePathTracer;
    const bool32 useTouchControls = true;
};

extern ModConfig config;