#include "RSDK-Online.hpp"

using namespace RSDK;

namespace GameLogic {

// -------------------
// Object Registration
// -------------------

MOD_REGISTER_OBJECT(MenuParam);

// ----------------
// Public Functions
// ----------------

MenuParam *(*MenuParam_GetParam)(void);

} // namespace GameLogic