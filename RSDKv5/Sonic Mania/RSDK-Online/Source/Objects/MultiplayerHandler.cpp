#include "RSDK-Online.hpp"

using namespace RSDK;

namespace GameLogic {

// -------------------
// Object Registration
// -------------------

MOD_REGISTER_OBJECT(MultiplayerHandler);

// -------------
// Object States
// -------------

// ----------------------
// Standard Entity Events
// ----------------------

void MultiplayerHandler::Update() {
    if (dcError && !this->state.Matches(&MultiplayerHandler::State_Exit))
        this->state.Set(&MultiplayerHandler::State_DisplayError);

    this->state.Run(this);
}

void MultiplayerHandler::Create(void *data) {
    this->active        = ACTIVE_NORMAL;
    this->updateRange.x = 0x800000;
    this->updateRange.y = 0x800000;
    this->state.Set(&MultiplayerHandler::State_WaitForRegular);

    Dev::Print(Dev::PRINT_NORMAL, "MultiplayerHandler Created");
}

// ----------------------
// Extra Entity Functions
// ----------------------

// copied from PauseMenu_SetupTintTable, handles the gray
// tint effect applied on the screen when an error dialog
// is active (handled in UIMultiplayerPanel::Draw)
void MultiplayerHandler::SetupDialogTint() {
    for (int32 i = 0; i < (1 << 16); ++i) {
        uint32 r = (0x20F * (i >> 11) + 23) >> 6;
        uint32 g = (0x103 * ((i >> 5) & 0x3F) + 33) >> 6;
        uint32 b = (0x20F * (i & 0x1F) + 23) >> 6;

        int32 brightness = MIN(((b + g + r) << 8) / 680, 0xFF);

        sVars->tintLookupTable[i] = (brightness >> 3) | ((brightness >> 2) << 5) | ((brightness >> 3) << 11);
    }
}

// -------------
// Object States
// -------------

void MultiplayerHandler::State_Idle() {
    SET_CURRENT_STATE();

    if (!(sceneInfo->activeCategory & 1)) {
        this->state.Set(&MultiplayerHandler::State_WaitForRegular);
        return;
    }

    if (this->timer >= 0.25f && !waitingForPing) {
        waitingForPing = true;
        this->timer    = 0;
        if (lastPing < 800.0f) {
            sprintf_s(this->buf, "Ping: %.1fms", lastPing);
            // this->pingLabel->g = 0xFF;
            // this->pingLabel->b = 0xFF;
        } else if (lastPing < 2000.0f) {
            // this->pingLabel->g = 0xFF;
            // this->pingLabel->b = 0x30;
            sprintf_s(this->buf, "Ping: %.2fs", lastPing / 1000);
        } else {
            // this->pingLabel->g = 0x30;
            // this->pingLabel->b = 0x30;
            sprintf_s(this->buf, "Ping: %.0fs", this->timer);
        }
        // SetStringToFont8(self->pingLabel->text, buf, FONT_TEXT);
    } else if (this->timer >= 10.0f) {
        DisconnectNetwork();
        dcError = DCErrorTypes::ConnectionTimeOut;
        this->state.Set(&MultiplayerHandler::State_DisplayError);
        vsPlaying = false;
    } else if (this->timer >= 5.0f && waitingForPing) {
        // this->pingLabel->g = 0xCF * (fmod(this->timer, .5) >= .25) + 0x30;
        // this->pingLabel->b = 0xCF * (fmod(this->timer, .5) >= .25) + 0x30;
        // this->pingLabel->alignPtr(this->pingLabel, ALIGN_CENTER);
        // this->pingLabel->x += 28.0f;
        sprintf_s(buf, " !! %.2fs !!", 10 - this->timer);
        // SetStringToFont8(self->pingLabel->text, buf, FONT_TEXT);
    }
    // SetRenderBlendMode(RENDER_BLEND_ALPHA);
    // RenderRect(SCREEN_XSIZE_F / 2 - 68, -(SCREEN_YSIZE_F / 2) + 16, 160, 68, 16, 0, 0, 0, 0x80);
}

void MultiplayerHandler::State_WaitForRegular() {
    SET_CURRENT_STATE();

    if (!vsPlaying) {
        if (dcError) {
            this->state.Set(&MultiplayerHandler::State_DisplayError);
        } else {
            // this->pingLabel->Destroy();
            // this->errorPanel->Destroy();
            this->Destroy();
        }
    } else if (sceneInfo->activeCategory & 1) {
        this->state.Set(&MultiplayerHandler::State_Idle);
    }
}

void MultiplayerHandler::State_DisplayError() {
    SET_CURRENT_STATE();

    Music_FadeOut(0.075);
    this->SetupDialogTint();

    String str{};

    char *errorString = (char *)"";
    switch (dcError) {
        case DCErrorTypes::PlayerDisconnected: errorString = (char *)"THE OTHER PLAYER HAS DISCONNECTED.\nRETURNING TO TITLE SCREEN."; break;
        case DCErrorTypes::ConnectionTimeOut: errorString = (char *)"CONNECTION TIMED OUT.\nRETURNING TO TITLE SCREEN."; break;
        case DCErrorTypes::RoomFull: errorString = (char *)"THIS ROOM IS FULL.\nRETURNING TO TITLE SCREEN.";
        // [Fallthrough]
        case DCErrorTypes::RoomInvalid:
            if (!errorString)
                errorString = (char *)"THIS ROOM DOESN'T EXIST.\nRETURNING TO TITLE SCREEN.";

            // self->fadeError->timer = self->fadeError->delay;

            for (auto menu : GameObject::GetEntities<MultiplayerMenu>(FOR_ACTIVE_ENTITIES)) {
                menu->Destroy();
            }

            break;
        case DCErrorTypes::ConnectionRetryFailed: errorString = (char *)"COULDN'T CONNECT AFTER 10 RETRIES.\nRETURNING TO TITLE SCREEN."; break;
    }

    // Create the error dialog
    str.Init(errorString);
    UIDialog *dialog    = UIDialog_CreateDialogOk(&str, ManiaModeMenu_StartReturnToTitle, true);
    this->hasError      = true;

    this->state.Set(&MultiplayerHandler::State_Exit);
    dcError = DCErrorTypes::ErrorNone;
}

void MultiplayerHandler::State_Exit() {
    SET_CURRENT_STATE();

    //
    //
}

} // namespace GameLogic