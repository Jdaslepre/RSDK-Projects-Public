#include "../3KTC.hpp"

using namespace RSDK;

namespace GameLogic
{

// -------------------
// Object Registration
// -------------------

MOD_REGISTER_OBJECT(S3K_SaveMenu);

// -------------
// Object States
// -------------

Action<void> S3K_SaveMenu::State_Navigate;
Action<void> S3K_SaveMenu::State_CursorMove;

// ----------------------
// Standard Entity Events
// ----------------------

void S3K_SaveMenu::Update()
{
    this->Action_Back();
    sVars->Super(SUPER_UPDATE);
    this->Action_DragScreen();
}

void S3K_SaveMenu::Draw()
{
    this->Draw_Back();
    sVars->Super(SUPER_DRAW);
}

void S3K_SaveMenu::StageLoad()
{
    sVars->Super(SUPER_STAGELOAD);

    modSVars->aniFrames.Load("3K_Menu/Menu_TouchEx.bin", SCOPE_STAGE);
    modSVars->animator.SetAnimation(modSVars->aniFrames, 0, true, 0);

    modSVars->touchDown         = false;
    modSVars->backActionPending = false;
}

void S3K_SaveMenu::StaticLoad(Static *sVars)
{
    RSDK_INIT_STATIC_VARS(S3K_SaveMenu);

    sVars->sfxButton.Init();
}

// ----------------------
// Extra Entity Functions
// ----------------------

void S3K_SaveMenu::Action_Back()
{
    SpriteFrame *backFrame = modSVars->aniFrames.GetFrame(0, 0);

    int32 touchX = (screenInfo->size.x - backFrame->width - 6);
    int32 touchY = (screenInfo->size.y - backFrame->height - 6);

    if (Touch::CheckRect(touchX, touchY, screenInfo->size.x, screenInfo->size.y, nullptr, nullptr) >= 0) {
        // check if we're touching the back button
        modSVars->backActionPending = true;
        modSVars->touchDown         = true;
    }
    else if (modSVars->touchDown && CheckAnyTouch()) {
        // check if we slid off the button, so cancel the scene transition
        modSVars->backActionPending = false;
        modSVars->touchDown         = false;
    }
    else if (modSVars->backActionPending) {
        // if we really mean to go back, just go back
        modSVars->backActionPending = false;
        modSVars->touchDown         = false;
        controllerInfo->keyB.press  = true;
    }
}

void S3K_SaveMenu::Draw_Back()
{
    SpriteFrame *backFrame = modSVars->aniFrames.GetFrame(0, 0);

    uint8 prevInk   = this->inkEffect;
    int32 prevAlpha = this->alpha;

    this->inkEffect = INK_ALPHA;
    this->alpha     = modSVars->touchDown ? 224 : 255;

    Vector2 drawPos;
    drawPos.x                  = TO_FIXED(screenInfo->size.x - backFrame->width);
    drawPos.y                  = TO_FIXED(screenInfo->size.y - backFrame->height);
    modSVars->animator.frameID = 0;
    modSVars->animator.DrawSprite(&drawPos, true);

    // Screen Rectangle:
    // drawPos.x = (screenInfo->size.x - backFrame->width - 6);
    // drawPos.y = (screenInfo->size.y - backFrame->height - 6);
    // Graphics::DrawRect(drawPos.x, drawPos.y, backFrame->width + 6, backFrame->height + 6, 0, 60, INK_ALPHA, true);

    this->inkEffect = prevInk;
    this->alpha     = prevAlpha;
}

void S3K_SaveMenu::Action_DragScreen()
{
    int32 touches = Touch::CheckRect(0, 0, screenInfo->size.x, screenInfo->size.y, 0, 0);
    int32 touchX  = (int32)(touchInfo->x[touches] * screenInfo->size.x);

    switch (modSVars->touchState) {
        case 0: { // MENUCONTROL_STATEINPUT_CHECKTOUCH
            if (touches >= 0) {
                modSVars->touchState            = 1;
                modSVars->lastDragTouchDistance = 0.0;
                modSVars->dragTouchX            = touchX;
                modSVars->lastButtonMovePos     = modSVars->buttonMovePos;
            }
            break;
        }

        case 1: { // MENUCONTROL_STATEINPUT_HANDLEDRAG

            if (touches <= -1) {
                modSVars->touchState = 2; // MENUCONTROL_STATEINPUT_HANDLEMOVEMENT
            }
            else {
                modSVars->autoButtonMoveVelocity = 0;
                modSVars->dragTouchDistance      = (modSVars->dragTouchX - touchX);

                if (abs(modSVars->lastDragTouchDistance) > 0) {
                    modSVars->autoButtonMoveVelocity = modSVars->dragTouchDistance - modSVars->lastDragTouchDistance;
                    modSVars->buttonMovePos += (modSVars->autoButtonMoveVelocity - modSVars->buttonMovePos);
                }
                modSVars->lastDragTouchDistance = modSVars->dragTouchDistance;
            }
            break;
        }

        case 2: { // MENUCONTROL_STATEINPUT_HANDLEMOVEMENT
            modSVars->buttonMovePos /= 1.125;

            if (!abs(modSVars->buttonMovePos))
                modSVars->touchState = 3;

            int32 nextStartX         = 0;
            int32 nearestStartX = 0;
            int32 moveVel            = 0;

            bool32 selectionChanged = false;
            if (!abs(modSVars->buttonMovePos)) {
                S3K_SaveSlot *activeSlot  = GameObject::Get<S3K_SaveSlot>(this->activeSaveSlot);
                S3K_SaveSlot *nearestSlot = nullptr;

                for (auto slot : GameObject::GetEntities<S3K_SaveSlot>(FOR_ALL_ENTITIES)) {
                    // Prevent the player from selecting a no-save slot when deleting
                    bool32 invalid = (sVars->deletingSave && slot->type == S3K_SaveSlot::TypeNoSave);

                    if (slot && !invalid && (!nearestSlot || abs(slot->startPos.x - this->cursorPos) < abs(nearestStartX - this->cursorPos))) {
                        nearestSlot   = slot;
                        nearestStartX = slot->startPos.x;
                    }
                }

                if (nearestSlot && (nearestSlot != activeSlot || nearestStartX != this->cursorPos)) {
                    this->activeSaveSlot   = nearestSlot->Slot();
                    this->velocity.x = (nearestStartX > this->cursorPos) ? TO_FIXED(7) : -TO_FIXED(7);

                    activeSlot->saveActive = false;
                    selectionChanged       = true;
                }
            }

            if (selectionChanged) {
                this->state.Set(S3K_SaveMenu::State_CursorMove.action);

                SoundFX sfx = sVars->deletingSave ? sVars->sfxBumper : sVars->sfxSlot;
                sfx.Play(false, 255);
            }
            break;
        }

        case 3: { // MENUCONTROL_STATEINPUT_MOVE
            if (touches > 0) {
                modSVars->touchState            = 1; // MENUCONTROL_STATEINPUT_HANDLEDRAG;
                modSVars->lastDragTouchDistance = 0.0;
                modSVars->dragTouchX            = touchX;
            }
            else {
                modSVars->buttonMovePos += (modSVars->targetButtonMovePos - modSVars->buttonMovePos);
                if (abs(modSVars->targetButtonMovePos - modSVars->buttonMovePos) < 0.00025) {
                    modSVars->buttonMovePos = modSVars->targetButtonMovePos;
                    modSVars->touchState    = 0;
                }
            }
            break;
        }
    }

    this->cursorPos += TO_FIXED(modSVars->buttonMovePos);
}

} // namespace GameLogic