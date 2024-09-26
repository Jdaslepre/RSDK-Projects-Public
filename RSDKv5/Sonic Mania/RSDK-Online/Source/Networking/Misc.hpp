#pragma once

extern bool32 onlineActive;

struct Misc {
    enum OnlineCBStates {
        CONNECT2PVS = 0x80,
        WAIT2PVS    = 0x81,
    };

    // "replacement" for Engine.gameMode
    static int32 callbackState;

    static void ModUpdateCB(void *);
    static void StrCopy(char *dest, const char *src);
};
