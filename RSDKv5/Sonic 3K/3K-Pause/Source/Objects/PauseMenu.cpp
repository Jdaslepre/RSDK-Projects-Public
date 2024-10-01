#include "3K-Pause.hpp"

using namespace RSDK;

namespace GameLogic
{

// -------------------
// Object Registration
// -------------------

MOD_REGISTER_OBJECT(PauseMenu);

// -------------
// Entity Events
// -------------

void PauseMenu::Update()
{
    this->state.Run(this);
    this->selectionAnimator.Process();

    ControllerState *controller = &controllerInfo[Input::CONT_P1];
    AnalogState *stick          = &analogStickInfoL[Input::CONT_P1];

    this->up = controller->keyUp.press;
    this->up |= stick->keyUp.press;

    this->down = controller->keyDown.press;
    this->down |= stick->keyDown.press;

    this->start = controller->keyStart.press;
    this->start |= controller->keyA.press;
    this->start |= unknownInfo->pausePress;
}

void PauseMenu::LateUpdate()
{
    auto pState = GameObject::Get<Player>(triggerPlayer)->state.state;

    if (this->state.Matches(StateMachine_None)) {
        if (1 == 0 /*pState.Matches(&Player::State_Death) || pState.Matches(&Player::State_Drown)*/) {
            Destroy();
        }
        else {
            visible   = true;
            drawGroup = DRAWGROUP_COUNT - 1;
            state.Set(&PauseMenu::State_StartPause);
        }
    }
}

void PauseMenu::StaticUpdate() {}

int32 temp0;

void PauseMenu::Draw()
{
    // 5 = Category Special

    if (sceneInfo->activeCategory == 5)
        paletteBank[3].SetActivePalette(0, 255);

    this->stateDraw.Run(this);

    if (sceneInfo->activeCategory == 5)
        paletteBank[0].SetActivePalette(0, 255);
}

void PauseMenu::Create(void *data)
{
    this->animator.SetAnimation(modSVars->aniFrames, 0, true, 0);

    switch (GET_CHARACTER_ID(1)) {
        default:
        case ID_NONE:
        case ID_SONIC: selectionAnimator.SetAnimation(modSVars->aniFrames, 1, true, 0); break;
        case ID_TAILS: selectionAnimator.SetAnimation(modSVars->aniFrames, 2, true, 0); break;
        case ID_KNUCKLES:
            selectionAnimator.SetAnimation(modSVars->aniFrames, 3, true, 0);
            break;
            // case ID_AMY: selectionAnimator.SetAnimation(modSVars->aniFrames, 4, true, 0); break;
    }

    this->backgroundAlpha = 74;

    if (!sceneInfo->inEditor) {
        this->active = ACTIVE_ALWAYS;

        if (data == INT_TO_VOID(true)) {
            this->visible   = true;
            this->drawGroup = DRAWGROUP_COUNT - 1;
        }
        else {
            this->state.Set(StateMachine_None);
            this->stateDraw.Set(StateMachine_None);
        }
    }
}

void PauseMenu::StageLoad()
{
    sVars->active = ACTIVE_ALWAYS;

    modSVars->aniFrames.Load("3K_Global/Pause.bin", SCOPE_STAGE);
    modSVars->sfxBleep.Get("Global/MenuBleep.wav");
    modSVars->sfxAccept.Get("Global/MenuAccept.wav");
    modSVars->sfxWoosh.Get("Global/MenuWoosh.wav");

    for (int32 i = 0; i < CHANNEL_COUNT; ++i) modSVars->activeChannels[i] = false;
}

// Extra Entity Functions
void PauseMenu::DrawPauseRect(int32 y)
{
    // 'PAUSE' rect left
    Graphics::DrawRect(this->position.x + 128, NULL, 128, screenInfo->size.y, 0x000000, 0xFF, INK_NONE, true);

    // 'PAUSE' text sprite
    this->animator.frameID = 4;
    this->drawPos.x        = TO_FIXED(this->pauseBarPos.x - screenInfo->size.x);
    this->drawPos.y        = TO_FIXED(y);
    this->animator.DrawSprite(&this->drawPos, true);

    // 'PAUSE' rect right
    Graphics::DrawRect(this->pauseBarPos.x - screenInfo->size.x + 106, y, screenInfo->size.x, 13, 0x000000, 0xFF, INK_NONE, true);
}

void PauseMenu::DrawSpikes()
{
    for (int32 i = 0; i < 8; i++) {
        this->animator.DrawSprite(&this->drawPos, true);
        this->drawPos.y += TO_FIXED(32);
    }
}

void PauseMenu::PauseSound()
{
    for (int32 i = 0; i < CHANNEL_COUNT; ++i) {
        if (channels[i].IsActive()) {
            channels[i].Pause();
            modSVars->activeChannels[i] = true;
        }
    }
}

void PauseMenu::ResumeSound()
{
    for (int32 i = 0; i < CHANNEL_COUNT; ++i) {
        if (modSVars->activeChannels[i]) {
            channels[i].Resume();
            modSVars->activeChannels[i] = false;
        }
    }
}

void PauseMenu::StopSound()
{
    for (int32 i = 0; i < CHANNEL_COUNT; ++i) {
        if (modSVars->activeChannels[i]) {
            channels[i].Stop();
            modSVars->activeChannels[i] = false;
        }
    }
}

void PauseMenu::Action_Accept()
{
    modSVars->sfxAccept.Play();

    this->state.Set(&PauseMenu::State_Confirmed);
    this->stateDraw.Set(&PauseMenu::Draw_Confirmed);

    this->alpha = 0xF8;
    this->timer = 0;
}

void PauseMenu::Action_TouchButton(int32 buttonIndex, int32 y)
{
    if (!config.hasTouchControls)
        return;

    if (Touch::CheckRect(lineX, y, screenInfo->size.x, y + 32, nullptr, nullptr) > -1) {
        this->selectedIndex = buttonIndex;
        return;
    }

    if (CheckAnyTouch() < 0) {
        if (this->selectedIndex == buttonIndex)
            this->Action_Accept();
    }
    else if (this->selectedIndex == buttonIndex) {
        this->selectedIndex = Buttons::MenuUnselected;
    }
}

// Object States
void PauseMenu::State_StartPause()
{
    SET_CURRENT_STATE();

    auto player = GameObject::Get<Player>(SLOT_PLAYER1);

    this->PauseSound();
    Stage::SetEngineState(ENGINESTATE_FROZEN);
    modSVars->sfxWoosh.Play();

    this->position.x = screenInfo->size.x;
    this->lineX      = screenInfo->size.x + 6;
    this->timer      = 0;
    this->alpha      = 0;

    // TODO: Add language switch for this(?)
    this->timerThreshold = 12;

    // 2 = StageCategoryCompetition
    // 4 = StageCategoryBonus
    // 5 = StageCategorySpecial

    bool32 blockedCategories = sceneInfo->activeCategory == 2 || sceneInfo->activeCategory == 5 || sceneInfo->activeCategory == 4;
    if (player->lives <= 1 || blockedCategories)
        this->disableRestart = true;
    else
        this->disableRestart = false;

    if (config.hasTouchControls)
        this->selectedIndex = Buttons::MenuUnselected;

    this->state.Set(&PauseMenu::State_SlideIn);
    this->stateDraw.Set(&PauseMenu::Draw_Init);
}

void PauseMenu::State_SlideIn()
{
    SET_CURRENT_STATE();

    this->pauseBarPos.x = (this->timer * screenInfo->size.x) / 12;
    this->pauseBarPos.y = (this->timer * screenInfo->size.y) / 12;
    this->position.x    = screenInfo->size.x - (this->timer << 7) / 12;

    if (this->timer++ >= this->timerThreshold) {
        this->timer = 0;
        this->lineX = (this->position.x + 48);
        this->state.Set(&PauseMenu::State_SpritesFadeIn);
    }
}

void PauseMenu::State_SpritesFadeIn()
{
    SET_CURRENT_STATE();

    if (this->timer <= 0xFF) {
        this->timer += 16;
        this->alpha = (this->timer < 0xFF) ? this->timer : 0xFF;
    }
    else {
        this->timer = 0;
        this->alpha = 0xFF;
        this->state.Set(&PauseMenu::State_Controls);
        this->stateDraw.Set(&PauseMenu::Draw_Controls);
    }
}

void PauseMenu::State_Controls()
{
    SET_CURRENT_STATE();

    if (config.hasTouchControls && !this->physicalControls) {
        this->Action_TouchButton(Buttons::ButtonContinue, 32);

        if (!this->disableRestart)
            this->Action_TouchButton(Buttons::ButtonRestart, 80);

        this->Action_TouchButton(2, 128);
        this->Action_TouchButton(Buttons::ButtonExit, 176);

        if (this->up || this->down) {
            this->up ? this->selectedIndex = Buttons::ButtonExit : false;
            this->down ? this->selectedIndex = Buttons::ButtonContinue : false;

            this->physicalControls = true;
        }
    }
    else {
        if (this->up || this->down) {
            this->timer = 0;
            this->lineX = screenInfo->size.x;
            modSVars->sfxBleep.Play();
        }

        if (this->up) {
            --this->selectedIndex;
            if (this->disableRestart && this->selectedIndex == Buttons::ButtonRestart)
                this->selectedIndex--;
        }
        if (this->down) {
            ++this->selectedIndex;
            if (this->disableRestart && this->selectedIndex == Buttons::ButtonRestart)
                this->selectedIndex++;
        }

        this->selectedIndex &= 3;

        if (this->start)
            this->Action_Accept();

        if (config.hasTouchControls && CheckAnyTouch() > -1) {
            this->physicalControls = false;
            this->selectedIndex    = Buttons::MenuUnselected;
        }
    }
}

void PauseMenu::State_Confirmed()
{
    SET_CURRENT_STATE();

    this->lineX += 4;

    this->timer += 1;
    this->timer &= 3;

    (this->alpha > 0) ? this->alpha -= 12 : this->alpha = 0;

    if (!this->alpha) {
        // Check for Resume (and options for now)
        if (this->selectedIndex == Buttons::MenuUnselected || this->selectedIndex == Buttons::ButtonContinue || this->selectedIndex == 2) {
            this->lineX         = this->position.x + 48;
            this->pauseBarPos.y = screenInfo->size.y - 38;

            this->timer = 0;
            this->alpha = this->backgroundAlpha; // Used for the BG, return to the initial opacity and then fade out
            this->state.Set(&PauseMenu::State_ResumeGame);
            this->stateDraw.Set(&PauseMenu::Draw_ResumeGame);
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

            this->lineX = this->position.x + 48;
            this->state.Set(&PauseMenu::State_ExitLevel);
            this->stateDraw.Set(&PauseMenu::Draw_ExitLevel);
        }
    }
}

void PauseMenu::State_ResumeGame()
{
    SET_CURRENT_STATE();

    if (this->alpha > 0) {
        this->alpha -= 8;
        this->position.x += 16;
        this->lineX += 16;
        this->pauseBarPos.y += 16;
    }
    else {
        this->ResumeSound();
        this->Destroy();
    }
}

void PauseMenu::State_ExitLevel()
{
    SET_CURRENT_STATE();

    if (this->position.x > -64) {
        this->position.x -= 16;
        this->lineX += 16;
    }
    else {
        switch (this->selectedIndex) {
            // Continue - Do nothing
            case Buttons::ButtonContinue: break;
            case Buttons::ButtonRestart: Stage::LoadScene(); break;

            // Options
            case 2:
                // TimeAttack.Round = -1;
                // Stage::SetEngineState(ENGINESTATE_DEVMENU);
                break;

            // Exit
            case Buttons::ButtonExit:
                // 2 = StageCategoryCompetition
                if (sceneInfo->activeCategory == 2)
                    Stage::SetScene("Presentation & Menus", "Menu Comp");
                else
                    Stage::SetScene("Presentation & Menus", "Title Screen");

                Stage::LoadScene();
                break;

            default: break;
        }
    }
}

// Draw States
void PauseMenu::Draw_Init()
{
    SET_CURRENT_STATE();

    this->inkEffect = INK_NONE;

    if (this->pauseBarHeight<SCREEN_YSIZE &&this->pauseBarPos.y> this->pauseBarHeight) {
        this->pauseBarHeight = this->pauseBarPos.y;
    }

    this->Draw_Controls();
}

void PauseMenu::Draw_Controls()
{
    SET_CURRENT_STATE();

    this->inkEffect = INK_NONE;

    // Background fade
    Graphics::DrawRect(NULL, NULL, screenInfo->size.x, this->pauseBarHeight, 0x000000, this->backgroundAlpha, INK_ALPHA, true);

    // 'PAUSE' bar
    this->DrawPauseRect(screenInfo->size.y - 38);

    // Spikes
    this->animator.frameID = 3;
    this->drawPos.x        = TO_FIXED(this->position.x);
    this->drawPos.y        = 0;
    this->DrawSpikes();

    this->inkEffect = INK_ALPHA;
    if (this->lineX > this->position.x + 48) {
        this->lineX += (this->position.x + 48 - this->lineX) >> 3;
    }

    // Draw 'CONTINUE' button
    this->animator.frameID = 6;
    this->drawPos.x        = TO_FIXED(this->position.x + 48);
    this->drawPos.y        = TO_FIXED(48);
    this->animator.DrawSprite(&this->drawPos, true);

    if (this->selectedIndex == Buttons::ButtonContinue) {
        // Selection Line
        this->animator.frameID = 5;
        this->drawPos.x        = TO_FIXED(this->lineX);
        this->animator.DrawSprite(&this->drawPos, true);

        // Selection Player
        this->drawPos.x = TO_FIXED(this->position.x + 48);
        this->selectionAnimator.DrawSprite(&this->drawPos, true);
    }

    // Draw 'RESTART' button
    this->animator.frameID = 7;
    this->drawPos.x        = TO_FIXED(this->position.x + 48);
    this->drawPos.y += TO_FIXED(48);

    if (!this->disableRestart) {
        this->animator.DrawSprite(&this->drawPos, true);
    }
    else {
        this->alpha >>= 1;
        this->animator.DrawSprite(&this->drawPos, true);
        this->alpha <<= 1;
    }

    if (this->selectedIndex == Buttons::ButtonRestart) {
        // Selection Line
        this->animator.frameID = 5;
        this->drawPos.x        = TO_FIXED(this->lineX);
        this->animator.DrawSprite(&this->drawPos, true);

        // Selection Player
        this->drawPos.x = TO_FIXED(this->position.x + 48);
        this->selectionAnimator.DrawSprite(&this->drawPos, true);
    }

    // Draw 'OPTIONS' button
    this->animator.frameID = 8;
    this->drawPos.y += TO_FIXED(48);
    this->animator.DrawSprite(&this->drawPos, true);

    if (this->selectedIndex == 2) {
        // Selection Line
        this->animator.frameID = 5;
        this->drawPos.x        = TO_FIXED(this->lineX);
        this->animator.DrawSprite(&this->drawPos, true);

        // Selection Player
        this->drawPos.x = TO_FIXED(this->position.x + 48);
        this->selectionAnimator.DrawSprite(&this->drawPos, true);
    }

    // Draw 'EXIT' button
    this->animator.frameID = 9;
    this->drawPos.y += TO_FIXED(48);
    this->animator.DrawSprite(&this->drawPos, true);

    if (this->selectedIndex == Buttons::ButtonExit) {
        // Selection Line
        this->animator.frameID = 5;
        this->drawPos.x        = TO_FIXED(this->lineX);
        this->animator.DrawSprite(&this->drawPos, true);

        // Selection Player
        this->drawPos.x = TO_FIXED(this->position.x + 48);
        this->selectionAnimator.DrawSprite(&this->drawPos, true);
    }
}

void PauseMenu::Draw_Confirmed()
{
    SET_CURRENT_STATE();

    this->inkEffect = INK_NONE;

    // Background fade
    Graphics::DrawRect(NULL, NULL, screenInfo->size.x, this->pauseBarHeight, 0x000000, this->backgroundAlpha, INK_ALPHA, true);

    // 'PAUSE' bar
    this->DrawPauseRect(screenInfo->size.y - 38);

    this->animator.frameID = 3;
    this->drawPos.x        = TO_FIXED(this->position.x);
    this->drawPos.y        = 0;
    this->DrawSpikes();

    // Continue
    this->drawPos.y = TO_FIXED(48);
    if (this->selectedIndex != Buttons::ButtonContinue) {
        this->inkEffect        = INK_ALPHA;
        this->animator.frameID = 6;
        this->drawPos.x        = TO_FIXED(this->position.x + 48);
        this->animator.DrawSprite(&this->drawPos, true);
    }
    // Continue (Selected)
    else {
        // Continue flash
        if (this->timer < 2) {
            this->inkEffect        = INK_NONE;
            this->animator.frameID = 6;
            this->drawPos.x        = TO_FIXED(this->position.x + 48);
            this->animator.DrawSprite(&this->drawPos, true);
        }

        // Selection Line
        this->animator.frameID = 5;
        this->drawPos.x        = TO_FIXED(this->lineX);
        this->animator.DrawSprite(&this->drawPos, true);

        // Selection Player
        this->drawPos.x = TO_FIXED(this->position.x + 48);
        this->selectionAnimator.DrawSprite(&this->drawPos, true);
    }

    // Restart
    this->drawPos.y += TO_FIXED(48);
    if (this->selectedIndex != Buttons::ButtonRestart) {
        if (!this->disableRestart) {
            this->inkEffect        = INK_ALPHA;
            this->animator.frameID = 7;
            this->drawPos.x        = TO_FIXED(this->position.x + 48);
            this->animator.DrawSprite(&this->drawPos, true);
        }
        else {
            this->inkEffect = INK_ALPHA;
            this->drawPos.x = TO_FIXED(this->position.x + 48);

            this->alpha >>= 1;
            this->animator.frameID = 7;
            this->animator.DrawSprite(&this->drawPos, true);
            this->alpha <<= 1;
        }
    }
    // Restart (Selected)
    else {
        // Restart flash
        if (this->timer < 2) {
            this->inkEffect        = INK_NONE;
            this->drawPos.x        = TO_FIXED(this->position.x + 48);
            this->animator.frameID = 7;
            this->animator.DrawSprite(&this->drawPos, true);
        }

        // Selection Line
        this->inkEffect        = INK_NONE;
        this->drawPos.x        = TO_FIXED(this->lineX);
        this->animator.frameID = 5;
        this->animator.DrawSprite(&this->drawPos, true);

        // Selection Player
        this->drawPos.x = TO_FIXED(this->position.x + 48);
        this->selectionAnimator.DrawSprite(&this->drawPos, true);
    }

    // Options
    this->drawPos.y += TO_FIXED(48);
    if (this->selectedIndex != 2) {
        this->inkEffect        = INK_ALPHA;
        this->animator.frameID = 8;
        this->drawPos.x        = TO_FIXED(this->position.x + 48);
        this->animator.DrawSprite(&this->drawPos, true);
    }
    // Options (Selected)
    else {
        // Options flash
        if (this->timer < 2) {
            this->inkEffect        = INK_NONE;
            this->animator.frameID = 8;
            this->drawPos.x        = TO_FIXED(this->position.x + 48);
            this->animator.DrawSprite(&this->drawPos, true);
        }

        // Selection Line
        this->inkEffect        = INK_NONE;
        this->animator.frameID = 5;
        this->drawPos.x        = TO_FIXED(this->lineX);
        this->animator.DrawSprite(&this->drawPos, true);

        // Selection Player
        this->drawPos.x = TO_FIXED(this->position.x + 48);
        this->selectionAnimator.DrawSprite(&this->drawPos, true);
    }

    // Exit
    this->drawPos.y += TO_FIXED(48);
    if (this->selectedIndex != Buttons::ButtonExit) {
        this->inkEffect        = INK_ALPHA;
        this->animator.frameID = 9;
        this->drawPos.x        = TO_FIXED(this->position.x + 48);
        this->animator.DrawSprite(&this->drawPos, true);
    }
    // Exit (Selected)
    else {
        // Exit flash
        if (this->timer < 2) {
            this->inkEffect        = INK_NONE;
            this->animator.frameID = 9;
            this->drawPos.x        = TO_FIXED(this->position.x + 48);
            this->animator.DrawSprite(&this->drawPos, true);
        }

        // Selection Line
        this->inkEffect        = INK_NONE;
        this->animator.frameID = 5;
        this->drawPos.x        = TO_FIXED(this->lineX);
        this->animator.DrawSprite(&this->drawPos, true);

        // Selection Player
        this->drawPos.x = TO_FIXED(this->position.x + 48);
        this->selectionAnimator.DrawSprite(&this->drawPos, true);
    }
}

void PauseMenu::Draw_ResumeGame()
{
    SET_CURRENT_STATE();

    this->inkEffect = INK_NONE;

    // Background fade
    Graphics::DrawRect(NULL, NULL, screenInfo->size.x, this->pauseBarHeight, 0x000000, this->alpha, INK_ALPHA, true);

    // 'PAUSE' bar
    this->DrawPauseRect(this->pauseBarPos.y);

    this->animator.frameID = 3;
    this->drawPos.x        = TO_FIXED(this->position.x);
    this->drawPos.y        = 0;
    this->DrawSpikes();

    switch (selectedIndex) {
        case Buttons::ButtonContinue:
            this->animator.frameID = 6;
            this->drawPos.x        = TO_FIXED(this->lineX);
            this->drawPos.y        = TO_FIXED(48);
            this->animator.DrawSprite(&this->drawPos, true);

            this->drawPos.x = TO_FIXED(this->position.x + 48);
            this->selectionAnimator.DrawSprite(&this->drawPos, true);
            break;
        case Buttons::ButtonRestart:
            this->animator.frameID = 7;
            this->drawPos.x        = TO_FIXED(this->lineX);
            this->drawPos.y        = TO_FIXED(96);
            this->animator.DrawSprite(&this->drawPos, true);

            this->drawPos.x = TO_FIXED(this->position.x + 48);
            this->selectionAnimator.DrawSprite(&this->drawPos, true);
            break;
        case 2: // Options
            this->animator.frameID = 8;
            this->drawPos.x        = TO_FIXED(lineX);
            this->drawPos.y        = TO_FIXED(144);
            animator.DrawSprite(&this->drawPos, true);

            this->drawPos.x = TO_FIXED(this->position.x + 48);
            this->selectionAnimator.DrawSprite(&this->drawPos, true);
            break;
        case Buttons::ButtonExit:
            this->animator.frameID = 9;
            this->drawPos.x        = TO_FIXED(this->lineX);
            this->drawPos.y        = TO_FIXED(192);
            this->animator.DrawSprite(&this->drawPos, true);

            this->drawPos.x = TO_FIXED(this->position.x + 48);
            this->selectionAnimator.DrawSprite(&this->drawPos, true);
            break;
    }
}

void PauseMenu::Draw_ExitLevel()
{
    SET_CURRENT_STATE();

    this->inkEffect = INK_NONE;

    // Background fade
    Graphics::DrawRect(NULL, NULL, screenInfo->size.x, this->pauseBarHeight, 0x000000, this->backgroundAlpha, INK_ALPHA, true);

    // 'PAUSE' bar
    this->DrawPauseRect(screenInfo->size.y - 38);

    this->animator.frameID = 3;
    this->drawPos.x        = TO_FIXED(this->position.x);
    this->drawPos.y        = 0;
    this->DrawSpikes();

    // The rectangle that consumes all life
    Graphics::DrawRect(this->position.x + 128, 0, screenInfo->size.x * 47, screenInfo->size.y, 0x000000, 0xFF, INK_NONE, true);

    this->drawPos.x = TO_FIXED(this->lineX);
    switch (selectedIndex) {
        case Buttons::ButtonContinue:
            this->animator.frameID = 6;
            this->drawPos.y        = TO_FIXED(48);
            this->animator.DrawSprite(&this->drawPos, true);
            this->selectionAnimator.DrawSprite(&this->drawPos, true);
            break;
        case Buttons::ButtonRestart:
            this->animator.frameID = 7;
            this->drawPos.y  = TO_FIXED(96);
            this->animator.DrawSprite(&this->drawPos, true);
            this->selectionAnimator.DrawSprite(&this->drawPos, true);
            break;
        case 2: // Options
            this->animator.frameID = 8;
            this->drawPos.y  = TO_FIXED(144);
            this->animator.DrawSprite(&this->drawPos, true);
            this->selectionAnimator.DrawSprite(&this->drawPos, true);
            break;
        case Buttons::ButtonExit:
            this->animator.frameID = 9;
            this->drawPos.y  = TO_FIXED(192);
            this->animator.DrawSprite(&this->drawPos, true);
            this->selectionAnimator.DrawSprite(&this->drawPos, true);
            break;
    }
}

void PauseMenu::StaticLoad(Static *sVars) { RSDK_INIT_STATIC_VARS(PauseMenu); }

void PauseMenu::Serialize() {}

} // namespace GameLogic