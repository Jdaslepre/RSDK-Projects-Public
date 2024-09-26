#include "RSDK-Online.hpp"

using namespace RSDK;

namespace GameLogic {

// -------------------
// Object Registration
// -------------------

RSDK_REGISTER_OBJECT(MultiplayerMenu);

// -------------
// Entity Events
// -------------

void MultiplayerMenu::Create(void *data) {
    //
    //
    Dev::Print(Dev::PRINT_NORMAL, "signa");
}

void MultiplayerMenu::Update() {
    //
    //
    Dev::Print(Dev::PRINT_NORMAL, "signa");
}

void MultiplayerMenu::StaticUpdate() {
    UIControl *ctrl = UIControl_GetUIControl();

    if (ctrl == sVars->pselControl || ctrl == sVars->pselControl_Legacy || ctrl == sVars->lobbyControl) {
        sVars->isMenuActive = true;
    } else {
        sVars->isMenuActive = false;
    }
}

void MultiplayerMenu::StageLoad() { MultiplayerMenu::Initialize(); }

// ----------------------
// Extra Entity Functions
// ----------------------

// Actions Callbacks

void MultiplayerMenu::OpenPlayerSelect_CB() {
    // We have plus, so we'll be using the menu that includes mighty/ray
    if (API::CheckDLC(DLC_PLUS)) {
        const char *tag = "CompOnline PSel";
        UIControl_MatchMenuTag(tag);
        UIControl_SetActiveMenu(sVars->pselControl);
        sVars->lobbyControl->parentTag = tag;
    }
    // We don't have plus, use the legacy sonic, tails & knux menu
    else {
        const char *tag = "CompOnline PSel L";
        UIControl_MatchMenuTag(tag);
        UIControl_SetActiveMenu(sVars->pselControl_Legacy);
        sVars->lobbyControl->parentTag = tag;
    }
}

void MultiplayerMenu::OpenLobby_CB() { UIControl_MatchMenuTag("CompOnline Lobby"); }

void MultiplayerMenu::CharButton_ActionCB() {
    auto self = ((UICharButton *)sceneInfo->entity);

    /*
    MenuParam *param   = MenuParam_GetParam();
    UIControl *control = TimeAttackMenu->taZoneSelControl;

    TimeAttackData_Clear();

    int32 characterID  = self->characterID + 1;
    param->characterID = characterID;

    API.InitLeaderboards();

    for (int32 i = 0; i < control->buttonCount; ++i) {
        EntityUITAZoneModule *charButton = (EntityUITAZoneModule *)control->buttons[i];
        charButton->characterID          = characterID;
    }

    UIControl_MatchMenuTag("Time Attack Zones");
    */

    MenuParam *param = MenuParam_GetParam();

    int32 characterID  = self->characterID + 1;
    param->characterID = characterID;

    UIControl_MatchMenuTag("CompOnline Lobby");

    onlineActive = true;

    int32 len    = 4;
    UserData::Connect2PVS(&len, &globals->itemMode);
}

//

void MultiplayerMenu::Initialize() {
    String tag{};

    // Get all UIControl entities
    for (auto control : GameObject::GetEntities<UIControl>(FOR_ALL_ENTITIES)) {
        tag.Set("CompOnline PSel");
        if (String::Compare(&tag, &control->tag, false))
            sVars->pselControl = control;

        tag.Set("CompOnline PSel L");
        if (String::Compare(&tag, &control->tag, false))
            sVars->pselControl_Legacy = control;

        tag.Set("CompOnline Lobby");
        if (String::Compare(&tag, &control->tag, false))
            sVars->lobbyControl = control;
    }

    for (auto charButton : GameObject::GetEntities<UICharButton>(FOR_ALL_ENTITIES)) {
        if (charButton->parent == (Entity *)sVars->pselControl || charButton->parent == (Entity *)sVars->pselControl_Legacy) {
            charButton->actionCB = MultiplayerMenu::CharButton_ActionCB;
        }
    }
}

void MultiplayerMenu::StartOrExit() {
    // if (self->dialog)
    //   self->dialog->state = DIALOGPANEL_STATE_IDLE;
    if (this->arrowAlpha > 0)
        this->arrowAlpha -= 8;

    /*if (self->timer < 0.2)
        self->scale = fmaxf(self->scale + ((1.5f - self->scale) / ((Engine.deltaTime * 60.0) * 8.0)), 0.0);
    else
        self->scale = fmaxf(self->scale + ((-1.0f - self->scale) / ((Engine.deltaTime * 60.0) * 8.0)), 0.0);
    //*/
    // NewRenderState();
    // MatrixScaleXYZF(&self->renderMatrix, self->scale, self->scale, 1.0);
    // MatrixTranslateXYZF(&self->matrixTemp, 0.0, -8.0, 160.0);
    // MatrixMultiplyF(&self->renderMatrix, &self->matrixTemp);
    // SetRenderMatrix(&self->renderMatrix);

    // memcpy(&self->label->renderMatrix, &self->renderMatrix, sizeof(MatrixF));
    // for (int i = 0; i < 3; ++i) memcpy(&self->codeLabel[i]->renderMatrix, &self->renderMatrix, sizeof(MatrixF));
    // for (int i = 0; i < MULTIPLAYERSCREEN_BUTTON_COUNT; ++i) memcpy(&self->buttons[i]->renderMatrix, &self->renderMatrix, sizeof(MatrixF));
    // for (int i = 0; i < 8; ++i) memcpy(&self->enterCodeLabel[i]->renderMatrix, &self->renderMatrix, sizeof(MatrixF));
    // memcpy(&self->enterCodeSlider[1]->renderMatrix, &self->renderMatrix, sizeof(MatrixF));
    // MatrixRotateZF(&self->enterCodeSlider[0]->renderMatrix, DegreesToRad(180));
    // MatrixMultiplyF(&self->enterCodeSlider[0]->renderMatrix, &self->renderMatrix);

    // self->timer += Engine.deltaTime;
    if (this->timer > 0.5) {
        if (this->state.Matches(&MultiplayerMenu::State_Exit)) {
            if (1 == 1 /*skipStartMenu*/) {
                // StopMusic(true);
                Music_FadeOut(0.075);
                /*
                // is there a better way of removing the pop up message? :(
                if (self->dialog) {
                    RemoveNativeObject(self->dialog);
                    RemoveNativeObject(self->label);
                    RemoveNativeObject(self->label);
                }
                */
                // SetGlobalVariableByName("options.stageSelectFlag", 0);
                // activeStageList   = 0;
                sceneInfo->listCategory = 0;
                // stageMode         = STAGEMODE_LOAD;
                // Engine.gameMode   = ENGINE_MAINGAME;
                //  stageListPosition = 0;
                sceneInfo->listPos = 0;
            } else {
                // Engine.gameMode = ENGINE_RESETGAME;
            }

        } else {
            // if (self->buttons[MULTIPLAYERSCREEN_BUTTON_JOINROOM]->state == PUSHBUTTON_STATE_UNSELECTED) { /// hhhhhhack
            if (1 == 1) {
                SetRoomCode(this->roomCode);
                ServerPacket send;
                send.header = CL_JOIN;
                vsPlayerID  = 1; // we are.... Little Guy

                SendServerPacket(send, true);
            }
        }
        this->Destroy();
        // MatrixScaleXYZF(&self->renderMatrix, Engine.windowScale, Engine.windowScale, 1.0);
        // MatrixTranslateXYZF(&self->matrixTemp, 0.0, 0.0, 160.0);
        // MatrixMultiplyF(&self->renderMatrix, &self->matrixTemp);
        // SetRenderMatrix(&self->renderMatrix);

        // RenderRect(-SCREEN_CENTERX_F, SCREEN_CENTERY_F, 160.0, SCREEN_XSIZE_F, SCREEN_YSIZE_F, 0, 0, 0, 255);
    }
}

// -------------
// Object States
// -------------

void MultiplayerMenu::State_Enter() {
    SET_CURRENT_STATE();

    if (this->arrowAlpha < 0x100)
        this->arrowAlpha += 8;

    // this->timer += Engine.deltaTime;
    this->timer++;
    if (this->timer > 0.5) {
        this->timer = 0.0;
        this->state.Set(&MultiplayerMenu::State_Main);
    }
}

void MultiplayerMenu::State_Main() {
    SET_CURRENT_STATE();
    //
}

void MultiplayerMenu::State_Action() {
    SET_CURRENT_STATE();
    //
}

void MultiplayerMenu::State_Exit() {
    SET_CURRENT_STATE();

    this->StartOrExit();
}

void MultiplayerMenu::State_Flip() {
    SET_CURRENT_STATE();
    //
}

void MultiplayerMenu::State_HostScr() {
    SET_CURRENT_STATE();

    if (!this->roomCode) {
        int code = GetRoomCode();
        if (code) {
            char buffer[0x30];
            int32 code = GetRoomCode();
            sprintf_s(buffer, "%08X", code);
            // SetStringToFont8(self->codeLabel[1]->text, buffer, self->codeLabel[1]->fontID);
            // self->codeLabel[1]->alignPtr(self->codeLabel[1], ALIGN_CENTER);
            this->roomCode = code;
        }
    }
}

void MultiplayerMenu::State_JoinScr() {
    SET_CURRENT_STATE();
    //
}

void MultiplayerMenu::State_StartGame() {
    SET_CURRENT_STATE();

    this->StartOrExit();
}

void MultiplayerMenu::State_DialogWait() {
    SET_CURRENT_STATE();
    //
}

} // namespace GameLogic