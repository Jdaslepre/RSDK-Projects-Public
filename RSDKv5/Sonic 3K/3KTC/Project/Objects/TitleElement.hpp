#pragma once
#include "GameAPI/Game.hpp"

using namespace RSDK;

namespace GameLogic {

struct TitleElement : GameObject::Entity {

    // ---------------
    // Enums & Structs
    // ---------------

    enum Types {
        TypeEmblem,
        TypeBanner,
        TypeTornado,
        TypeCopyright,
        TypeStart,
        TypeOption,
        TypeCount,
    };

    // ----------------
    // Static Variables
    // ----------------

    struct Static : GameObject::Static {
        SpriteAnimation aniFrames;
    };

    struct ModStatic : GameObject::Static {};

    // ----------------
    // Entity Variables
    // ----------------

    uint16 timer;
    StateMachine<TitleElement> state;
    Animator animator;
    Animator sonicWinkAnimator;
    Animator sonicWagAnimator;
    uint8 type;
    Vector2 originPos;
    int32 osc;
    uint8 sub;

    // ----------------------
    // Standard Entity Events
    // ----------------------

    void Create(void *data);

    // -------------------
    // Static Declarations
    // -------------------

    MOD_DECLARE(TitleElement)
};
} // namespace GameLogic