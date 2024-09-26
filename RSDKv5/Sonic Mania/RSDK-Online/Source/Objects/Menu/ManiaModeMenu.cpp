#include "RSDK-Online.hpp"

using namespace RSDK;

namespace GameLogic {

// -------------------
// Object Registration
// -------------------

MOD_REGISTER_OBJECT(ManiaModeMenu);

// ----------------
// Public Functions
// ----------------

void (*ManiaModeMenu_StartReturnToTitle)(void);

void ManiaModeMenu::StaticUpdate() {
    for (auto button : GameObject::GetEntities<UIButton>(FOR_ALL_ENTITIES)) {
        switch (button->listID) {
            // Abusing the extras button for now, until i feel like making a proper one
            case 1:
                if (button->frameID == 4)
                    button->actionCB = MultiplayerMenu::OpenPlayerSelect_CB;
                break;
        }
    }
    MultiplayerMenu::Initialize();

    if (!modSVars->initialized) {
        ManiaModeMenu::InitializeExtra();
        MultiplayerMenu::Initialize();
        modSVars->initialized = true;
    }
}

void ManiaModeMenu::InitializeExtra() {
    //
    ManiaModeMenu::SetupActions();
}

void ManiaModeMenu::SetupActions() {
    foreach_all(UIButton, button) {
        switch (button->listID) {
            // Abusing the extras button for now, until i feel like making a proper one
            case 1:
                if (button->frameID == 4)
                    button->actionCB = MultiplayerMenu::OpenPlayerSelect_CB;
                break;
        }
    }
}

} // namespace GameLogic