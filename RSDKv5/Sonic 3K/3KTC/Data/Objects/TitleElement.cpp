#include "../3KTC.hpp"

using namespace RSDK;

namespace GameLogic {

// -------------------
// Object Registration
// -------------------

MOD_REGISTER_OBJECT(TitleElement);

// ----------------------
// Standard Entity Events
// ----------------------

void TitleElement::Create(void *data) {
    sVars->Super(SUPER_CREATE, data);

    if (!sceneInfo->inEditor && this->type == Types::TypeStart)
        this->animator.SetAnimation(sVars->aniFrames, 5, true, 13); // "Touch to Start"
}

} // namespace GameLogic