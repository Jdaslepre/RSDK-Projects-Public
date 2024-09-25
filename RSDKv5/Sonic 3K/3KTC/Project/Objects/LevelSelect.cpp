#include "../3KTC.hpp"

using namespace RSDK;

namespace GameLogic {

// -------------------
// Object Registration
// -------------------

MOD_REGISTER_OBJECT(LevelSelect);

// -------------
// Object States
// -------------

Action<void> LevelSelect::State_Navigate;

// ----------------------
// Standard Entity Events
// ----------------------

void LevelSelect::Draw(void) {

    int32 prevInfo[3];
    prevInfo[0] = this->alpha;
    prevInfo[1] = this->inkEffect;
    prevInfo[2] = paletteBank[0].GetEntry(82);

    this->alpha     = 160;
    this->inkEffect = INK_ALPHA;

    // set a blue color, because this specific index
    // is messed up in origins for whatever reason
    paletteBank[0].SetEntry(82, 0x000080);

    Vector2 drawPos;
    drawPos.x = TO_FIXED(62);
    drawPos.y = TO_FIXED(screenInfo->size.y - 38);

    // Dpad
    modSVars->animator.SetAnimation(modSVars->aniFrames, 0, true, 0);

    // Up
    modSVars->animator.frameID = controllerInfo->keyUp.down ? DPadFrameIDs::DpadUpPressed : DPadFrameIDs::DpadUp;
    modSVars->animator.DrawSprite(&drawPos, true);

    // Down
    modSVars->animator.frameID = controllerInfo->keyDown.down ? DPadFrameIDs::DpadDownPressed : DPadFrameIDs::DpadDown;
    modSVars->animator.DrawSprite(&drawPos, true);

    // Left
    modSVars->animator.frameID = controllerInfo->keyLeft.down ? DPadFrameIDs::DpadLeftPressed : DPadFrameIDs::DpadLeft;
    modSVars->animator.DrawSprite(&drawPos, true);

    // Right
    modSVars->animator.frameID = controllerInfo->keyRight.down ? DPadFrameIDs::DpadRightPressed : DPadFrameIDs::DpadRight;
    modSVars->animator.DrawSprite(&drawPos, true);

    // Go/Start button
    modSVars->animator.SetAnimation(modSVars->aniFrames, 1, false, 0);

    // Sound test
    if (this->labelID >= this->labelCount - 1) {
        modSVars->pressed ? modSVars->animator.frameID = ButtonFrameIDs::ButtonPlayDown : modSVars->animator.frameID = ButtonFrameIDs::ButtonPlay;
    }
    // Stages
    else {
        modSVars->pressed ? modSVars->animator.frameID = ButtonFrameIDs::ButtonGoDown : modSVars->animator.frameID = ButtonFrameIDs::ButtonGo;
    }

    drawPos.x = TO_FIXED(screenInfo->size.x - 38);
    modSVars->animator.DrawSprite(&drawPos, true);

    this->alpha     = prevInfo[0];
    this->inkEffect = prevInfo[1];
    paletteBank[0].SetEntry(82, prevInfo[2]);

    sVars->Super(SUPER_DRAW);
}

void LevelSelect::StageLoad(void) {
    modSVars->aniFrames.Load("LSelect/LSelect_TouchEx.bin", SCOPE_STAGE);
    modSVars->animator.SetAnimation(modSVars->aniFrames, 0, true, 0);

    sVars->Super(SUPER_STAGELOAD);
}

void LevelSelect::StaticLoad(Static *sVars) {
    RSDK_INIT_STATIC_VARS(LevelSelect);

    int32 bgAniDurationTable[]     = { 240, 3, 3, 3 };
    int32 cheat_RickyMode[]        = { 1, 9, 7, 9, 0, 8, 1, 1, 255 };
    int32 cheat_AllEmeralds[]      = { 4, 1, 2, 6, 255 };
    int32 cheat_MaxContinues[]     = { 1, 9, 9, 2, 1, 1, 2, 4, 255 };
    int32 cheat_SwapGameMode[]     = { 2, 0, 1, 8, 0, 6, 2, 3, 255 };
    int32 cheat_UnlockAllMedals[]  = { 1, 9, 8, 9, 0, 5, 0, 1, 255 };
    int32 cheat_SuperDash[]        = { 2, 0, 1, 7, 0, 8, 1, 5, 255 };
    int32 cheat_MaxControl[]       = { 9, 0, 0, 1, 255 };
    int32 cheat_ToggleSuperMusic[] = { 6, 2, 1, 4, 255, 0, 0, 0, 0 };

    memcpy(&sVars->bgAniDurationTable, bgAniDurationTable, sizeof(bgAniDurationTable));
    memcpy(&sVars->cheat_RickyMode, cheat_RickyMode, sizeof(cheat_RickyMode));
    memcpy(&sVars->cheat_AllEmeralds, cheat_AllEmeralds, sizeof(cheat_AllEmeralds));
    memcpy(&sVars->cheat_MaxContinues, cheat_MaxContinues, sizeof(cheat_MaxContinues));
    memcpy(&sVars->cheat_SwapGameMode, cheat_SwapGameMode, sizeof(cheat_SwapGameMode));
    memcpy(&sVars->cheat_UnlockAllMedals, cheat_UnlockAllMedals, sizeof(cheat_UnlockAllMedals));
    memcpy(&sVars->cheat_SuperDash, cheat_SuperDash, sizeof(cheat_SuperDash));
    memcpy(&sVars->cheat_MaxControl, cheat_MaxControl, sizeof(cheat_MaxControl));
    memcpy(&sVars->cheat_ToggleSuperMusic, cheat_ToggleSuperMusic, sizeof(cheat_ToggleSuperMusic));

    sVars->bgAniDuration = 240;
    sVars->sfxFail.Init();
    sVars->sfxRing.Init();
    sVars->sfxEmerald.Init();
    sVars->sfxContinue.Init();
    sVars->sfxMedalCaught.Init();

    /*
    sVars->checkCheatActivated[0] = LevelSelect::Cheat_RickyMode;
    // sVars->checkCheatActivated[1] = sub_140201490;
    sVars->checkCheatActivated[2] = LevelSelect::Cheat_MaxContinues;
    sVars->checkCheatActivated[3] = LevelSelect::Cheat_SuperDash;
    sVars->checkCheatActivated[4] = LevelSelect::Cheat_SuperMusic;
    sVars->checkCheatActivated[5] = LevelSelect::Cheat_VSPhysics;
    // sVars->checkCheatActivated[6] = LevelSelect::Cheat_SpriteStyle;
    sVars->checkCheatActivated[7] = LevelSelect::Cheat_DebugMode;
    sVars->checkCheatActivated[8] = LevelSelect::Cheat_CameraTracking;
    // sVars->checkCheatActivated[9] = nullsub_1;
    sVars->checkCheatActivated[10] = LevelSelect::Cheat_PenPenMode;
    sVars->checkCheatActivated[11] = LevelSelect::Cheat_RandomItems;
    sVars->checkCheatActivated[12] = LevelSelect::Cheat_BlueShieldMode;
    sVars->checkCheatActivated[13] = LevelSelect::Cheat_Peelout;
    sVars->checkCheatActivated[14] = LevelSelect::Cheat_BananaMode;
    sVars->checkCheatActivated[15] = LevelSelect::Cheat_NoItems;
    */
}

// ----------------
// Public Functions
// ----------------

void (*LevelSelect_State_Navigate)(void) = nullptr;

// ----------------------
// Extra Entity Functions
// ----------------------

bool32 LevelSelect_State_Navigate_Hook(bool32 skippedState) {
    SELF_REF(LevelSelect);

    // Dpad
    int32 touch = Touch::CheckRect(0, 96, screenInfo->center.x - 56, screenInfo->size.y, NULL, NULL);
    if (touch >= 0) {

        int32 touchX = (int32)(touchInfo->x[touch] * screenInfo->size.x) - 64;
        int32 touchY = (int32)(touchInfo->y[touch] * screenInfo->size.y) - 202;

        switch (((Math::ATan2(touchX, touchY) + 0x20) & 0xFF) >> 6) {
            case 0:
                controllerInfo->keyRight.down = true;

                if (!LevelSelect::modSVars->pressedLR)
                    controllerInfo->keyRight.press |= controllerInfo->keyRight.down;

                LevelSelect::modSVars->pressedLR = controllerInfo->keyRight.down;
                break;

            case 1: controllerInfo->keyDown.down = true; break;

            case 2:
                controllerInfo->keyLeft.down = true;

                if (!LevelSelect::modSVars->pressedLR)
                    controllerInfo->keyLeft.press |= controllerInfo->keyLeft.down;

                LevelSelect::modSVars->pressedLR = controllerInfo->keyLeft.down;
                break;

            case 3: controllerInfo->keyUp.down = true; break;
        }

        int32 x1 = screenInfo->size.x - 62;
        int32 x2 = x1 + 48;

        if (Touch::CheckRect(x1, 172, x2, 222, NULL, NULL) >= 0)
            LevelSelect::modSVars->pressed = true;
        else
            LevelSelect::modSVars->pressed = false;
    } else {
        LevelSelect::modSVars->pressedLR = false;
    }

    // Go/Start button
    if (CheckAnyTouch()) {
        int32 x1 = screenInfo->size.x - 62;
        int32 x2 = x1 + 48;

        if (Touch::CheckRect(x1, 172, x2, 222, NULL, NULL) >= 0)
            LevelSelect::modSVars->pressed = true;
        else
            LevelSelect::modSVars->pressed = false;
    } else if (LevelSelect::modSVars->pressed) {
        LevelSelect::modSVars->pressed = false;

        if (self->labelID >= self->labelCount - 1)
            controllerInfo->keyA.press = true;
        else
            controllerInfo->keyStart.press = true;
    }

    return false;
}

} // namespace GameLogic