#include "../3KTC.hpp"

using namespace RSDK;

namespace GameLogic {

// -------------------
// Object Registration
// -------------------

MOD_REGISTER_OBJECT(S3K_SS_HUD);

// ----------------------
// Standard Entity Events
// ----------------------

void S3K_SS_HUD::Draw(void) {
    sVars->Super(SUPER_DRAW);
    this->DrawTouchControls();
}

void S3K_SS_HUD::StageLoad(void) {
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

void S3K_SS_HUD::DrawTouchControls(void) {
    paletteBank[3].SetActivePalette(0, 255);

    S3K_SS_Player *player = RSDK_GET_ENTITY(SLOT_PLAYER1, S3K_SS_Player);

    int32 alphaStore   = this->alpha;
    int32 inkStore     = this->inkEffect;
    int32 fxStore      = this->drawFX;
    Vector2 scaleStore = this->scale;

    modSVars->dpadPos.x = TO_FIXED(config.moveDPadPos.x);
    modSVars->dpadPos.y = TO_FIXED(config.moveDPadPos.y);

    modSVars->actionPos.x = TO_FIXED(screenInfo[sceneInfo->currentScreenID].size.x + config.jumpDPadPos.x);
    modSVars->actionPos.y = TO_FIXED(config.jumpDPadPos.y);

    modSVars->pausePos.x = TO_FIXED(screenInfo[sceneInfo->currentScreenID].center.x);
    modSVars->pausePos.y = TO_FIXED(16);

    this->inkEffect = INK_ALPHA;
    this->drawFX    = FX_SCALE;

    int32 opacity = (int32)(0x100 * config.vDPadOpacity);
    this->scale.x = (int32)(0x200 * config.vDPadSize);
    this->scale.y = (int32)(0x200 * config.vDPadSize);

    bool32 enabled = player->stateInput.Matches(S3K_SS_Player::Input_Gamepad.action);
    if (enabled) {
        if ((sceneInfo->state & 3) == ENGINESTATE_REGULAR) {
            if (modSVars->dpadAlpha < opacity) {
                modSVars->dpadAlpha += 4;
                modSVars->pauseAlpha = modSVars->dpadAlpha << 1;
            }

            // Draw DPad
            this->alpha                    = modSVars->dpadAlpha;
            modSVars->dpadAnimator.frameID = 10;
            modSVars->dpadAnimator.DrawSprite(&modSVars->dpadPos, true);

            if (player->left) {
                this->alpha                         = opacity;
                modSVars->dpadTouchAnimator.frameID = 6;
                modSVars->dpadTouchAnimator.DrawSprite(&modSVars->dpadPos, true);
            } else {
                this->alpha                    = modSVars->dpadAlpha;
                modSVars->dpadAnimator.frameID = 6;
                modSVars->dpadAnimator.DrawSprite(&modSVars->dpadPos, true);
            }

            if (player->down) {
                this->alpha                         = opacity;
                modSVars->dpadTouchAnimator.frameID = 9;
                modSVars->dpadTouchAnimator.DrawSprite(&modSVars->dpadPos, true);

                if (player->left) {
                    modSVars->dpadTouchAnimator.frameID = 14;
                    modSVars->dpadTouchAnimator.DrawSprite(&modSVars->dpadPos, true);
                } else if (player->right) {
                    modSVars->dpadTouchAnimator.frameID = 15;
                    modSVars->dpadTouchAnimator.DrawSprite(&modSVars->dpadPos, true);
                }
            } else {
                this->alpha                    = modSVars->dpadAlpha;
                modSVars->dpadAnimator.frameID = 9;
                modSVars->dpadAnimator.DrawSprite(&modSVars->dpadPos, true);
            }

            if (player->right) {
                this->alpha                         = opacity;
                modSVars->dpadTouchAnimator.frameID = 7;
                modSVars->dpadTouchAnimator.DrawSprite(&modSVars->dpadPos, true);
            } else {
                this->alpha                    = modSVars->dpadAlpha;
                modSVars->dpadAnimator.frameID = 7;
                modSVars->dpadAnimator.DrawSprite(&modSVars->dpadPos, true);
            }

            if (player->up) {
                this->alpha                         = opacity;
                modSVars->dpadTouchAnimator.frameID = 8;
                modSVars->dpadTouchAnimator.DrawSprite(&modSVars->dpadPos, true);

                if (player->left) {
                    modSVars->dpadTouchAnimator.frameID = 12;
                    modSVars->dpadTouchAnimator.DrawSprite(&modSVars->dpadPos, true);
                } else if (player->right) {
                    modSVars->dpadTouchAnimator.frameID = 13;
                    modSVars->dpadTouchAnimator.DrawSprite(&modSVars->dpadPos, true);
                }
            } else {
                this->alpha                    = modSVars->dpadAlpha;
                modSVars->dpadAnimator.frameID = 8;
                modSVars->dpadAnimator.DrawSprite(&modSVars->dpadPos, true);
            }

            if (!player->up && !player->down && !player->left && !player->right) {
                this->alpha                    = modSVars->dpadAlpha;
                modSVars->dpadAnimator.frameID = 11;
                modSVars->dpadAnimator.DrawSprite(&modSVars->dpadPos, true);
            }

            ControllerState *controller = &controllerInfo[player->controllerID];
            bool32 jumpHold             = controller->keyA.down || controller->keyB.down || controller->keyC.down || controller->keyX.down;
            if (jumpHold) {
                this->alpha                         = opacity;
                modSVars->dpadTouchAnimator.frameID = 1;
                modSVars->dpadTouchAnimator.DrawSprite(&modSVars->actionPos, true);
            } else {
                this->alpha                    = modSVars->dpadAlpha;
                modSVars->dpadAnimator.frameID = 1;
                modSVars->dpadAnimator.DrawSprite(&modSVars->actionPos, true);
            }
        } else {
            modSVars->dpadAlpha  = 0;
            modSVars->pauseAlpha = 0;
        }

        this->alpha                         = modSVars->pauseAlpha;
        modSVars->dpadTouchAnimator.frameID = 5;
        modSVars->dpadTouchAnimator.DrawSprite(&modSVars->pausePos, true);
    } else {
        if (modSVars->dpadAlpha > 0) {
            modSVars->dpadAlpha -= 4;
            modSVars->pauseAlpha -= 8;
        }

        this->alpha = modSVars->dpadAlpha;
        if (this->alpha > 0) {
            modSVars->dpadAnimator.frameID = 0;
            modSVars->dpadAnimator.DrawSprite(&modSVars->dpadPos, true);

            modSVars->dpadAnimator.frameID = 1;
            modSVars->dpadAnimator.DrawSprite(&modSVars->actionPos, true);
        }

        if (modSVars->pauseAlpha < 0)
            this->alpha = 0;
        else
            this->alpha = modSVars->pauseAlpha;

        modSVars->dpadTouchAnimator.frameID = 5;
        modSVars->dpadTouchAnimator.DrawSprite(&modSVars->pausePos, true);
    }

    this->alpha     = alphaStore;
    this->inkEffect = inkStore;
    this->drawFX    = fxStore;
    this->scale     = scaleStore;

    paletteBank[0].SetActivePalette(0, 255);
}

} // namespace GameLogic