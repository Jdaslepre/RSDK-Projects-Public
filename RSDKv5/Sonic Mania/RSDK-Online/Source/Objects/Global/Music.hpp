#pragma once
#include "RSDK-Online.hpp"

// ------------------
// Macros/Definitions
// ------------------

#define Music_IsPlaying RSDK::RSDKTable->ChannelActive(Music::sVars->channelID)

namespace GameLogic {

struct Music : RSDK::GameObject::Entity {

    // ----------------
    // Static Variables
    // ----------------

    struct Static : RSDK::GameObject::Static {
        char trackNames[16][32];
        uint32 trackLoops[16];
        int32 trackStartPos;
        int32 channelID;
        int32 activeTrack;
#if MANIA_USE_PLUS
        int32 nextTrack;
        int32 restartTrackID;
#else
        int32 prevTrack;
        int32 queuedTrack;
        int32 nextTrack;
        bool32 playingRegularTrack;
        bool32 playingDrownTrack;
        bool32 playing1UPTrack;
#endif
        RSDK::SpriteAnimation aniFrames;
    };

    struct ModStatic : RSDK::GameObject::Static {};

    // -------------------
    // Static Declarations
    // -------------------

    MOD_DECLARE(Music)
};

// ----------------
// Public Functions
// ----------------

extern void (*Music_PlayTrack)(uint8 trackID);
extern void (*Music_TransitionTrack)(uint8 trackID, float fadeSpeed);
extern void (*Music_FadeOut)(float fadeSpeed);

} // namespace GameLogic