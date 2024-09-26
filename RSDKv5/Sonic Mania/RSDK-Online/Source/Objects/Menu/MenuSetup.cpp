#include "RSDK-Online.hpp"

using namespace RSDK;

namespace GameLogic {

// -------------------
// Object Registration
// -------------------

MOD_REGISTER_OBJECT(MenuSetup);

// ----------------
// Public Functions
// ----------------

int32 (*MenuSetup_GetActiveMenu)(void);
void (*MenuSetup_SetBGColors)(void);

// ----------------------
// Standard Entity Events
// ----------------------

void MenuSetup::Update() {

    if (controllerInfo[Input::CONT_ANY].keyY.down) {
        String str{};
        str.Init("This room is full.\rReturning to title screen.");
        Dev::Print(Dev::PRINT_NORMAL, "aaaaaaar");
        UIDialog_CreateDialogOk(&str, StateMachine_None, true);
    }

    sVars->Super(SUPER_UPDATE);
}

// ----------------------
// Extra Entity Functions
// ----------------------

void MenuSetup::SetBGColors() {
    if (MultiplayerMenu::sVars->isMenuActive) {
        // i was trying to guess the encore index from memory but instead ended up with this
        // cool looking red background, so we'll be keeping it lol
        UIBackground::sVars->activeColors = &UIBackground::sVars->bgColors[9];
    }
}

} // namespace GameLogic