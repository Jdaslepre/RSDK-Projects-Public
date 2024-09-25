#include "../3KTC.hpp"

using namespace RSDK;

namespace GameLogic
{

// -------------------
// Object Registration
// -------------------

MOD_REGISTER_OBJECT(SlotHUD);

// ----------------------
// Standard Entity Events
// ----------------------

void SlotHUD::Create(void *data)
{
    sVars->Super(SUPER_CREATE, data);

    if (!sceneInfo->inEditor) {
        this->lifePos.x = TO_FIXED(screenInfo->size.x - 64);
        this->lifePos.y = TO_FIXED(24);
    }
}

void SlotHUD::Draw(void) { this->DrawMobile(); }

void SlotHUD::StageLoad(void)
{
    sVars->Super(SUPER_STAGELOAD);

    if (globals->gameSpriteStyle == GAME_SM)
        modSVars->dpadFrames.Load("Global/TouchControls.bin", SCOPE_STAGE);
    else
        modSVars->dpadFrames.Load("3K_Global/TouchControls.bin", SCOPE_STAGE);

    modSVars->dpadAnimator.SetAnimation(modSVars->dpadFrames, 0, true, 0);
    modSVars->dpadTouchAnimator.SetAnimation(modSVars->dpadFrames, 1, true, 0);
}

// ----------------------
// Extra Entity Functions
// ----------------------

void SlotHUD::DrawMobile(void)
{
    S1SS_Player *player = RSDK_GET_ENTITY(sceneInfo->currentScreenID, S1SS_Player);

    Vector2 drawPos;
    Vector2 ringsPos;
    ringsPos.x = this->ringsPos.x;
    ringsPos.y = this->ringsPos.y;

    Vector2 lifePos;
    lifePos.x = this->lifePos.x;
    lifePos.y = this->lifePos.y;

    this->ringFlashFrame = player->rings ? 0 : ((globals->persistentTimer >> 3) & 1);

    // Draw "Rings" Text
    this->hudElementsAnimator.frameID = this->ringFlashFrame + 3;
    this->hudElementsAnimator.DrawSprite(&ringsPos, true);

    // Draw Rings
    if (!this->enableRingFlash || globals->persistentTimer & 8) {
        this->numbersAnimator.frameID = 0;
        drawPos.x                     = ringsPos.x + (this->extendedHUD ? 0x630000 : 0x4B0000);
        drawPos.y                     = ringsPos.y + TO_FIXED(this->numbersAnimator.frames[0].height);

        if (player->hyperRing) {
            HUD_DrawNumbersBase10(&this->hyperNumbersAnimator, &drawPos, player->rings, 0);
            drawPos.x -= 0x40000;
            this->hyperNumbersAnimator.frameID = 10;
            this->hyperNumbersAnimator.DrawSprite(&drawPos, true);
        }
        else
            HUD_DrawNumbersBase10(&this->numbersAnimator, &drawPos, player->rings, 0);
    }

    S1SS_Player *player1 = RSDK_GET_ENTITY(SLOT_PLAYER1, S1SS_Player);

    // Draw Debug Info
    if (player1->classID == DebugMode::sVars->classID) {
        if (player->camera) {
            // Draw Camera YPos
            drawPos.x = TO_FIXED(screenInfo[player->camera->screenID].size.x - 16);
            drawPos.y = 0x180000;
            HUD_DrawNumbersBase16((HUD *)this, &drawPos, screenInfo[player->camera->screenID].position.y);

            // Draw Camera XPos
            drawPos.x -= 0x90000;
            HUD_DrawNumbersBase16((HUD *)this, &drawPos, screenInfo[player->camera->screenID].position.x);

            // Draw Player YPos
            drawPos.x = TO_FIXED(screenInfo[player->camera->screenID].size.x - 16);
            drawPos.y += 0x100000;
            HUD_DrawNumbersBase16((HUD *)this, &drawPos, TO_FIXED(player->position.y));

            // Draw Player XPos
            drawPos.x -= 0x90000;
            HUD_DrawNumbersBase16((HUD *)this, &drawPos, TO_FIXED(player->position.x));
        }
    }

    drawPos = lifePos;
    int32 lives;
    if (globals->medalMods & MEDAL_NOLIVES) {
        this->lifeIconAnimator.frameID  = this->lifeIconAnimator.frameCount - 1;
        this->lifeNamesAnimator.frameID = this->lifeIconAnimator.frameID;
        lives                           = globals->coinCount;
    }
    else {
        lives                           = this->lives[player->playerID];
        this->lifeIconAnimator.frameID  = HUD_CharacterIndexFromID(player->characterID);
        this->lifeNamesAnimator.frameID = HUD_CharacterIndexFromID(player->characterID);

        // "Miles" name
        if ((globals->playerID & 0xFF) == ID_TAILS && globals->secrets & SECRET_REGIONSWAP)
            this->lifeNamesAnimator.frameID = this->lifeNamesAnimator.frameCount - 1;
    }

    if (this->lifeIconAnimator.frameID < 0) {
        this->lifeIconAnimator.frameID = this->lifeFrameIDs[SLOT_PLAYER1];
        lives--;
    }
    else {
        this->lifeFrameIDs[SLOT_PLAYER1] = this->lifeIconAnimator.frameID;
        this->lives[player->playerID]    = player->lives;
    }

    this->lifeIconAnimator.DrawSprite(&drawPos, true);

    if (globals->gameMode == MODE_ENCORE) {
        for (int32 p = 0; p < PLAYER_COUNT; ++p) {
            if (sVars->stockFlashTimers[p] > 0)
                sVars->stockFlashTimers[p]--;
        }
    }
    else {
        switch (globals->gameSpriteStyle) {
            case GAME_S1:
            case GAME_CD:
            case GAME_S2:
            case GAME_SM:
                this->hudElementsAnimator.frameID = 14;
                this->hudElementsAnimator.DrawSprite(&drawPos, true);
                drawPos.x += 0x300000;
                if (player->lives < 10)
                    drawPos.x -= 0x80000;
                HUD_DrawNumbersBase10(&this->numbersAnimator, &drawPos, lives, 0);
                break;

            case GAME_S3K:
            case GAME_S3:
            case GAME_SK:
                this->lifeNamesAnimator.DrawSprite(&drawPos, true);
                this->hudElementsAnimator.frameID = 14;
                this->hudElementsAnimator.DrawSprite(&drawPos, true); // X
                drawPos.x += 0x280000;
                HUD_DrawNumbersBase10(&this->lifeNumbersAnimator, &drawPos, lives, 0);
                break;
        }
    }

    this->DrawTouchControls();
}

void SlotHUD::DrawTouchControls(void)
{
    int32 playerID      = sceneInfo->currentScreenID;
    S1SS_Player *player = RSDK_GET_ENTITY(playerID, S1SS_Player);

    int32 alphaStore   = this->alpha;
    int32 inkStore     = this->inkEffect;
    int32 fxStore      = this->drawFX;
    Vector2 scaleStore = this->scale;

    modSVars->dpadPos.x = TO_FIXED(config.moveDPadPos.x);
    modSVars->dpadPos.y = TO_FIXED(config.moveDPadPos.y);

    modSVars->actionPos.x = TO_FIXED(screenInfo[sceneInfo->currentScreenID].size.x + config.jumpDPadPos.x);
    modSVars->actionPos.y = TO_FIXED(config.jumpDPadPos.y);

    if (globals->gameMode == MODE_ENCORE)
        modSVars->pausePos.x = TO_FIXED(screenInfo[sceneInfo->currentScreenID].size.x - 100);
    else
        modSVars->pausePos.x = TO_FIXED(screenInfo[sceneInfo->currentScreenID].size.x - 76);

    modSVars->pausePos.y = TO_FIXED(16);

    this->inkEffect = INK_ALPHA;
    this->drawFX    = FX_SCALE;

    int32 opacity = (int32)(0x100 * config.vDPadOpacity);
    this->scale.x = (int32)(0x200 * config.vDPadSize);
    this->scale.y = (int32)(0x200 * config.vDPadSize);

    bool32 canMove = player->stateInput.Matches(Player::Input_Gamepad.action);
    canMove &= player->state.Matches(S1SS_Player::State_Static.action) == false;

    bool32 canJump = player->stateInput.Matches(Player::Input_Gamepad.action);
    canJump &= player->state.Matches(S1SS_Player::State_Static.action) == false;

    bool32 canPause = canMove;

    ControllerState *controller = &controllerInfo[player->controllerID];

    // -------------------
    // Draw touch controls
    // -------------------

    if (canMove && (sceneInfo->state & 3) == ENGINESTATE_REGULAR) {
        // Fade in
        if (modSVars->dpadAlpha[playerID] < opacity)
            modSVars->dpadAlpha[playerID] += 8;

        this->alpha                    = modSVars->dpadAlpha[playerID];
        modSVars->dpadAnimator.frameID = 10;
        modSVars->dpadAnimator.DrawSprite(&modSVars->dpadPos, true);

        if (player->classID == S1SS_Player::sVars->classID ? player->left : controller->keyLeft.down) {
            this->alpha                         = opacity;
            modSVars->dpadTouchAnimator.frameID = 6;
            modSVars->dpadTouchAnimator.DrawSprite(&modSVars->dpadPos, true);
        }
        else {
            this->alpha                    = modSVars->dpadAlpha[playerID];
            modSVars->dpadAnimator.frameID = 6;
            modSVars->dpadAnimator.DrawSprite(&modSVars->dpadPos, true);
        }

        if (player->classID == S1SS_Player::sVars->classID ? player->down : controller->keyDown.down) {
            this->alpha                         = opacity;
            modSVars->dpadTouchAnimator.frameID = 9;
            modSVars->dpadTouchAnimator.DrawSprite(&modSVars->dpadPos, true);

            if (player->classID == S1SS_Player::sVars->classID ? player->left : controller->keyLeft.down) {
                modSVars->dpadTouchAnimator.frameID = 14;
                modSVars->dpadTouchAnimator.DrawSprite(&modSVars->dpadPos, true);
            }
            else if (player->classID == S1SS_Player::sVars->classID ? player->right : controller->keyRight.down) {
                modSVars->dpadTouchAnimator.frameID = 15;
                modSVars->dpadTouchAnimator.DrawSprite(&modSVars->dpadPos, true);
            }
        }
        else {
            this->alpha                    = modSVars->dpadAlpha[playerID];
            modSVars->dpadAnimator.frameID = 9;
            modSVars->dpadAnimator.DrawSprite(&modSVars->dpadPos, true);
        }

        if (player->classID == S1SS_Player::sVars->classID ? player->right : controller->keyRight.down) {
            this->alpha                         = opacity;
            modSVars->dpadTouchAnimator.frameID = 7;
            modSVars->dpadTouchAnimator.DrawSprite(&modSVars->dpadPos, true);
        }
        else {
            this->alpha                    = modSVars->dpadAlpha[playerID];
            modSVars->dpadAnimator.frameID = 7;
            modSVars->dpadAnimator.DrawSprite(&modSVars->dpadPos, true);
        }

        if (player->classID == S1SS_Player::sVars->classID ? player->up : controller->keyUp.down) {
            this->alpha                         = opacity;
            modSVars->dpadTouchAnimator.frameID = 8;
            modSVars->dpadTouchAnimator.DrawSprite(&modSVars->dpadPos, true);

            if (player->classID == S1SS_Player::sVars->classID ? player->left : controller->keyLeft.down) {
                modSVars->dpadTouchAnimator.frameID = 12;
                modSVars->dpadTouchAnimator.DrawSprite(&modSVars->dpadPos, true);
            }
            else if (player->classID == S1SS_Player::sVars->classID ? player->right : controller->keyRight.down) {
                modSVars->dpadTouchAnimator.frameID = 13;
                modSVars->dpadTouchAnimator.DrawSprite(&modSVars->dpadPos, true);
            }
        }
        else {
            this->alpha                    = modSVars->dpadAlpha[playerID];
            modSVars->dpadAnimator.frameID = 8;
            modSVars->dpadAnimator.DrawSprite(&modSVars->dpadPos, true);
        }

        if (player->classID == S1SS_Player::sVars->classID
                ? (!player->up && !player->down && !player->left && !player->right)
                : (!controller->keyUp.down && !controller->keyDown.down && !controller->keyLeft.down && !controller->keyRight.down)) {
            this->alpha                    = modSVars->dpadAlpha[playerID];
            modSVars->dpadAnimator.frameID = 11;
            modSVars->dpadAnimator.DrawSprite(&modSVars->dpadPos, true);
        }
    }
    else {
        // Fade out
        if (modSVars->dpadAlpha[playerID] >= 0)
            modSVars->dpadAlpha[playerID] -= 8;

        this->alpha = modSVars->dpadAlpha[playerID];
        if (this->alpha > 0) {
            modSVars->dpadTouchAnimator.frameID = 0;
            modSVars->dpadTouchAnimator.DrawSprite(&modSVars->dpadPos, true);
        }
    }

    // ----------------
    // Draw jump button
    // ----------------

    if (canJump && (sceneInfo->state & 3) == ENGINESTATE_REGULAR) {
        // Fade in
        if (modSVars->jumpAlpha[playerID] < opacity)
            modSVars->jumpAlpha[playerID] += 8;

        if (player->classID == S1SS_Player::sVars->classID ? player->jumpHold : controller->keyC.down) {
            this->alpha                         = opacity;
            modSVars->dpadTouchAnimator.frameID = 1;
            modSVars->dpadTouchAnimator.DrawSprite(&modSVars->actionPos, true);
        }
        else {
            this->alpha                    = modSVars->jumpAlpha[playerID];
            modSVars->dpadAnimator.frameID = 1;
            modSVars->dpadAnimator.DrawSprite(&modSVars->actionPos, true);
        }
    }
    else {
        // Fade out
        if (modSVars->jumpAlpha[playerID] >= 0)
            modSVars->jumpAlpha[playerID] -= 8;

        this->alpha = modSVars->jumpAlpha[playerID];
        if (this->alpha > 0) {
            modSVars->dpadAnimator.frameID = 1;
            modSVars->dpadAnimator.DrawSprite(&modSVars->actionPos, true);
        }
    }

    // -----------------
    // Draw pause button
    // -----------------

    if (canPause && (sceneInfo->state & 3) == ENGINESTATE_REGULAR) {
        if (modSVars->pauseAlpha[playerID] < 255)
            modSVars->pauseAlpha[playerID] += 8;

        this->alpha                         = modSVars->pauseAlpha[playerID];
        modSVars->dpadTouchAnimator.frameID = 5;
        modSVars->dpadTouchAnimator.DrawSprite(&modSVars->pausePos, true);
    }
    else {
        if (modSVars->pauseAlpha[playerID] > 0)
            modSVars->pauseAlpha[playerID] -= 8;

        this->alpha = modSVars->pauseAlpha[playerID];
        if (this->alpha > 0) {
            modSVars->dpadTouchAnimator.frameID = 5;
            modSVars->dpadTouchAnimator.DrawSprite(&modSVars->pausePos, true);
        }
    }

    this->alpha     = alphaStore;
    this->inkEffect = inkStore;
    this->drawFX    = fxStore;
    this->scale     = scaleStore;
}

} // namespace GameLogic