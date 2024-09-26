#include "../3KTC.hpp"

using namespace RSDK;

namespace GameLogic
{

// -------------------
// Object Registration
// -------------------

MOD_REGISTER_OBJECT(HUD);

// ----------------------
// Standard Entity Events
// ----------------------

void HUD::Create(void *data)
{
    sVars->Super(SUPER_CREATE, data);

    if (!sceneInfo->inEditor) {
        this->lifePos.x = TO_FIXED(screenInfo->size.x - 64);
        this->lifePos.y = TO_FIXED(24);
    }
}

void HUD::Draw(void) { this->DrawMobile(); }

void HUD::StageLoad(void)
{
    sVars->Super(SUPER_STAGELOAD);

    // will add more when i feel like doing so
    if (globals->gameSpriteStyle == GAME_SM)
        modSVars->dpadFrames.Load("Global/TouchControls.bin", SCOPE_STAGE);
    else
        modSVars->dpadFrames.Load("3K_Global/TouchControls.bin", SCOPE_STAGE);

    modSVars->dpadAnimator.SetAnimation(modSVars->dpadFrames, 0, true, 0);
    modSVars->dpadTouchAnimator.SetAnimation(modSVars->dpadFrames, 1, true, 0);
}

// ----------------
// Public Functions
// ----------------

void (*HUD_DrawNumbersBase10)(Animator *animator, Vector2 *drawPos, int32 value, int32 digitCount) = nullptr;
void (*HUD_DrawNumbersBase16)(HUD *entity, Vector2 *drawPos, int32 value)                          = nullptr;
int32 (*HUD_CharacterIndexFromID)(int32 characterID)                                               = nullptr;

// ----------------------
// Extra Entity Functions
// ----------------------

void HUD::DrawMobile(void)
{
    if (!globals->showHUD)
        return;

    if (globals->playMode == BOOT_PLAYMODE_MISSION || globals->playMode == BOOT_PLAYMODE_BOSSRUSH) {
        globals->hudEnable = HUDENABLE_ON;
        return;
    }

    auto player = GameObject::Get<Player>(sceneInfo->currentScreenID);

    Vector2 drawPos;
    Vector2 scorePos = this->scorePos;
    Vector2 timePos  = this->timePos;
    Vector2 ringPos  = this->ringsPos;
    Vector2 lifePos  = this->lifePos;

    if (globals->gameMode == MODE_COMPETITION) {
        scorePos.x = this->vsScorePos[sceneInfo->currentScreenID].x;
        scorePos.y = this->vsScorePos[sceneInfo->currentScreenID].y;
        timePos.x  = this->vsTimePos[sceneInfo->currentScreenID].x;
        timePos.y  = this->vsTimePos[sceneInfo->currentScreenID].y;
        ringPos.x  = this->vsRingsPos[sceneInfo->currentScreenID].x;
        ringPos.y  = this->vsRingsPos[sceneInfo->currentScreenID].y;
        lifePos.x  = this->vsLifePos[sceneInfo->currentScreenID].x;
        lifePos.y  = this->vsLifePos[sceneInfo->currentScreenID].y;

        if (globals->useManiaBehavior) {
            for (auto plr : GameObject::GetEntities<Player>(FOR_ACTIVE_ENTITIES)) {
                if (plr != player) {
                    this->playerIDAnimator.frameID = plr->playerID;
                    this->playerIDAnimator.DrawSprite(&plr->position, false);
                }
            }
        }
    }
    else {
        if (sVars->swapCooldown > 0) {
            this->playerIDAnimator.Process();
            this->playerIDAnimator.DrawSprite(&player->position, false);
            --sVars->swapCooldown;
        }
    }

    this->ringFlashFrame = player->rings ? 0 : ((globals->persistentTimer >> 3) & 1);

    this->timeFlashFrame = 0;
    if ((sceneInfo->minutes == 9 && isMainGameMode() && !(globals->medalMods & MEDAL_NOTIMEOVER)) /*&& ActClear::sVars->disableTimeBonus*/)
        this->timeFlashFrame = (globals->persistentTimer >> 3) & 1;

    // Draw "Score" Text
    this->hudElementsAnimator.frameID = 0;
    this->hudElementsAnimator.DrawSprite(&scorePos, true);

    // Draw Score
    drawPos.x = scorePos.x + 0x630000;
    drawPos.y = scorePos.y + 0xB0000;
    HUD_DrawNumbersBase10(&this->numbersAnimator, &drawPos, player->score, 0);

    // Draw "Time" Text
    this->hudElementsAnimator.frameID = this->timeFlashFrame + 1;
    this->hudElementsAnimator.DrawSprite(&timePos, true);

    // Draw Time
    if (!this->enableTimeFlash || globals->persistentTimer & 8) {
        // Draw : or "
        drawPos.x                         = timePos.x;
        drawPos.y                         = timePos.y;
        this->hudElementsAnimator.frameID = this->extendedHUD ? 12 : 20;
        this->hudElementsAnimator.DrawSprite(&drawPos, true);

        this->numbersAnimator.frameID = 0;
        drawPos.y                     = timePos.y + TO_FIXED(this->numbersAnimator.frames[0].height);
        if (this->extendedHUD) {
            // Draw Milliseconds
            drawPos.x = timePos.x + 0x630000;
            HUD_DrawNumbersBase10(&this->numbersAnimator, &drawPos, sceneInfo->milliseconds, 2);
            drawPos.x -= 0x80000;
        }
        else {
            drawPos.x = timePos.x + 0x4B0000;
        }

        if (sceneInfo->minutes > 9) {
            // Draw Seconds
            HUD_DrawNumbersBase10(&this->numbersAnimator, &drawPos, 59, 2);
            drawPos.x -= 0x80000;

            // Draw Minutes
            HUD_DrawNumbersBase10(&this->numbersAnimator, &lifePos, 9, 1);
        }
        else {
            // Draw Seconds
            HUD_DrawNumbersBase10(&this->numbersAnimator, &drawPos, sceneInfo->seconds, 2);
            drawPos.x -= 0x80000;

            // Draw Minutes
            if (sceneInfo->minutes > 9 && globals->medalMods & MEDAL_NOTIMEOVER)
                HUD_DrawNumbersBase10(&this->numbersAnimator, &drawPos, sceneInfo->minutes, 2);
            else
                HUD_DrawNumbersBase10(&this->numbersAnimator, &drawPos, sceneInfo->minutes, 1);
        }
    }

    // Draw "Rings" Text
    this->hudElementsAnimator.frameID = this->ringFlashFrame + 3;
    this->hudElementsAnimator.DrawSprite(&ringPos, true);

    // Draw Rings
    if (!this->enableRingFlash || globals->persistentTimer & 8) {
        this->numbersAnimator.frameID = 0;
        drawPos.x                     = ringsPos.x + (this->extendedHUD ? 0x630000 : 0x4B0000);
        drawPos.y                     = ringsPos.y + TO_FIXED(this->numbersAnimator.frames[this->numbersAnimator.frameID].height);

        if (player->hyperRing) {
            HUD_DrawNumbersBase10(&this->hyperNumbersAnimator, &drawPos, player->rings, 0);
            drawPos.x -= 0x40000;
            this->hyperNumbersAnimator.frameID = 10;
            this->hyperNumbersAnimator.DrawSprite(&drawPos, true);
        }
        else
            HUD_DrawNumbersBase10(&this->numbersAnimator, &drawPos, player->rings, 0);
    }

    // Draw Debug Info
    if (sceneInfo->debugMode) {
        if (player->camera) {
            // Draw Camera YPos
            drawPos.x = TO_FIXED(screenInfo[player->camera->screenID].size.x - 16);
            drawPos.y = TO_FIXED(0x2B);
            HUD_DrawNumbersBase16(this, &drawPos, screenInfo[player->camera->screenID].position.y);

            // Draw Camera XPos
            drawPos.x -= TO_FIXED(9);
            HUD_DrawNumbersBase16(this, &drawPos, screenInfo[player->camera->screenID].position.x);

            // Draw Player YPos
            drawPos.x = TO_FIXED(screenInfo[player->camera->screenID].size.x - 16);
            drawPos.y += TO_FIXED(16);
            HUD_DrawNumbersBase16(this, &drawPos, FROM_FIXED(player->position.y));

            // Draw Player XPos
            drawPos.x -= TO_FIXED(9);
            HUD_DrawNumbersBase16(this, &drawPos, FROM_FIXED(player->position.x));
        }
    }
    else if (this->actionPromptPos > -0x400000 && globals->gameMode == MODE_TIMEATTACK) {
        drawPos.x = TO_FIXED(screenInfo[sceneInfo->currentScreenID].size.x) - this->actionPromptPos;
        drawPos.y = 0x140000;
    }
    else if (this->actionPromptPos > -0x200000) {
        // Draw Super Icon
        drawPos.x = TO_FIXED(screenInfo[sceneInfo->currentScreenID].size.x) - this->actionPromptPos;
        drawPos.y = 0x140000;
        this->superIconAnimator.DrawSprite(&drawPos, true);

        drawPos.x -= 0x140000;
        bool32 canSuper = true;

        if (Player::sVars->canSuperCB)
            canSuper = Player::sVars->canSuperCB(true);

        // Draw Super Button
        /*
        if (!player->state.Matches(&Player::State_Air) && player->jumpAbilityState == 1 && canSuper) {
            this->superButtonAnimator.DrawSprite(&drawPos, true);
        } else {
            this->inkEffect = INK_BLEND;
            this->superButtonAnimator.DrawSprite(&drawPos, true);
            this->inkEffect = INK_NONE;
        }
        */
    }

    int32 lives = this->lives[player->playerID];

    if (globals->somethingRelatedToLives) {
        drawPos = this->lifePos;

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

        if (!*config.usePathTracer)
            this->lifeIconAnimator.frameID = this->lifeIconAnimator.frameCount - 2;

        if (this->lifeIconAnimator.frameID < 0) {
            this->lifeIconAnimator.frameID = this->lifeFrameIDs[player->playerID];
            lives--;
        }
        else {
            this->lifeFrameIDs[player->playerID] = this->lifeIconAnimator.frameID;
            this->lives[player->playerID]        = player->lives;
        }

        this->lifeIconAnimator.DrawSprite(&drawPos, true);

        if (globals->gameMode == MODE_ENCORE) {
            for (int32 p = 0; p < PLAYER_COUNT; ++p) {
                if (sVars->stockFlashTimers[p] > 0)
                    sVars->stockFlashTimers[p]--;
            }

            drawPos.x += TO_FIXED(20);

            auto sidekick = GameObject::Get<Player>(SLOT_PLAYER2);
            if (sidekick->classID) {
                // Draw Buddy Icon
                /*
                this->lifeIconAnimator.frameID = HUD_CharacterIndexFromID(sidekick->characterID);
                if (this->lifeIconAnimator.frameID >= 0 && !(sVars->stockFlashTimers[0] & 4)) {
                    if ((!sidekick->state.Matches(&Player::State_Death) && !sidekick->state.Matches(&Player::State_Drown)
                         && !sidekick->state.Matches(&Player::State_DeathHold))
                        || !sidekick->abilityValues[0]) {
                        this->lifeIconAnimator.DrawSprite(&drawPos, true);
                    }
                }
                */

                // Draw Stock Icons
                drawPos.x += TO_FIXED(20);
                this->lifeIconAnimator.SetAnimation(sVars->aniFrames, 12, true, 0);

                for (int32 i = 1; i < 4; ++i) {
                    this->lifeIconAnimator.frameID = HUD_CharacterIndexFromID(GET_STOCK_ID(i));
                    if (this->lifeIconAnimator.frameID >= 0 && !(sVars->stockFlashTimers[i] & 4))
                        this->lifeIconAnimator.DrawSprite(&drawPos, true);

                    drawPos.x += TO_FIXED(16);
                }

                this->lifeIconAnimator.SetAnimation(sVars->aniFrames, 2, true, 0);
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
                    this->hudElementsAnimator.frameID = 14; // X
                    this->hudElementsAnimator.DrawSprite(&drawPos, true);
                    drawPos.x += 0x290000;
                    HUD_DrawNumbersBase10(&this->lifeNumbersAnimator, &drawPos, lives, 0);
                    break;
            }
        }
    }

    this->DrawTouchControls();
}

void HUD::DrawTouchControls(void)
{
    int32 playerID = sceneInfo->currentScreenID;
    auto player = GameObject::Get<Player>(playerID);

    int32 alphaStore   = this->alpha;
    int32 inkStore     = this->inkEffect;
    int32 fxStore      = this->drawFX;
    Vector2 scaleStore = this->scale;

    modSVars->dpadPos.x = TO_FIXED(config.moveDPadPos.x);
    modSVars->dpadPos.y = TO_FIXED(config.moveDPadPos.y);

    modSVars->actionPos.x = TO_FIXED(screenInfo[sceneInfo->currentScreenID].size.x + config.jumpDPadPos.x);
    modSVars->actionPos.y = TO_FIXED(config.jumpDPadPos.y);

    modSVars->superPos.x = modSVars->actionPos.x - TO_FIXED(64);
    modSVars->superPos.y = modSVars->actionPos.y;

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
    canMove &= player->state.Matches(Player::State_Victory.action) == false;

    bool32 canJump = player->stateInput.Matches(Player::Input_Gamepad.action);
    canJump &= player->state.Matches(Player::State_Victory.action) == false;

    bool32 canSuper = (canJump && player->CanTransform()) == true;
    bool32 canSwap =
        (canJump && globals->gameMode == MODE_ENCORE && !sVars->swapCooldown && Player_CheckValidState(player) && player->CanSwap()) == true;

    bool32 canPause  = canMove;
    Vector2 superPos = modSVars->superPos;

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

        if (player->classID == Player::sVars->classID ? player->left : controller->keyLeft.down) {
            this->alpha                         = opacity;
            modSVars->dpadTouchAnimator.frameID = 6;
            modSVars->dpadTouchAnimator.DrawSprite(&modSVars->dpadPos, true);
        }
        else {
            this->alpha                    = modSVars->dpadAlpha[playerID];
            modSVars->dpadAnimator.frameID = 6;
            modSVars->dpadAnimator.DrawSprite(&modSVars->dpadPos, true);
        }

        if (player->classID == Player::sVars->classID ? player->down : controller->keyDown.down) {
            this->alpha                         = opacity;
            modSVars->dpadTouchAnimator.frameID = 9;
            modSVars->dpadTouchAnimator.DrawSprite(&modSVars->dpadPos, true);

            if (player->classID == Player::sVars->classID ? player->left : controller->keyLeft.down) {
                modSVars->dpadTouchAnimator.frameID = 14;
                modSVars->dpadTouchAnimator.DrawSprite(&modSVars->dpadPos, true);
            }
            else if (player->classID == Player::sVars->classID ? player->right : controller->keyRight.down) {
                modSVars->dpadTouchAnimator.frameID = 15;
                modSVars->dpadTouchAnimator.DrawSprite(&modSVars->dpadPos, true);
            }
        }
        else {
            this->alpha                    = modSVars->dpadAlpha[playerID];
            modSVars->dpadAnimator.frameID = 9;
            modSVars->dpadAnimator.DrawSprite(&modSVars->dpadPos, true);
        }

        if (player->classID == Player::sVars->classID ? player->right : controller->keyRight.down) {
            this->alpha                         = opacity;
            modSVars->dpadTouchAnimator.frameID = 7;
            modSVars->dpadTouchAnimator.DrawSprite(&modSVars->dpadPos, true);
        }
        else {
            this->alpha                    = modSVars->dpadAlpha[playerID];
            modSVars->dpadAnimator.frameID = 7;
            modSVars->dpadAnimator.DrawSprite(&modSVars->dpadPos, true);
        }

        if (player->classID == Player::sVars->classID ? player->up : controller->keyUp.down) {
            this->alpha                         = opacity;
            modSVars->dpadTouchAnimator.frameID = 8;
            modSVars->dpadTouchAnimator.DrawSprite(&modSVars->dpadPos, true);

            if (player->classID == Player::sVars->classID ? player->left : controller->keyLeft.down) {
                modSVars->dpadTouchAnimator.frameID = 12;
                modSVars->dpadTouchAnimator.DrawSprite(&modSVars->dpadPos, true);
            }
            else if (player->classID == Player::sVars->classID ? player->right : controller->keyRight.down) {
                modSVars->dpadTouchAnimator.frameID = 13;
                modSVars->dpadTouchAnimator.DrawSprite(&modSVars->dpadPos, true);
            }
        }
        else {
            this->alpha                    = modSVars->dpadAlpha[playerID];
            modSVars->dpadAnimator.frameID = 8;
            modSVars->dpadAnimator.DrawSprite(&modSVars->dpadPos, true);
        }

        if (player->classID == Player::sVars->classID
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

        if (player->classID == Player::sVars->classID ? player->jumpHold : controller->keyC.down) {
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
    // Draw super button
    // -----------------

    if (canSuper && (sceneInfo->state & 3) == ENGINESTATE_REGULAR) {
        if (modSVars->superAlpha[playerID] < opacity)
            modSVars->superAlpha[playerID] += 8;

        if (!player->onGround && controllerInfo[player->controllerID].keyY.down) {
            this->alpha                         = opacity;
            modSVars->dpadTouchAnimator.frameID = 3;
            modSVars->dpadTouchAnimator.DrawSprite(&superPos, true);
        }
        else {
            this->alpha                    = modSVars->superAlpha[playerID];
            modSVars->dpadAnimator.frameID = 3;
            modSVars->dpadAnimator.DrawSprite(&superPos, true);
        }
    }
    else {
        if (modSVars->superAlpha[playerID] > 0)
            modSVars->superAlpha[playerID] -= 8;

        this->alpha = modSVars->superAlpha[playerID];
        if (this->alpha > 0) {
            modSVars->dpadAnimator.frameID = 3;
            modSVars->dpadAnimator.DrawSprite(&superPos, true);
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