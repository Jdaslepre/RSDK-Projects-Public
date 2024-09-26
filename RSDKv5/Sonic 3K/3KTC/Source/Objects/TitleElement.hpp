#pragma once
#include "GameAPI/Game.hpp"

namespace GameLogic {

struct TitleElement : RSDK::GameObject::Entity {

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

    struct Static : RSDK::GameObject::Static {
        RSDK::SpriteAnimation aniFrames;
    };

    struct ModStatic : RSDK::GameObject::Static {
    };

    // ----------------
    // Entity Variables
    // ----------------

    uint16 timer;
    RSDK::StateMachine<TitleElement> state;
    RSDK::Animator animator;
    RSDK::Animator sonicWinkAnimator;
    RSDK::Animator sonicWagAnimator;
    uint8 type;
    RSDK::Vector2 originPos;
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