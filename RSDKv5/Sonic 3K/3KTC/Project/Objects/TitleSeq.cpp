#include "../3KTC.hpp"

using namespace RSDK;

namespace GameLogic {

// -------------------
// Object Registration
// -------------------

MOD_REGISTER_OBJECT(TitleSeq);

// -------------
// Object States
// -------------

Action<void> TitleSeq::State_WaitSEGA;
Action<void> TitleSeq::State_Animate;
Action<void> TitleSeq::State_WaitEx;

// ----------------------
// Standard Entity Events
// ----------------------

void TitleSeq::Create(void *data) {
    globals->skipTitleIntro       = false;
    modSVars->levelSelectCheatPos = false;

    sVars->Super(SUPER_CREATE, data);
}

void TitleSeq::StaticLoad(Static *sVars) {
    RSDK_INIT_STATIC_VARS(TitleSeq);

    sVars->sfxSega.Init();
    sVars->sfxButton.Init();
    sVars->sfxFail.Init();
    sVars->sfxStart.Init();
    sVars->sfxRing.Init();
    sVars->unused        = 0;
    sVars->timer         = 0;
    sVars->introLayer.id = 0;
    memset(sVars->colors, 0, sizeof(color) * 14);

    int8 sonicIntroFrameTimes[] = { 8, 8, 5, 5, 5, 5, 7, 16, 16, 11, 10, 5 };
    memcpy(&sVars->sonicIntroFrameTimes, sonicIntroFrameTimes, sizeof(sonicIntroFrameTimes));

    // up, up, down, down, up, up, up, up
    uint8 matchLevelSelect[] = { 0x01, 0x01, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01 };
    memcpy(&sVars->matchLevelSelect, matchLevelSelect, sizeof(matchLevelSelect));

    // up, up, up, down, down, down, up
    uint8 matchUnknown[] = { 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x01 };
    memcpy(&sVars->matchUnknown, matchUnknown, sizeof(matchUnknown));

    // down-right, down-right, down-right, down-right, down-right, down-right, up, down, down, down, left, right
    // NOTE - this is effectively impossible under normal play due to requiring frame perfect diagonal inputs for the first 6 presses
    uint8 matchUnknown2[] = { 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x01, 0x02, 0x02, 0x02, 0x04, 0x08 };
    memcpy(&sVars->matchUnknown2, matchUnknown2, sizeof(matchUnknown2));

    memset(&sVars->statusLevelSelect, 0, sizeof(CheatStatus));
    memset(&sVars->statusUnknown, 0, sizeof(CheatStatus));
    memset(&sVars->statusUnknown2, 0, sizeof(CheatStatus));
    sVars->seqCountLevelSelect = 0;
    sVars->seqCountUnknown     = 0;
    sVars->seqCountUnknown2    = 0;
}

// ----------------------
// Extra Entity Functions
// ----------------------

void TitleSeq::CheckTouchCheatCodes(void) {
    if (Touch::CheckRect(0, 0, screenInfo->size.x, screenInfo->size.y, 0, 0) == -1)
        modSVars->touchDown = false;

    if (!modSVars->touchDown) {
        int32 pos = screenInfo->center.x; // letter position
        int32 len = 0;                    // letter length

        // Match level select (SEGA)
        switch (modSVars->levelSelectCheatPos) {
            case 0: // S
                pos -= 88;
                len = pos + 40;
                break;
            case 1: // E
                pos -= 46;
                len = pos + 38;
                break;
            case 2: // G
                pos -= 6;
                len = pos + 40;
                break;
            case 3: // A
                pos += 34;
                len = pos + 55;
                break;
        }

        if (Touch::CheckRect(pos, 90, len, 160, NULL, NULL) >= 0) {
            modSVars->touchDown = true;

            modSVars->levelSelectCheatPos++;

            if (modSVars->levelSelectCheatPos == 4) {
                sVars->sfxRing.Play(false, 255);
                globals->soundTestEnabled = true;
            }
        }
    }
}

bool32 TitleSeq_State_WaitSEGA_Hook(bool32 skippedState) {
    TitleSeq::CheckTouchCheatCodes();

    // Since we're checking for cheat inputs above, we can't just use
    // CheckAnyTouch() here - instead, we check everywhere but "SEGA"

    bool32 touched = false;
    touched |= Touch::CheckRect(0, 0, screenInfo->center.x - 90, screenInfo->size.y, NULL, NULL) >= 0;
    touched |= Touch::CheckRect(screenInfo->center.x + 91, 0, screenInfo->size.x, screenInfo->size.y, NULL, NULL) >= 0;
    touched |= Touch::CheckRect(screenInfo->center.x - 90, 0, screenInfo->center.x + 91, 88, NULL, NULL) >= 0;
    touched |= Touch::CheckRect(screenInfo->center.x - 90, 152, screenInfo->center.x + 91, screenInfo->size.y, NULL, NULL) >= 0;

    if (touched) {
        controllerInfo->keyStart.press = true;
    }

    return false;
}

// Generic statehook that allows you to skip
// the intro sequence by touching the screen
bool32 TitleSeq_CheckSkip(bool32 skippedState) {

    if (CheckAnyTouch()) {
        controllerInfo->keyStart.press = true;
    }

    return false;
}

} // namespace GameLogic