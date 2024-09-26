#include "RSDK-Online.hpp"

using namespace RSDK;

namespace GameLogic {

// -------------------
// Object Registration
// -------------------

MOD_REGISTER_OBJECT(Music);

// ----------------
// Public Functions
// ----------------

void (*Music_PlayTrack)(uint8 trackID);
void (*Music_TransitionTrack)(uint8 trackID, float fadeSpeed);
void (*Music_FadeOut)(float fadeSpeed);

} // namespace GameLogic