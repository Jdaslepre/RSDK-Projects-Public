#include "../3KTC.hpp"

using namespace RSDK;

namespace GameLogic
{

// -------------------
// Object Registration
// -------------------

MOD_REGISTER_OBJECT(DebugMode);

// ----------------------
// Standard Entity Events
// ----------------------

void DebugMode::Update(void)
{
    ControllerState *controller = &controllerInfo[Input::CONT_P1];

    Touch::Control8Dir(controller);

    if (sVars->itemType == 0xFF)
        sVars->itemType = sVars->itemTypeCount ? (sVars->itemTypeCount - 1) : 0;

    int32 tx = 0, ty = 0;
    if (Touch::CheckRect(screenInfo->center.x - 48, 0, screenInfo->center.x + 48, 56, &tx, &ty) >= 0) {
        if (tx > screenInfo->center.x) {
            if (!Player::modSVars->touchJump) {
                sVars->itemType++;
                if (sVars->itemType >= sVars->itemTypeCount) {
                    sVars->itemType      = 0;
                    sVars->itemTypeCount = 0;

                    sVars->itemID++;
                    if (sVars->itemID >= sVars->itemCount)
                        sVars->itemID = 0;
                }
            }

            Player::modSVars->touchJump = true;
        }
        else {
            if (!Player::modSVars->touchJump) {
                sVars->itemType--;

                if (sVars->itemType == 0xFF) {
                    sVars->itemTypeCount = 0;

                    sVars->itemID--;
                    if (sVars->itemID < 0)
                        sVars->itemID = sVars->itemCount - 1;
                }
            }

            Player::modSVars->touchJump = true;
        }
    }
    else {
        if (Touch::CheckRect(screenInfo->center.x, 96, screenInfo->size.x, screenInfo->size.y, NULL, NULL) >= 0) {
            controllerInfo->keyC.down = true;
            controller->keyC.down     = true;
            if (!Player::modSVars->touchJump) {
                controllerInfo->keyC.press = true;
                controller->keyC.press     = true;
            }
            Player::modSVars->touchJump = controller->keyC.down;
        }
        else
            Player::modSVars->touchJump = false;
    }

    bool32 touchedDebug = false;
    if (Touch::CheckRect(0, 0, 112, 56, NULL, NULL) >= 0) {
        controllerInfo->keyX.down = true;
        controller->keyX.down     = true;
        touchedDebug              = true;
    }

    if (!Player::modSVars->touchDebug && touchedDebug) {
        controllerInfo->keyX.press = true;
        controller->keyX.press     = true;
    }

    Player::modSVars->touchDebug = controller->keyX.down;
    sVars->Super(SUPER_UPDATE);
}

void DebugMode::Draw(void)
{
    sVars->Super(SUPER_DRAW);

    int32 prevDir   = this->direction;
    this->direction = FLIP_NONE;

    Vector2 drawPos;
    drawPos.x = TO_FIXED(screenInfo->center.x);
    drawPos.y = TO_FIXED(16);

    // X
    modSVars->animator.frameID = 0;
    modSVars->animator.DrawSprite(&drawPos, true);

    // Y
    modSVars->animator.frameID = 1;
    modSVars->animator.DrawSprite(&drawPos, true);

    this->direction = prevDir;
}

void DebugMode::StageLoad(void)
{
    if (globals->gameSpriteStyle == GAME_SM)
        modSVars->aniFrames.Load("Global/TouchControls.bin", SCOPE_STAGE);
    else
        modSVars->aniFrames.Load("3K_Global/TouchControls.bin", SCOPE_STAGE);

    // Debug mode buttons (Plus/Minus)
    modSVars->animator.SetAnimation(modSVars->aniFrames, 3, true, 0);

    sVars->Super(SUPER_STAGELOAD);
}

} // namespace GameLogic