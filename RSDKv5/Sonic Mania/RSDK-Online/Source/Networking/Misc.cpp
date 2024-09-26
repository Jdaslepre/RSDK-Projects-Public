#include "RSDK-Online.hpp"

using namespace RSDK;

bool32 onlineActive       = false;
int32 Misc::callbackState = 0;

void Misc::ModUpdateCB(void *) {

    // This switch handles the networking part of RSDKv4's
    // RetroGameLoop_Main

    switch (Misc::callbackState) {
        case OnlineCBStates::CONNECT2PVS:
            // ...
            Misc::callbackState = OnlineCBStates::WAIT2PVS;
            break;
        case OnlineCBStates::WAIT2PVS:
            // wait for vs response
            if (dcError)
                GameObject::Create<GameLogic::MultiplayerHandler>(nullptr, NULL, NULL);
            break;
        default: break;
    }
}

void Misc::StrCopy(char *dest, const char *src) {
#ifdef USE_STDLIB
    strcpy(dest, src);
#else
    int i = 0;
    for (; src[i]; ++i) dest[i] = src[i];
    dest[i] = 0;
#endif
}