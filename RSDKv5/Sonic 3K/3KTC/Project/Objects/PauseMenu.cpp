// ---------------------------------------------------------------------
// RSDK Project: S3KT
// Object Name: PauseMenu
// Object Author: Jd1206, Nd1206
// ---------------------------------------------------------------------

#include "include.hpp"

using namespace RSDK;

namespace GameLogic
{

MOD_REGISTER_OBJECT(PauseMenu);

void PauseMenu::Update()
{
    this->state.Run(this);
    this->plrSelectorAnimator.Process();
}

void PauseMenu::LateUpdate()
{
    /*
    StateMachine<Player> state = RSDK_GET_ENTITY(this->triggerPlayer, Player)->state;

    if (this->state.Matches(StateMachine_None)) {
        if (state.Matches(&Player::State_Death) || state.Matches(&Player::State_Drown)) {
            this->Destroy();
        }
        else {
            this->visible = true;
            this->state.Set(&PauseMenu::State_StartPause);
            this->drawGroup = DRAWGROUP_COUNT - 1;
        }
    }
    */

    if (this->state.Matches(StateMachine_None)) {

        this->visible = true;
        this->state.Set(&PauseMenu::State_StartPause);
        this->drawGroup = DRAWGROUP_COUNT - 1;
    }
}

void PauseMenu::StaticUpdate() {}

void PauseMenu::Draw()
{
    /*
    if (S3K_SS_Setup::sVars)
        paletteBank[3].SetActivePalette(0, 255);
        */

    // Spike animation timer
    static int32 spikeTimer = 0;

    if (++spikeTimer == 2) {
        if (++this->spikePos.y > 32)
            this->spikePos.y -= 32;
        spikeTimer = 0;
    }

    this->inkEffect = INK_NONE;

    switch (this->stateDraw) {
        case PAUSEMENU_START_PAUSE:
        case PAUSEMENU_SLIDE_IN:
        case PAUSEMENU_SPRITES_FADE_IN:
            // Tinted BG Rect Position
            if (this->blackBarHeight < 240) {
                if (this->blackBarPos.y > this->blackBarHeight) {
                    temp0 = this->blackBarPos.y;
                    temp0 -= this->blackBarHeight;
                    this->blackBarHeight = this->blackBarPos.y;
                }
            }
        // Fall-through
        case PAUSEMENU_CONTROLS:
            Graphics::DrawRect(0, 0, screenInfo->size.x, this->blackBarHeight, 0x0, this->backgroundAlpha, INK_ALPHA, true);

            // Black Bar position
            temp0 = this->position.x + 128;
            Graphics::DrawRect(temp0, 0, 128, screenInfo->size.y, 0x0, 255, INK_NONE, true);

            temp0 = this->blackBarPos.x - screenInfo->size.x + 106;
            Graphics::DrawRect(temp0, 202, screenInfo->size.x, 13, 0x0, 255, INK_NONE, true);

            // Draw 'PAUSE' text sprite
            this->animator.frameID = 4;
            drawPos.x              = TO_FIXED(temp0 - 106);
            drawPos.y              = TO_FIXED(202);
            this->animator.DrawSprite(&drawPos, true);

            // Initial spike setup
            this->animator.frameID = 3;
            drawPos.x              = TO_FIXED(this->position.x);

            // Loop to draw spikes across the screen
            for (int i = 0; i < 10; i++) {
                // Draw each spike in their respective positions, and then animate them
                drawPos.y = TO_FIXED(this->spikePos.y - 32 + i * 32);
                this->animator.DrawSprite(&drawPos, true);
            }

            this->inkEffect = INK_ALPHA; // eh

            temp0 = this->position.x + 48;

            if (this->spritesXPos > temp0) {
                temp1 = temp0;
                temp1 -= this->spritesXPos;
                temp1 >>= 3;
                this->spritesXPos += temp1;
            }

            // Draw 'CONTINUE' button
            temp1                  = 48;
            this->animator.frameID = 6;
            drawPos.x              = TO_FIXED(temp0);
            drawPos.y              = TO_FIXED(temp1);
            this->animator.DrawSprite(&drawPos, true);

            if (this->selectedButton == 0) {
                this->animator.frameID = 5;
                drawPos.x              = TO_FIXED(this->spritesXPos);
                this->animator.DrawSprite(&drawPos, true);

                drawPos.x = TO_FIXED(temp0);
                this->plrSelectorAnimator.DrawSprite(&drawPos, true);
            }

            // Draw 'RESTART' button
            temp1 += 48;

            this->animator.frameID = 7;
            drawPos.x              = TO_FIXED(temp0);
            drawPos.y              = TO_FIXED(temp1);

            if (this->blockRestart == false) {
                this->animator.DrawSprite(&drawPos, true);
            }
            else {
                temp2 = this->alpha;
                this->alpha >>= 1;
                this->animator.DrawSprite(&drawPos, true);
                this->alpha = temp2;
            }

            if (this->selectedButton == 1) {
                this->animator.frameID = 5;
                drawPos.x              = TO_FIXED(this->spritesXPos);
                this->animator.DrawSprite(&drawPos, true);

                drawPos.x = TO_FIXED(temp0);
                this->plrSelectorAnimator.DrawSprite(&drawPos, true);
            }

            temp1 += 48;

            // Draw 'OPTIONS' button
            this->animator.frameID = 8;
            drawPos.y              = TO_FIXED(temp1);
            this->animator.DrawSprite(&drawPos, true);
            if (this->selectedButton == 2) {

                this->animator.frameID = 5;
                drawPos.x              = TO_FIXED(this->spritesXPos);
                this->animator.DrawSprite(&drawPos, true);

                drawPos.x = TO_FIXED(temp0);
                this->plrSelectorAnimator.DrawSprite(&drawPos, true);
            }

            temp1 += 48;

            // Draw 'EXIT' button
            this->animator.frameID = 9;
            drawPos.y              = TO_FIXED(temp1);
            this->animator.DrawSprite(&drawPos, true);
            if (this->selectedButton == 3) {

                this->animator.frameID = 5;
                drawPos.x              = TO_FIXED(this->spritesXPos);
                this->animator.DrawSprite(&drawPos, true);

                drawPos.x = TO_FIXED(temp0);
                this->plrSelectorAnimator.DrawSprite(&drawPos, true);
            }
            break;

        case PAUSEMENU_CONFIRMED:
            Graphics::DrawRect(0, 0, screenInfo->size.x, this->blackBarHeight, 0x0, this->backgroundAlpha, INK_ALPHA, true);

            // Black Bar position
            temp1 = this->position.x + 128;
            Graphics::DrawRect(temp1, 0, 128, screenInfo->size.y, 0x0, 255, INK_NONE, true);

            temp1 = this->blackBarPos.x - screenInfo->size.x + 106;
            Graphics::DrawRect(temp1, 202, screenInfo->size.x, 13, 0x0, 255, INK_NONE, true);

            this->animator.frameID = 4;
            drawPos.x              = TO_FIXED(temp1 - 106);
            drawPos.y              = TO_FIXED(202);
            this->animator.DrawSprite(&drawPos, true);

            this->animator.frameID = 3;
            drawPos.x              = TO_FIXED(this->position.x);
            for (int i = 0; i < 10; i++) {
                drawPos.y = TO_FIXED(this->spikePos.y - 32 + i * 32);
                this->animator.DrawSprite(&drawPos, true);
            }

            this->inkEffect = INK_NONE; // eh 2

            temp0 = this->position.x + 48;
            temp1 = 48;

            if (this->selectedButton == 0) { // Continue
                if (this->timer < 2) {
                    this->inkEffect        = INK_NONE;
                    this->animator.frameID = 6;
                    drawPos.x              = TO_FIXED(temp0);
                    drawPos.y              = TO_FIXED(temp1);
                    this->animator.DrawSprite(&drawPos, true);
                }
                this->animator.frameID = 5;
                drawPos.x              = TO_FIXED(this->spritesXPos);
                drawPos.y              = TO_FIXED(temp1);
                this->animator.DrawSprite(&drawPos, true);

                drawPos.x = TO_FIXED(temp0);
                drawPos.y = TO_FIXED(temp1);
                this->plrSelectorAnimator.DrawSprite(&drawPos, true);
            }
            else {
                this->inkEffect        = INK_ALPHA;
                this->animator.frameID = 6;
                drawPos.x              = TO_FIXED(temp0);
                drawPos.y              = TO_FIXED(temp1);
                this->animator.DrawSprite(&drawPos, true);
            }

            this->inkEffect = INK_ALPHA;

            temp1 += 48;
            if (this->selectedButton == 1) { // Reset
                if (this->timer < 2) {
                    this->inkEffect        = INK_NONE;
                    this->animator.frameID = 7;
                    drawPos.x              = TO_FIXED(temp0);
                    drawPos.y              = TO_FIXED(temp1);
                    this->animator.DrawSprite(&drawPos, true);
                }

                this->inkEffect        = INK_NONE;
                this->animator.frameID = 5;
                drawPos.x              = TO_FIXED(this->spritesXPos);
                drawPos.y              = TO_FIXED(temp1);
                this->animator.DrawSprite(&drawPos, true);

                drawPos.x = TO_FIXED(temp0);
                this->plrSelectorAnimator.DrawSprite(&drawPos, true);
            }
            else {
                if (this->blockRestart == false) {
                    this->inkEffect        = INK_ALPHA;
                    this->animator.frameID = 7;
                    drawPos.x              = TO_FIXED(temp0);
                    drawPos.y              = TO_FIXED(temp1);
                    this->animator.DrawSprite(&drawPos, true);
                }
                else {
                    temp2 = this->alpha;
                    this->alpha >>= 1;
                    this->inkEffect        = INK_ALPHA;
                    this->animator.frameID = 7;
                    drawPos.x              = TO_FIXED(temp0);
                    drawPos.y              = TO_FIXED(temp1);
                    this->animator.DrawSprite(&drawPos, true);
                    this->alpha = temp2;
                }
            }

            this->inkEffect = INK_ALPHA;

            temp1 += 48;
            drawPos.y = TO_FIXED(temp1);

            if (this->selectedButton == 2) { // Options
                if (this->timer < 2) {

                    this->inkEffect        = INK_NONE;
                    this->animator.frameID = 8;
                    drawPos.x              = TO_FIXED(temp0);
                    this->animator.DrawSprite(&drawPos, true);
                }

                this->inkEffect        = INK_NONE;
                this->animator.frameID = 5;
                drawPos.x              = TO_FIXED(this->spritesXPos);
                this->animator.DrawSprite(&drawPos, true);

                drawPos.x = TO_FIXED(temp0);
                this->plrSelectorAnimator.DrawSprite(&drawPos, true);
            }
            else {
                this->inkEffect        = INK_ALPHA;
                this->animator.frameID = 8;

                drawPos.x = TO_FIXED(temp0);
                this->animator.DrawSprite(&drawPos, true);
            }

            this->inkEffect = INK_ALPHA;

            temp1 += 48;
            drawPos.y = TO_FIXED(temp1);

            if (this->selectedButton == 3) { // Exit
                if (this->timer < 2) {
                    this->inkEffect        = INK_NONE;
                    this->animator.frameID = 9;
                    drawPos.x              = TO_FIXED(temp0);
                    this->animator.DrawSprite(&drawPos, true);
                }

                this->inkEffect        = INK_NONE;
                this->animator.frameID = 5;
                drawPos.x              = TO_FIXED(this->spritesXPos);
                this->animator.DrawSprite(&drawPos, true);

                drawPos.x = TO_FIXED(temp0);
                this->plrSelectorAnimator.DrawSprite(&drawPos, true);
            }
            else {
                this->inkEffect        = INK_ALPHA;
                this->animator.frameID = 9;
                drawPos.x              = TO_FIXED(temp0);
                this->animator.DrawSprite(&drawPos, true);
            }

            break;

        case PAUSEMENU_RESUME_GAME:
            Graphics::DrawRect(0, 0, screenInfo->size.x, screenInfo->size.y, 0x0, this->alpha, INK_ALPHA, true);

            // Black Bar position
            temp0 = this->position.x + 128;
            Graphics::DrawRect(temp0, 0, 128, screenInfo->size.y, 0, 255, INK_NONE, true);
            Graphics::DrawRect(0, this->blackBarPos.y, screenInfo->size.x, 13, 0, 255, INK_NONE, true);

            this->animator.frameID = 4;
            drawPos.x              = 0;
            drawPos.y              = TO_FIXED(this->blackBarPos.y);
            this->animator.DrawSprite(&drawPos, true);

            this->animator.frameID = 3;
            drawPos.x              = TO_FIXED(this->position.x);
            for (int i = 0; i < 10; i++) {
                drawPos.y = TO_FIXED(this->spikePos.y - 32 + i * 32);
                this->animator.DrawSprite(&drawPos, true);
            }

            this->inkEffect = INK_NONE; // eh 3

            drawPos.x = TO_FIXED(this->spritesXPos);

            switch (this->selectedButton) {
                case 0: // Continue
                    this->animator.frameID = 6;
                    drawPos.y              = TO_FIXED(48);
                    this->animator.DrawSprite(&drawPos, true);

                    drawPos.x = TO_FIXED(temp0);
                    this->plrSelectorAnimator.DrawSprite(&drawPos, true);
                    break;
                case 1: // Reset
                    this->animator.frameID = 7;
                    drawPos.y              = TO_FIXED(96);
                    this->animator.DrawSprite(&drawPos, true);

                    drawPos.x = TO_FIXED(temp0);
                    this->plrSelectorAnimator.DrawSprite(&drawPos, true);
                    break;
                case 2: // Options
                    this->animator.frameID = 8;
                    drawPos.y              = TO_FIXED(144);
                    this->animator.DrawSprite(&drawPos, true);

                    drawPos.x = TO_FIXED(temp0);
                    this->plrSelectorAnimator.DrawSprite(&drawPos, true);
                    break;
                case 3: // Exit

                    this->animator.frameID = 9;
                    drawPos.y              = TO_FIXED(192);
                    this->animator.DrawSprite(&drawPos, true);

                    drawPos.x = TO_FIXED(temp0);
                    this->plrSelectorAnimator.DrawSprite(&drawPos, true);
                    break;
            }
            break;

        case PAUSEMENU_EXIT_LEVEL:
            Graphics::DrawRect(0, 0, 384, this->blackBarHeight, 0x0, this->backgroundAlpha, INK_ALPHA, true);

            Graphics::DrawRect(screenInfo->size.x - 96, 0, screenInfo->size.x * 47, 240, 0x0, 255, INK_NONE, true);

            // Black Bar position
            Graphics::DrawRect(this->position.x + 128, 0, screenInfo->size.x * 47, screenInfo->size.y, 0x0, 255, INK_NONE, true);

            this->animator.frameID = 3;
            drawPos.x              = TO_FIXED(this->position.x);
            for (int i = 0; i < 10; i++) {
                drawPos.y = TO_FIXED(this->spikePos.y - 32 + i * 32);
                this->animator.DrawSprite(&drawPos, true);
            }

            drawPos.x = TO_FIXED(this->spritesXPos);

            switch (this->selectedButton) {
                case 0: // Continue
                    this->animator.frameID = 6;
                    drawPos.y              = TO_FIXED(48);
                    this->animator.DrawSprite(&drawPos, true);

                    this->plrSelectorAnimator.DrawSprite(&drawPos, true);
                    break;
                case 1: // Reset
                    this->animator.frameID = 7;
                    drawPos.y              = TO_FIXED(96);
                    this->animator.DrawSprite(&drawPos, true);

                    this->plrSelectorAnimator.DrawSprite(&drawPos, true);
                    break;
                case 2: // Options
                    this->animator.frameID = 8;
                    drawPos.y              = TO_FIXED(144);
                    this->animator.DrawSprite(&drawPos, true);

                    this->plrSelectorAnimator.DrawSprite(&drawPos, true);
                    break;
                case 3: // Exit
                    this->animator.frameID = 9;
                    drawPos.y              = TO_FIXED(192);
                    this->animator.DrawSprite(&drawPos, true);

                    this->plrSelectorAnimator.DrawSprite(&drawPos, true);
                    break;
            }
            break;
    }

    /*
    if (S3K_SS_Setup::sVars)
        paletteBank[0].SetActivePalette(0, 255);
        */
}

void PauseMenu::Create(void *data)
{
    this->controller = &controllerInfo[Input::CONT_P1];
    this->animator.SetAnimation(modSVars->aniFrames, 0, true, 0);

    uint16 targetListID = 1; // 0;

    /*
    switch (GET_CHARACTER_ID(1)) {
        case ID_NONE:
        case ID_SONIC: targetListID = 1; break;
        case ID_TAILS: targetListID = 2; break;
        case ID_KNUCKLES: targetListID = 3; break;
        case ID_AMY: targetListID = 4; break;
    }
    */

    this->plrSelectorAnimator.SetAnimation(modSVars->aniFrames, targetListID, true, 0);

    this->stateDraw = 0;

    this->backgroundAlpha = 74;

    if (!sceneInfo->inEditor) {
        this->active = ACTIVE_ALWAYS;

        if (data == INT_TO_VOID(true)) {
            this->visible   = true;
            this->drawGroup = DRAWGROUP_COUNT - 1;
        }
        else {
            this->state.Set(StateMachine_None);
            // this->stateDraw.Set(StateMachine_None);
        }
    }
}

void PauseMenu::StageLoad()
{
    sVars->active = ACTIVE_ALWAYS;

    modSVars->sfxBleep.Get("Global/MenuBleep.wav");
    modSVars->sfxAccept.Get("Global/MenuAccept.wav");
    modSVars->sfxWoosh.Get("Global/MenuWoosh.wav");

    modSVars->aniFrames.Load("3K_Global/Pause.bin", SCOPE_STAGE);

    for (int32 i = 0; i < CHANNEL_COUNT; ++i) modSVars->activeChannels[i] = false;
}

#if RETRO_INCLUDE_EDITOR
void PauseMenu::EditorDraw() {}

void PauseMenu::EditorLoad() {}
#endif

void PauseMenu::StaticLoad(Static *sVars)
{
    RSDK_INIT_STATIC_VARS(PauseMenu);

    modSVars->sfxBleep.Init();
    modSVars->sfxAccept.Init();
    modSVars->sfxWoosh.Init();
    modSVars->aniFrames.Init();
}

void PauseMenu::Serialize() {}

// Extra Entity Functions

void PauseMenu::PauseSound()
{
    for (int32 i = 0; i < CHANNEL_COUNT; ++i) {
        if (RSDKTable->ChannelActive(i)) {
            RSDKTable->PauseChannel(i);
            modSVars->activeChannels[i] = true;
        }
    }
}

void PauseMenu::ResumeSound()
{
    for (int32 i = 0; i < CHANNEL_COUNT; ++i) {
        if (modSVars->activeChannels[i]) {
            RSDKTable->ResumeChannel(i);
            modSVars->activeChannels[i] = false;
        }
    }
}

void PauseMenu::StopSound()
{
    for (int32 i = 0; i < CHANNEL_COUNT; ++i) {
        if (modSVars->activeChannels[i]) {
            RSDKTable->StopChannel(i);
            modSVars->activeChannels[i] = false;
        }
    }
}

// States

void PauseMenu::State_StartPause()
{
    SET_CURRENT_STATE();

    // Player *player = RSDK_GET_ENTITY(SLOT_PLAYER1, Player);

    // if (Music::IsPlaying())
    PauseMenu::PauseSound();

    modSVars->sfxWoosh.Play(false, 255);

    this->position.x    = screenInfo->size.x;
    this->blackBarPos.x = 0;
    this->spritesXPos   = screenInfo->size.x + 6;
    this->timer         = 0;
    this->inkEffect     = INK_ALPHA;
    this->alpha         = 0;

    Stage::SetEngineState(ENGINESTATE_FROZEN);

    // Add language switch for this(?)
    this->timerThreshold = 12;

    /*
    if (player->lives < 2 || S3K_SS_Setup::sVars)
        this->blockRestart = true;
    else
        this->blockRestart = false;
        */

    this->blockRestart = false;

    if (cfg.useTouch) {
        this->selectedButton = -1;
    }

    this->state.Set(&PauseMenu::State_SlideIn);
    this->stateDraw++;
}

void PauseMenu::State_SlideIn()
{
    SET_CURRENT_STATE();

    // Controls the position of the "PAUSE" bar that slides across the screen
    this->blackBarPos.x = (this->timer * screenInfo->size.x) / 12;
    this->blackBarPos.y = (this->timer * screenInfo->size.y) / 12;

    // Controls the position of the main pause content, based on the timer
    this->position.x = screenInfo->size.x - (this->timer << 7) / 12;

    if (this->timer < this->timerThreshold) {
        this->timer++;
    }
    else {
        this->spritesXPos = this->position.x + 48;
        this->timer       = 0;
        this->state.Set(&PauseMenu::State_SpritesFadeIn);
        this->stateDraw++;
    }
}

void PauseMenu::State_SpritesFadeIn()
{
    SET_CURRENT_STATE();

    if (this->timer < 256) {
        this->timer += 16;

        if (this->timer < 255)
            this->alpha = this->timer;
        else
            this->alpha = 255;
    }
    else {
        this->timer = 0;
        this->alpha = 255;
        this->state.Set(&PauseMenu::State_Controls);
        this->stateDraw++;
    }
}

void PauseMenu::State_Controls()
{
    SET_CURRENT_STATE();

    if (!cfg.useTouch) {
        if (this->controller->keyUp.press) {
            modSVars->sfxBleep.Play(false, 255);

            this->timer       = 0;
            this->spritesXPos = screenInfo->size.x;
            this->selectedButton--;

            if (this->selectedButton < 0)
                this->selectedButton = 3;

            if (this->blockRestart && this->selectedButton == 1)
                this->selectedButton--;
        }

        if (this->controller->keyDown.press) {
            modSVars->sfxBleep.Play(false, 255);

            this->timer       = 0;
            this->spritesXPos = screenInfo->size.x;
            this->selectedButton++;

            if (this->selectedButton > 3)
                this->selectedButton = 0;

            if (this->blockRestart && this->selectedButton == 1)
                this->selectedButton++;
        }

        if (this->controller->keyStart.press || this->controller->keyA.press) {
            modSVars->sfxAccept.Play(false, 255);

            this->state.Set(&PauseMenu::State_Confirmed);
            this->stateDraw = PAUSEMENU_CONFIRMED;
            this->alpha     = 248;
            this->timer     = 0;
        }

        if (InputHelpers::CheckTouchRect(0, 0, screenInfo->size.x, screenInfo->size.y, NULL, NULL) > -1 && cfg.useTouch) {
            // options->physicalControls = false;
            this->selectedButton = -1;
        }
    }
    else {
        int32 someRectCheck = InputHelpers::CheckTouchRect(0, 0, screenInfo->size.x, screenInfo->size.y, NULL, NULL);

        if (InputHelpers::CheckTouchRect(this->spritesXPos, 32, screenInfo->size.x, 64, NULL, NULL) > -1) {
            this->selectedButton = 0;
        }
        else {
            if (someRectCheck < 0) {
                if (this->selectedButton == 0) {
                    modSVars->sfxAccept.Play(false, 255);

                    this->state.Set(&PauseMenu::State_Confirmed);
                    this->stateDraw = PAUSEMENU_CONFIRMED;
                    this->alpha     = 248;
                    this->timer     = 0;
                }
                else {
                    if (this->selectedButton == 0)
                        this->selectedButton = -1;
                }
            }
        }

        // Restart
        if (!this->blockRestart) {
            if (InputHelpers::CheckTouchRect(this->spritesXPos, 80, screenInfo->size.x, 112, NULL, NULL) > -1) {
                this->selectedButton = 1;
            }
            else {
                if (someRectCheck < 0) {
                    if (this->selectedButton == 1) {
                        modSVars->sfxAccept.Play(false, 255);

                        this->state.Set(&PauseMenu::State_Confirmed);
                        this->stateDraw = PAUSEMENU_CONFIRMED;
                        this->alpha     = 248;
                        this->timer     = 0;
                    }
                    else {
                        if (this->selectedButton == 1)
                            this->selectedButton = -1;
                    }
                }
            }
        }

        if (InputHelpers::CheckTouchRect(this->spritesXPos, 128, screenInfo->size.x, 160, NULL, NULL) > -1) {
            this->selectedButton = 2;
        }
        else {
            if (someRectCheck < 0) {
                if (this->selectedButton == 2) {
                    modSVars->sfxAccept.Play(false, 255);

                    this->state.Set(&PauseMenu::State_Confirmed);
                    this->stateDraw = PAUSEMENU_CONFIRMED;
                    this->alpha     = 248;
                    this->timer     = 0;
                }
            }
            else {
                if (this->selectedButton == 2)
                    this->selectedButton = -1;
            }
        }

        // Options
        if (InputHelpers::CheckTouchRect(this->spritesXPos, 176, screenInfo->size.x, 208, NULL, NULL) > -1) {
            this->selectedButton = 3;
        }
        else {
            if (someRectCheck < 0) {
                if (this->selectedButton == 3) {
                    modSVars->sfxAccept.Play(false, 255);

                    this->state.Set(&PauseMenu::State_Confirmed);
                    this->stateDraw = PAUSEMENU_CONFIRMED;
                    this->alpha     = 248;
                    this->timer     = 0;
                }
            }
            else {
                if (this->selectedButton == 3)
                    this->selectedButton = -1;
            }
        }

        if (this->controller->keyUp.press) {
            this->selectedButton = 3;

            /* Mobile
                options->physicalControls = true;
            */
        }

        if (this->controller->keyDown.press) {
            this->selectedButton = 0;

            /* Mobile
                options->physicalControls = true
            */
        }

        if (this->timer < 60)
            this->timer++;
    }
}

void PauseMenu::State_Confirmed()
{
    SET_CURRENT_STATE();

    this->timer++;
    this->timer &= 3;

    this->spritesXPos += 4;

    if (this->alpha > 0) {
        this->alpha -= 8;
    }
    else {

        // Check for Resume (and options for now)
        if (this->selectedButton == 0 || this->selectedButton == 2) {
            this->spritesXPos   = this->position.x + 48;
            this->blackBarPos.y = 202;

            this->timer = 0;
            this->alpha = this->backgroundAlpha; // Used for the BG, return to the initial opacity and then fade out

            this->state.Set(&PauseMenu::State_ResumeGame);
            this->stateDraw = PAUSEMENU_RESUME_GAME;
            Stage::SetEngineState(ENGINESTATE_REGULAR);
        }
        else {
            // globals->recallEntities = false;
            // globals->initCoolBonus  = false;
            /*
            if (StarPost) {
                StarPost->postIDs[0] = 0;
                StarPost->postIDs[1] = 0;
                StarPost->postIDs[2] = 0;
                StarPost->postIDs[3] = 0;
            }
            */
            // globals->specialRingID = 0;

            // Music::Stop();

            this->spritesXPos = this->position.x + 48;

            this->state.Set(&PauseMenu::State_ExitLevel);
            this->stateDraw = PAUSEMENU_EXIT_LEVEL;
        }
    }
}

void PauseMenu::State_ResumeGame()
{
    SET_CURRENT_STATE();

    if (this->alpha > 0) {
        this->alpha -= 8;
        this->position.x += 16;
        this->spritesXPos += 16;
        this->blackBarPos.y += 16;
    }
    else {
        PauseMenu::ResumeSound();
        this->Destroy();

        /*
        if (this->P1Entity->animator.animationID == ANI_FLY) {
            RSDKTable->PlaySfx(Player->sfxFlying, true, 255);
        }

        if (this->P1Entity->animator.animationID == ANI_FLY_TIRED) {
            RSDKTable->PlaySfx(Player->sfxTired, true, 255);
        }
        */
    }
}

void PauseMenu::State_ExitLevel()
{
    SET_CURRENT_STATE();

    if (this->position.x > -64) {
        this->position.x -= 16;
        this->spritesXPos += 16;
    }
    else {
        switch (this->selectedButton) {
            case 1: // Restart
                // LampPost.Check = 0;

                /* don't be mean and keep their lives?
                if (1 == 0) { // (options->gameMode == MODE_TIMEATTACK) {
                    this->player->lives = 1;
                    this->player->score = 0;
                }
                else {
                    this->player->lives--;
                }
                */
                Stage::LoadScene();
                break;

            case 2: // Options
                // TimeAttack.Round = -1;
                // Stage::SetEngineState(ENGINESTATE_DEVMENU);

                break;

            case 3: // Exit
                // Stage.ActiveList = PRESENTATION_STAGE;
                // LampPost.Check   = 0;

                if (1 == 0) { // (options->gameMode == MODE_TIMEATTACK) {
                    // Stage.ListPos     = STAGE_P_TATTACK;
                    // TimeAttack.Result = 0;
                }
                else {
                    // Stage.ListPos = STAGE_P_TITLE;
                }
                Stage::SetScene("Presentation & Menus", "Title Screen");
                Stage::LoadScene();
                break;
        }
    }
}

// Draw states

void PauseMenu::Draw_SpritesFadeIn()
{
    SET_CURRENT_STATE();

    if (this->blackBarHeight < SCREEN_YSIZE) {
        if (this->blackBarPos.y > this->blackBarHeight) {
            temp0                = this->blackBarPos.y - this->blackBarHeight;
            this->blackBarHeight = this->blackBarPos.y;
        }
    }
}

void PauseMenu::Draw_Controls()
{
    SET_CURRENT_STATE();

    Graphics::DrawRect(0, 0, screenInfo->size.x, this->blackBarHeight, 0x0, this->backgroundAlpha, INK_ALPHA, true);

    // Black Bar position
    temp0 = this->position.x + 128;
    Graphics::DrawRect(temp0, 0, 128, screenInfo->size.y, 0x0, 255, INK_NONE, true);

    temp0 = this->blackBarPos.x - screenInfo->size.x + 106;
    Graphics::DrawRect(temp0, 202, screenInfo->size.x, 13, 0x0, 255, INK_NONE, true);

    // Draw 'PAUSE' text sprite
    this->animator.frameID = 4;
    drawPos.x              = TO_FIXED(temp0 - 106);
    drawPos.y              = TO_FIXED(202);
    this->animator.DrawSprite(&drawPos, true);

    // Initial spike setup
    this->animator.frameID = 3;
    drawPos.x              = TO_FIXED(this->position.x);

    // Loop to draw spikes across the screen
    for (int i = 0; i < 10; i++) {
        // Draw each spike in their respective positions, and then animate them
        drawPos.y = TO_FIXED(this->spikePos.y - 32 + i * 32);
        this->animator.DrawSprite(&drawPos, true);
    }

    this->inkEffect = INK_ALPHA; // eh

    temp0 = this->position.x + 48;

    if (this->spritesXPos > temp0) {
        temp1 = temp0;
        temp1 -= this->spritesXPos;
        temp1 >>= 3;
        this->spritesXPos += temp1;
    }

    // Draw 'CONTINUE' button
    temp1                  = 48;
    this->animator.frameID = 6;
    drawPos.x              = TO_FIXED(temp0);
    drawPos.y              = TO_FIXED(temp1);
    this->animator.DrawSprite(&drawPos, true);

    if (this->selectedButton == 0) {
        this->animator.frameID = 5;
        drawPos.x              = TO_FIXED(this->spritesXPos);
        this->animator.DrawSprite(&drawPos, true);

        drawPos.x = TO_FIXED(temp0);
        this->plrSelectorAnimator.DrawSprite(&drawPos, true);
    }

    // Draw 'RESTART' button
    temp1 += 48;

    this->animator.frameID = 7;
    drawPos.x              = TO_FIXED(temp0);
    drawPos.y              = TO_FIXED(temp1);

    if (this->blockRestart == false) {
        this->animator.DrawSprite(&drawPos, true);
    }
    else {
        temp2 = this->alpha;
        this->alpha >>= 1;
        this->animator.DrawSprite(&drawPos, true);
        this->alpha = temp2;
    }

    if (this->selectedButton == 1) {
        this->animator.frameID = 5;
        drawPos.x              = TO_FIXED(this->spritesXPos);
        this->animator.DrawSprite(&drawPos, true);

        drawPos.x = TO_FIXED(temp0);
        this->plrSelectorAnimator.DrawSprite(&drawPos, true);
    }

    temp1 += 48;

    // Draw 'OPTIONS' button
    this->animator.frameID = 8;
    drawPos.y              = TO_FIXED(temp1);
    this->animator.DrawSprite(&drawPos, true);
    if (this->selectedButton == 2) {

        this->animator.frameID = 5;
        drawPos.x              = TO_FIXED(this->spritesXPos);
        this->animator.DrawSprite(&drawPos, true);

        drawPos.x = TO_FIXED(temp0);
        this->plrSelectorAnimator.DrawSprite(&drawPos, true);
    }

    temp1 += 48;

    // Draw 'EXIT' button
    this->animator.frameID = 9;
    drawPos.y              = TO_FIXED(temp1);
    this->animator.DrawSprite(&drawPos, true);
    if (this->selectedButton == 3) {

        this->animator.frameID = 5;
        drawPos.x              = TO_FIXED(this->spritesXPos);
        this->animator.DrawSprite(&drawPos, true);

        drawPos.x = TO_FIXED(temp0);
        this->plrSelectorAnimator.DrawSprite(&drawPos, true);
    }
}

void PauseMenu::Draw_Confirmed()
{
    SET_CURRENT_STATE();

    Graphics::DrawRect(0, 0, screenInfo->size.x, this->blackBarHeight, 0x0, this->backgroundAlpha, INK_ALPHA, true);

    // Black Bar position
    temp1 = this->position.x + 128;
    Graphics::DrawRect(temp1, 0, 128, screenInfo->size.y, 0x0, 255, INK_NONE, true);

    temp1 = this->blackBarPos.x - screenInfo->size.x + 106;
    Graphics::DrawRect(temp1, 202, screenInfo->size.x, 13, 0x0, 255, INK_NONE, true);

    this->animator.frameID = 4;
    drawPos.x              = TO_FIXED(temp1 - 106);
    drawPos.y              = TO_FIXED(202);
    this->animator.DrawSprite(&drawPos, true);

    this->animator.frameID = 3;
    drawPos.x              = TO_FIXED(this->position.x);
    for (int i = 0; i < 10; i++) {
        drawPos.y = TO_FIXED(this->spikePos.y - 32 + i * 32);
        this->animator.DrawSprite(&drawPos, true);
    }

    this->inkEffect = INK_NONE; // eh 2

    temp0 = this->position.x + 48;
    temp1 = 48;

    if (this->selectedButton == 0) { // Continue
        if (this->timer < 2) {
            this->inkEffect        = INK_NONE;
            this->animator.frameID = 6;
            drawPos.x              = TO_FIXED(temp0);
            drawPos.y              = TO_FIXED(temp1);
            this->animator.DrawSprite(&drawPos, true);
        }
        this->animator.frameID = 5;
        drawPos.x              = TO_FIXED(this->spritesXPos);
        drawPos.y              = TO_FIXED(temp1);
        this->animator.DrawSprite(&drawPos, true);

        drawPos.x = TO_FIXED(temp0);
        drawPos.y = TO_FIXED(temp1);
        this->plrSelectorAnimator.DrawSprite(&drawPos, true);
    }
    else {
        this->inkEffect        = INK_ALPHA;
        this->animator.frameID = 6;
        drawPos.x              = TO_FIXED(temp0);
        drawPos.y              = TO_FIXED(temp1);
        this->animator.DrawSprite(&drawPos, true);
    }

    this->inkEffect = INK_ALPHA;

    temp1 += 48;
    if (this->selectedButton == 1) { // Reset
        if (this->timer < 2) {
            this->inkEffect        = INK_NONE;
            this->animator.frameID = 7;
            drawPos.x              = TO_FIXED(temp0);
            drawPos.y              = TO_FIXED(temp1);
            this->animator.DrawSprite(&drawPos, true);
        }

        this->inkEffect        = INK_NONE;
        this->animator.frameID = 5;
        drawPos.x              = TO_FIXED(this->spritesXPos);
        drawPos.y              = TO_FIXED(temp1);
        this->animator.DrawSprite(&drawPos, true);

        drawPos.x = TO_FIXED(temp0);
        this->plrSelectorAnimator.DrawSprite(&drawPos, true);
    }
    else {
        if (this->blockRestart == false) {
            this->inkEffect        = INK_ALPHA;
            this->animator.frameID = 7;
            drawPos.x              = TO_FIXED(temp0);
            drawPos.y              = TO_FIXED(temp1);
            this->animator.DrawSprite(&drawPos, true);
        }
        else {
            temp2 = this->alpha;
            this->alpha >>= 1;
            this->inkEffect        = INK_ALPHA;
            this->animator.frameID = 7;
            drawPos.x              = TO_FIXED(temp0);
            drawPos.y              = TO_FIXED(temp1);
            this->animator.DrawSprite(&drawPos, true);
            this->alpha = temp2;
        }
    }

    this->inkEffect = INK_ALPHA;

    temp1 += 48;
    drawPos.y = TO_FIXED(temp1);

    if (this->selectedButton == 2) { // Options
        if (this->timer < 2) {

            this->inkEffect        = INK_NONE;
            this->animator.frameID = 8;
            drawPos.x              = TO_FIXED(temp0);
            this->animator.DrawSprite(&drawPos, true);
        }

        this->inkEffect        = INK_NONE;
        this->animator.frameID = 5;
        drawPos.x              = TO_FIXED(this->spritesXPos);
        this->animator.DrawSprite(&drawPos, true);

        drawPos.x = TO_FIXED(temp0);
        this->plrSelectorAnimator.DrawSprite(&drawPos, true);
    }
    else {
        this->inkEffect        = INK_ALPHA;
        this->animator.frameID = 8;

        drawPos.x = TO_FIXED(temp0);
        this->animator.DrawSprite(&drawPos, true);
    }

    this->inkEffect = INK_ALPHA;

    temp1 += 48;
    drawPos.y = TO_FIXED(temp1);

    if (this->selectedButton == 3) { // Exit
        if (this->timer < 2) {
            this->inkEffect        = INK_NONE;
            this->animator.frameID = 9;
            drawPos.x              = TO_FIXED(temp0);
            this->animator.DrawSprite(&drawPos, true);
        }

        this->inkEffect        = INK_NONE;
        this->animator.frameID = 5;
        drawPos.x              = TO_FIXED(this->spritesXPos);
        this->animator.DrawSprite(&drawPos, true);

        drawPos.x = TO_FIXED(temp0);
        this->plrSelectorAnimator.DrawSprite(&drawPos, true);
    }
    else {
        this->inkEffect        = INK_ALPHA;
        this->animator.frameID = 9;
        drawPos.x              = TO_FIXED(temp0);
        this->animator.DrawSprite(&drawPos, true);
    }
}

void PauseMenu::Draw_ResumeGame()
{
    SET_CURRENT_STATE();

    Graphics::DrawRect(0, 0, screenInfo->size.x, screenInfo->size.y, 0x0, this->alpha, INK_ALPHA, true);

    // Black Bar position
    temp0 = this->position.x + 128;
    Graphics::DrawRect(temp0, 0, 128, screenInfo->size.y, 0, 255, INK_NONE, true);
    Graphics::DrawRect(0, this->blackBarPos.y, screenInfo->size.x, 13, 0, 255, INK_NONE, true);

    this->animator.frameID = 4;
    drawPos.x              = 0;
    drawPos.y              = TO_FIXED(this->blackBarPos.y);
    this->animator.DrawSprite(&drawPos, true);

    this->animator.frameID = 3;
    drawPos.x              = TO_FIXED(this->position.x);
    for (int i = 0; i < 10; i++) {
        drawPos.y = TO_FIXED(this->spikePos.y - 32 + i * 32);
        this->animator.DrawSprite(&drawPos, true);
    }

    this->inkEffect = INK_NONE; // eh 3

    drawPos.x = TO_FIXED(this->spritesXPos);

    switch (this->selectedButton) {
        case 0: // Continue
            this->animator.frameID = 6;
            drawPos.y              = TO_FIXED(48);
            this->animator.DrawSprite(&drawPos, true);

            drawPos.x = TO_FIXED(temp0);
            this->plrSelectorAnimator.DrawSprite(&drawPos, true);
            break;
        case 1: // Reset
            this->animator.frameID = 7;
            drawPos.y              = TO_FIXED(96);
            this->animator.DrawSprite(&drawPos, true);

            drawPos.x = TO_FIXED(temp0);
            this->plrSelectorAnimator.DrawSprite(&drawPos, true);
            break;
        case 2: // Options
            this->animator.frameID = 8;
            drawPos.y              = TO_FIXED(144);
            this->animator.DrawSprite(&drawPos, true);

            drawPos.x = TO_FIXED(temp0);
            this->plrSelectorAnimator.DrawSprite(&drawPos, true);
            break;
        case 3: // Exit

            this->animator.frameID = 9;
            drawPos.y              = TO_FIXED(192);
            this->animator.DrawSprite(&drawPos, true);

            drawPos.x = TO_FIXED(temp0);
            this->plrSelectorAnimator.DrawSprite(&drawPos, true);
            break;
    }
}

void PauseMenu::Draw_ExitLevel()
{
    SET_CURRENT_STATE();

    Graphics::DrawRect(0, 0, 384, this->blackBarHeight, 0x0, this->backgroundAlpha, INK_ALPHA, true);

    Graphics::DrawRect(screenInfo->size.x - 96, 0, screenInfo->size.x * 47, 240, 0x0, 255, INK_NONE, true);

    // Black Bar position
    Graphics::DrawRect(this->position.x + 128, 0, screenInfo->size.x * 47, screenInfo->size.y, 0x0, 255, INK_NONE, true);

    this->animator.frameID = 3;
    drawPos.x              = TO_FIXED(this->position.x);
    for (int i = 0; i < 10; i++) {
        drawPos.y = TO_FIXED(this->spikePos.y - 32 + i * 32);
        this->animator.DrawSprite(&drawPos, true);
    }

    drawPos.x = TO_FIXED(this->spritesXPos);

    switch (this->selectedButton) {
        case 0: // Continue
            this->animator.frameID = 6;
            drawPos.y              = TO_FIXED(48);
            this->animator.DrawSprite(&drawPos, true);

            this->plrSelectorAnimator.DrawSprite(&drawPos, true);
            break;
        case 1: // Reset
            this->animator.frameID = 7;
            drawPos.y              = TO_FIXED(96);
            this->animator.DrawSprite(&drawPos, true);

            this->plrSelectorAnimator.DrawSprite(&drawPos, true);
            break;
        case 2: // Options
            this->animator.frameID = 8;
            drawPos.y              = TO_FIXED(144);
            this->animator.DrawSprite(&drawPos, true);

            this->plrSelectorAnimator.DrawSprite(&drawPos, true);
            break;
        case 3: // Exit
            this->animator.frameID = 9;
            drawPos.y              = TO_FIXED(192);
            this->animator.DrawSprite(&drawPos, true);

            this->plrSelectorAnimator.DrawSprite(&drawPos, true);
            break;
    }
}

// ...

} // namespace GameLogic