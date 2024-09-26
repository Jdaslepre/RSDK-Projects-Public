#include "RSDK-Online.hpp"

using namespace RSDK;

namespace GameLogic {

// -------------------
// Object Registration
// -------------------

MOD_REGISTER_OBJECT(UIMultiplayerPanel);

// -------------
// Entity Events
// -------------

void UIMultiplayerPanel::Update() {
    if (dcError && this->state.Matches(&UIMultiplayerPanel::State_Hosting))
        GameObject::Create<MultiplayerHandler>(nullptr, NULL, NULL);

    this->state.Run(this);
    // globals->gameMode = MODE_COMPETITION;

    UserData::ReceiveValue(&this->sendReceieveValue, true);
    
    if (this->sendReceieveValue > 0) {
        Stage::SetScene("Mania Mode", "Press Garden Zone");
        Stage::LoadScene();
    }
}

void UIMultiplayerPanel::Draw() {
    this->DrawBackground();

    // Draw the header
    this->topAnimator.DrawSprite(&this->drawPosTop, false);

    this->stateDraw.Run(this);

    // if there's an error, apply a gray tint to the screen
    for (auto entity : GameObject::GetEntities<MultiplayerHandler>(FOR_ALL_ENTITIES)) {
        if (entity->hasError) {
            Palette::SetTintLookupTable(MultiplayerHandler::sVars->tintLookupTable);
            Graphics::DrawRect(0, 0, screenInfo->size.x, screenInfo->size.y, 0, 255, INK_TINT, true);
            Stage::SetEngineState(ENGINESTATE_FROZEN);
        }
    }
}

void UIMultiplayerPanel::Create(void *data) {
    this->startPos      = this->position;
    this->active        = ACTIVE_BOUNDS;
    this->drawGroup     = 2;
    this->visible       = true;
    this->drawFX        = FX_FLIP;
    this->updateRange.x = 0x800000;
    this->updateRange.y = 0x800000;

    this->state.Set(&UIMultiplayerPanel::State_Init);
}

void UIMultiplayerPanel::StageLoad() {
    sVars->aniFrames.Load("UI/Multi.bin", SCOPE_STAGE);
    UIText::sVars->aniFrames = sVars->aniFrames;
    sVars->sfxBleep.Get("Global/MenuBleep.wav");
    sVars->sfxAccept.Get("Global/MenuAccept.wav");
}

// ----------------------
// Extra Entity Functions
// ----------------------

void UIMultiplayerPanel::InputSetup() {
    RSDK::ControllerState *controller = &controllerInfo[Input::CONT_ANY];
    RSDK::AnalogState *stick          = &analogStickInfoL[Input::CONT_ANY];

    this->left  = controller->keyLeft.press || stick->keyLeft.press || stick->hDelta < -0.3;
    this->right = controller->keyRight.press || stick->keyRight.press || stick->hDelta > 0.3;

    this->up   = controller->keyUp.press || stick->keyUp.press || stick->vDelta > 0.3;
    this->down = controller->keyDown.press || stick->keyDown.press || stick->vDelta < -0.3;

    if (this->left && this->right) {
        this->left  = false;
        this->right = false;
    }

    this->start = controller->keyStart.press;
}

void UIMultiplayerPanel::TestSelectionRange(int16 max) {
    // :shhhh:

    if (this->currentSelection > max) {
        this->currentSelection = 0;
    } else if (this->currentSelection < 0) {
        this->currentSelection = max;
    }
}

void UIMultiplayerPanel::DrawBackground() {
    Graphics::DrawRect(this->position.x - (this->size.x >> 1), this->position.y - (this->size.y >> 1), this->size.x, this->size.y, 0x30A0F0, 255,
                       INK_NONE, false);

    int32 x = this->position.x - (this->size.x >> 1);
    int32 y = this->position.y - (this->size.y >> 1);
    Graphics::DrawRect(x, y, 0xE60000, 0x180000, 0, 255, INK_NONE, false);

    UIWidgets_DrawRightTriangle(0xE60000 + x, y, 23, 0x00, 0x00, 0x00);

    if (!this->botHidden) {
        x = (this->size.x >> 1) + this->position.x - 0xE60000;
        y = (this->size.y >> 1) + this->position.y - 0x180000;
        Graphics::DrawRect(x, y, 0xE60000, 0x180000, 0, 255, INK_NONE, false);

        UIWidgets_DrawRightTriangle(x, y + 0x170000, -23, 0x00, 0x00, 0x00);
    }
}

void UIMultiplayerPanel::DrawRoomCode(int32 v) {
    union {
        uint32 val;
        uint8 bytes[sizeof(uint32)];
    } u;
    u.val = this->roomCode;

    for (int32 i = 0; i < 8; i += 2) {
        int32 n         = 7 - i;
        int32 nybbles[] = {
            u.bytes[n >> 1] & 0xF,
            ((u.bytes[n >> 1] & 0xF0) >> 4) & 0xF,
        };

        this->enterCodeLabel[i + 0]->alpha = 0x100;
        this->enterCodeLabel[i + 1]->alpha = 0x100;

        // this->enterCodeLabel[i + 0]->useColors = false;
        // this->enterCodeLabel[i + 1]->useColors = false;

        char codeBuf[0x10];
        sprintf_s(codeBuf, "%X", nybbles[1]);
        this->enterCodeLabel[i + 0]->text.Set(codeBuf);
        this->enterCodeLabel[i + 0]->text.SetSpriteString(UIText::sVars->aniFrames, 3);

        sprintf_s(codeBuf, "%X", nybbles[0]);
        this->enterCodeLabel[i + 1]->text.Set(codeBuf);
        this->enterCodeLabel[i + 1]->text.SetSpriteString(UIText::sVars->aniFrames, 3);
    }
    // this->enterCodeLabel[v]->useColors = true;
}

// -------------
// Object States
// -------------

void UIMultiplayerPanel::State_Init() {
    SET_CURRENT_STATE();

    this->currentSelection = 0;
    if (this->panelSize < 152)
        this->panelSize = 152;

    this->size.x       = WIDE_SCR_XSIZE << 16;
    this->size.y       = this->panelSize << 16;
    this->drawPosTop.x = this->position.x - TO_FIXED(146);
    this->drawPosTop.y = this->position.y + (-TO_FIXED(55) - (((this->panelSize << 15) - TO_FIXED(67)) & 0xFFFF0000));

    this->hitbox.left   = -212;
    this->hitbox.top    = -68;
    this->hitbox.right  = 212;
    this->hitbox.bottom = 68;

    this->drawPosBottom = this->position;
    if (!this->botAlignRight)
        this->drawPosBottom.x -= 0xA0000;
    else
        this->drawPosBottom.x += 0xA20000;
    this->drawPosBottom.y += 0x390000;

    this->topAnimator.SetAnimation(sVars->aniFrames, 0, true, 0);
    this->botHidden = true;

    char codeBuf[0x8];
    sprintf_s(codeBuf, "%X", 0);

    for (int32 i = 0; i < 8; ++i) {
        UIText *label    = GameObject::Create<UIText>(nullptr, this->position.x, this->position.y);
        label->drawGroup = this->drawGroup + 1;
        label->visible   = false;
        label->listID    = 3;
        label->text.Set(codeBuf);
        label->text.SetSpriteString(UIText::sVars->aniFrames, 3);
        label->align = UIText::AlignCenter;

        this->enterCodeLabel[i] = label;
    }

    UIText *labelCode    = GameObject::Create<UIText>(nullptr, this->position.x, this->position.y);
    labelCode->drawGroup = this->drawGroup + 1;
    labelCode->visible   = false;
    labelCode->listID    = 3;
    labelCode->text.Set("FETCHING...");
    labelCode->text.SetSpriteString(UIText::sVars->aniFrames, 3);

    UIText *labelPlayer    = GameObject::Create<UIText>(nullptr, this->position.x, this->position.y);
    labelPlayer->drawGroup = this->drawGroup + 1;
    labelPlayer->visible   = false;
    labelPlayer->listID    = 3;
    labelPlayer->text.Set("WAITING FOR 2P...");
    labelPlayer->align = UIText::AlignCenter;

    this->codeLabel[CodeLabels::LabelHostCode]         = labelCode;
    this->codeLabel[CodeLabels::LabelWaitingForPlayer] = labelPlayer;

    this->state.Set(&UIMultiplayerPanel::State_Lobby);
    this->stateDraw.Set(&UIMultiplayerPanel::State_DrawLobby);
}

void UIMultiplayerPanel::State_Lobby() {
    SET_CURRENT_STATE();

    // Handles the FrameID of the buttons
    this->UIElementAnimator.SetAnimation(sVars->aniFrames, 1, false, 0);
    this->UIElementAnimator.frameID = this->currentSelection;

    this->InputSetup();

    if (this->left) {
        sVars->sfxBleep.Play(false, 255);
        --this->currentSelection;
    }

    if (this->right) {
        sVars->sfxBleep.Play(false, 255);
        ++this->currentSelection;
    }

    this->TestSelectionRange(1);

    if (this->start) {
        sVars->sfxAccept.Play(false, 255);

        // Room code background
        this->UIElementAnimator.SetAnimation(sVars->aniFrames, 2, true, 0);

        switch (this->currentSelection) {
            case 0:
                // Hosting
                this->topAnimator.SetAnimation(sVars->aniFrames, 0, true, 1);
                this->state.Set(&UIMultiplayerPanel::State_Hosting);
                this->stateDraw.Set(&UIMultiplayerPanel::State_DrawHosting);
                this->botHidden = false;
                break;
            case 1:
                // Joining
                this->currentSelection = 0;
                this->topAnimator.SetAnimation(sVars->aniFrames, 0, true, 2);
                this->state.Set(&UIMultiplayerPanel::State_Joining);
                this->stateDraw.Set(&UIMultiplayerPanel::State_DrawJoining);
                this->botHidden = false;
                break;
            default: break;
        }
    }
}

void UIMultiplayerPanel::State_DrawLobby() {
    SET_CURRENT_STATE();

    // Draws the Host/Join buttons at the center of the screen
    Vector2 drawPos;
    drawPos.x = TO_FIXED(screenInfo->center.x);
    drawPos.y = TO_FIXED(screenInfo->center.y + 24);
    this->UIElementAnimator.DrawSprite(&drawPos, true);
}

void UIMultiplayerPanel::State_Hosting() {
    SET_CURRENT_STATE();

    UIText *labelCode = this->codeLabel[CodeLabels::LabelHostCode];

    if (!this->roomCode) {
        int32 code = GetRoomCode();
        if (code) {
            char buffer[0x30];
            int32 code = GetRoomCode();
            sprintf_s(buffer, "%08X", code);
            labelCode->text.Set(buffer);
            labelCode->text.SetSpriteString(UIText::sVars->aniFrames, 3);
            labelCode->align = UIText::AlignCenter;
            this->roomCode   = code;
        }
    } else {
        if (Misc::callbackState != Misc::OnlineCBStates::WAIT2PVS) {
            // self->buttons[MULTIPLAYERSCREEN_BUTTON_JOINROOM]->state = PUSHBUTTON_STATE_UNSELECTED;
            // self->selectedButton                                    = MULTIPLAYERSCREEN_BUTTON_JOINROOM;
            // self->state                                             = MULTIPLAYERSCREEN_STATE_ACTION;
        }
    }
}

void UIMultiplayerPanel::State_DrawHosting() {
    SET_CURRENT_STATE();

    /*
    for (int i = 0; i < MULTIPLAYERSCREEN_BUTTON_COUNT; ++i) self->buttons[i]->alpha = 0;
    for (int i = 0; i < 2; ++i) self->codeLabel[i]->alpha = 0x100;
    for (int i = 0; i < 8; ++i) self->enterCodeLabel[i]->alpha = 0;
    for (int i = 0; i < 2; ++i) self->enterCodeSlider[i]->alpha = 0;

    self->selectedButton                                = MULTIPLAYERSCREEN_BUTTON_COPY;
    self->buttons[MULTIPLAYERSCREEN_BUTTON_COPY]->alpha = 0x100;
    */

    for (int32 i = 0; i < 2; ++i) this->codeLabel[i]->alpha = 0x100;
    for (int32 i = 0; i < 8; ++i) this->enterCodeLabel[i]->alpha = 0;

    Vector2 drawPos;
    drawPos.x = TO_FIXED(screenInfo->center.x);
    drawPos.y = TO_FIXED(screenInfo->center.y + 24);

    // Draws the code's background plate at the center of the screen
    this->UIElementAnimator.frameID = 0;
    this->UIElementAnimator.DrawSprite(&drawPos, true);

    // Draws "ROOM CODE"
    this->UIElementAnimator.frameID = 1;
    this->UIElementAnimator.DrawSprite(&drawPos, true);

    //
    UIText *labelCode  = this->codeLabel[CodeLabels::LabelHostCode];
    labelCode->visible = true;

    labelCode->align      = UIText::AlignCenter;
    labelCode->position.x = this->position.x + TO_FIXED(64);
    labelCode->position.y = this->position.y + TO_FIXED(2);

    // this->roomCode = 0;
    ServerPacket send;
    send.header = CL_REQUEST_CODE;
    // send over a preferred roomcode style
    if (!vsGameLength)
        vsGameLength = 4;
    if (!vsItemMode)
        vsItemMode = ManiaItemModes::ITEMS_RANDOM;
    send.data.multiData.type    = 0x00000FF0;
    send.data.multiData.data[0] = (vsGameLength << 4) | (vsItemMode << 8);
    vsPlayerID                  = 0; // we are... Big Host

    SendServerPacket(send, true);
}

void UIMultiplayerPanel::State_Joining() {
    SET_CURRENT_STATE();

    this->InputSetup();

    if (this->left) {
        sVars->sfxBleep.Play(false, 255);
        this->currentSelection--;
        if (this->currentSelection < 0)
            this->currentSelection = 7;

        /*
        if (this->selectedButton < 3)
            this->selectedButton = 12;
            */
    } else if (this->right) {
        sVars->sfxBleep.Play(false, 255);
        this->currentSelection++;
        if (this->currentSelection > 7)
            this->currentSelection = 0;

        /*
        if (this->selectedButton > 12)
            this->selectedButton = 3;
            */
    }

    // Add Join/Paste checks
    if ((this->up || this->down)) {
        union {
            int32 val;
            uint8 bytes[sizeof(int32)];
        } u;
        u.val   = this->roomCode;
        int32 n = 7 - (this->currentSelection); // 7 - (this->selectedButton - 5);

        int32 nybbles[] = {
            u.bytes[n >> 1] & 0xF,
            ((u.bytes[n >> 1] & 0xF0) >> 4) & 0xF,
        };

        if (this->up) {
            sVars->sfxBleep.Play(false, 255);
            nybbles[n & 1]++;      // increase the value
            nybbles[n & 1] &= 0xF; // limit the max value to 15 (0xF)

        } else if (this->down) {
            sVars->sfxBleep.Play(false, 255);
            nybbles[n & 1]--;      // decrease the value
            nybbles[n & 1] &= 0xF; // limit the max value to 15 (0xF)
        }

        u.bytes[n >> 1] = (nybbles[1] << 4) | (nybbles[0] & 0xF);
        this->roomCode  = u.val;

        this->DrawRoomCode(n);
    }

    // TEMP, forces room join
    if (controllerInfo->keyY.press) {
        SetRoomCode(this->roomCode);
        ServerPacket send;
        send.header = CL_JOIN;
        vsPlayerID  = 1; // we are.... Little Guy

        this->sendReceieveValue = 1;

        UserData::SendValue(this->sendReceieveValue, true);
        SendServerPacket(send, true);
    }

    // using this as a way to say that we're ready, for now
    if (sendReceieveValue == 1) {
        Stage::SetScene("Mania Mode", "Press Garden Zone");
        Stage::LoadScene();
    }
}

void UIMultiplayerPanel::State_DrawJoining() {
    SET_CURRENT_STATE();

    Vector2 drawPos;
    drawPos.x = TO_FIXED(screenInfo->center.x);
    drawPos.y = TO_FIXED(screenInfo->center.y + 24);

    // Draws the code's background plate at the center of the screen
    this->UIElementAnimator.frameID = 0;
    this->UIElementAnimator.DrawSprite(&drawPos, true);

    // Draws "ROOM CODE"
    this->UIElementAnimator.frameID = 1;
    this->UIElementAnimator.DrawSprite(&drawPos, true);

    if (!this->initializedDraw) {
        // for (int i = 0; i < MULTIPLAYERSCREEN_BUTTON_COUNT; ++i) self->buttons[i]->alpha = 0;
        // self->selectedButton = MULTIPLAYERSCREEN_BUTTON_COUNT;
        this->touchedUpID   = -1;
        this->touchedDownID = -1;

        for (int32 i = 0; i < 2; ++i) this->codeLabel[i]->alpha = 0;
        this->roomCode = 0;
    }

    for (int32 i = 0; i < 8; ++i) {
        this->enterCodeLabel[i]->alpha = 0x100;
        // self->enterCodeLabel[i]->useColors = false;

        UIText *label  = this->enterCodeLabel[i];
        label->visible = true;

        // Just some initialization
        if (!this->initializedDraw) {
            char codeBuf[0x10];
            sprintf_s(codeBuf, "%X", 0);

            label->text.Set(codeBuf);
            label->text.SetSpriteString(UIText::sVars->aniFrames, 3);
            label->align = UIText::AlignLeft;
        }

        // Handle the position of the labels
        int32 w   = sVars->aniFrames.GetFrame(label->listID, label->animator.frameID)->width;
        int32 off = this->position.x + TO_FIXED(64) - ((TO_FIXED(w) * 8) / 2);

        label->position.x = off + (i * TO_FIXED(w));
        label->position.y = this->position.y + TO_FIXED(2);
    }
    // self->enterCodeLabel[0]->useColors                      = true;
    // self->buttons[MULTIPLAYERSCREEN_BUTTON_JOINROOM]->alpha = 0x100;
    // self->buttons[MULTIPLAYERSCREEN_BUTTON_PASTE]->alpha    = 0x100;

    if (!this->initializedDraw)
        this->initializedDraw = true;
}

} // namespace GameLogic