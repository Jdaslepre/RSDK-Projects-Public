#include "RSDK-Online.hpp"

using namespace RSDK;

namespace GameLogic {

// -------------------
// Object Registration
// -------------------

MOD_REGISTER_OBJECT(MainMenu);

// ----------------
// Public Functions
// ----------------

bool32 (*MainMenu_BackPressCB_ReturnToTitle)(void);

// ----------------------
// Standard Entity Events
// ----------------------

void MainMenu::StaticUpdate() {
    UIControl *control = sVars->menuControl;

    if (control && control->active) {
        UIDiorama *diorama            = sVars->diorama;
        sVars->confirmPrompt->visible = ((int32)(control->shifter->shiftOffset.y & 0xFFFF0000)) > -0x700000;
        UIButton *button              = control->buttons[control->lastButtonID];

        if (button) {
            switch (button->frameID) {
                case 0: diorama->dioramaID = UIDiorama::IDManiaMode; break;
                case 1: diorama->dioramaID = UIDiorama::IDTimeAttack; break;
                case 2: diorama->dioramaID = UIDiorama::IDCompetition; break;
                case 3: diorama->dioramaID = UIDiorama::IDOptions; break;
                case 4: diorama->dioramaID = UIDiorama::IDExtras; break;
                case 5: diorama->dioramaID = UIDiorama::IDEncoreMode; break;
                case 6: diorama->dioramaID = UIDiorama::IDPlusUpsell; break;
                case 7: diorama->dioramaID = UIDiorama::IDExit; break;
                default: break;
            }

            if (button->disabled)
                diorama->timer = 12;
        }
    }
}

} // namespace GameLogic