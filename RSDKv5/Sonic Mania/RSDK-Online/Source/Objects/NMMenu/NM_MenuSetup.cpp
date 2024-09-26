// unused

#include "RSDK-Online.hpp"

using namespace RSDK;

namespace GameLogic {

// -------------------
// Object Registration
// -------------------

MOD_REGISTER_OBJECT(NM_MenuSetup);

// ----------------
// Public Functions
// ----------------

// -------------
// Entity Events
// -------------

void NM_MenuSetup::Update() {
    this->state.Run(this);
    //
}

void NM_MenuSetup::Draw() {
    this->stateDraw.Run(this);
    //
}

void NM_MenuSetup::Create(void *data) {
    if (!sceneInfo->inEditor) {
        this->active    = ACTIVE_ALWAYS;
        this->visible   = true;
        this->drawGroup = 12;
        this->state.Set(&NM_MenuSetup::State_Init);
        this->stateDraw.Set(&NM_MenuSetup::Draw_Fade);
        this->fade = 640;
    }
}

void NM_MenuSetup::StageLoad() {
    // Check if UIBackground exists before trying
    // to do anything with it, just to be safe :)

    if (UIBackground::sVars) {
        sVars->bgColor[0]                 = 0x343951;
        sVars->bgColor[1]                 = 0x595C7F;
        sVars->bgColor[2]                 = 0x232433;
        UIBackground::sVars->activeColors = sVars->bgColor;
    }
}

void NM_MenuSetup::ReturnToTitle() {
    // Returning to the title screen, as promised
    Stage::SetScene("Presentation", "Title Screen");

    // Create the screen fade
    FXFade *fxFade          = GameObject::Create<FXFade>(nullptr, NULL, NULL);
    fxFade->active          = ACTIVE_ALWAYS;
    fxFade->state           = FXFade_State_FadeOut;
    fxFade->drawGroup       = DRAWGROUP_COUNT - 1;
    fxFade->timer           = 0;
    fxFade->oneWay          = true;
    fxFade->speedIn         = 12;
    fxFade->speedOut        = 12;

    // This will load our set scene when
    // the fade is complete
    fxFade->transitionScene = true;
}

// -------------
// Object States
// -------------

void NM_MenuSetup::State_Init() {
    SET_CURRENT_STATE();

    this->state.Set(&NM_MenuSetup::State_FadeIn);
}

void NM_MenuSetup::State_FadeIn() {
    SET_CURRENT_STATE();

    if (this->fade <= 0) {
        this->fade = 0;
        this->state.Set(&NM_MenuSetup::State_Idle);
        this->stateDraw.Set(StateMachine_None);
    } else {
        this->fade -= 16;
    }
}

int32 sigma;
int32 evSigma;

void NM_MenuSetup::State_Idle() {
    // Testing

    if (controllerInfo[Input::CONT_ANY].keyLeft.press) {
        String str{};
        str.Init("COULDN'T CONNECT AFTER 10 RETRIES.\nRETURNING TO TITLE SCREEN.");

        UIDialog *dialog = UIDialog_CreateDialogOk(&str, NM_MenuSetup::ReturnToTitle, true);
    }

    if (controllerInfo[Input::CONT_ANY].keyRight.press) {
        String str{};
        str.Init("THE OTHER PLAYER HAS DISCONNECTED.\nRETURNING TO TITLE SCREEN.");
        onlineActive = true;
        int32 len    = 4;
        int32 mode   = ManiaItemModes::ITEMS_FIXED;
        UserData::Connect2PVS(&len, &mode);

        UIDialog *dialog = UIDialog_CreateDialogOk(&str, StateMachine_None, true);
    }

    sigma++;
    if (sigma >= 64) {
        sigma = 0;

        if (!evSigma) {
            int32 code = GetRoomCode();
            if (code) {
                char buffer[0x30];
                int code = GetRoomCode();
                sprintf_s(buffer, "%08X", code);
                evSigma = code;
            }
        }

        Dev::PrintInt32(Dev::PRINT_NORMAL, "room code", evSigma);
    }
}

// -------------
// Object States
// -------------

void NM_MenuSetup::Draw_Fade() {
    SET_CURRENT_STATE();

    Graphics::FillScreen(0x000000, this->fade, this->fade - 128, this->fade - 256);
}

} // namespace GameLogic